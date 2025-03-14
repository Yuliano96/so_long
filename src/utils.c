/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:42:11 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/11 20:32:58 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	counter_row(t_map *map, char *line, int fd)
{
	if (fd < 0)
	{
		free(map);
		ft_error("Error\nAl abrir el archivo");
	}		
	map -> count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n' && line[0] != '\0')
			map -> count++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
}

void	free_trash(char *line, int fd)
{
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	check_wall_row(t_map *map, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (map -> map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < len)
	{
		if (map -> map[map -> count - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}
