#include "bsq.h"
#include <stddef.h>
#include <stdio.h>

int ft_strlen(char *line)
{
    int i = 0;
    int size = 0;

    if (!line)
        return (0);

    while (line[i])
    {
        i++;
        size++;
    }
    return (size);
}

char    *ft_strndup(char *src, int n)
{
    char    *res;

    if (n == 0)
        return (NULL);
    res = calloc(sizeof(char), n + 1);
    if (!res)
        return (NULL);
    int i = 0;
    while (src[i] && i < n)
    {
        res[i] = src[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

void    free_tab(int **tab, int size)
{
    if (!tab || !*tab)
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

void    free_split(char **s)
{
    if (!s || !*s)
        return ;
    for (int i = 0; s[i]; i++)
    {
        if (s[i])
        {
            free(s[i]);
            s[i] = NULL;
        }
    }
    free(s);
    s = NULL;
}

int parse_info(t_map *map)
{
    if (map->lines <= 0
        || map->empty == map->obstacle
        || map->empty == map->full
        || map->obstacle == map->full)
            return (1);
    if (map->empty < 32 || map->obstacle < 32 || map->full < 32)
        return (1);
    return (0);
}

int charset(t_map *map, char c)
{
    if (c == map->empty || c == map->obstacle)
    {
        if (c == map->obstacle)
            map->count++;
        return (1);
    }
    return (0);
}

int parse_map(t_map *map)
{
    int i = 0;
    map->len = ft_strlen(map->map[i]);
    while (map->map[i])
    {
        int j = 0;
        if (map->len != ft_strlen(map->map[i]))
                return (1);
        while (map->map[i][j])
        {
            if (!charset(map, map->map[i][j]))
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int parse_file(t_map *map, char *path)
{
    FILE    *file;
    char    *line = NULL;
    size_t  len = 0;
    int     i = 0;

    map->count = 0;
    map->len = 0;
    file = fopen(path, "r");
    if (!file)
        return (1);
    if (fscanf(file, "%d %c %c %c", &map->lines, &map->empty, &map->obstacle, &map->full) != 4)
            return (fclose(file), 1);
    getline(&line, &len, file);
    if (parse_info(map))
            return (free(line), fclose(file), 1);
    map->map = calloc(sizeof(char *), map->lines + 1);
    if (!map->map)
        return (free(line), fclose(file), 1);
    while (i < map->lines)
    {
        free(line);
        line = NULL;
        getline(&line, &len, file);
        if (!line)
                return (free_split(map->map), map->map = NULL, fclose(file), 1);
        map->map[i] = ft_strndup(line, ft_strlen(line) - 1);
        if (!map->map[i])
            return (free(line), free_split(map->map), map->map = NULL, fclose(file), 1);
        i++;
    }
    map->map[i] = NULL;
    fclose(file);
    if (parse_map(map))
            return (free(line), free_split(map->map), map->map = NULL, 1);
    return (free(line), 0);
}

int parse_in(t_map *map)
{
    char        *line = NULL;
    int         i = 0;
    size_t      len = 0;

    map->count = 0;
    map->len = 0;
    if (fscanf(stdin, "%d %c %c %c", &map->lines, &map->empty, &map->obstacle, &map->full) != 4)
            return (1);
    getline(&line, &len, stdin);
    if (parse_info(map))
            return (free(line), 1);
    map->map = calloc(sizeof(char *), map->lines + 1);
    if (!map->map)
        return (free(line), 1);
    while (i < map->lines)
    {
        free(line);
        line = NULL;
        getline(&line, &len, stdin);
        if (!line)
                return (free_split(map->map), map->map = NULL, 1);
        map->map[i] = ft_strndup(line, ft_strlen(line) - 1);
        if (!map->map[i])
            return (free(line), free_split(map->map), map->map = NULL, 1);
        i++;
    }
    map->map[i] = NULL;
    if (parse_map(map))
            return (free(line), free_split(map->map), map->map = NULL, 1);
    return (free(line), 0);
}

int mini(int a, int b, int c)
{
    int m = a;
    if (b < m)
        m = b;
    if (c < m)
        m = c;
    return (m);
}

int solver(t_map *map)
{
    map->max = 0;
    map->dp = calloc(sizeof(int *), map->lines);
    if (!map->dp)
        return (1);
    for (int i = 0; i < map->lines; i++)
    {
        map->dp[i] = calloc(sizeof(int), map->len);
        if (!map->dp[i])
            return (free_tab(map->dp, map->lines), 1);
    }
    for (int i = 0; i < map->lines; i++)
    {
        for (int y = 0; y < map->len; y++)
        {
            if (map->map[i][y] == map->obstacle)
                map->dp[i][y] = 0;
            else if (i == 0 || y == 0)
                map->dp[i][y] = 1;
            else
                map->dp[i][y] = 1 + mini(map->dp[i-1][y], map->dp[i][y-1], map->dp[i-1][y-1]);
            if (map->dp[i][y] > map->max)
            {
                map->max = map->dp[i][y];
                map->maxi = i;
                map->maxy = y;
            }
        }
    }
    for (int i = map->maxi; i > map->maxi - map->max; i--)
    {
        for (int y = map->maxy; y > map->maxy - map->max; y--)
            map->map[i][y] = map->full;
    }
    free_tab(map->dp, map->lines);
    for (int i = 0; i < map->lines; i++)
        fprintf(stdout, "%s\n", map->map[i]);
    return (0);
}

int main(int argc, char **argv)
{
    t_map   *map = calloc(sizeof(t_map), 1);

    if (!map)
        return (1);
    if (argc == 1)
    {
        if (parse_in(map))
        {
            free(map);
            fprintf(stderr, "map error\n");
        }
        if (solver(map))
        {
            free_split(map->map);
            map->map = NULL;
            free(map);
            fprintf(stderr, "map error\n");
        }
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            free_split(map->map);
            map->map = NULL;
            if (parse_file(map, argv[i]))
            {
                fprintf(stderr, "map error\n");
                continue ;
            }
            if (solver(map))
            {
                free_split(map->map);
                map->map = NULL;
                fprintf(stderr, "map error\n");
                continue ;
            }
            if (i + 1 < argc)
                fprintf(stdout, "\n");
        }
    }
    return (free_split(map->map), free(map), 0);
}
