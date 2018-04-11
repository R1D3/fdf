/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 12:06:28 by emassou           #+#    #+#             */
/*   Updated: 2018/04/11 12:06:30 by emassou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			init(t_env *a)
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

void			put_pixel(t_env *a)
{
	if (a->proj == 0)
		a->imgstr[((a->point.x + a->point.y) / 2) *
		a->win_width + (a->point.x - a->point.y)] = WHITE;
	else
	{
		if (a->point.x < a->win_width && a->point.x > -a->win_width &&
		a->point.y < a->win_length && a->point.y > -a->win_length)
			a->imgstr[a->point.y * a->win_width + a->point.x] = WHITE;
	}
}

static	void	init_segment(t_env *a)
{
	a->point.x = a->point.x1;
	a->point.y = a->point.y1;
	a->point.dx = (a->point.x2 - a->point.x1);
	a->point.dy = (a->point.y2 - a->point.y1);
	a->point.xinc = (a->point.dx > 0) ? 1 : -1;
	a->point.yinc = (a->point.dy > 0) ? 1 : -1;
	a->point.dx = abs(a->point.dx);
	a->point.dy = abs(a->point.dy);
}

static	void	ft_dy(t_env *a)
{
	a->point.cumul = a->point.dy / 2;
	a->i = 1;
	while (a->i++ <= a->point.dy)
	{
		a->point.y += a->point.yinc;
		a->point.cumul += a->point.dx;
		if (a->point.cumul >= a->point.dy)
		{
			a->point.cumul -= a->point.dy;
			a->point.x += a->point.xinc;
		}
		put_pixel(a);
	}
}

void			segment(t_env *a)
{
	init_segment(a);
	put_pixel(a);
	if (a->point.dx > a->point.dy)
	{
		a->point.cumul = a->point.dx / 2;
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
		ft_dy(a);
	}
}
