/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:17:45 by ypacileo          #+#    #+#             */
/*   Updated: 2025/03/20 21:43:29 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	obj_posit(t_map *map, char c)
{
	t_point	obj;

	obj.y = 0;
	while (obj.y < map->height)
	{
		obj.x = 0;
		while (obj.x < map->width)
		{
			if (map->map[obj.y][obj.x] == c)
				return (obj);
			obj.x++;
		}
		obj.y++;
	}
	obj.x = -1;
	obj.y = -1;
	return (obj);
}