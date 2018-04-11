/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 12:05:49 by emassou           #+#    #+#             */
/*   Updated: 2018/04/11 12:05:51 by emassou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static	int	alloctab2(t_env *a, char *line)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(line, ' ');
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (a->lines == 0)
		a->chars = i;
	else
	{
		if (i != a->chars)
			return (-1);
	}
	a->lines++;
	free(tab);
	free(line);
	return (0);
}

static	int	alloctab(t_env *a)
{
	char	*line;
	int		ret;

	line = NULL;
	a->lines = 0;
	a->chars = 0;
	while ((ret = get_next_line(a->fd, &line) > 0))
	{
		if (alloctab2(a, line) == -1)
			return (-1);
	}
	a->map = malloc(sizeof(int*) * a->lines);
	close(a->fd);
	a->fd = open(a->file, O_RDONLY);
	return (0);
}

int			ft_reader(t_env *a)
{
	char	*line;
	char	**tab;
	int		tabxy[3];

	tabxy[1] = 0;
	if (alloctab(a) == -1)
		return (-1);
	while ((tabxy[2] = get_next_line(a->fd, &line) > 0))
	{
		tabxy[0] = 0;
		a->map[tabxy[1]] = malloc(sizeof(int) * a->chars);
		tab = ft_strsplit(line, ' ');
		while (tab[tabxy[0]] != NULL)
		{
			a->map[tabxy[1]][tabxy[0]] = ft_atoi(tab[tabxy[0]]);
			free(tab[tabxy[0]]);
			tabxy[0]++;
		}
		free(tab);
		tabxy[1]++;
	}
	return ((tabxy[2] == -1) ? -1 : 0);
}

void		mlx(t_env *a)
{
	a->proj = 0;
	a->mul = 4;
	init(a);
	ft_space(a);
	ft_window(a);
	a->mlx = mlx_init();
	a->win = mlx_new_window(a->mlx, a->win_width, a->win_length, "fdf42");
	a->img = mlx_new_image(a->mlx, a->win_width, a->win_length);
	a->imgstr = (int*)mlx_get_data_addr(a->img, &a->bpp, &a->sl, &a->endian);
	drawcoord(a);
	mlx_key_hook(a->win, key_funct, a);
	mlx_expose_hook(a->win, ft_expose_hook, a);
	mlx_loop(a->mlx);
}

int			main(int ac, char **av)
{
	t_env main;

	ft_bzero(&main, sizeof(t_env));
	if (ac == 2)
	{
		main.file = av[1];
		main.fd = open(main.file, O_RDONLY);
		if (main.fd == -1)
			return (-1);
		if (ft_reader(&main) == -1)
			return (-1);
		if ((close(main.fd)) == -1)
			return (-1);
		mlx(&main);
		free(main.map);
		ft_bzero(&main, sizeof(t_env));
	}
	else
		ft_putendl("usage : ./fdf file ");
	return (0);
}
