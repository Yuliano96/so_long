/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:05:32 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/22 20:51:44 by ypacileo         ###   ########.fr       */
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

# define W 119
# define S 115
# define A 97
# define D 100
# define Up 65362
# define Down 65364
# define Right 65363
# define Left 65361
# define Esc 65307
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

// Estructura para almacenar imágenes
typedef struct s_img 
{
    void    *player;
    void    *collec;
    void    *wall;
    void    *path;
    void    *ext;
    int     width;
    int     height;
} t_img;

// Estructura principal del juego
typedef struct s_game
{
    int     width;
    int     height;
    void    *mlx;
    void    *win;
    t_map   *map;
    t_img   *img;
    t_point pos;
    int		cont;
	int		collec;
	int     on_exit;
} t_game;


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
int map_validation(t_map **map, int argc, char **argv);
int	count_collectibles(t_map *map);
void	ft_free_copy_map(char **map_visi, int i);
void	liberar_bfs(char ***map_visited, t_queue **cola, int alto);
void	init_directions(int dir[4][2]);
char	*init_map_row(char *source, int width);
char	**map_copy(t_map *map);
t_queue	*init_cola(int size);
void	anadir_cola(t_queue *q, t_point pos);
t_point	extraer_cola(t_queue *q);
t_point	obj_posit(t_map *map, char c);
int	init_bfs(t_queue **q, t_data *data, t_map *map, t_point posi);
void	neighbors_bfs(t_queue *q, t_point pto, t_map *map, t_data *dat);
int	validate_path_bfs(t_map *map, t_point start_player);
void upload_img(t_game *game);
void draw_object(t_game *game, char obj_char, void *img);
void draw_map(t_game *game);
int close_window(t_game *game);
#endif