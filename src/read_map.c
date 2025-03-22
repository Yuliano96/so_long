/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:40:01 by ypacileo          #+#    #+#             */
/*   Updated: 2025/03/22 19:24:34 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	file_extension(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (len <= 8)
		return (0);
	if (s[len - 4] == '.' && s[len - 3] == 'b'
		&& s[len - 2] == 'e' && s[len - 1] == 'r')
		return (1);
	return (0);
}

void	free_map(t_map **map)
{
	int	i;

	if (!map || !(*map))
		return ;
	i = 0;
	while (i < (*map)->height)
	{
		free((*map)->map[i]);
		(*map)->map[i] = NULL;
		i++;
	}
	free((*map)->map);
	(*map)->map = NULL;
	free(*map);
	*map = NULL;
}

void	read_map(t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(map->name, O_RDONLY);
	line = NULL;
	counter_row(map, line, fd);
	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		ft_error("Error\nAl reabrir el archivo\n");
	map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		ft_error("Error\nFallo de asignación de memoria\n");
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		map->map[i] = line;
		i++;
	}
	free_trash(line, fd);
	map->map[i] = NULL;
	close(fd);
}

//aqui tambien defino la anchura del mapa
int	check_rectangle(t_map *map)
{
	int	i;

	if (!map || !map->map || !map->map[0])
		return (0);

	i = 0;
	while (map -> map[i] != NULL)
	{
		if (map->map[i][ft_strlen(map->map[i]) - 1] == '\n')
			map->map[i][ft_strlen(map->map[i]) - 1] = '\0';
		i ++;
	}
	map->width = (int)ft_strlen(map->map[0]);
	i = 1;
	while (map->map[i] != NULL)
	{
		if ((int)ft_strlen(map->map[i]) != map->width)
			return (0);
		i++;
	}
	return (1);
}

int	check_wall(t_map *map)
{
	int	i;

	if (check_wall_row(map) == 0)
		return (0);
	i = 1;
	while (i < (map -> height - 1))
	{
		if (map -> map[i][0] != '1'
			|| map -> map[i][map->width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
