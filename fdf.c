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

# include "fdf.h"

int key_funct(int keycode, t_env *a)
{
    printf("%d\n", keycode );
    if (keycode == 53)
        exit(1);

    return (0);
}

void segment(t_env *a, int coord[][a->chars + 1][2], int tabxy[2])
{
    a->x = a->x1;
    a->y = a->y1;
    a->dx = (a->x2 - a->x1);
    a->dy = (a->y2 - a->y1);
    a->xinc = ( a->dx > 0 ) ? 1 : -1;
    a->yinc = ( a->dy > 0 ) ? 1 : -1;
    a->dx = abs(a->dx);
    a->dy = abs(a->dy);
    if (a->map[tabxy[0]][tabxy[1]] != 0)
        a->imgstr[((a->x + a->y) / 2 ) * WIDTH + (a->x - a->y )] = 0x00FF0000;
    else 
        a->imgstr[((a->x + a->y) / 2 ) * WIDTH + (a->x - a->y )] = 0x00FFFFFF;
    if (a->dx > a->dy)
    {
        a->cumul = a->dx / 2 ;
        a->i = 1;
        while (a->i++ <= a->dx && tabxy[1] < a->chars - 1)
        {
            a->x += a->xinc;
            a->cumul += a->dy;
            if (a->cumul >= a->dx)
            {
                a->cumul -= a->dx;
                a->y += a->yinc;
            }
            if (a->map[tabxy[0]][tabxy[1]] != 0)
                a->imgstr[((a->x + a->y) / 2 ) * WIDTH + (a->x - a->y )] = 0x00FF0000;
            else 
                a->imgstr[((a->x + a->y) / 2 ) * WIDTH + (a->x - a->y )] = 0x00FFFFFF;
        }
    }
    else 
    {
        a->cumul = a->dy / 2 ;
        a->i = 1;
        while (a->i++ <= a->dy && tabxy[0] < a->lines - 1)
        {
            a->y += a->yinc ;
            a->cumul += a->dx ;
            if ( a->cumul >= a->dy ) 
            {
                a->cumul -= a->dy ;
                a->x += a->xinc ;
            }
            if (a->map[tabxy[0]][tabxy[1]] != 0)
                a->imgstr[((a->x + a->y) / 2 ) * WIDTH + (a->x - a->y )] = 0x00FF0000;
            else 
                a->imgstr[((a->x + a->y) / 2 ) * WIDTH + (a->x - a->y )] = 0x00FFFFFF;
        }
    }
}

void draw(t_env *a, int coord[][a->chars + 1][2], int tabxy[2])
{   
    tabxy[0] = 0;
    while (a->y1 < HEIGHT && tabxy[0] < a->lines)
        {
            tabxy[1] = 0;
            while (a->x1 < WIDTH && tabxy[1] < a->chars)
                {
                    a->x1 = coord[tabxy[0]][tabxy[1]][0];
                    a->y1 = coord[tabxy[0]][tabxy[1]][1];
                    if (tabxy[1] != (a->chars - 1))
                    {
                        a->x2 = coord[tabxy[0]][tabxy[1] + 1][0];
                        a->y2 = coord[tabxy[0]][tabxy[1] + 1][1];
                        segment(a, coord, tabxy);
                    }
                    if (tabxy[0] != (a->lines - 1))
                    {
                        a->x2 = coord[tabxy[0] + 1][tabxy[1]][0];
                        a->y2 = coord[tabxy[0] + 1][tabxy[1]][1];
                        segment(a, coord, tabxy);
                    }
                    tabxy[1]++;
                }
            tabxy[0]++;
        }
    mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
}

void drawcoord(t_env *a)
{
    int tabxy[2];
    int coord[a->lines + 1][a->chars + 1][2];

    tabxy[0] = 0;
    a->y1 = a->propy;
    while (a->y1 < HEIGHT && tabxy[0] < a->lines)
        {

            a->x1 = a->propx;
            tabxy[1] = 0;
            while (a->x1 < WIDTH && tabxy[1] < a->chars)
                {
                    if (a->map[tabxy[0]][tabxy[1]] == 0)
                    {
                        coord[tabxy[0]][tabxy[1]][0] = a->x1;
                        coord[tabxy[0]][tabxy[1]][1] = a->y1;
                    }
                    else
                    {
                        coord[tabxy[0]][tabxy[1]][0] = a->x1 - a->map[tabxy[0]][tabxy[1]] * 10;
                        coord[tabxy[0]][tabxy[1]][1] = a->y1 - a->map[tabxy[0]][tabxy[1]] * 10;
                    }
                    a->x1 += a->prop;
                    tabxy[1]++;
                }
            a->y1 += a->prop;
            tabxy[0]++;
        }
    draw(a, coord, tabxy);
}

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
    int     ret;

    line = NULL;
    a->lines = 0;
    a->chars = 0;
    while ((ret = get_next_line(a->fd, &line) > 0))
    {
        if (alloctab2(a, line) == -1)
            return (-1);
    }
    a->map = malloc(sizeof(int*) * a->lines);
    close(a->fd);
    a->fd = open(a->file, O_RDONLY);
    return (0);
}

int ft_reader(t_env *a)
{
    char    *line;
    char    **tab;
    int     tabxy[3];

    tabxy[1] = 0;
    if (alloctab(a) == -1)
        return (-1);
    while ((tabxy[2] = get_next_line(a->fd, &line) > 0))
        {
            tabxy[0] = 0;
            a->map[tabxy[1]] = malloc(sizeof(int) * a->chars);
            tab = ft_strsplit(line, ' ');
            while (tab[tabxy[0]] != NULL)
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

void init(t_env *a)
{
    if (a->chars > 40 && a->chars < 99)
    {   
        a->prop = 15;
        a->propy = -500;
        a->propx = WIDTH / 4;
    }
    else if (a->chars > 99 && a->lines > 99)
    {   
        a->prop = 7;
        a->propy = -200;
        a->propx = WIDTH / 5; 
    }
    else
    {
        a->propy = -250;
        a->prop = 30;
        a->propx = WIDTH / 2;
    }
        
}
void mlx(t_env *a)
{
    int bpp;
    int sl;
    int endian;
    init(a);
    a->mlx = mlx_init();
    a->win = mlx_new_window(a->mlx, WIDTH, HEIGHT, "fdf42");
    a->img = mlx_new_image(a->mlx, WIDTH, HEIGHT);
    a->imgstr = (int*)mlx_get_data_addr(a->img, &bpp, &sl, &endian);
    drawcoord(a);
    mlx_key_hook(a->win, key_funct, a);
    mlx_loop(a->mlx);
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
        mlx(&main);
	}
    else
	    ft_putendl("usage : ./fdf file ");
	return (0);
}
