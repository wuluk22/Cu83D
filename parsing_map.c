#include "includes/cub3D.h"

int	verif_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < map->x_map_size)
	{
		while (y < map->y_map_size)
		{
			if (map->map[y][x] != '1' && map->map[y][x] != '0'
				&& map->map[y][x] != ' ' && map->map[y][x] != 'E'
				&& map->map[y][x] != 'N' && map->map[y][x] != 'S'
				&& map->map[y][x] != 'W')
				return (1);
			printf("%c", map->map[x][y]);
			y++;
		}
		x++;
	}
	printf("\n\n");
	return (0);
}

void	get_map(t_env *e, t_map *map, int fd)
{
	int	length_of_a_line;

	(void)e;
	map->y = -1;
	map->x_map_size = 0;
	while (1)
	{
		map->y++;
		map->map[map->y] = get_next_line(fd);
		printf("%s", map->map[map->y]);
		if (!map->map[map->y])
			break ;
		length_of_a_line = (int)(ft_strlen(map->map[map->y]));
		if (length_of_a_line > map->x_map_size)
			map->x_map_size = length_of_a_line;
	}
	map->y_map_size = map->y;
	close(fd);
}

int	parse_map(t_env *e, t_map *map, int fd)
{
	get_map(e, map, fd);
	if (verif_map(map) != 0)
		return (1);
	return (0);
}
