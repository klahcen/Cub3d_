/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next1_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:56 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/26 15:32:13 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

void	ft_set_cf(t_map *map, char *str)
{
	if (str[0] == 'F' && (str[1] == ' ' || str[1] == '\t'))
		map->f = ft_substr(str, 0, ft_strlen(str) - 1);
	if (str[0] == 'C' && (str[1] == ' ' || str[1] == '\t'))
		map->c = ft_substr(str, 0, ft_strlen(str) - 1);
}

void	ft_initialize(t_map *map)
{
	map->floor = 0;
	map->ceiling = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = NULL;
	map->c = NULL;
}

void	ft_so_we1(t_map *map, char *str)
{
	if (str[0] == 'S' && str[1] == 'O' && (str[2] == ' ' || str[2] == '\t'))
		map->so = ft_substr(str, 0, ft_strlen(str) - 1);
	if (str[0] == 'W' && str[1] == 'E' && (str[2] == ' ' || str[2] == '\t'))
		map->we = ft_substr(str, 0, ft_strlen(str) - 1);
}

t_map	*ft_fill_map(t_line *head, t_map *map)
{
	t_line	*tmp;

	ft_initialize(map);
	if (!head)
		(ft_putstr(2, "Error\nInvalid map\n"), exit(1));
	tmp = head;
	while (tmp)
	{
		tmp->str = ft_strtrim(tmp->str);
		if (tmp->str[0] == 'N' && tmp->str[1] == 'O' && (tmp->str[2] == ' '
				|| tmp->str[2] == '\t'))
			map->no = ft_substr(tmp->str, 0, ft_strlen(tmp->str) - 1);
		if (tmp->str[0] == 'E' && tmp->str[1] == 'A' && (tmp->str[2] == ' '
				|| tmp->str[2] == '\t'))
			map->ea = ft_substr(tmp->str, 0, ft_strlen(tmp->str) - 1);
		ft_so_we1(map, tmp->str);
		ft_set_cf(map, tmp->str);
		free(tmp->str);
		tmp = tmp->next;
	}
	return (map);
}

void	ft_check_validity(char *str)
{
	int	i;

	if (!str)
	{
		ft_putstr(2, "Error\nInvalid Map\n");
		exit(1);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '\n' && str[i] != '\t'
			&& str[i] != '0' && str[i] != 'N' && str[i] != 'S' && str[i] != 'W'
			&& str[i] != 'E' && str[i] != ' ')
		{
			ft_putstr(2, "Error\nInvalid 1 map\n");
			exit(1);
		}
		i++;
	}
}
