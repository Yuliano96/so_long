/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:56:55 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/29 12:49:26 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_invalid_items(char s)
{
	if (s != '1' && s != '0' && s != 'E' && s != 'P' && s != 'C')
		return (0);
	return (1);
}

int	map_character(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (check_invalid_items(map->map[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*valida que el mapa tenga una sola salida y un jugador*/
int	character_validation(t_map *map, char c)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] == c)
			{
				count++;
				if (count > 1)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (count == 1);
}

/*verifica que el mapa tenga al menos un coleccionable*/
int	collectible_validation(t_map *map, char c)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] == c)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	map_validation(t_map **map, int argc, char **argv)
{
	if (argc != 2)
		ft_error("Error\nUso: ./so_long <mapa.ber>\n");
	if (file_extension(argv[1]) == 0)
		ft_error("Error\nArchivo inválido\n");
	*map = (t_map *)malloc(sizeof(t_map));
	if (!(*map))
		ft_error("Error\nFallo de asignación de memoria para el mapa\n");
	(*map)->name = argv[1];
	read_map(*map);
	if (check_rectangle(*map) == 0)
		map_error(map, "Error\nEl mapa no es un rectángulo\n");
	if (map_character(*map) == 0)
		map_error(map, "Error\nEl mapa tiene caracter(s), no valido\n");
	if (check_wall(*map) == 0)
		map_error(map, "Error\nEl mapa no está rodeado de muros\n");
	if (character_validation(*map, 'P') == 0)
		map_error(map, "Error\nEl mapa debe tener un jugador\n");
	if (character_validation(*map, 'E') == 0)
		map_error(map, "Error\nEl mapa debe tener una salida\n");
	if (collectible_validation(*map, 'C') == 0)
		map_error(map, "Error\nEl mapa debe tener al menos un coleccionable\n");
	if (validate_path_bfs(*map, obj_posit(*map, 'P')) == 0)
		map_error(map, "Error\nRuta no valida");
}
