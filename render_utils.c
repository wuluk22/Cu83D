/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:02:56 by clegros           #+#    #+#             */
/*   Updated: 2024/09/11 09:02:58 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	initialize_map_coordinates(t_env *e)
{
	e->map_x = (int)e->pos_x;
	e->map_y = (int)e->pos_y;
}

void	compute_delta_distances(t_env *e)
{
	if (e->ray_dir_x == 0)
		e->delta_dist_x = 1e30;
	else
		e->delta_dist_x = fabs(1 / e->ray_dir_x);
	if (e->ray_dir_y == 0)
		e->delta_dist_y = 1e30;
	else
		e->delta_dist_y = fabs(1 / e->ray_dir_y);
}

void	compute_perpendicular_wall_distance(t_env *e)
{
	if (e->side == 0)
		e->perp_wall_dist = (e->map_x - e->pos_x + (1 - e->step_x) / 2)
			/ e->ray_dir_x;
	else
		e->perp_wall_dist = (e->map_y - e->pos_y + (1 - e->step_y) / 2)
			/ e->ray_dir_y;
}

static int	*walls_texture(t_env *e, int *texture)
{
	if (e->side == 0 && e->ray_dir_x > 0)
		texture = e->texture[TEXTURE_SOUTH];
	else if (e->side == 0 && e->ray_dir_x < 0)
		texture = e->texture[TEXTURE_NORTH];
	else if (e->side == 1 && e->ray_dir_y > 0)
		texture = e->texture[TEXTURE_EAST];
	else
		texture = e->texture[TEXTURE_WEST];
	return (texture);
}

void	draw_wall(t_env *e, int x, int y, int color)
{
	int		tx_x;
	int		tx_y;
	int		d;
	double	wall_x;
	int		*texture;

	texture = 0;
	if (e->side == 0)
		wall_x = e->pos_y + e->perp_wall_dist * e->ray_dir_y;
	else
		wall_x = e->pos_x + e->perp_wall_dist * e->ray_dir_x;
	wall_x -= floor(wall_x);
	texture = walls_texture(e, texture);
	tx_x = (int)(wall_x * (double)64);
	y = e->draw_start;
	while (y < e->draw_end)
	{
		d = (y * 256 - SCREEN_HEIGHT * 128 + e->line_height * 128);
		tx_y = ((d * 64) / e->line_height) / 256;
		color = texture[64 * tx_y + tx_x];
		e->data[y++ *SCREEN_WIDTH + x] = color;
	}
}
