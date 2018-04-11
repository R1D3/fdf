/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 12:06:00 by emassou           #+#    #+#             */
/*   Updated: 2018/04/11 12:06:01 by emassou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			draw(t_env *a, int coord[][a->chars + 1][2], int tabxy[2])
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

static	void	ft_boucle(t_env *a, int coord[][a->chars + 1][2], int tabxy[2])
{
	if (a->map[tabxy[0]][tabxy[1]] == 0)
	{
		coord[tabxy[0]][tabxy[1]][0] = a->point.x1;
		coord[tabxy[0]][tabxy[1]][1] = a->point.y1;
	}
	else if (a->map[tabxy[0]][tabxy[1]] > 40 ||
		a->map[tabxy[0]][tabxy[1]] < -40)
	{
		coord[tabxy[0]][tabxy[1]][0] = a->point.x1 -
		a->map[tabxy[0]][tabxy[1]] * 2;
		coord[tabxy[0]][tabxy[1]][1] = a->point.y1 -
		a->map[tabxy[0]][tabxy[1]] * 2;
	}
	else
	{
		coord[tabxy[0]][tabxy[1]][0] = a->point.x1 -
		a->map[tabxy[0]][tabxy[1]] * 5;
		coord[tabxy[0]][tabxy[1]][1] = a->point.y1 -
		a->map[tabxy[0]][tabxy[1]] * 5;
	}
}

static	void	initcoord(t_env *a, int coord[][a->chars + 1][2], int tabxy[2])
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

void			drawcoord(t_env *a)
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
			ft_boucle(a, coord, tabxy);
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
