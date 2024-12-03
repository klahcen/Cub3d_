/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_moving.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:56:20 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/26 20:14:27 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

int	key_hook(int key, t_data *data)
{
	ft_key(key, data);
	mlx_clear_window(data->mlx, data->mlx_win);
	render_map(data);
	return (0);
}

void	ft_next_init(t_data *data, char c)
{
	if (c == 'N')
		data->start_angle = 270;
	else if (c == 'S')
		data->start_angle = 90;
	else if (c == 'E')
		data->start_angle = 0;
	else if (c == 'W')
		data->start_angle = 180;
}

void	init_player(t_data *data)
{
	int		y;
	char	c;
	int		x ;
	char	**map;

	map = data->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || \
				map[y][x] == 'W' || map[y][x] == 'E')
			{
				c = map[y][x];
				ft_next_init(data, c);
			}
			x++;
		}
		y++;
	}
}
