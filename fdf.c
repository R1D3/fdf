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

void put_pixel(t_env *a)
{
    printf(" xmax = %d\n", a->point.xmax);
    printf("ymax = %d\n", a->point.ymax);
    printf(" xmin = %d\n", a->point.xmin);
    printf("ymin = %d\n", a->point.ymin);
        if (a->proj == 0)
            a->imgstr[((a->point.x + a->point.y) / 2) * a->win_width + (a->point.x - a->point.y )] = WHITE;
        else 
            if (a->point.x < a->win_width && a->point.x > -a->win_width &&
            a->point.y < a->win_length && a->point.y > -a->win_length)
                a->imgstr[a->point.y * a->win_width + a->point.x] = WHITE;
}       

void initcoord(t_env *a, int coord[][a->chars + 1][2], int tabxy[2])
{
    a->point.xmin = a->propx;
    a->point.ymin = a->propy;
    if (coord[tabxy[0]][tabxy[1]][0] > a->point.xmax &&
         tabxy[0] < a->lines && tabxy[1] < a->chars)
        a->point.xmax = coord[tabxy[0]][tabxy[1]][0];
    if (coord[tabxy[0]][tabxy[1]][0] < a->point.xmin &&
         tabxy[0] < a->lines && tabxy[1] < a->chars)
        a->point.xmin = coord[tabxy[0]][tabxy[1]][0];
    if (coord[tabxy[0]][tabxy[1]][1] > a->point.ymax &&
         tabxy[0] < a->lines && tabxy[1] < a->chars)
        a->point.ymax = coord[tabxy[0]][tabxy[1]][1];
    if (coord[tabxy[0]][tabxy[1]][0] < a->point.xmin &&
         tabxy[0] < a->lines && tabxy[1] < a->chars)
        a->point.ymin = coord[tabxy[0]][tabxy[1]][1];
}

