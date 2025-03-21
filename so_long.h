/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:05:32 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/20 21:57:04 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "libft.h"
#include "get_next_line.h"
#include <mlx.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_map
{
    const char *name;
    char **map;
    int		width;
    int		height;
}   t_map;

// Estructura para coordenadas
typedef struct s_point
{
    int x;
    int y;
} t_point;

// Cola para BFS
typedef struct s_queue
{
    t_point *points;
    int frente;
    int final;
    int size;
} t_queue;

typedef struct s_data
{
    int colec;
    int exit;
    char **copy;
} t_data;



void	counter_row(t_map *map, char *line, int fd);
void	free_trash(char *line, int fd);
int    check_wall_row(t_map *map);
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
int	count_collectibles(t_map *map);
void	ft_free_copy_map(char **map_visi, int i);
void	liberar_bfs(char ***map_visited, t_queue **cola, int alto);
void	init_directions(int dir[4][2]);
char	*init_map_row(char *source, int width);
char	**map_visi(t_map *map);
t_queue	*init_cola(int size);
void	anadir_cola(t_queue *q, t_point pos);
t_point	extraer_cola(t_queue *q);
t_point	obj_posit(t_map *map, char c);
int	init_bfs(t_queue **q, t_data *data, t_map *map, t_point posi);
void	neighbors_bfs(t_queue *q, t_point pto, t_map *map, t_data *dat);
int	validate_path_bfs(t_map *map, t_point start_player);
#endif