/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:03:44 by clegros           #+#    #+#             */
/*   Updated: 2024/09/24 14:24:53 by alion            ###   ########.fr       */
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
	e->map.world_map = NULL;
}
int	size_fd(char ** argv, t_env *e)
{
	int		i;
	int		fd;
	char	*line;

	printf("A\n");
	i = 1;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit(e, "No fd\n", 0);
	line = get_next_line(fd);
	printf("B\n");
	while (line != NULL)
	{
		printf("%d\n", i);
		i++;
		if (line == NULL)
			break ;
		line = get_next_line(fd);
	}
	printf("C\n");
	close(fd);
	printf("D\n");
	return (i);
}

int	main(int argc, char **argv)
{
	t_env	e;
	t_map	map;
	int		i;

	e.mlx = mlx_init();
	if (!e.mlx)
		ft_exit(&e, "Problem with data.mlx", 0);
	i = size_fd(argv, &e);
	map.map = ft_calloc((i), sizeof(char *)); // a modifier pour la bonne taille aml
	if (!map.map)
		ft_exit(&e, "Problem with map.map", 0);
	parsing(argc, argv, &map, &e);
	e.win = mlx_new_window(e.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	e.img = mlx_new_image(e.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	e.data = (int *)mlx_get_data_addr(e.img, &e.bpp, &e.sizeline, &e.endian);
	init(&e);
	load_map(&e, "map.cub"); // a modifier pour avoir avec argument
	display_map(e.map.world_map, e.map.map_height, e.map.map_width);
//	load_texture(&e);
	mlx_hook(e.win, 2, 1L << 0, key_press, &e);
	mlx_hook(e.win, 3, 1L << 1, key_release, &e);
	//mlx_hook(e.win, 6, 0, mouse_hook, &e);
	mlx_loop_hook(e.mlx, render_scene, &e);
	mlx_loop(e.mlx);
	//mlx_mouse_hide(e.mlx, e.win);
	//printf("-----%f------%f\n", e.pos_x, e.pos_y);
	return (0);
}
