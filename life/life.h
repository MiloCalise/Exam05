#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_life
{
    int     **tab;
    int     **next_tab;

    int     width;
    int     height;
    int     interations;

    int     pen_x;
    int     pen_y;
    int     writing;

} t_life;
