/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:20:49 by ysaber            #+#    #+#             */
/*   Updated: 2024/07/26 16:36:52 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

void	ft_no_0_inlast(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0')
		{
			ft_putstr(2, "Error\nInvalid 5 map\n");
			exit(1);
		}
		i++;
	}
}

int	ft_get_longest_line(char **str)
{
	int	i;
	int	j;
	int	longest_line;

	longest_line = 0;
	i = 0;
	while (str[i])
	{
		j = ft_strlen(str[i]);
		if (j > longest_line)
			longest_line = j;
		i++;
	}
	return (longest_line);
}

char	**ft_fill_spaces(char **str)
{
	t_norm	norm;

	norm.longest_line = ft_get_longest_line(str);
	norm.news = malloc(sizeof(char *) * (ft_strlen2d(str) + 1));
	if (!norm.news)
		(ft_putstr(2, "Error\nMalloc failed\n"), exit(1));
	norm.i = 0;
	while (str[norm.i])
	{
		norm.news[norm.i] = malloc(sizeof(char) * (norm.longest_line + 1));
		if (!norm.news[norm.i])
			(ft_putstr(2, "Error\nMalloc failed\n"), exit(1));
		norm.j = 0;
		while (str[norm.i][norm.j])
		{
			norm.news[norm.i][norm.j] = str[norm.i][norm.j];
			norm.j++;
		}
		while (norm.j < norm.longest_line)
			norm.news[norm.i][norm.j++] = ' ';
		norm.news[norm.i][norm.j] = '\0';
		norm.i++;
	}
	norm.news[norm.i] = NULL;
	return (norm.news);
}

void	check_conditions(t_norm n, int i, int j)
{
	if ((n.news[i][j] == '0' || n.news[i][j] == 'N' || n.news[i][j] == 'S'
			|| n.news[i][j] == 'W' || n.news[i][j] == 'E') && (n.news[i][j
			+ 1] == ' ' || n.news[i][j + 1] == '\t' || n.news[i][j - 1] == ' '
			|| n.news[i][j - 1] == '\t' || n.news[i][j + 1] == '\0'))
		ft_error_here(n.news);
	if ((n.news[i][j] == '0' || n.news[i][j] == 'N' || n.news[i][j] == 'S'
			|| n.news[i][j] == 'W' || n.news[i][j] == 'E') && (n.news[i
			+ 1][j] == ' ' || n.news[i + 1][j] == '\t' || n.news[i
			- 1][j] == ' ' || n.news[i - 1][j] == '\t' || n.news[i
			+ 1][j] == '\0' || n.news[i - 1][j] == '\0'))
		ft_error_here(n.news);
}

void	ft_check_0space(char **str)
{
	t_norm	n;
	int		i;
	int		j;

	n.news = ft_fill_spaces(str);
	ft_no_0_inlast(n.news[ft_strlen2d(n.news) - 1]);
	i = 1;
	while (n.news[i])
	{
		j = 1;
		while (n.news[i][j] && j < ft_strlen(n.news[i]) - 1)
		{
			check_conditions(n, i, j);
			j++;
		}
		i++;
	}
	ft_free_hna(n.news);
}
