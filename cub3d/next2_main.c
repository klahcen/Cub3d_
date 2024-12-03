/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next2_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:38:16 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/26 16:38:10 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

char	*ft_read_rest(int fd, t_norm *norm, char *str)
{
	int	i;

	norm->flag = 0;
	i = 0;
	while (get_next_line(fd, &norm->line))
	{
		if (ft_check_line(norm->line) == -1 && norm->flag == 0)
		{
			free(norm->line);
			continue ;
		}
		norm->flag = 1;
		norm->len = ft_strlen(norm->line);
		if (norm->line[0] == '\n' && norm->len == 1)
		{
			while (i <= norm->len)
			{
				norm->line = ft_strjoin(norm->line, "                   \n");
				i++;
			}
		}
		str = ft_strjoin(str, norm->line);
		free(norm->line);
	}
	return (str);
}

int	ft_next_read(t_norm *norm)
{
	norm->new = malloc(sizeof(t_line));
	if (!norm->new)
	{
		free(norm->line);
		return (-1);
	}
	norm->new->str = norm->line;
	norm->new->next = norm->head;
	norm->head = norm->new;
	return (1);
}

void	ft_read_six_lines(int fd, t_norm *norm)
{
	while (get_next_line(fd, &norm->line))
	{
		if (ft_check_line(norm->line) == -1)
		{
			free(norm->line);
			continue ;
		}
		if (norm->head->str == NULL)
		{
			norm->head->str = norm->line;
			norm->head->next = NULL;
		}
		else
		{
			if (ft_next_read(norm) == -1)
				break ;
		}
		if (ft_lst_size(norm->head) == 6)
			break ;
	}
	if (ft_lst_size(norm->head) != 6)
	{
		ft_putstr(2, "Error\n Map is Invalid\n");
		exit(1);
	}
}

int	ft_check_valid_maphh(char **str)
{
	int	i;

	if (ft_strlen2d(str) == 0 || ft_strlen2d(str) == 1)
		return (-1);
	i = 0;
	while (str[0][i])
	{
		if (str[0][i] != '1' && str[0][i] != ' ' && str[0][i] != '\t'
			&& str[0][i] != '0')
			return (-1);
		if (str[0][i] == '0' && str[1][i] != '1')
			return (-1);
		i++;
	}
	return (0);
}

t_map	*ft_check_map(int fd, t_map *map)
{
	t_norm	norm;
	char	*str;

	norm.head = malloc(sizeof(t_line));
	if (!norm.head)
		exit(1);
	norm.head->str = NULL;
	norm.head->next = NULL;
	norm.line = NULL;
	ft_read_six_lines(fd, &norm);
	norm.flag2 = 0;
	str = NULL;
	str = ft_read_rest(fd, &norm, str);
	map = ft_fill_map(norm.head, map);
	ft_free_head(norm.head);
	ft_check_validity(str);
	map->map = ft_split(str, '\n');
	ft_check_counter(map->map);
	if (ft_check_valid_maphh(map->map) == -1)
	{
		free(str);
		(ft_putstr(2, "Error\nInvalid F|L map\n"), exit(1));
	}
	ft_check_0space(map->map);
	return (free(str), map);
}
