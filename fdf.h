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
# define BLACK		0x000000
# define BLUE 		0x0041FF
# define BROWN 		0x613519
# define GREEN1		0x234F0F
# define GREEN		0x2A6B11
# define GREY		0x808080
# define RED 		0xFF0000
# define YELLOW 	0xFFFF00
# define WHITE 		0xFFFFFF
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
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
	int				mul;
	int				prop;
	int				propy;
	int				propx;
	int				lines;
	int				chars;
	int				win_width;
	int				win_length;
	int				bpp;
	int				sl;
	int				endian;
	int				proj;		
	int				i;
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
