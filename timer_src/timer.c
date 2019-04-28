#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "timer.h"

int main(int argc, char **argv)
{
    setup_term();
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        fprintf(stderr, "Failed to catch signal.\n");

    /* parse arguments and print them out */
    consume_args(argc, argv);
    print_info();

    /* loop infinitely, changing state from work to break to work */
    while (1) {
        if (is_work(&timer)) {
            print_and_sleep(&timer, 1, "Time to Work ");
            inc(&timer);
        }
        else {
            take_break(&timer);
        }
    }

    return 0;
}

void print_and_sleep(ptimer *t, int s, const char *msg)
{
    fprintf(stderr, "%s[%2dm:%2ds, done %d time%s]\r",
            msg, t->mins, t->secs, t->iter, t->iter==1 ? "" : "s");
    sleep(s);
}

void inc(ptimer *t)
{
    if (t->secs == 59) {
        t->mins++;
        t->secs = 0;
    } else {
        t->secs++;
    }
}

void take_break(ptimer *t)
{
    /* reset timer and terminal for break */
    t->secs = 0;
    t->mins = 0;
    clear_line();

    while (is_break(t)) {
        fprintf(stderr, "Take a break [%2dm:%2ds]\r", t->mins, t->secs);
        sleep(1);
        inc(t);
    }

    /* reset timer and terminal for main loop use */
    t->secs = 0;
    t->mins = 0;
    t->iter++;
    clear_line();
}

int is_work(ptimer *t)
{
    if (t->mins == config.work_time)
        return 0;
    return 1;
}

int is_break(ptimer *t)
{
    if (t->mins == config.break_time)
        return 0;
    return 1;
}

void clear_line(void)
{
    char *empty;
    int spaces = 80; /* better use terminal width here */

    empty = (char *)malloc(spaces * sizeof(char));
    for (int i=0; i<spaces; empty[i++] = ' ')
        ;
    fprintf(stderr, "%s\r", empty);
    free(empty);
}

void consume_args(int argc, char **argv)
{
    while (--argc > 0 && ++argv) {
        /* interpret flags */
        if (!strcmp(*argv, "--help") || !strcmp(*argv, "-h")) {
            fprintf(stderr, "%s", help_msg);
            exit(0);
        }

        /* interpret options & their arguments */
        if (!strcmp(*argv, "--work") || !strcmp(*argv, "-w")) {
            get_option(&argc, &argv, "--work", 0);
            continue;
        }
        if (!strcmp(*argv, "--break") || !strcmp(*argv, "-b")) {
            get_option(&argc, &argv, "--break", 1);
            continue;
        }
        if (!strcmp(*argv, "--log-file") || !strcmp(*argv, "-f")) {
            get_option(&argc, &argv, "--log-file", 2);
            continue;
        }
        bad_option(0, *argv, MODE_CONTINUE);
    }
}

void get_option(int *argc, char ***argv, const char *opt_name, int mode)
{
    int ntime;

    if (*argc > 1) { /* check if there are still values */
        /* modify argc & argv and parse the parameter */
        (*argv)++;
        (*argc)--;

        if (mode == 0 || mode == 1) {
            ntime = atoi(**argv);
            if (ntime < 1)
                bad_option(ntime, opt_name, MODE_FAIL);
        }
        if (mode == 2) {
            config.save_path = (char *)malloc(BUFSIZ*sizeof(char));
            strncpy(config.save_path, **argv, BUFSIZ);
        }

        /* conditionally add parsed parameter to configs */
        if (mode == 0)
            config.work_time = ntime;
        if (mode == 1)
            config.break_time = ntime;
    } else {
        fprintf(stderr, "Warning: Need value after %s.\n", opt_name);
    }
}

void bad_option(int val, const char *option, int mode)
{
    if (mode == MODE_FAIL) {
        fprintf(stderr, "Error: Provided bad value %d to %s (must be int>0).\n",
                val, option);
        exit(1);
    } else if (mode == MODE_CONTINUE) {
        fprintf(stderr, "Warning: Provided bad option %s.\n", option);
    }
}

void sigint_handler(int signum)
{
    if (config.save_path)
        save_stats(config.save_path);
    fprintf(stderr, "\n\nDone.\n");

    /* free resources and go */
    free(config.save_path);
    exit(0);
}

void save_stats(const char *path)
{
    FILE *file;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int elapsed;

    /* open the log file, calculate the time and save it */
    file = fopen(path, "a");
    elapsed = (timer.iter*(config.work_time*60+config.break_time*60)+
               (timer.mins*60+timer.secs)); /* in secs */
    fprintf(file, "[%2d/%02d/%d %2dh:%2dm]\t%dmins (%dsecs)\n",
            tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, elapsed/60, elapsed);
    fclose(file);
}

void setup_term(void)
{
    struct termios t;

    /* disable ECHOCTL, not POSIX though so compile conditionally */
    tcgetattr(0, &t);
#ifdef ECHOCTL
    t.c_lflag &= ~ECHOCTL;
#endif
    tcsetattr(0, TCSANOW, &t);
}

void print_info(void)
{
    fprintf(stderr, "Length of work time: %d, length of break time: %d.\n",
            config.work_time, config.break_time);
    if (config.save_path)
        fprintf(stderr, "Saving logs to `%s'.\n", config.save_path);
    fprintf(stderr, "Exit with ctrl+c.\n\n");
}
