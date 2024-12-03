/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:31:13 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/15 18:21:37 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

void	draw_filled_circle(t_data *data, int x_center, int y_center, int color)
{
	int	x;
	int	y;
	int	radius;
	int	sqr_radius;

	radius = TILE_SIZE / 2;
	sqr_radius = radius * radius;
	x = x_center - radius;
	while (x <= x_center + radius)
	{
		y = y_center - radius;
		while (y <= y_center + radius)
		{
			if ((x - x_center) * (x - x_center) + (y - y_center) \
				* (y - y_center) <= sqr_radius)
				my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

void	check_move(t_data *ptr, double y, double x)
{
	if (ptr->y_n + (y) > ptr->height || ptr->x_n + (x) > ptr->width \
		|| ptr->y_n + y < 0 || ptr->x_n + x < 0)
		return ;
	if (ptr->map[(int)(ptr->y_n)][(int)(ptr->x_n + (x))] == '0' )
		ptr->x_n += x;
	if (ptr->map[(int)(ptr->y_n + y)][(int)(ptr->x_n)] == '0')
		ptr->y_n += y;
}

void	ft_next_up(t_data *data, int key)
{
	double	i;
	double	j;

	if (key == KEY_D)
	{
		i = data->sped * sin(data->d + 1.5707963268);
		j = data->sped * cos(data->d + 1.5707963268);
		check_move(data, i, j);
	}
	else if (key == KEY_A)
	{
		i = -data->sped * sin(data->d + 1.5707963268);
		j = -data->sped * cos(data->d + 1.5707963268);
		check_move(data, i, j);
	}
}

void	ft_updatemap(int key, t_data *data)
{
	double	i;
	double	j;

	i = 0;
	j = 0;
	data->start_angle = ft_saving_angle(data->start_angle);
	data->sped = 0.2;
	if (key == KEY_W)
	{
		i = data->sped * sin(data->d);
		j = data->sped * cos(data->d);
		check_move(data, i, j);
	}
	else if (key == KEY_S)
	{
		i = -data->sped * sin(data->d);
		j = -data->sped * cos(data->d);
		check_move(data, i, j);
	}
	else if (key == KEY_D || key == KEY_A)
		ft_next_up(data, key);
}

void	ft_key(int key, t_data *data)
{
	if (key == KEY_LEFT)
		data->start_angle -= 10;
	if (key == KEY_RIGHT)
		data->start_angle += 10;
	if (key == KEY_SPEDDOWN)
		data->sped -= 0.0002;
	if (key == KEY_SPEDUP)
		data->sped += 0.0002;
	if (data->sped <= 0)
		data->sped = 0.02;
	ft_updatemap(key, data);
	if (key == KEY_ESC)
	{
		exit(0);
	}
}
