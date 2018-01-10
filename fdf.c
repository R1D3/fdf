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

void mlx(t_env *m)
{

	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "fdf 42");
	m->img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	mlx_key_hook(m->win, key_funct, m);
	mlx_loop(m->mlx);
}
