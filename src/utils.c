/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:42:11 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/15 18:18:40 by ypacileo         ###   ########.fr       */
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

// Contar coleccionables en el mapa
int	count_collectibles(t_map *map)
{
	int		count;
	int		height;
	size_t	width;
	int		i;
	int		j;

	height = map -> count;
	width = ft_strlen(map -> map[0]);
	count = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < (int)width)
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
