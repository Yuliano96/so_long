/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:17:45 by ypacileo          #+#    #+#             */
/*   Updated: 2025/03/15 18:17:56 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	search_player(t_map *map)
{
	t_point	player;
	size_t	width;
	int		height;

	height = map->count;
	width = ft_strlen(map->map[0]);
	player.y = 0;
	while (player.y < height)
	{
		player.x = 0;
		while (player.x < (int)width)
		{
			if (map->map[player.y][player.x] == 'P')
				return (player);
			player.x++;
		}
		player.y++;
	}
	player.x = -1;
	player.y = -1;
	return (player);
}
