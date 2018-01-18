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
	int				**map;
	int				fd;
	int				lines;
	int				chars;
	int				z;
	int				y;
	int				x;
	int				dx;
	int				dy;
}					t_env;

#endif
