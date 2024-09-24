/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:36:17 by clegros           #+#    #+#             */
/*   Updated: 2024/09/24 12:52:08 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

static void	set_player_position(t_env *e, char direction, int row, int col)
{
	e->pos_x = row + 0.5;
	e->pos_y = col + 0.5;
	if (direction == 'N')
	{
		e->dir_x = -1;
		e->plane_y = 0.66;
	}
	else if (direction == 'S')
	{
		e->dir_x = 1;
		e->plane_y = -0.66;
	}
	else if (direction == 'E')
	{
		e->dir_y = 1;
		e->plane_x = 0.66;
	}
	else if (direction == 'W')
	{
		e->dir_y = -1;
		e->plane_x = -0.66;
	}
}

static void	process_character(t_env *e, char c, int row, int col)
{
	if (c == '1')
		e->map.world_map[row][col] = 1;
	else if (c == '0' || c == ' ')
		e->map.world_map[row][col] = 0;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		set_player_position(e, c, row, col);
		e->map.world_map[row][col] = 0;
	}
	//ft_putnbr_fd(e->map.world_map[row][col], 1);
}

static void	parse_line(t_env *e, char *line, int row)
{
	int		col;
	char	*trimmed_line;

	trimmed_line = ft_strdup(line);
	e->map.map_width[row] = ft_strlen(trimmed_line);
	e->map.world_map[row] = (int *)ft_calloc(e->map.map_width[row], sizeof(int));
	if (!e->map.world_map[row])
		exit(1);
	col = 0;
	while (trimmed_line[col])
	{
		process_character(e, trimmed_line[col], row, col);
		col++;
	}
	free(trimmed_line);
}

static void	resize_map(t_env *e)
{
	int		*new_map_width;
	int		**new_world_map;

	new_map_width = (int *)ft_calloc(e->map.map_height + 1, sizeof(int));
	new_world_map = (int **)ft_calloc(e->map.map_height + 1, sizeof(int *));
	if (!new_map_width || !new_world_map)
		exit(1);
	if (e->map.map_height > 0)
	{
		ft_memcpy(new_map_width, e->map.map_width, \
				e->map.map_height * sizeof(int));
		ft_memcpy(new_world_map, e->map.world_map, \
				e->map.map_height * sizeof(int *));
		free(e->map.map_width);
		free(e->map.world_map);
	}
	e->map.map_width = new_map_width;
	e->map.world_map = new_world_map;
}


void	load_map(t_env *e, const char *filename)
{
	int		fd;
	char	*line;
	int		row;
	char	*tmp_line;
	int		current_line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open map file");
		exit(1);
	}
	current_line = 0;
	row = 0;
	while (1)
	{
		tmp_line = get_next_line(fd);
		if (tmp_line == NULL)
			break ;
		if (current_line++ < e->i)
		{
			free(tmp_line);
			continue;
		}
		line = tmp_line;
		resize_map(e);
		parse_line(e, line, row);
		e->map.map_height++;
		free(line);
		row++;
	}
	close(fd);
}

void	display_map(int **map, int map_height, int *map_width)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width[i])
		{
			ft_putnbr_fd(map[i][j], 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}
