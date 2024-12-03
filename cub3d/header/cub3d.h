/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:50:59 by lkazaz            #+#    #+#             */
/*   Updated: 2024/07/26 17:20:14 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
// # include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 700
# define HEIGHT 500

# define M_PI 3.14159265358979323846
# define KL 640

// Linux
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SPEDUP 65451
# define KEY_SPEDDOWN 65453
# define LEFT_CLICK 1
# define RIGHT_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5

// mini_map
# define TILE_SIZE 2

# define BONUS 1

typedef struct s_list
{
	void			*ptr;
	struct s_list	*next;
}					t_list;

typedef struct s_all
{
	t_list			*g_alloc;
}					t_all;

typedef struct s_cub
{
	int				fd;
	char			*line;

}					t_cub;

typedef struct s_line
{
	char			*str;
	char			*new;
	int				count_not_empty;
	struct s_line	*next;
}					t_line;

typedef struct s_map
{
	char			*no;
	char			*ea;
	char			*so;
	char			*we;
	char			*c;
	char			*f;

	int				c_hex;
	int				f_hex;

	unsigned int	ceiling;
	unsigned int	floor;

	int				fd_no;
	int				fd_ea;
	int				fd_so;
	int				fd_we;

	char			**map;
}					t_map;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_tex
{
	t_img			no;
	t_img			ea;
	t_img			so;
	t_img			we;
}					t_tex;

typedef struct s_minimap
{
	double			x0;
	double			y0;
	double			x1;
	double			y1;
	double			dx;
	double			dy;
	double			sx;
	double			sy;
	double			i;
	double			err;
	double			e2;
	int				ri;
}					t_minimap;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	void			*mlx_win1;
	void			*img;
	char			*addr;
	char			**map;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	double			start_p;
	double			d;
	double			v_x;
	double			v_y;
	double			h_x;
	double			h_y;

	double			x;
	double			y;
	double			ray;
	double			x_n;
	double			y_n;
	int				ver;

	char			side;

	t_map			*gmap;
	double			start_angle;
	double			start;
	double			end;
	int				*pixels;
	double			floor;
	double			sped;

	t_tex			*tex;

}					t_data;

typedef struct s_norm
{
	t_line			*new;
	t_line			*head;
	char			*line;
	char			*str;
	int				len;
	int				i;
	int				j;
	int				flag;
	int				flag2;
	char			**tab;
	int				r;
	int				g;
	int				b;
	int				color;
	int				nc;
	double			h_x;
	double			h_y;
	double			x_step;
	double			y_step;
	int				pixel;
	double			p_x;
	double			p_y;
	char			**news;
	int				longest_line;
}					t_norm;

typedef struct s_norminette
{
	int				j;
	int				color;
	double			wallheight;
	double			drawstart;
	double			drawend;
	double			hitx;
	double			hity;
}					t_norminette;

typedef struct s_norminette1
{
	int				i;
	int				j;
	int				k;
	char			*new;
	char			*snew;
}					t_norminette1;

typedef struct s_norminette2
{
	double			texpos;
	double			drawstart;
	int				texx;
	int				texy;
	char			*dst;
	int				color;
}					t_norminette2;

typedef struct s_norminette3
{
	char			*new_str;
	int				i;
	int				j;
	int				k;
}					t_norminette3;

int					ft_atoi(char *str);
char				*ft_substr(char *s, unsigned int start, size_t len);
char				**ft_split(char const *s, char c);
int					ft_strlen(char *str);
int					ft_lst_size(t_line *head);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, int n);
void				cub(t_map *map);
char				*ft_strtrim(char *s1);
void				ft_putstr(int fd, char *str);
int					ft_strlen2d(char **str);
t_data				ft_dimaps(char **map);
int					ft_max(int i, int j);
t_tex				*ft_get_xpm(t_data *data);
void				render_map(t_data *data);
void				ft_free(t_data *data);
void				ft_cubtext(t_data *data, t_map *map);
void				raycasting(t_data *data, double angle);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
double				ft_saving_angle(double angle);
int					ft_get_pixel(void *img, t_norminette e, char side);
int					is_wall(double x, double y, t_data *data);
void				ft_drawing(t_data *data, double ray, double andgle, int *i);
void				ft_updatemap(int key, t_data *data);
void				ft_key(int key, t_data *data);
int					key_hook(int key, t_data *data);
void				render_map(t_data *data);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				draw_filled_circle(t_data *data, int x_center, int y_center,
						int color);
void				init_player(t_data *data);
void				ft_horizontal_interception1(t_data *data, double angle);
double				ft_saving_angle(double angle);
void				ft_vertical_interception1(t_data *data, double angle);
void				draw(t_data *data, int x, int y, int color);
void				draw_minimap(t_data *data);
int					mouse_move(int x, int y, t_data *data);
int					rgb_to_int(int red, int green, int blue);
int					dir(double angle, char c);
void				check_valid_xpm(t_map *map);
void				ft_printf(t_map *map);
void				check_valid_01(t_map *map);
int					ft_check_name(char *str);
int					ft_check_line(char *line);
int					ft_check_first_line(char *line);
char				*ft_before_last_word(char *str);
int					ft_check_valid_map(char *str);
void				ft_set_cf(t_map *map, char *str);
t_map				*ft_fill_map(t_line *head, t_map *map);
void				ft_check_validity(char *str);
void				ft_helper(char **str, int i, int k, int j);
void				ft_check_0space(char **str);
char				*ft_read_rest(int fd, t_norm *norm, char *str);
void				ft_read_six_lines(int fd, t_norm *norm);
t_map				*ft_check_map(int fd, t_map *map);
int					ft_count_comma(char *str);
void				ft_check_path(t_map *map);
char				*ft_remove_names(char *str, char *name);
int					ft_set_color(char *str);

// ft_spaces.c
char				**ft_strdup2d(char **map);
void				ft_free_tmp(char **tmp);
void				check_valid_01(t_map *map);

void				ft_free_head(t_line *head);
void				ft_check_counter(char **str);
void				ft_check_char(char **tab);
int					ft_count_comma(char *str);
void				ft_error_here(char **str);
void				ft_free_hna(char **str);
int					ft_only_s(char *str);

#endif