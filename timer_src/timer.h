#ifndef __TIMER_H__

#define WORK_TIME_DEFAULT   25
#define BREAK_TIME_DEFAULT  5
#define MODE_FAIL           0
#define MODE_CONTINUE       1

const static char* help_msg =
"Counts to 25 minutes in 1 second intervals, asking you to do work. Then,\n"
"a break of 5 minutes is recommended. These intervals might be changed.\n"
"Author: Daniel Schuette <d.schuette@online.de>\n"
"\n"
"USAGE:\n"
"\ttimer [FLAGS] [OPTIONS]\n"
"\n"
"FLAGS:\n"
"\t-h, --help\t\tDisplay this help message\n"
"\n"
"OPTIONS:\n"
"\t-w, --work <TIME>\tChange the default work time to TIME\n"
"\t-b, --break <TIME>\tChange the default break time to TIME\n";

typedef struct ptimer {
    int secs;
    int mins;
    int iter; /* iterations of the timer */
} ptimer;

typedef struct configs {
    int work_time;
    int break_time;
} configs;

/* global because it's tedious to pass it around */
configs config = { WORK_TIME_DEFAULT, BREAK_TIME_DEFAULT };

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
void get_option(int *, char ***, const char *, int);

/* bad_option: used by `consume_args'; make sure to provide a valid mode. */
void bad_option(int, const char *, int);

#endif /* __TIMER_H__ */
