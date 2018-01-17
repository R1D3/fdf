/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:04:27 by emassou           #+#    #+#             */
/*   Updated: 2018/01/10 18:04:30 by emassou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

int alloctab2(t_env *a, char *line)
{
    char  **tab;
    int i;

    i = 0;
    tab = ft_strsplit(line, ' ');
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    if (a->lines == 0)
        a->chars = i;
    else
    {
       if (i != a->chars)
        return (-1);
    }
    a->lines++;
    free(tab);
    free(line);
    return (0);
}

int alloctab(t_env *a)
{
    char    *line;

    a->lines = 0;
    a->chars = 0;
    while (get_next_line(a->fd, &line) == 1)
    {
        if (alloctab2(a, line) == -1)
            return (-1);
    }
    a->map = ft_memalloc(sizeof(int*) * a->lines);
    close(a->fd);
    a->fd = open(a->file, O_RDONLY);
    return (1);
}

int ft_reader(t_env *a)
{
    char    *line;
    char    *tab;
    int     tabxy[3];

    tabxy[1] = 0;
    if (alloctab(a) == -1)
        return (-1);
    while ((tabxy[2] = get_next_line(a->fd, &line) == 1))
        {
            tabxy[0] = 0;
            a->map = ft_memalloc(sizeof(int*) * a->chars);
            tab = ft_strsplit(line, ' ');
            while (tabxy[0] != NULL)
            {
                a->map[tabxy[1]][tabxy[0]] = ft_atoi(tab[tabxy[0]]);
                free(tab[tabxy[0]]);
                tabxy[0]++;
            }
        free(tab);
        tabxy[1]++;
        }

    return ((tabxy[2] == -1) ? -1 : 0);
}

int main(int ac, char **av)
{
	t_env main;
	if (ac == 2)
	{
        main.file = av[1];
        main.fd = open(main.file, O_RDONLY);
		if (ft_reader(&main) == -1)
            return (-1);
	}
    else
	    ft_putendl("usage : ./fdf file ");
	return (0);
}
