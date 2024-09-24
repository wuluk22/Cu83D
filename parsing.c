/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:51:23 by alion             #+#    #+#             */
/*   Updated: 2024/09/24 13:06:43 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	init(t_env *e)
{
	e->map.no = 0;
	e->map.so = 0;
	e->map.ea = 0;
	e->map.we = 0;
	e->map.fc = 0;
	e->map.cc = 0;
}

int	parse_map(t_env *e, t_map *map, int fd)
{
	get_map(e, map, fd);
	close(fd);
	if (check_inside(map) != 0)
		return (1);
	if (check_perso(map) != 0)
		return (1);
	if (check_border(map) != 0)
		return (1);
	return (0);
}

int	parsing(int argc, char **argv, t_map *map, t_env *e)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit(e, "No fd\n", 0);
	if (argc != 2)
		ft_exit(e, "Not a number of arguments allowed\n", 0);
	printf("nmbr of argc ok\n");
	if (check_name(argv[1]) == 1)
		ft_exit(e, "Not a valid name\n", 0);
	printf("name of file ok\n");
	init(e);
	if (get_info(e, fd) == 1)
		ft_exit(e, "No good info\n", 0);
	printf("info ok\n");
	if (parse_map(e, map, fd) != 0)
		ft_exit(e, "Not a valid map\n", 0);
	free_map(map->map);
	printf("map ok\n");
	return (0);
}
