/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:51:27 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/29 12:25:13 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Inicializa la cola
t_queue	*init_queue(int size)
{
	t_queue	*q;

	q = malloc(sizeof(t_queue));
	if (!q)
		return (NULL);
	q->points = malloc(sizeof(t_point) * size);
	if (!q->points)
	{
		free(q);
		return (NULL);
	}
	q->front = 0;
	q->end = 0;
	q->size = size;
	return (q);
}

// Añadir a la cola
void	add_queue(t_queue *q, t_point pos)
{
	q->points[q->end].x = pos.x;
	q->points[q->end].y = pos.y;
	q->end++;
}

// Extraer de la cola
t_point	extract_queue(t_queue *q)
{
	return (q->points[q->front++]);
}

//visito los vecinos del mapa
void	neighbors_bfs(t_queue *q, t_point pto, t_map *map, t_data *dat)
{
	int		dir[4][2];
	int		i;
	t_point	pos;
	int		width;

	width = map->width;
	init_directions(dir);
	i = 0;
	while (i < 4)
	{
		pos.x = pto.x + dir[i][0];
		pos.y = pto.y + dir[i][1];
		if (pos.x >= 0 && pos.y >= 0 && pos.x < width && pos.y < map->height
			&& dat->copy[pos.y][pos.x] != '1' && dat->copy[pos.y][pos.x] != 'V')
		{
			if (dat->copy[pos.y][pos.x] == 'C')
				dat->colec++;
			if (dat->copy[pos.y][pos.x] == 'E')
				dat->exit = 1;
			add_queue(q, pos);
			dat->copy[pos.y][pos.x] = 'V';
		}
		i++;
	}
}

//funcion principal para validar ruta del mapa
int	validate_path_bfs(t_map *map, t_point start_player)
{
	t_queue	*q;
	t_data	data;
	t_point	pto;
	int		total_collectibl;
	int		valid;

	total_collectibl = count_collectibles(map);
	if (!init_bfs(&q, &data, map, start_player))
		return (0);
	valid = 0;
	while (q->front < q->end)
	{
		pto = extract_queue(q);
		if (data.exit && data.colec == total_collectibl)
		{
			valid = 1;
			break ;
		}
		neighbors_bfs(q, pto, map, &data);
	}
	free_bfs(&data.copy, &q, map->height);
	return (valid);
}
