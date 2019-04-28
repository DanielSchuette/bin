#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#define SPRITE_LEN 32
#define FRAME_RATE 1000000000

static const char *mario =
"                      #####     "
"      ######         #'''''###  "
"     #''''''##      #'''''''''# "
"    #'''''''''#     ###'.#.###  "
"    ###..#.###     #..##.#....# "
"   #..##.#....#    #..##..#...# "
"   #..##..#...#     ##...#####  "
"    ##...#####      ###.....#   "
"     ##.....#     ##'''##''###  "
"    #''##''#     #..''''##''#'# "
"   #''''##''#    #..'''######'.#"
"   #''''#####     #..####.##.#.#"
"    #...##.##     .#########''# "
"    #..'''###     #''######'''# "
"     #'''''#      #'''#  #'''#  "
"      #####        ###    ###   ";

/* additional Marios: */
/*
"      #####                           #####     "
"     #########         #####         #########  "
"     %%%''%'          #########      %%%''%'    "
"    %'%'''%'''        %%%''%'       %'%'''%'''  "
"    %'%%'''%'''      %'%'''%'''     %'%%'''%''' "
"    %%''''%%%%       %'%%'''%''     %%''''%%%%  "
"      '''''''        %%''''%%%%       '''''''   "
"     %%#%%%            '''''''     %%%%##%%     "
"    %%%%##%%          %%%%#% '   ''%%%%###%%%'''"
"    %%%##'##'        '%%%%%%'''  ''' %%#'###%%''"
"    %%%%#####       ''#%%%%%''   ''  #######  % "
"    #%%'''###       %%#######       #########%% "
"     #%''###        %########      ##########%% "
"      ###%%%       %%### ###      %%###   ###%% "
"      %%%%%%%      %    %%%       %%%           "
"      %%%%              %%%%       %%%          "

"           ##   ##                           ##   ##                           ##   ##                "
"           #.######                          #.######                          #.######               "
"           #..#,,,,#                         #..#,,,,#                         #..#,,,,#              "
"          #,..,,,,,#                        #,..,,,,,#                        #,..,,,,,#              "
"         #,,.,,,,,,,#                      #,,.,,,,,,,#                      #,,.,,,,,,,#             "
"         #,,,,,,,,,,#                      #,,,,,,,,,,#                      #,,,,,,,,,,#             "
"        #,,,,,,,,,,,#                     #,,,,,,,,,,,#                     #,,,,,,,,,,,#             "
"        #,,,,,,####,#                     #,,,,,,####,#                     #,,,,,,####,#             "
"        #,,,,,#..#.#                      #,,,,,#..#.#                      #,,,,,#..#.#              "
"        #,,,,,...#.###                    #,,,,,...#.###                    #,,,,,...#.###            "
"        #,,,,,........#######             #,,,,,........#######             #,,,,,........#######     "
"         #,,,,..#.....##....##             #,,,,..#.....##....##             #,,,,..#.....##....##    "
"         #,,,,.###...##.......#            #,,,,.###...##.......#            #,,,,.###...##.......#   "
"          ##,,...#####.######..##           ##,,...#####.######..##           ##,,...#####.######..## "
"           ####....#..#,,,,,,#...#           ####....#..#,,,,,,#...#           ####....#..#,,,,,,#...#"
"          #,#,,####.###,,,,,,###..          #,#,,####.###,,,,,,###..          #,#,,####.###,,,,,,###.."
"          ##,,,,,####,,#,,,,#,,###          ##,,,,,####,,#,,,,#,,###          ##,,,,,####,,#,,,,#,,###"
"         #,#,,,,,,,##,,,####,,,,,#         #,#,,,,,,,##,,,####,,,,,#         #,#,,,,,,,##,,,####,,,,,#"
"         #,,#,,,,,#..#,#,,,,#,,,##         #,,#,,,,,#..#,#,,,,#,,,##         #,,#,,,,,#..#,#,,,,#,,,##"
"       ###,,,##,,#....#,,,,,,#,##     ######,,,##,,#....#,,,,,,#,##  #########,,,##,,#....#,,,,,,#,## "
"     ##..#,,,,,###....#,,,,,,,#,#   ###,,..#,,,,,###....#,,,,,,,#,# ##,..,,...#,,,,###....#,,,,,,,#,# "
"    #.,..#,,,,,,,##..##,,,,,,#,#   ##..,,..#,,,,,,,##..##,,,,,,#,#  #,,..,,...#,,,,,,##..##,,,,,,#,#  "
"   #...,.#,,,,,,,..##,,#,,,,#,,#   #,,..,,#,,,,,,,,..##,,#,,,,#,,#  #,,..,,..#,,,,,,,,.##.##,,,,#,,#  "
"  #,,..,# #,,,,,,,..##,,####,,#    #,,..,,#,,,,,,,,,..,#,,####,,#   ##,..,,##..,,,,,,,,...#,####,,#   "
"  #,,..#  #,,,,,,,,,# ##,,,,##     ##,,###,,,,,,,#,,,,,.##,,,,##     #######..,,,,,###,...##,,,,##    "
"  #,,,#    #,,,,,,##   ######       ###   #.,,,,# #,,,..#######            #..,,###   #..########     "
"  ##,,#    #,,,,,#                        #..,,#   #,..#                   #..##       ###            "
"   ###     #......#                        #....#  #..#                     ##                        "
"           ########                         ####    ##                                                "
*/

