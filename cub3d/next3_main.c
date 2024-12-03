/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next3_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:38:31 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/20 08:18:51 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

int	rgb_to_int(int red, int green, int blue)
{
	red = fmax(0, fmin(255, red));
	green = fmax(0, fmin(255, green));
	blue = fmax(0, fmin(255, blue));
	return ((red << 16) | (green << 8) | blue);
}

void	check_valid_xpm(t_map *map)
{
	if (map->no == NULL || map->ea == NULL || map->so == NULL || map->we == NULL
		|| map->c == NULL || map->f == NULL)
	{
		ft_putstr(2, "Error\nInvalid  3 map\n");
		exit(1);
	}
	map->no = ft_remove_names(map->no, "NO");
	map->ea = ft_remove_names(map->ea, "EA");
	map->so = ft_remove_names(map->so, "SO");
	map->we = ft_remove_names(map->we, "WE");
	ft_check_path(map);
	map->c = ft_remove_names(map->c, "C");
	map->f = ft_remove_names(map->f, "F");
	map->floor = ft_set_color(map->f);
	map->ceiling = ft_set_color(map->c);
}

int	ft_check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' || str[i \
		- 4] != '.')
		return (-1);
	return (0);
}

void	ft_check_char(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] == ' ' || tab[i][j] == '\t')
			j++;
		while (tab[i][j])
		{
			if (tab[i][j] < '0' || tab[i][j] > '9')
			{
				ft_putstr(2, "Error\nInvalid color\n");
				exit(1);
			}
			if (tab[i][j] == ' ')
				break ;
			j++;
		}
		i++;
	}
}

int	ft_count_comma(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}
