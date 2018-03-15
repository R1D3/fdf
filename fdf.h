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
# define WIDTH		3600
# define HEIGHT		2400
# include "libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*imgstr;
	char			*file;
	int				fd;
	int				prop;
	int				propy;
	int				propx;
	int				lines;
	int				chars;
	int				i;
	int				j;
	int				k;
	int				x;
	int				y;
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				dx;
	int				dy;
	int				xinc;
	int				yinc;
	int				cumul;
	int				check;
	int				color;
	int				**map;
}					t_env;

#endif