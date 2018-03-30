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
# include "fdf.h"

void put_pixel(t_env *a)
{
    if (a->proj == 0)
        a->imgstr[((a->x + a->y) / 2) * a->win_width + (a->x - a->y )] = WHITE;
    else 
        a->imgstr[a->y * a->win_width + a->x] = WHITE;
}       

void segment(t_env *a)
{
    a->x = a->x1;
    a->y = a->y1;
    a->dx = (a->x2 - a->x1);
    a->dy = (a->y2 - a->y1);
    a->xinc = ( a->dx > 0 ) ? 1 : -1;
    a->yinc = ( a->dy > 0 ) ? 1 : -1;
    a->dx = abs(a->dx);
    a->dy = abs(a->dy);
    put_pixel(a);
    if (a->dx > a->dy)
    {
        a->cumul = a->dx / 2 ;
        a->i = 1;
        while (a->i++ <= a->dx)
        {
            a->x += a->xinc;
            a->cumul += a->dy;
            if (a->cumul >= a->dx)
            {
                a->cumul -= a->dx;
                a->y += a->yinc;
            }
        put_pixel(a);
        }
    }
    else 
    {
        a->cumul = a->dy / 2 ;
        a->i = 1;
        while (a->i++ <= a->dy)
        {
            a->y += a->yinc ;
            a->cumul += a->dx ;
            if ( a->cumul >= a->dy ) 
            {
                a->cumul -= a->dy ;
                a->x += a->xinc ;
            }
        put_pixel(a);
        }
    }
}