/* dims in format x_start, x_size, y_start, y1_size */
static const int mario_stand_dims[] = {0, 16, 0, 16};
static const int mario_run_dims[] = {16, 16, 0, 16};

static void print_sprite(const char *, const int[2], int, int);
static void counter(int, int, int);
static void sleep_and_clear_screen(long);

int main(int argc, char **argv)
{
    int frame_rate;
    struct winsize w;

    if (argc > 2 && strcmp(argv[1], "-f") == 0)
        frame_rate = FRAME_RATE/atoi(argv[2]);
    else
        frame_rate = FRAME_RATE/10; /* 10 FPS */


    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    for (int i = 0; i < (w.ws_col-(SPRITE_LEN/2)); i++) {
        sleep_and_clear_screen(frame_rate);
        print_sprite(mario, mario_stand_dims, SPRITE_LEN, i);

        sleep_and_clear_screen(frame_rate);
        print_sprite(mario, mario_run_dims, SPRITE_LEN, i);
    }

    return 0;
}

/* indexing into `dims' is not save at all */
static void print_sprite(const char *sprite, const int *dims,
                         int total_sprite_len, int padding)
{
    int x_lim = dims[0] + dims[1];
    int y_lim = dims[2] + dims[3];

    for (int row = dims[2]; row < y_lim; row++) { /* y, rows */
        fprintf(stderr, "\n");
        for (int i = 0; i < padding; i++) fprintf(stderr, " ");
        for (int col = dims[0]; col < x_lim; col++) /* x, columns */
            fprintf(stderr, "%c", sprite[col+(row*total_sprite_len)]);
    }
    fprintf(stderr, "\n");
}

/* debugging only */
static void counter(int start, int end, int delay)
{
    for (int i = start; i < end; i++) {
        fprintf(stderr, "progress: %d\r", i);
        sleep(delay);
    }
    fprintf(stderr, "\n");
}

static void sleep_and_clear_screen(long delay)
{
    int nanosec = 1000000000;
    struct timespec time;

    if (delay >= nanosec) {
        time.tv_sec = delay/nanosec;
        delay -= time.tv_sec * nanosec;
    } else {
        time.tv_sec = 0;
    }
    time.tv_nsec = delay;
    nanosleep(&time, NULL);

    /* determine current terminal height */
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    /* clear screen */
    for (int i = 0; i < w.ws_row; i++)
        fprintf(stderr, "\n");
}
