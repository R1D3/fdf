/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 12:06:08 by emassou           #+#    #+#             */
/*   Updated: 2018/04/11 12:06:09 by emassou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_space(t_env *fdf)
{
	if (fdf->chars <= 20)
		fdf->prop = 20;
	else if (fdf->chars >= 20 && fdf->chars < 50)
		fdf->prop = 10;
	else if (fdf->chars >= 50 && fdf->chars <= 100)
		fdf->prop = 5;
	else if (fdf->chars >= 100 && fdf->chars <= 200)
		fdf->prop = 5;
	else
		fdf->prop = 1;
}

void	ft_pos3(t_env *fdf)
{
	if (fdf->chars >= 20 && fdf->chars < 50)
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

void	ft_pos2(t_env *fdf)
{
	if (fdf->chars < 10)
	{
		fdf->propx = 10;
		fdf->propy = 10;
	}
	else if (fdf->chars < 20)
	{
		fdf->propx = 20;
		fdf->propy = 20;
	}
	else if (fdf->chars <= 20)
	{
		fdf->propx = 50;
		fdf->propy = 50;
	}
	ft_pos3(fdf);
}

void	ft_pos(t_env *fdf)
{
	if (fdf->chars < 10)
	{
		fdf->propx = 180;
		fdf->propy = -20;
	}
	else if (fdf->chars <= 20)
	{
		fdf->propx = 250;
		fdf->propy = -50;
	}
	else if (fdf->chars >= 20 && fdf->chars < 50)
	{
		fdf->propx = 340;
		fdf->propy = -100;
	}
	else if (fdf->chars >= 50 && fdf->chars < 100)
	{
		fdf->propx = 40;
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
		fdf->win_length = 1000;
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
		fdf->win_width = 2000;
	else
		fdf->win_width = fdf->chars * 20;
}
