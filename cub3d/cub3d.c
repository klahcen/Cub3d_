/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:38:37 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/26 20:14:32 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

int	ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	exit(0);
}

void	ft_get_pos_p(t_data *data, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W' \
				|| map[y][x] == 'E')
			{
				data->x_n = x;
				data->y_n = y;
				data->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

void	cub(t_map *map)
{
	t_data	data;

	data = ft_dimaps(map->map);
	data.floor = 0;
	data.sped = 1;
	data.map = map->map;
	data.gmap = map;
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3d");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	data.tex = ft_get_xpm(&data);
	init_player(&data);
	ft_get_pos_p(&data, map->map);
	render_map(&data);
	mlx_hook(data.mlx_win, 02, 1L >> 0, key_hook, &data);
	mlx_hook(data.mlx_win, 17, 0, ft_close, &data);
	mlx_loop(data.mlx);
}
