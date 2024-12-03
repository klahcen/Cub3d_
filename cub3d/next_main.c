/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:36 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/20 08:06:26 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

int	ft_check_line(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
		{
			flag = 1;
			return (1);
		}
		i++;
	}
	if (flag == 0)
		return (-1);
	return (0);
}

int	ft_check_first_line(char *line)
{
	int	i;

	if (!line)
		return (-1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '\t')
			return (-1);
		i++;
	}
	return (0);
}

char	*ft_before_last_word(char *str)
{
	int		i;
	int		j;
	char	*last_line;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
		i--;
	while (str[i] != '\n' && str[i] != '\t')
		i--;
	i++;
	last_line = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!last_line)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		last_line[j] = str[i];
		i++;
		j++;
	}
	last_line[j - 1] = '\0';
	return (last_line);
}

void	ft_check_counter(char **str)
{
	int	i;
	int	a;
	int	j;

	i = 0;
	a = 0;
	j = 0;
	while (str[j])
	{
		i = 0;
		while (str[j][i])
		{
			if (str[j][i] == 'N' || str[j][i] == 'S' || str[j][i] == 'W'
				|| str[j][i] == 'E')
				a++;
			i++;
		}
		j++;
	}
	if (a != 1)
	{
		ft_putstr(2, "Error\nInvalid map\n");
		exit(1);
	}
}

int	ft_check_valid_map(char *str)
{
	char	*first_line;
	char	*last_line;
	int		i;

	first_line = NULL;
	last_line = NULL;
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	first_line = ft_substr(str, 0, i);
	last_line = ft_before_last_word(str);
	if (ft_check_first_line(first_line) == -1
		|| ft_check_first_line(last_line) == -1)
	{
		free(first_line);
		free(last_line);
		return (-1);
	}
	free(first_line);
	free(last_line);
	return (0);
}
