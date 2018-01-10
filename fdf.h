/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 17:55:12 by emassou           #+#    #+#             */
/*   Updated: 2018/01/10 17:55:14 by emassou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FDF_H_
# define _FDF_H_
# define WIDTH		800
# define HEIGHT		600
# include "mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct  s_env
{
	void *mlx;
	void *win;
	void *img;
	int	*imgstr;
	int z;
	int y;
	int x;
	int dx;
	int dy;
	int fd;
	t_coord	 **coord;

}				t_env;

#endif