void draw(t_env *a, int coord[][a->chars + 1][2], int tabxy[2])
{   
    tabxy[0] = 0;
    while (tabxy[0] < a->lines)
        {
            tabxy[1] = 0;
            while (tabxy[1] < a->chars)
                {
                    a->x1 = coord[tabxy[0]][tabxy[1]][0];
                    a->y1 = coord[tabxy[0]][tabxy[1]][1];
                    if (tabxy[1] != (a->chars - 1))
                    {
                        a->x2 = coord[tabxy[0]][tabxy[1] + 1][0];
                        a->y2 = coord[tabxy[0]][tabxy[1] + 1][1];
                        segment(a);
                    }
                     if (tabxy[0] != (a->lines - 1))
                    {
                        a->x2 = coord[tabxy[0] + 1][tabxy[1]][0];
                        a->y2 = coord[tabxy[0] + 1][tabxy[1]][1];
                        segment(a);
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
    while (tabxy[0] < a->lines)
        {

            a->x1 = a->propx;
            tabxy[1] = 0;
            while (tabxy[1] < a->chars)
                {
                    if (a->map[tabxy[0]][tabxy[1]] == 0)
                    {
                        coord[tabxy[0]][tabxy[1]][0] = a->x1;
                        coord[tabxy[0]][tabxy[1]][1] = a->y1;
                    }
                    else
                    {
                        if (a->map[tabxy[0]][tabxy[1]] > 40 || a->map[tabxy[0]][tabxy[1]] < -40)
                            a->mul = 2;
                        coord[tabxy[0]][tabxy[1]][0] = a->x1 - a->map[tabxy[0]][tabxy[1]] * a->mul;
                        coord[tabxy[0]][tabxy[1]][1] = a->y1 - a->map[tabxy[0]][tabxy[1]] * a->mul;
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

void	ft_space(t_env *fdf)
{
	if (fdf->chars <= 20)
		fdf->prop = 30;
	else if (fdf->chars >= 20 && fdf->chars < 50)
		fdf->prop = 20;
	else if (fdf->chars >= 50 && fdf->chars <= 100)
		fdf->prop = 10;
	else if (fdf->chars >= 100 && fdf->chars <= 200)
		fdf->prop = 5;
	else
		fdf->prop = 1;
}

void	ft_pos(t_env *fdf)
{
    if (fdf->chars < 10)
        {
            fdf->propx = 200;
            fdf->propy = 0;
        }
	else if (fdf->chars <= 20)
		{
            fdf->propx = 260;
            fdf->propy = -120;
        }
	else if (fdf->chars >= 20 && fdf->chars < 50)
		{
            fdf->propx = 340;
            fdf->propy = -100;
        }
	else if (fdf->chars >= 50 && fdf->chars <= 100)
		{
            fdf->propx = 480;
            fdf->propy = -20;
        }
	else if (fdf->chars >= 100 && fdf->chars <= 200)
		{
            fdf->propx = 600;
            fdf->propy = -200;
        }
}

void	ft_window(t_env *fdf)
{
	if (fdf->lines <= 10)
		fdf->win_length = fdf->lines * 70;
	else if (fdf->lines < 20)
		fdf->win_length = fdf->lines * 50;
	else if (fdf->lines >= 20 && fdf->lines < 50)
		fdf->win_length = fdf->lines * 40;
	else if (fdf->lines >= 50 && fdf->lines < 100)
		fdf->win_length = fdf->lines * 20;
	else if (fdf->lines >= 100 && fdf->lines <= 200)
		fdf->win_length = fdf->lines * 10;
	else
		fdf->win_length = fdf->lines * 10;
	if (fdf->chars <= 10)
		fdf->win_width = fdf->chars * 100;
    else if (fdf->chars < 20)
		fdf->win_width = fdf->chars * 50;
	else if (fdf->chars >= 20 && fdf->chars < 50)
		fdf->win_width = fdf->chars * 40;
	else if (fdf->chars >= 50 && fdf->chars < 100)
		fdf->win_width = fdf->chars * 20;
	else if (fdf->chars >= 100 && fdf->chars <= 200)
		fdf->win_width = fdf->chars * 10;
	else
		fdf->win_width = fdf->chars * 20;
}

void init(t_env *a)
{
    if (a->proj == 1)
    {
        a->propx = 150;
        a->propy = 150;  
    }
    else
    {
        ft_pos(a);
        a->mul = 4;
    }
}

int	ft_expose_hook(t_env *a)
{
	a->img = mlx_new_image(a->mlx, a->win_width, a->win_length);
	a->imgstr = (int*)mlx_get_data_addr(a->img, &a->bpp, &a->sl, &a->endian);
	drawcoord(a);
	mlx_destroy_image(a->mlx, a->img);
	return (0);
}

void	key_proj(t_env *fdf)
{
	if (fdf->proj == 0)
		fdf->proj = 1;
	else if (fdf->proj == 1)
		fdf->proj = 0;
}
void key_move2(int keycode, t_env *a)
{

    if (keycode == 125)
    {
        a->propy += 20;
    }
    else if (keycode == 126)
    {
        a->propy -= 20;
    }
    else if (keycode == 124)
    {
        a->propx += 20;
  
    }
    else if (keycode == 123)
    {
        a->propx -= 20;
    }  
}
void key_move(int keycode, t_env *a)
{
    if (a->proj == 1)
        key_move2(keycode, a);
    else if (keycode == 125 && (a->x < a->win_width || a->y < a->win_width
        || a->x > -a->win_width || a->y > -a->win_width))
    {
        a->propx += 20;
        a->propy += 20;
    }
    else if (keycode == 126 && (a->x < a->win_width || a->y < a->win_width
        || a->x > -a->win_width || a->y > -a->win_width))
    {
        a->propx -= 20;
        a->propy -= 20;
    }
    else if (keycode == 124 &&  (a->x < a->win_width || a->y < a->win_width
        || a->x > -a->win_width || a->y > -a->win_width))
    {
        a->propx += 20;
        a->propy -= 20;
    }
    else if (keycode == 123 &&  (a->x < a->win_width || a->y < a->win_width
        || a->x > -a->win_width || a->y > -a->win_width))
    {
        a->propx -= 20;
        a->propy += 20;
    }
    printf("x = %d\n", a->propx);
    printf("y = %d\n", a->propy);
    printf("width = %d\n", a->win_width);
    printf("length = %d\n", a->win_length);
}

void key_alt(int keycode, t_env *a)
{
    if (keycode == 12 &&  (a->x < a->win_width || a->y < a->win_width
        || a->x > -a->win_width || a->y  > -a->win_width))
        a->mul++;
    if (keycode == 13 &&  (a->x < a->win_width || a->y < a->win_width
        || a->x >= -a->win_width || a->y > -a->win_width))
        a->mul--;
}

void key_zoom(int keycode, t_env *a)
{
    if (keycode == 24 && (a->x < a->win_width || a->y < a->win_width
        || a->x <= -a->win_width || a->y <= -a->win_width))
    {
        a->prop += 5;
    }
    if (keycode == 27)
    {
        a->prop -= 5;
        if (a->prop <= 0)
            a->prop = 5;
    }
    printf(" x = %d\n", a->x);
    printf("y = %d\n", a->y);
}

int key_funct(int keycode, t_env *a)
{
    printf("%d\n", keycode );
    if (keycode == 53)
    {
        exit(1);
    }
    if (keycode == 124 || keycode == 125 || 
            keycode == 126 || keycode == 123)
            key_move(keycode, a);
    else if (keycode == 24 || keycode == 27)
            key_zoom(keycode, a);
    else if (keycode == 49)
    {
        key_proj(a);
        init(a);
    }
    else if (keycode == 12 || keycode == 13)
        key_alt(keycode, a);
    ft_expose_hook(a);
    return (0);
}

void mlx(t_env *a)
{
    a->proj = 0;
    init(a);
    ft_space(a);
    ft_window(a);
    a->mlx = mlx_init();
    a->win = mlx_new_window(a->mlx, a->win_width, a->win_length, "fdf42");
    a->img = mlx_new_image(a->mlx,a->win_width, a->win_length);
    a->imgstr = (int*)mlx_get_data_addr(a->img, &a->bpp, &a->sl, &a->endian);
    drawcoord(a);
    mlx_key_hook(a->win, key_funct, a);
    mlx_expose_hook(a->win, ft_expose_hook, a);
    mlx_loop(a->mlx);
}

int main(int ac, char **av)
{
	t_env main;

    ft_bzero(&main, sizeof(t_env));
	if (ac == 2)
	{
        main.file = av[1];
        main.fd = open(main.file, O_RDONLY);
        if (main.fd == -1)
            return (-1);
		if (ft_reader(&main) == -1)
            return (-1);
        if ((close(main.fd)) == -1)
		    return (-1);
        mlx(&main);
        free(main.map);
        ft_bzero(&main, sizeof(t_env));
	}
    else
	    ft_putendl("usage : ./fdf file ");
	return (0);
}

