/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:14:37 by ysaber            #+#    #+#             */
/*   Updated: 2024/07/15 18:20:08 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

int	ft_next(t_data *data, t_norminette e, double angle)
{
	if (cos((angle) * (M_PI / 180)) > 0)
	{
		data->side = 'W';
		e.color = ft_get_pixel(data->tex->we.addr, e, data->side);
	}
	else if (cos((angle) * (M_PI / 180)) < 0)
	{
		data->side = 'E';
		e.color = ft_get_pixel(data->tex->ea.addr, e, data->side);
	}
	return (e.color);
}

int	ft_next1(t_data *data, t_norminette e, double angle)
{
	if (sin((angle) * (M_PI / 180)) > 0)
	{
		data->side = 'S';
		e.color = ft_get_pixel(data->tex->so.addr, e, data->side);
	}
	else if (sin((angle) * (M_PI / 180)) < 0)
	{
		data->side = 'N';
		e.color = ft_get_pixel(data->tex->no.addr, e, data->side);
	}
	return (e.color);
}

void	ft(t_data *data, double angle, int *i, t_norminette e)
{
	if (data->ver == -1)
		e.color = 0;
	else if (data->ver == 0)
		e.color = ft_next(data, e, angle);
	else if (data->ver == 1)
		e.color = ft_next1(data, e, angle);
	my_mlx_pixel_put(data, *i, e.j, e.color);
}

void	ft_drawing(t_data *data, double ray, double angle, int *i)
{
	t_norminette	e;

	e.j = 0;
	e.wallheight = 1.2 * HEIGHT / ray;
	e.drawstart = -e.wallheight / 2 + HEIGHT / 2;
	e.drawend = e.wallheight / 2 + HEIGHT / 2;
	if (e.drawstart < 0)
		e.drawstart = 0;
	if (e.drawend >= HEIGHT)
		e.drawend = HEIGHT - 1;
	e.hitx = data->x;
	e.hity = data->y;
	while (e.j < HEIGHT)
	{
		if (e.j < e.drawstart)
			my_mlx_pixel_put(data, *i, e.j, data->gmap->ceiling);
		else if (e.j >= e.drawstart && e.j <= e.drawend)
			ft(data, angle, i, e);
		else
			my_mlx_pixel_put(data, *i, e.j, data->gmap->floor);
		e.j++;
	}
}
