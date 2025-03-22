/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:05:45 by ypacileo          #+#    #+#             */
/*   Updated: 2025/03/20 22:05:11 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Liberar memoria de BFS
void	liberar_bfs(char ***map_visited, t_queue **queu, int height)
{
	int	i;

	if (*map_visited)
	{
		i = 0;
		while (i < height)
		{
			if ((*map_visited)[i])
				free((*map_visited)[i]);
			i++;
		}
		free(*map_visited);
		*map_visited = NULL;
	}
	if (*queu)
	{
		if ((*queu)->points)
			free((*queu)->points);
		free(*queu);
		*queu = NULL;
	}
}

//direciones
void	init_directions(int dir[4][2])
{
	dir[0][0] = -1;
	dir[0][1] = 0;
	dir[1][0] = 1;
	dir[1][1] = 0;
	dir[2][0] = 0;
	dir[2][1] = -1;
	dir[3][0] = 0;
	dir[3][1] = 1;
}

// copia una fila del mapa
char	*init_map_row(char *source, int width)
{
	char	*row;
	int		j;

	row = (char *)malloc(sizeof(char) * (width));
	if (!row)
		return (NULL);
	j = 0;
	while (j < width)
	{
		row[j] = source[j];
		j++;
	}
	return (row);
}

//genera una copia del mapa
char	**map_visi(t_map *map)
{
	char	**map_visited;
	int		i;
	

	map_visited = (char **)malloc(sizeof(char *) * map->height);
	if (!map_visited)
		return (NULL);
	
	i = 0;
	while (i < map->height)
	{
		map_visited[i] = init_map_row(map->map[i], map->width);
		if (!map_visited[i])
		{
			ft_free_copy_map(map_visited, i - 1);
			return (NULL);
		}
		i++;
	}
	return (map_visited);
}

//inicia los datos para el bfs
int	init_bfs(t_queue **q, t_data *data, t_map *map, t_point posi)
{
	data->colec = 0;
	data->exit = 0;
	*q = init_cola(map->width * map->height);
	if (!(*q))
		return (0);
	data->copy = map_visi(map);
	if (!data->copy)
	{
		if (*q)
		{
			if ((*q)->points)
				free((*q)->points);
			free(*q);
		}
		return (0);
	}
	anadir_cola(*q, posi);
	data->copy[posi.y][posi.x] = 'V';
	return (1);
}