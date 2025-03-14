/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:05:32 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/11 07:02:44 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H


#include "get_next_line.h"

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_map
{
    const char *name;
    char **map;
    int count;
}   t_map;

void	counter_row(t_map *map, char *line, int fd);
void	free_trash(char *line, int fd);
int    check_wall_row(t_map *map, int len);
void ft_error(const char *string);
void	map_error(t_map **map,const char *msg);
int	file_extension(char *s);
void	free_map(t_map **map);
void	read_map(t_map *map);
int	check_rectangle(t_map *map);
int	check_wall(t_map *map);
int	character_validation(t_map *map, char c);
int	collectible_validation(t_map *map, char c);
void map_validation(t_map **map, int argc, char **argv);
#endif