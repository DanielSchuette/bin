#ifndef __TIMER_H__

#include <stdlib.h>

#define WORK_TIME_DEFAULT   25
#define BREAK_TIME_DEFAULT  5
#define MODE_FAIL           0
#define MODE_CONTINUE       1

/* ANSI escape codes for terminal colors */
#define ANSI_RESET   "\x1b[0m"
#define ANSI_BLACK   "\x1b[30m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_WHITE   "\x1b[37m"

const static char* help_msg =
"Counts to 25 minutes in 1 second intervals, asking you to do work. Then,\n"
"a break of 5 minutes is recommended. These intervals might be changed.\n"
"Author: Daniel Schuette <d.schuette@online.de>\n"
"Date: 2019/04/28\n"
"Sources: https://github.com/DanielSchuette/bin/tree/master/timer_src\n"
"License: GPLv3 (https://www.gnu.org/licenses/gpl-3.0.en.html)\n"
"\n"
"USAGE:\n"
"\ttimer [FLAGS] [OPTIONS]\n"
"\n"
"FLAGS:\n"
"\t-h, --help\t\tDisplay this help message\n"
"\n"
"OPTIONS:\n"
"\t-w, --work <TIME>\tChange the default work time to TIME\n"
"\t-b, --break <TIME>\tChange the default break time to TIME\n"
"\t-f, --log-file <FILE>\tPath to a log file (without, no logs are saved)\n";

typedef struct ptimer {
    int secs;
    int mins;
    int num_work;  /* number of work cycles */
    int num_break; /* number of break cycles */
} ptimer;

typedef struct configs {
    int work_time;
    int break_time;
    char *save_path;
} configs;

/* global because it's tedious to pass these around (and signals need them) */
configs config = { WORK_TIME_DEFAULT, BREAK_TIME_DEFAULT, NULL };
ptimer timer = { 0, 0, 0, 0 };

/* print_and_sleep: print `msg' and timer information, then sleep `s' secs. */
void print_and_sleep(ptimer *, int, const char *);

/* inc: increment fields of a timer. */
void inc(ptimer *);

/* take_break: display break message and timer for `config.break_time' secs. */
void take_break(ptimer *);

/* is_work, is_break: determine if it's appropriate to work/take break. */
int is_work(ptimer *);
int is_break(ptimer *);

/* clear_line: a dirty hack to clear a terminal line. */
void clear_line(void);

/* consume_args: adds parsed options to global `config' struct. */
void consume_args(int, char **);

/* get_option: add an option to `config' and modify argc & argv. */
void get_option(int *, char ***, const char *);

/* bad_option: used by `consume_args'; make sure to provide a valid mode. */
void bad_option(int, const char *, int);

/* sigint_handler: catch signals to be able to save stats before exiting. */
void sigint_handler(int);

/* save_stats: save some stats to a log file. */
void save_stats(const char *);

/* setup_term: disable ECHOCTL, i.e. don't print ^C on sigint. */
void setup_term(void);

/* print_info: print info about initial setup to terminal. */
void print_info(void);

#endif /* __TIMER_H__ */
