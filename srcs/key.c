/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 12:06:17 by emassou           #+#    #+#             */
/*   Updated: 2018/04/11 12:06:18 by emassou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int				ft_expose_hook(t_env *a)
{
	mlx_destroy_image(a->mlx, a->img);
	a->img = mlx_new_image(a->mlx, a->win_width, a->win_length);
	a->imgstr = (int*)mlx_get_data_addr(a->img, &a->bpp, &a->sl, &a->endian);
	ft_bzero(&a->point, sizeof(t_point));
	drawcoord(a);
	return (0);
}

static	void	key_proj(t_env *fdf)
{
	if (fdf->proj == 0)
		fdf->proj = 1;
	else if (fdf->proj == 1)
		fdf->proj = 0;
}

static	void	key_move2(int keycode, t_env *a)
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

static	void	key_move(int keycode, t_env *a)
{
	if (a->proj == 1)
		key_move2(keycode, a);
	else if (keycode == 125 && a->point.xmax < a->win_width &&
		a->point.ymax < a->win_length)
	{
		a->propx += 10;
		a->propy += 10;
	}
	else if (keycode == 126 && a->propx > -100 && a->propy > -250)
	{
		a->propx -= 10;
		a->propy -= 10;
	}
	else if (keycode == 124 && a->point.xmax < a->win_width && a->propy > -250)
	{
		a->propx += 10;
		a->propy -= 10;
	}
	else if (keycode == 123 && a->propx > -100 && a->point.ymax < a->win_length)
	{
		a->propx -= 10;
		a->propy += 10;
	}
}

int				key_funct(int keycode, t_env *a)
{
	if (keycode == 53)
	{
		exit(1);
	}
	if (keycode == 124 || keycode == 125 ||
		keycode == 126 || keycode == 123)
		key_move(keycode, a);
	else if (keycode == 49)
	{
		key_proj(a);
		init(a);
	}
	ft_expose_hook(a);
	return (0);
}
