#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define XLEN 34
#define YLEN 16

const char *peach =
"               #####       ## ### "
"              #######     # +#++##"
"             ###+####     # ++++##"
"             #+++++###    #+++++##"
"   ###       #+#+#+###     #+++## "
"  #######    #+++++####     #+##  "
" ###++#+      ++#++####      ##   "
"##+##++++      #+######           "
"##++++##+     O+++O####           "
"  ++++++     OOOOOOO###           "
" ##O##O      ++OOO++##            "
"###O##O##     ++O++O              "
"++# OO ##+    O+++OOO             "
"++OOOOOO++   OOOOOOOOO            "
"  ##  ##     OOOOOOOOOO           "
" #### ###    OOOOOOOOOOO          ";

int main(void)
{
    for (int y = 0; y < YLEN; y++) {
        for (int x = 0; x < XLEN; x++) {
            int idx = x+y*XLEN;
            fprintf(stderr, "%c", peach[idx]);
        }
        fputc('\n', stderr);
    }
    sleep(1);

    for (int i = 0; i < 140; i++)
        fprintf(stderr, "\n");

    fprintf(stderr, "Your Princess is in Another Castle.\n");

    return 0;
}
