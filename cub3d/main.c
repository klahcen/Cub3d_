/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:14:13 by ysaber            #+#    #+#             */
/*   Updated: 2024/07/20 08:09:20 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

void	ft_check_fd(int i, int j)
{
	if (j == 0 && i == -1)
	{
		ft_putstr(2, "Error\nInvalid path\n");
		exit(1);
	}
	else if (j == 1 && i == 0)
	{
		ft_putstr(2, "Error\nMalloc failed\n");
		exit(1);
	}
}

void	ft_check_path(t_map *map)
{
	map->fd_no = open(map->no, O_RDONLY);
	ft_check_fd(map->fd_no, 0);
	map->fd_ea = open(map->ea, O_RDONLY);
	if (map->fd_ea == -1)
	{
		ft_putstr(2, "Error\nInvalid path\n");
		close(map->fd_no);
		exit(1);
	}
	map->fd_so = open(map->so, O_RDONLY);
	if (map->fd_so == -1)
	{
		ft_putstr(2, "Error\nInvalid path\n");
		close(map->fd_no);
		close(map->fd_ea);
		exit(1);
	}
	map->fd_we = open(map->we, O_RDONLY);
	if (map->fd_we == -1)
	{
		ft_putstr(2, "Error\nInvalid path\n");
		close(map->fd_no);
		close(map->fd_ea);
		(close(map->fd_so), exit(1));
	}
}

char	*ft_remove_names(char *str, char *name)
{
	t_norminette1	e;

	e.snew = NULL;
	e.i = 0;
	e.j = 0;
	e.k = 0;
	e.new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!e.new)
		ft_check_fd(0, 1);
	while (str[e.i])
	{
		if (str[e.i] == name[e.j])
			e.j++;
		else
		{
			e.new[e.k] = str[e.i];
			e.k++;
		}
		e.i++;
	}
	e.new[e.k] = '\0';
	e.snew = ft_strtrim(e.new);
	free(str);
	return (e.snew);
}

int	ft_set_color(char *str)
{
	t_norm	norm;

	norm.nc = ft_count_comma(str);
	if (norm.nc != 2)
		(ft_putstr(2, "Error\nInvalid color\n"), exit(1));
	norm.tab = ft_split(str, ',');
	if (!norm.tab[0] || !norm.tab[1] || !norm.tab[2])
		(ft_putstr(2, "Error\nInvalid color\n"), exit(1));
	ft_check_char(norm.tab);
	norm.r = ft_atoi(norm.tab[0]);
	norm.g = ft_atoi(norm.tab[1]);
	norm.b = ft_atoi(norm.tab[2]);
	if (norm.r < 0 || norm.r > 255 || norm.g < 0 || norm.g > 255 || norm.b < 0
		|| norm.b > 255)
		(ft_putstr(2, "Error\nInvalid color\n"), exit(1));
	norm.color = rgb_to_int(norm.r, norm.g, norm.b);
	norm.i = 0;
	while (norm.tab[norm.i])
	{
		free(norm.tab[norm.i]);
		norm.i++;
	}
	free(norm.tab);
	return (norm.color);
}

int	main(int ac, char **av)
{
	int		fd;
	t_map	*map;

	if (ac != 2)
	{
		ft_putstr(2, "Error\nInvalid arguments\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1 || ft_check_name(av[1]) == -1)
	{
		ft_putstr(2, "Error\nInvalid file\n");
		return (0);
	}
	map = malloc(sizeof(t_map));
	if (!map)
	{
		ft_putstr(2, "Error\nMalloc failed\n");
		return (0);
	}
	map = ft_check_map(fd, map);
	check_valid_01(map);
	check_valid_xpm(map);
	cub(map);
	return (0);
}
