/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:03:44 by clegros           #+#    #+#             */
/*   Updated: 2024/08/27 10:04:27 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

static void	init(t_env *e)
{
	e->keys[KEY_W] = 0;
	e->keys[KEY_A] = 0;
	e->keys[KEY_S] = 0;
	e->keys[KEY_D] = 0;
	e->keys[KEY_LEFT] = 0;
	e->keys[KEY_RIGHT] = 0;
	e->pos_x = 0;
	e->pos_y = 0;
	e->dir_x = 0;
	e->dir_y = 0;
	e->plane_x = 0;
	e->plane_y = 0;
	e->map_height = MAP_HEIGHT;
	e->map_width = MAP_WIDTH;
	e->map.map_height = 0;
	e->map.map_width = NULL;
	e->map.worldMap = NULL;
}

int	main(void)
{
	t_env	e;

	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	e.img = mlx_new_image(e.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	e.data = (int *)mlx_get_data_addr(e.img, &e.bpp, &e.sizeline, &e.endian);
	init(&e);
	load_map(&e, "map.cub");
	display_map(e.map.worldMap, e.map.map_height, e.map.map_width);
	load_texture(&e);
	mlx_hook(e.win, 2, 1L << 0, key_press, &e);
	mlx_hook(e.win, 3, 1L << 1, key_release, &e);
	//mlx_hook(e.win, 6, 0, mouse_hook, &e);
	mlx_loop_hook(e.mlx, render_scene, &e);
	mlx_loop(e.mlx);
	//mlx_mouse_hide(e.mlx, e.win);
	//printf("-----%f------%f\n", e.pos_x, e.pos_y);
	return (0);
}
