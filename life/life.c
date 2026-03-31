#include "life.h"
#include <stddef.h>

void    free_tab(int **tab, int size)
{
    if (!tab)
        return ;
    for (int i = 0; i < size; i++)
    {
        if (tab[i])
        {
            free(tab[i]);
            tab[i] = NULL;
        }
    }
    free(tab);
    tab = NULL;
}

int create_tab(t_life *life)
{
    life->tab = calloc(sizeof(int *), life->height);
    if (!life->tab)
        return (1);
    for (int i = 0; i < life->height; i++)
    {
        life->tab[i] = calloc(sizeof(int), life->width);
        if (!life->tab[i])
            return (free_tab(life->tab, life->height), 1);
    }
    return (0);
}

void condition(t_life *life)
{
    if (life->writing && life->pen_x >= 0 && life->pen_x < life->width && life->pen_y >= 0 && life->pen_y < life->height)
    {
        life->tab[life->pen_y][life->pen_x] = 1;
        return ;
    }
}

int    read_command(t_life *life)
{
    char    c;
    int     ret;

    ret = read(0, &c, 1);
    while (ret > 0)
    {
        if (c == 'x')
        {
            if (life->writing)
                life->writing = 0;
            else
                life->writing = 1;
        }
        else if (c == 'w')
        {
            life->pen_y--;
            condition(life);
        }
        else if (c == 's')
        {
            life->pen_y++;
            condition(life);
        }
        else if (c == 'a')
        {
            life->pen_x--;
            condition(life);
        }
        else if (c == 'd')
        {
            life->pen_x++;
            condition(life);
        }
        else
            break ;
        ret = read(0, &c, 1);
    }
    if (ret == -1)
        return (1);
    return (0);
}

int count_nb(t_life *life, int x, int y)
{
    int count = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue ;
            int new_x = x + j;
            int new_y = y + i;
            if (new_x >= 0 && new_x < life->width && new_y >= 0 && new_y < life->height)
            {
                if (life->tab[new_y][new_x])
                    count++;
            }
        }
    }
    return (count);
}

int simulate(t_life *life)
{
    life->next_tab = calloc(sizeof(int *), life->height);
    if (!life->next_tab)
        return (1);
    for (int i = 0; i < life->height; i++)
    {
        life->next_tab[i] = calloc(sizeof(int), life->width);
        if (!life->next_tab[i])
            return (free_tab(life->next_tab, life->height), 1);
    }
    for (int i = 0; i < life->height; i++)
    {
        for (int y = 0; y < life->width; y++)
        {
            int nb = count_nb(life, y, i);
            if (life->tab[i][y])
            {
                if (nb == 2 || nb == 3)
                    life->next_tab[i][y] = 1;
            }
            else
            {
                if (nb == 3)
                    life->next_tab[i][y] = 1;
            }
        }
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_life  *life = calloc(sizeof(t_life), 1);

    if (!life)
        return (1);
    if (argc != 4)
        return (free(life), 1);
    life->width = atoi(argv[1]);
    life->height = atoi(argv[2]);
    life->interations = atoi(argv[3]);
    if (create_tab(life))
        return (1);
    if (read_command(life))
        return (free_tab(life->tab, life->height), free(life), 1);
    for (int i = 0; i < life->interations; i++)
    {
        simulate(life);
        free_tab(life->tab, life->height);
        life->tab = NULL;
        life->tab = life->next_tab;
    }
    for (int i = 0; i < life->height; i++)
    {
        for (int y = 0; y < life->width; y++)
        {
            putchar(life->tab[i][y] ? 'O' : ' ');
        }
        putchar('\n');
    }
    return (free_tab(life->tab, life->height), free(life), 0);
}
