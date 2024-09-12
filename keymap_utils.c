/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:07:29 by clegros           #+#    #+#             */
/*   Updated: 2024/09/11 10:07:32 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	move_forward_backward(t_env *e, double moveSpeed)
{
	if (e->keys[KEY_W])
	{
		if (e->map.worldMap[(int)(e->pos_x + e->dir_x * moveSpeed)] \
			[(int)(e->pos_y)] == 0)
			e->pos_x += e->dir_x * moveSpeed;
		if (e->map.worldMap[(int)(e->pos_x)] \
			[(int)(e->pos_y + e->dir_y * moveSpeed)] == 0)
			e->pos_y += e->dir_y * moveSpeed;
	}
	if (e->keys[KEY_S])
	{
		if (e->map.worldMap[(int)(e->pos_x - e->dir_x * moveSpeed)] \
			[(int)(e->pos_y)] == 0)
			e->pos_x -= e->dir_x * moveSpeed;
		if (e->map.worldMap[(int)(e->pos_x)] \
			[(int)(e->pos_y - e->dir_y * moveSpeed)] == 0)
			e->pos_y -= e->dir_y * moveSpeed;
	}
}

void	move_left_right(t_env *e, double moveSpeed)
{
	if (e->keys[KEY_A])
	{
		if (e->map.worldMap[(int)(e->pos_x - e->plane_x * moveSpeed)] \
			[(int)(e->pos_y)] == 0)
			e->pos_x -= e->plane_x * moveSpeed;
		if (e->map.worldMap[(int)(e->pos_x)] \
			[(int)(e->pos_y - e->plane_y * moveSpeed)] == 0)
			e->pos_y -= e->plane_y * moveSpeed;
	}
	if (e->keys[KEY_D])
	{
		if (e->map.worldMap[(int)(e->pos_x + e->plane_x * moveSpeed)] \
			[(int)(e->pos_y)] == 0)
			e->pos_x += e->plane_x * moveSpeed;
		if (e->map.worldMap[(int)(e->pos_x)] \
			[(int)(e->pos_y + e->plane_y * moveSpeed)] == 0)
			e->pos_y += e->plane_y * moveSpeed;
	}
}

void	rotate_left(t_env *e, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = e->dir_x;
	old_plane_x = e->plane_x;
	e->dir_x = e->dir_x * cos(rotSpeed) - e->dir_y * sin(rotSpeed);
	e->dir_y = old_dir_x * sin(rotSpeed) + e->dir_y * cos(rotSpeed);
	e->plane_x = e->plane_x * cos(rotSpeed) - e->plane_y * sin(rotSpeed);
	e->plane_y = old_plane_x * sin(rotSpeed) + e->plane_y * cos(rotSpeed);
}

void	rotate_right(t_env *e, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = e->dir_x;
	old_plane_x = e->plane_x;
	e->dir_x = e->dir_x * cos(-rotSpeed) - e->dir_y * sin(-rotSpeed);
	e->dir_y = old_dir_x * sin(-rotSpeed) + e->dir_y * cos(-rotSpeed);
	e->plane_x = e->plane_x * cos(-rotSpeed) - e->plane_y * sin(-rotSpeed);
	e->plane_y = old_plane_x * sin(-rotSpeed) + e->plane_y * cos(-rotSpeed);
}
