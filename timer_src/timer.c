#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "timer.h"

int main(int argc, char **argv)
{
    ptimer timer = { 0, 0, 0 };

    consume_args(argc, argv);
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
}

void consume_args(int argc, char **argv)
{
    int ntime;

    while (--argc > 0 && ++argv) {
        /* interpret flags */
        if (!strcmp(*argv, "--help") || !strcmp(*argv, "-h")) {
            fprintf(stderr, "%s", help_msg);
            exit(0);
            continue;
        }
        /* interpret options */
        if (!strcmp(*argv, "--work") || !strcmp(*argv, "-w")) {
            if (argc > 1) { /* check if there are still values */
                argv++;
                argc--;
                ntime = atoi(*argv);
                if (ntime < 1)
                    bad_option(ntime, "--work", MODE_FAIL);
                config.work_time = ntime;
            } else {
                fprintf(stderr, "Warning: Need value after %s.\n",
                        "--work");
            }
            continue;
        }
        /* TODO: could reduce some redundancy here */
        if (!strcmp(*argv, "--break") || !strcmp(*argv, "-b")) {
            if (argc > 1) {
                argv++;
                argc--;
                ntime = atoi(*argv);
                if (ntime < 1)
                    bad_option(ntime, "--break", MODE_FAIL);
                config.break_time = ntime;
            } else {
                fprintf(stderr, "Warning: Need value after %s.\n",
                        "--break");
            }
            continue;
        }
        bad_option(0, *argv, MODE_CONTINUE);
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
