/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:03:26 by clegros           #+#    #+#             */
/*   Updated: 2024/09/25 09:20:05 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../utils/libft.h"
# include "../utils/get_next_line/ft_get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define TEXTURE_NORTH 0
# define TEXTURE_SOUTH 1
# define TEXTURE_EAST 2
# define TEXTURE_WEST 3

typedef struct s_map
{
	int		**world_map;
	int		map_height;
	int		*map_width;
	char	**map; //alion
	int		x;
	int		y;
	int		player;
	int		floor;
	int		ceiling;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		fc;
	int		cc;
	int		x_map_size;
	int		y_map_size;
}	t_map;

typedef struct s_env
{
	int		i;
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
	int		bpp;
	int		sizeline;
	int		endian;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		side;
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	perp_wall_dist;
	double	map_height;
	double	map_width;
	int		keys[256];
	int		buf[SCREEN_HEIGHT][SCREEN_WIDTH];
	int		texture[4][64 * 64];
	int		img_width;
	int		img_height;
	double	wall_x;
	t_map	map;
}	t_env;

void	cleanup(t_map map);
//-----------keymap_utils.c
void	move_forward_backward(t_env *e, double moveSpeed);
void	move_left_right(t_env *e, double moveSpeed);
void	rotate_left(t_env *e, double rotSpeed);
void	rotate_right(t_env *e, double rotSpeed);
//-----------keymap.c
int		mouse_hook(int x, int y, t_env *e);
int		key_press(int keycode, t_env *e);
int		key_release(int keycode, t_env *e);
void	move_player(t_env *e);
//-----------parsing_help.c
void	ft_exit(t_map map, char *str, int i);
void	free_map(char **map);
int		check_name(char *map_name);
//-----------parsing_info.c
int		get_info(t_env *e, int fd);
//-----------parsing_map.c
int		recursive(t_map *map, int x, int y);
int		check_border(t_map *map);
int		check_perso(t_map *map);
int		check_inside(t_map *map);
void	get_map(t_env *e, t_map *map, int fd);
//-----------parsing.c
int		parsing(int argc, char **argv, t_map *map, t_env *e);
//-----------map.c
void	load_map(t_env *e, const char *filename);
void	display_map(int **map, int map_height, int *map_width);
//-----------map_utils.c
void	set_player_position(t_env *e, char direction, int row, int col);
void	process_character(t_env *e, char c, int row, int col);
void	parse_line(t_env *e, char *line, int row);
void	resize_map(t_env *e);
int		skip_and_open_file(const char *filename, int start_line);
//-----------raycasting.c
void	calculate_step_and_side_dist(t_env *e);
void	perform_dda(t_env *e);
void	calculate_line_positions(t_env *e);
void	draw_ceiling_and_floor(t_env *e, int x);
void	compute_ray_direction(t_env *e, int x);
//-----------render_utils.c
void	initialize_map_coordinates(t_env *e);
void	compute_delta_distances(t_env *e);
void	compute_perpendicular_wall_distance(t_env *e);
void	draw_wall(t_env *e, int x, int y, int color);
//-----------render.c
int		create_rgb(int r, int g, int b);
void	load_texture(t_env *e);
int		load_image(t_env *e, int *texture, char *path);
int		render_scene(t_env *e);

#endif
