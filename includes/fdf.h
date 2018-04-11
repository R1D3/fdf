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
# define WHITE 		0xFFFFFF
# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct		s_point
{
	int				xmin;
	int				ymin;
	int				xmax;
	int				ymax;		
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
}					t_point;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*imgstr;
	char			*file;
	int				fd;
	int				mul;
	int				i;
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
	int				check;
	int				color;
	int				**map;
	struct s_point	point;
}					t_env;

void	mlx(t_env *a);
int		ft_reader(t_env *a);
void	ft_space(t_env *fdf);
void	ft_pos3(t_env *fdf);
void	ft_pos2(t_env *fdf);
void	ft_pos(t_env *fdf);
void	ft_window(t_env *fdf);
void	drawcoord(t_env *a);
void	draw(t_env *a, int coord[][a->chars + 1][2], int tabxy[2]);
void	segment(t_env *a);
void	put_pixel(t_env *a);
void	init(t_env *a);
int		ft_expose_hook(t_env *a);
int		key_funct(int keycode, t_env *a);
#endif