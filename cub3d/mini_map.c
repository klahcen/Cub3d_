/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: /0 01:05:56 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/10 02:33:53 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

void	draw(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < ft_strlen(data->map[y]))
		{
			if (data->map[y][x] == '1')
			{
				draw(data, x * TILE_SIZE, y * TILE_SIZE, 0xEB5B00);
			}
			else if (data->map[y][x] == '0')
				draw(data, x * TILE_SIZE, y * TILE_SIZE, 0x151515);
			x++;
		}
		y++;
	}
	draw_filled_circle(data, data->x_n * TILE_SIZE, data->y_n * TILE_SIZE,
		0xFFFFFF);
}

int	ft_only_s(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
