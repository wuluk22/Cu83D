/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:25 by clegros           #+#    #+#             */
/*   Updated: 2024/09/22 15:16:28 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	calculate_step_and_side_dist(t_env *e)
{
	if (e->ray_dir_x < 0)
	{
		e->step_x = -1;
		e->side_dist_x = (e->pos_x - e->map_x) * fabs(1 / e->ray_dir_x);
	}
	else
	{
		e->step_x = 1;
		e->side_dist_x = (e->map_x + 1.0 - e->pos_x) * fabs(1 / e->ray_dir_x);
	}
	if (e->ray_dir_y < 0)
	{
		e->step_y = -1;
		e->side_dist_y = (e->pos_y - e->map_y) * fabs(1 / e->ray_dir_y);
	}
	else
	{
		e->step_y = 1;
		e->side_dist_y = (e->map_y + 1.0 - e->pos_y) * fabs(1 / e->ray_dir_y);
	}
}

void	perform_dda(t_env *e)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (e->side_dist_x < e->side_dist_y)
		{
			e->side_dist_x += e->delta_dist_x;
			e->map_x += e->step_x;
			e->side = 0;
		}
		else
		{
			e->side_dist_y += e->delta_dist_y;
			e->map_y += e->step_y;
			e->side = 1;
		}
		if (e->map_x >= 0 && e->map_x < e->map.map_height && \
				e->map_y >= 0 && e->map_y < e->map.map_width[e->map_x])
			if (e->map.worldMap[e->map_x][e->map_y] > 0)
				hit = 1;
	}
}

void	calculate_line_positions(t_env *e)
{
	e->line_height = (int)(SCREEN_HEIGHT / e->perp_wall_dist);
	e->draw_start = -e->line_height / 2 + SCREEN_HEIGHT / 2;
	if (e->draw_start < 0)
		e->draw_start = 0;
	e->draw_end = e->line_height / 2 + SCREEN_HEIGHT / 2;
	if (e->draw_end >= SCREEN_HEIGHT)
		e->draw_end = SCREEN_HEIGHT - 1;
}

void	draw_ceiling_and_floor(t_env *e, int x)
{
	int	y;

	y = 0;
	while (y < e->draw_start)
	{
		if (y >= 0 && y < SCREEN_HEIGHT)
			e->data[y * SCREEN_WIDTH + x] = e->map.cc;
		y++;
	}
	y = e->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		if (y >= 0 && y < SCREEN_HEIGHT)
			e->data[y * SCREEN_WIDTH + x] = e->map.fc;
		y++;
	}
}

void	compute_ray_direction(t_env *e, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	e->ray_dir_x = e->dir_x + e->plane_x * camera_x;
	e->ray_dir_y = e->dir_y + e->plane_y * camera_x;
}
