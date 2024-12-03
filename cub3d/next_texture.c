/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:55:57 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/15 18:57:09 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	ft_saving_angle(double angle)
{
	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;
	return (angle);
}

int	ft_get_pixel(void *img, t_norminette e, char side)
{
	t_norminette2	n;

	n.texpos = 0;
	if (side == 'N' || side == 'S')
		n.texpos = e.hitx;
	else if (side == 'E' || side == 'W')
		n.texpos = e.hity;
	n.drawstart = -e.wallheight / 2 + HEIGHT / 2;
	n.texx = (int)(n.texpos * 64) % 64;
	n.texy = (int)((e.j - n.drawstart) * 64 / e.wallheight) % 64;
	n.dst = img + (n.texy * 64 + n.texx) * 4;
	n.color = *(unsigned int *)n.dst;
	return (n.color);
}

int	ft_max(int i, int j)
{
	if (i > j)
		return (i);
	else
		return (j);
}

int	dir(double angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}
