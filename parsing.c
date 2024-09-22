#include "includes/cub3D.h"

int	get_color(char *line, int t, t_env *e)
{
	char	*str;
	int		nbr[3];
	int		i;
	int		j;


	i = 0;
	while (i < 3)
	{
		j = 0;
		str = malloc(sizeof(char) * 4);
		while (line[t] != ',' && line[t] != '\n')
			str[j++] = line[t++];
		t++;
		str[j] = '\0';
//		nbr[i] = malloc(sizeof(int) * 4); // free
		nbr[i] = ft_atoi(str);
		if (nbr[i] < 0 || nbr[i] > 255)
			return (problem_found(e, line, 1));
//		str = NULL;
		i++;
	}
	return (nbr[0] << 16 | nbr[1] << 8 | nbr[2]);
}

int	get_texture(char *line, int id, t_env *e, int side)
{
	int 	i;
	char	*texture;

	(void)e;
	i = 0;
	texture = malloc(sizeof(char) * (ft_strlen(line))); // free
	id++;
	id++;
	while (line[id] != '\n')
		texture[i++] = line[id++];
	texture[i] = '\0';
	load_image(e, e->texture[side], texture);
    return (0);
}

int get_one_info(char *line, t_env *e, int infos)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (get_texture(line, 3, e, 0) != 0)
			return (1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (get_texture(line, 3, e, 1) != 0)
			return (1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (get_texture(line, 3, e, 3) != 0)
			return (1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (get_texture(line, 3, e, 2) != 0)
			return (1);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
		e->map.fc = get_color(line, 2, e);
	else if (ft_strncmp(line, "C ", 2) == 0)
		e->map.cc = get_color(line, 2, e);
    else if (line[0] == '\n')
		return (infos);
	else
		return (-1);
	return (0);
}

void get_info(t_env *e, int fd)
{
    char    *line;
    int     infos;

    infos = 0;
    line = get_next_line(fd);
	while (line && infos != 6 && infos >= 0)
	{
		if (get_one_info(line, e, infos) == 0)
			infos++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
    if (infos < 0)
    {
        close(fd);
        ft_exit(e, "No correct fd\n", 0);
    }
}

int	parsing(int argc, char **argv, t_map *map, t_env *e)
{
	int     fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
        ft_exit(e, "No fd\n", 0);
	if (argc != 2)
        ft_exit(e, "Not a number of arguments allowed\n", 0);
	printf("nmbr of argc ok\n");
    if (check_name(argv[1]) == 1)
		ft_exit(e, "Not a valid name\n", 0);
	printf("name of file ok\n");
	get_info(e, fd);
	printf("info ok\n");
	parse_map(e, map, fd);
	printf("map ok\n");
	return (0);
}

