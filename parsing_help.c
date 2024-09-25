/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:06:26 by alion             #+#    #+#             */
/*   Updated: 2024/09/24 16:01:43 by alion            ###   ########.fr       */
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

void	ft_exit(t_env *e, char *str, int i)
{
	(void)e;
	printf("Error\n");
	printf("%s", str);
	exit (i);
}

int	check_name(char *map_name)
{
	int	len;

	len = ft_strlen(map_name);
	if (len < 4)
		return (1);
	if (ft_strncmp(&map_name[len - 4], ".cub", 4) == 0)
		return (0);
	return (1);
}
