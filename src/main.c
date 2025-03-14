/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:37:39 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/11 07:20:03 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map *map;
	int i = 0;

	map_validation(&map, argc, argv);
	printf("¡Mapa válido!\n\n");
	while(map -> map[i] != NULL)
	{
		printf("%s\n",map -> map[i]);
		i++;
	}
	free_map(&map);
	return (0);
}
