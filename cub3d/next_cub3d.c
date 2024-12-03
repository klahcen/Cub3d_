/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:39:19 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/26 20:12:09 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cub3d.h"

t_data	ft_dimaps(char **map)
{
	int		i;
	int		width;
	t_data	data;

	width = 0;
	i = 0;
	while (map[i])
	{
		if (!map[i])
		{
			printf("errorr\n");
			exit(254);
		}
		if (width < ft_strlen(map[i]))
			width = ft_strlen(map[i]);
		i++;
	}
	data.height = i;
	data.width = width;
	return (data);
}

void	ft_error(char *str)
{
	printf("Error\n%s\n", str);
	exit(0);
}

void	ft_so_we(t_data *data, t_tex *tex)
{
	tex->so.img = mlx_xpm_file_to_image(data->mlx, data->gmap->so,
			&tex->so.width, &tex->so.height);
	if (!tex->so.img || tex->so.width != 64 || tex->so.height != 64)
		ft_error("Invalid so image");
	tex->so.addr = mlx_get_data_addr(tex->so.img, &tex->so.bits_per_pixel,
			&tex->so.line_length, &tex->so.endian);
	tex->we.img = mlx_xpm_file_to_image(data->mlx, data->gmap->we,
			&tex->we.width, &tex->we.height);
	if (!tex->we.img || tex->we.width != 64 || tex->we.height != 64)
		ft_error("Invalid we image");
	tex->we.addr = mlx_get_data_addr(tex->we.img, &tex->we.bits_per_pixel,
			&tex->we.line_length, &tex->we.endian);
	close(data->gmap->fd_no);
	close(data->gmap->fd_ea);
	close(data->gmap->fd_so);
	close(data->gmap->fd_we);
}

t_tex	*ft_get_xpm(t_data *data)
{
	t_tex	*tex;

	tex = malloc(sizeof(t_tex));
	tex->no.img = mlx_xpm_file_to_image(data->mlx, data->gmap->no,
			&tex->no.width, &tex->no.height);
	if (!tex->no.img || tex->no.width != 64 || tex->no.height != 64)
		ft_error("Invalid no image");
	tex->no.addr = mlx_get_data_addr(tex->no.img, &tex->no.bits_per_pixel,
			&tex->no.line_length, &tex->no.endian);
	tex->ea.img = mlx_xpm_file_to_image(data->mlx, data->gmap->ea,
			&tex->ea.width, &tex->ea.height);
	if (!tex->ea.img || tex->ea.width != 64 || tex->ea.height != 64)
		ft_error("Invalid ea image");
	tex->ea.addr = mlx_get_data_addr(tex->ea.img, &tex->ea.bits_per_pixel,
			&tex->ea.line_length, &tex->ea.endian);
	ft_so_we(data, tex);
	return (tex);
}

void	render_map(t_data *data)
{
	double	re;
	double	ray_angle;
	int		i;
	double	ray;

	re = 60.0 / WIDTH;
	ray = 0;
	ray_angle = data->start_angle - 30;
	i = 0;
	data->start = ray_angle;
	while (i < WIDTH - 1)
	{
		raycasting(data, ray_angle);
		ray_angle = ft_saving_angle(ray_angle);
		i++;
		if (i == WIDTH / 2)
			data->d = ray_angle * (M_PI / 180);
		ray = (data->ray) * cos((ray_angle - data->start_angle) * (M_PI / 180));
		ft_drawing(data, ray, ray_angle, &i);
		ray_angle += re;
	}
	data->end = ray_angle;
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}
