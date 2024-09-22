#include "includes/cub3D.h"

int problem_found(t_env *e, char *line, int i)
{
        free(line);
        free_struct(e);
		return (i);
}

void	ft_exit(t_env *e, char *str, int i)
{
	(void)e;
	(void)i;
	printf("Error\n");
	printf("%s", str);
//	if (i == 1)
//		ft_exit_window(e);
//	else
		exit (1);
}

void	free_map(char **map, int i)
{
	int	j;

	j = 0;
	while (map[j])
	{
		free(map[j]);
		map[j] = NULL;
		j++;
	}
	free(map);
	if (i == 1)
		exit (1);
}

int	check_name(char *map_name)
{
	if (ft_strnstr(map_name, ".cub\0", ft_strlen(map_name)))
		return (0);
	return (1);
}


void	free_struct(t_env *e)
{
	int	i;

	i = 0;
	if (e->map.map)
		while (e->map.map[i])
			free(e->map.map[i++]);
	free(e->map.map);
//	if (e->img)
//		mlx_delete_image(e->mlx, e->img);
//	mlx_terminate(e->mlx);
	exit (0);
}
