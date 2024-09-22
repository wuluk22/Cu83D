/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:31 by clegros           #+#    #+#             */
/*   Updated: 2024/09/22 15:21:40 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

/*
int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	load_texture(t_env *e)
{
	load_image(e, e->texture[TEXTURE_NORTH], "textures/32.xpm");
	load_image(e, e->texture[TEXTURE_SOUTH], "textures/33.xpm");
	load_image(e, e->texture[TEXTURE_EAST], "textures/29.xpm");
	load_image(e, e->texture[TEXTURE_WEST], "textures/30.xpm");
}*/

void	load_image(t_env *e, int *texture, char *path)
{
	int		x;
	int		y;
	void	*img;
	int		*img_data;

	img = mlx_xpm_file_to_image(e->mlx, path, &e->img_width, &e->img_height);
	if (e->img_width != 64 || e->img_height != 64 || !img)
		exit(1);
	img_data = (int *)mlx_get_data_addr(img, &e->bpp, &e->sizeline, &e->endian);
	y = 0;
	while (y < e->img_height)
	{
		x = 0;
		while (x < e->img_width)
		{
			texture[64 * y + x] = img_data[e->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(e->mlx, img);
}

static void	draw(t_env *e)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		while (x < SCREEN_WIDTH)
		{
			e->data[y * SCREEN_WIDTH + x] = e->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

int	render_scene(t_env *e)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	color = 0;
	move_player(e);
	while (x < SCREEN_WIDTH)
	{
		compute_ray_direction(e, x);
		initialize_map_coordinates(e);
		compute_delta_distances(e);
		calculate_step_and_side_dist(e);
		perform_dda(e);
		compute_perpendicular_wall_distance(e);
		calculate_line_positions(e);
		draw_ceiling_and_floor(e, x);
		draw_wall(e, x, y, color);
		x++;
	}
	draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}
