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
		nbr[i] = ft_atoi(str);
		free(str);
		if (nbr[i] < 0 || nbr[i] > 255)
			return (problem_found(e, line, 1));
		printf("%d\n", nbr[i]);
		i++;
	}
	printf("A\n");
	return (nbr[0] << 16 | nbr[1] << 8 | nbr[2]);
}

int	put_texture(char *line, int id, t_env *e, int side)
{
	int		i;
	char	*texture;

	i = 0;
	id++;
	id++;
	texture = malloc(sizeof(char) * (ft_strlen(line))); // free
	while (line[id] != '\n')
		texture[i++] = line[id++];
	texture[i] = '\0';
	load_image(e, e->texture[side], texture);
	free(texture);
	return (0);
}

int	get_texture(char *line, t_env *e)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		e->map.no++;
		if (put_texture(line, 3, e, 0) != 0)
			return (1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		e->map.so++;
		if (put_texture(line, 3, e, 1) != 0)
			return (1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		e->map.we++;
		if (put_texture(line, 3, e, 3) != 0)
			return (1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		e->map.ea++;
		if (put_texture(line, 3, e, 2) != 0)
			return (1);
	}
	return (0);
}

int	get_one_info(char *line, t_env *e, int infos)
{
	if (ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		if (get_texture(line, e) != 0)
			return (1);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		e->map.fc++;
		e->map.floor = get_color(line, 2, e);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		e->map.cc++;
		e->map.ceiling = get_color(line, 2, e);
	}
	else if (line[0] == '\n')
		return (infos);
	else
		return (-1);
	return (0);
}

int	get_info(t_env *e, int fd)
{
	char	*line;
	int		infos;

	infos = 0;
	line = get_next_line(fd);
	while (line && infos != 6 && infos >= 0)
	{
		if (get_one_info(line, e, infos) == 0)
			infos++;
		free(line);
		line = get_next_line(fd);
	}
	if (e->map.no > 1 || e->map.so > 1 || e->map.ea > 1 || e->map.we > 1
		|| e->map.fc > 1 || e->map.cc > 1)
		infos = -1;
	free(line);
	printf("info = %d\n", infos);
	if (infos != 6)
		return (1);
	return (0);
}
