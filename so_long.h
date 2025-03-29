/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:05:32 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/29 12:46:25 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "get_next_line.h"
# include "libftprintf.h"
# include <mlx.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define W 119
# define S 115
# define A 97
# define D 100
# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361
# define ESC 65307

typedef struct s_map
{
	const char	*name;
	char		**map;
	int			width;
	int			height;
}	t_map;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_queue
{
	t_point	*points;
	int		front;
	int		end;
	int		size;
}	t_queue;

typedef struct s_data
{
	int		colec;
	int		exit;
	char	**copy;
}	t_data;

typedef struct s_img
{
	void	*player;
	void	*collec;
	void	*wall;
	void	*path;
	void	*ext;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	*img;
	t_point	pos;
	int		cont;
	int		collec;
	int		on_exit;
	int		move;
}	t_game;

void	counter_row(t_map *map, char *line, int fd);
void	free_trash(char *line, int fd);
int		check_wall_row(t_map *map);
void	ft_error(const char *string);
void	map_error(t_map **map, const char *msg);
int		file_extension(const char *str);
int		validate_directory(const char *str);
int		check_invalid_items(char s);
int		map_character(t_map *map);
void	free_map(t_map **map);
void	read_map(t_map *map);
int		check_rectangle(t_map *map);
int		check_wall(t_map *map);
int		character_validation(t_map *map, char c);
int		collectible_validation(t_map *map, char c);
void	map_validation(t_map **map, int argc, char **argv);
int		count_collectibles(t_map *map);
void	ft_free_copy_map(char **map_visi, int i);
void	free_bfs(char ***map_visited, t_queue **cola, int alto);
void	init_directions(int dir[4][2]);
char	*init_map_row(char *source, int width);
char	**map_copy(t_map *map);
t_queue	*init_queue(int size);
void	add_queue(t_queue *q, t_point pos);
t_point	extract_queue(t_queue *q);
t_point	obj_posit(t_map *map, char c);
int		init_bfs(t_queue **q, t_data *data, t_map *map, t_point posi);
void	neighbors_bfs(t_queue *q, t_point pto, t_map *map, t_data *dat);
int		validate_path_bfs(t_map *map, t_point start_player);
void	upload_img(t_game *game);
void	draw_object(t_game *game, char obj_char, void *img);
void	draw_map(t_game *game);
int		close_window(t_game *game);
void	init_game(t_game **game, t_map *map);
void	move_player(t_game *game, int dx, int dy);
int		mover_player(int key, t_game *game);
int		render_next_frame(t_game *game);
#endif