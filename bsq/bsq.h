#include "stdlib.h"
#include "stdio.h"

typedef struct s_map
{
    int     lines;
    int     count;
    int     len;
    int     max;
    int     maxi;
    int     maxy;
    int     **dp;

    char    empty;
    char    obstacle;
    char    full;

    char    **map;

}   t_map;
