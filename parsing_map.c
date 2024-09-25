/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:18:58 by alion             #+#    #+#             */
/*   Updated: 2024/09/25 13:52:29 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	recursive(t_map *map, int x, int y)
{
	if (!map->map[y] || !map->map[y][x] || (x == 0 && map->map[y][x] == '0')
		|| (y == 0 && map->map[y][x] == '0') || map->map[y][x] == ' '
		|| map->map[y][x] == '\n' || map->map[y][x] == '\0')
		return (1);
	else if (map->map[y][x] == '0' || map->map[y][x] == 'N'
		|| map->map[y][x] == 'S' || map->map[y][x] == 'E'
		|| map->map[y][x] == 'W')
	{
		map->map[y][x] = '1';
		if (recursive(map, x, y - 1) != 0)
			return (1);
		if (recursive(map, x + 1, y) != 0)
			return (1);
		if (recursive(map, x, y + 1) != 0)
			return (1);
		if (recursive(map, x - 1, y) != 0)
			return (1);
	}
	return (0);
}

int	check_border(t_map *map)
{
	int		x;
	int		y;

	y = -1;
	while (++y < map->y_map_size)
	{
		x = -1;
		while (map->map[y][++x] != '\n')
		{
			if (map->map[y][x] == '0' || map->map[y][x] == 'N'
				|| map->map[y][x] == 'S' || map->map[y][x] == 'E'
				|| map->map[y][x] == 'W')
			{
				if (recursive(map, x, y) == 1)
					return (1);
			}
		}
	}
	return (0);
}

int	check_perso(t_map *map)
{
	int		y;
	int		x;
	int		perso;

	perso = 0;
	y = -1;
	while (++y < map->y_map_size)
	{
		x = -1;
		while (map->map[y][++x] != '\n')
		{
			if (map->map[y][x] == 'E' || map->map[y][x] == 'N'
				|| map->map[y][x] == 'S' || map->map[y][x] == 'W')
				perso++;
		}
	}
	if (perso != 1)
		return (1);
	return (0);
}

int	check_inside(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->y_map_size)
	{
		x = -1;
		while (map->map[y][++x] != '\n')
		{
			if (map->map[y][x] != '1' && map->map[y][x] != '0'
				&& map->map[y][x] != ' ' && map->map[y][x] != 'E'
				&& map->map[y][x] != 'N' && map->map[y][x] != 'S'
				&& map->map[y][x] != 'W' && map->map[y][x] != '\t')
				return (1);
		}
	}
	return (0);
}

void	get_map(t_env *e, t_map *map, int fd)
{
	int		length_of_a_line;
	char	*line;

	(void)e;
	map->y = 0;
	map->x_map_size = 0;
	line = get_next_line(fd);
	while (line[0] == '\n')
	{
		line = get_next_line(fd);
		e->i++;
	}
	map->map[map->y] = line;
	while (1)
	{
		map->y++;
		map->map[map->y] = get_next_line(fd);
		if (!map->map[map->y])
			break ;
		map->map[map->y][ft_strlen(map->map[map->y]) + 1] = '\n';
		length_of_a_line = (int)(ft_strlen(map->map[map->y]));
		if (length_of_a_line > map->x_map_size)
			map->x_map_size = length_of_a_line;
	}
	map->y_map_size = map->y;
}
