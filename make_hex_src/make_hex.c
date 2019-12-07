/* make_hex.c: print binary, hex, and octal representations of a number. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const static char *help_msg =
"Print a decimal number in binary, hexadecimal, and octal formats.\n"
"\n"
"Author: Daniel Schuette <d.schuette@online.de>\n"
"Date: 2019/12/07\n"
"Sources: https://github.com/DanielSchuette/bin/tree/master/make_hex_src\n"
"License: GPLv3 (https://www.gnu.org/licenses/gpl-3.0.en.html)\n"
"\n"
"USAGE:\n"
"\tmake_hex [FLAGS] [OPTIONS]\n"
"\n"
"FLAGS:\n"
"\t-h, --help\t\tDisplay this help message\n"
"\n"
"OPTIONS:\n"
"\t-n, --number <NUMBER>\tNumber of which to show different representations";

static char *progname;

static void usage(void);

int main(int argc, char **argv)
{
    uint64_t to_convert;
    progname = *argv;

    if (argc == 2 && (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))) {
        usage();
        exit(0);
    } else if (argc == 3 && (!strcmp(argv[1], "--number") ||
                             !strcmp(argv[1], "-n"))) {
        to_convert = atoi(argv[2]);
    } else {
        fprintf(stderr, "%s: wrong number of arguments "
                "(--help for more information)\n", progname);
        exit(1);
    }

    printf("%ld => 0x%lx O%lo\n", to_convert, to_convert, to_convert);

    return 0;
}

static void usage(void)
{
    fprintf(stderr, "%s\n", help_msg);
}
