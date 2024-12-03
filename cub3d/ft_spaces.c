/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spaces.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:01:50 by ysaber            #+#    #+#             */
/*   Updated: 2024/07/26 17:10:40 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

char	**ft_strdup2d(char **map)
{
	int		i;
	char	**tmp;

	i = 0;
	while (map[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
	{
		ft_putstr(2, "Error\nMalloc failed\n");
		exit(1);
	}
	i = 0;
	while (map[i])
	{
		tmp[i] = ft_strdup(map[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	ft_free_tmp(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	check_valid_01(t_map *map)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = ft_strdup2d(map->map);
	i = 1;
	while (tmp[i])
	{
		tmp[i] = ft_strtrim(tmp[i]);
		if (tmp[i][0] != '1' || tmp[i][ft_strlen(tmp[i]) - 1] != '1')
		{
			if (ft_strlen(tmp[i]) == 0 || ft_only_s(tmp[i]))
			{
				i++;
				continue ;
			}
			ft_putstr(2, "Error\nInvalid 44 map\n");
			j = 0;
			while (tmp[j])
				free(tmp[j++]);
			(free(tmp), exit(1));
		}
		i++;
	}
	ft_free_tmp(tmp);
}

void	ft_free_head(t_line *head)
{
	t_line	*tmp;

	tmp = head;
	while (tmp)
	{
		head = head->next;
		free(tmp);
		tmp = head;
	}
	free(head);
}

void	ft_free_hna(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
