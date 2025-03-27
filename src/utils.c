/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:42:11 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/27 21:30:35 by yuliano          ###   ########.fr       */
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
	map -> height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n' && line[0] != '\0')
			map -> height++;
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

int	check_wall_row(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map -> map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->width)
	{
		if (map -> map[map -> height - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

// Contar coleccionables en el mapa
int	count_collectibles(t_map *map)
{
	int		count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map -> map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

// Función para liberar mao_visit
void	ft_free_copy_map(char **map_visi, int i)
{
	while (i >= 0)
	{
		free(map_visi[i]);
		i--;
	}
	free(map_visi);
}