void segment(t_env *a)
{
    a->point.x = a->point.x1;
    a->point.y = a->point.y1;
    a->point.dx = (a->point.x2 - a->point.x1);
    a->point.dy = (a->point.y2 - a->point.y1);
    a->point.xinc = ( a->point.dx > 0 ) ? 1 : -1;
    a->point.yinc = ( a->point.dy > 0 ) ? 1 : -1;
    a->point.dx = abs(a->point.dx);
    a->point.dy = abs(a->point.dy);
    put_pixel(a);
    if (a->point.dx > a->point.dy)
    {
        a->point.cumul = a->point.dx / 2 ;
        a->i = 1;
        while (a->i++ <= a->point.dx)
        {
            a->point.x += a->point.xinc;
            a->point.cumul += a->point.dy;
            if (a->point.cumul >= a->point.dx)
            {
                a->point.cumul -= a->point.dx;
                a->point.y += a->point.yinc;
            }
        put_pixel(a);
        
        }
    }
    else 
    {
        a->point.cumul = a->point.dy / 2 ;
        a->i = 1;
        while (a->i++ <= a->point.dy)
        {
            a->point.y += a->point.yinc ;
            a->point.cumul += a->point.dx ;
            if ( a->point.cumul >= a->point.dy ) 
            {
                a->point.cumul -= a->point.dy ;
                a->point.x += a->point.xinc ;
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
                    a->point.x1 = coord[tabxy[0]][tabxy[1]][0];
                    a->point.y1 = coord[tabxy[0]][tabxy[1]][1];
                    if (tabxy[1] != (a->chars - 1))
                    {
                        a->point.x2 = coord[tabxy[0]][tabxy[1] + 1][0];
                        a->point.y2 = coord[tabxy[0]][tabxy[1] + 1][1];
                        segment(a);
                    }
                     if (tabxy[0] != (a->lines - 1))
                    {
                        a->point.x2 = coord[tabxy[0] + 1][tabxy[1]][0];
                        a->point.y2 = coord[tabxy[0] + 1][tabxy[1]][1];
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
    a->point.y1 = a->propy;
    while (tabxy[0] < a->lines)
        {
            a->point.x1 = a->propx;
            tabxy[1] = 0;
            while (tabxy[1] < a->chars)
                {
                    if (a->map[tabxy[0]][tabxy[1]] == 0)
                    {
                        coord[tabxy[0]][tabxy[1]][0] = a->point.x1;
                        coord[tabxy[0]][tabxy[1]][1] = a->point.y1;
                    }
                    else
                    {
                        coord[tabxy[0]][tabxy[1]][0] = a->point.x1 - a->map[tabxy[0]][tabxy[1]] * a->mul;
                        coord[tabxy[0]][tabxy[1]][1] = a->point.y1 - a->map[tabxy[0]][tabxy[1]] * a->mul;
                    }
                    initcoord(a, coord, tabxy);
                    a->point.x1 += a->prop;
                    tabxy[1]++;
                }
            a->point.y1 += a->prop;
            tabxy[0]++;
        }
    initcoord(a, coord, tabxy);
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

void	ft_pos2(t_env *fdf)
{
    if (fdf->chars < 10)
        {
            fdf->propx = 10;
            fdf->propy = 10;
        }
    else if (fdf->chars < 20)
		{
            fdf->propx = 0;
            fdf->propy = 0;
        }
	else if (fdf->chars <= 20)
		{
            fdf->propx = 50;
            fdf->propy = 50;
        }
	else if (fdf->chars >= 20 && fdf->chars < 50)
		{
            fdf->propx = 50;
            fdf->propy = 50;
        }
	else if (fdf->chars >= 50 && fdf->chars <= 100)
		{
            fdf->propx = 100;
            fdf->propy = 100;
        }
	else if (fdf->chars >= 100 && fdf->chars <= 200)
		{
            fdf->propx = 150;
            fdf->propy = 150;
        }
}

void	ft_pos(t_env *fdf)
{
    if (fdf->chars < 10)
        {
            fdf->propx = 100;
            fdf->propy = 20;
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
        ft_pos2(a);  
    }
    else
    {
        ft_pos(a);
    }
}

int	ft_expose_hook(t_env *a)
{
    mlx_destroy_image(a->mlx, a->img);
	a->img = mlx_new_image(a->mlx, a->win_width, a->win_length);
	a->imgstr = (int*)mlx_get_data_addr(a->img, &a->bpp, &a->sl, &a->endian);
    ft_bzero(&a->point, sizeof(t_point));
	drawcoord(a);
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

    if (keycode == 125 && a->point.ymax < a->win_length)
    {
        a->propy += a->prop;
    }
    else if (keycode == 126 && a->point.ymin > 50)
    {
        a->propy -= a->prop;
        if (a->propy < 0)
            a->propy = 0;
    }
    else if (keycode == 124 && a->point.xmax < a->win_width)
    {
        a->propx += a->prop;
  
    }
    else if (keycode == 123 && a->point.xmin > 50)
    {
        a->propx -= a->prop;
        if (a->propx < 0)
            a->propx = 0;
    }  
}
void key_move(int keycode, t_env *a)
{
    if (a->proj == 1)
        key_move2(keycode, a);
    else if (keycode == 125 && a->point.xmax < a->win_width && a->point.ymax < a->win_length)
    {
        a->propx += 10;
        a->propy += 10;
    }
    else if (keycode == 126 && a->point.xmin > -a->win_width && a->point.ymin > -a->win_length)
    {
        a->propx -= 10;
        a->propy -= 10;
    }
    else if (keycode == 124 && a->point.xmax < a->win_width && a->point.ymin > -a->win_length)
    {
        a->propx += 10;
        a->propy -= 10;
    }
    else if (keycode == 123 && a->point.xmin > -a->win_width && a->point.ymax < a->win_length)
    {
        a->propx -= 10;
        a->propy += 10;
    }
    printf("width = %d\n", a->win_width);
    printf("length = %d\n", a->win_length);
    printf(" xmax = %d\n", a->point.xmax);
    printf("ymax = %d\n", a->point.ymax);
    printf(" xmin = %d\n", a->point.xmin);
    printf("ymin = %d\n", a->point.ymin);
    printf("prop = %d\n", a->prop);
}

void key_alt(int keycode, t_env *a)
{
    if (keycode == 12 &&  (a->point.x < a->win_width || a->point.y < a->win_width
        || a->point.x > -a->win_width || a->point.y  > -a->win_width))
        a->mul++;
    if (keycode == 13 &&  (a->point.x < a->win_width || a->point.y < a->win_width
        || a->point.x >= -a->win_width || a->point.y > -a->win_width))
        a->mul--;
}

void key_zoom(int keycode, t_env *a)
{
    if (keycode == 24 && (a->point.x < a->win_width || a->point.y < a->win_width
        || a->point.x <= -a->win_width || a->point.y <= -a->win_width))
    {
        a->prop += 5;
    }
    if (keycode == 27)
    {
        a->prop -= 5;
        if (a->prop <= 0)
            a->prop = 5;
    }
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
    a->mul = 4;
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

