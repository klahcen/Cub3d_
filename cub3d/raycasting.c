/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:10:23 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/26 20:22:46 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

int	inter(double angle, double *inter, double *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += KL;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += KL;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	is_wall(double x, double y, t_data *data)
{
	double	x_m;
	double	y_m;

	x_m = 0;
	y_m = 0;
	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / KL);
	y_m = floor(y / KL);
	if ((y_m >= data->height || x_m >= data->width))
		return (0);
	if (data->map[(int)y_m] && x_m <= (int)ft_strlen(data->map[(int)y_m]))
		if (data->map[(int)y_m][(int)x_m] == '1')
			return (0);
	return (1);
}

double	ft_horizontal_interception(t_data *data, double angle)
{
	double	h_x;
	double	h_y;
	int		pixel;
	t_norm	norm;

	norm.p_x = data->x_n * KL;
	norm.p_y = data->y_n * KL;
	norm.y_step = KL;
	norm.x_step = KL / tan(angle);
	h_y = floor(norm.p_y / KL) * KL;
	pixel = inter(angle, &h_y, &norm.y_step, 1);
	h_x = norm.p_x + (h_y - norm.p_y) / tan(angle);
	if ((dir(angle, 'y') && norm.x_step > 0) || (!dir(angle, 'y')
			&& norm.x_step < 0))
	{
		norm.x_step *= -1;
	}
	while (is_wall(h_x, h_y - pixel, data))
	{
		h_x += norm.x_step;
		h_y += norm.y_step;
	}
	data->h_x = h_x;
	data->h_y = h_y;
	return (sqrt(pow(h_x - norm.p_x, 2) + pow(h_y - norm.p_y, 2)));
}

double	ft_vertical_interception(t_data *data, double angle)
{
	double	v_x;
	double	v_y;
	int		pixel;
	t_norm	norm;

	norm.p_x = data->x_n * KL;
	norm.p_y = data->y_n * KL;
	norm.x_step = KL;
	norm.y_step = KL * tan(angle);
	v_x = floor(norm.p_x / KL) * KL;
	pixel = inter(angle, &v_x, &norm.x_step, 0);
	v_y = norm.p_y + (v_x - norm.p_x) * tan(angle);
	if ((dir(angle, 'x') && norm.y_step < 0) || (!dir(angle, 'x')
			&& norm.y_step > 0))
	{
		norm.y_step *= -1;
	}
	while (is_wall(v_x - pixel, v_y, data))
	{
		v_x += norm.x_step;
		v_y += norm.y_step;
	}
	data->v_x = v_x;
	data->v_y = v_y;
	return (sqrt(pow(v_x - norm.p_x, 2) + pow(v_y - norm.p_y, 2)));
}

void	raycasting(t_data *data, double angle)
{
	double	x1;
	double	y1;

	x1 = 0;
	y1 = 0;
	angle = angle * M_PI / 180.0;
	angle = ft_saving_angle(angle);
	x1 = ft_horizontal_interception(data, angle);
	y1 = ft_vertical_interception(data, angle);
	if (x1 > y1)
	{
		data->ver = 0;
		data->ray = y1 / KL;
		data->x = data->v_x / KL;
		data->y = data->v_y / KL;
	}
	else
	{
		data->ver = 1;
		data->ray = x1 / KL;
		data->x = data->h_x / KL;
		data->y = data->h_y / KL;
	}
}
