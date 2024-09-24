/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:06:26 by alion             #+#    #+#             */
/*   Updated: 2024/09/24 13:06:30 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	free_map(char **map)
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
}

int	problem_found(t_env *e, char *line, int i)
{
	(void)e;
	free(line);
	return (i);
}

void	ft_exit(t_env *e, char *str, int i)
{
	(void)e;
	printf("Error\n");
	printf("%s", str);
	exit (i);
}

int	check_name(char *map_name)
{
	if (ft_strnstr(map_name, ".cub\0", ft_strlen(map_name)))
		return (0);
	return (1);
}
