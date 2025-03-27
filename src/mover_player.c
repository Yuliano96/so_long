/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mover_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 06:23:03 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/27 07:32:10 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game **game, t_map *map)
{
	*game = malloc(sizeof(t_game));
	if (!(*game))
		map_error(&map, "Error\nNo se puede iniciar el juego\n");
	(*game)->img = malloc(sizeof(t_img));
	if (!(*game)->img)
	{
		free(*game);
		map_error(&map, "Error\nNo se puede iniciar el juego\n");
	}
	(*game)->mlx = mlx_init();
	if (!(*game)->mlx)
	{
		free((*game)->img);
		free(*game);
		map_error(&map, "Error\nNo se puede iniciar el juego\n");
	}
	(*game)->map = map;
	(*game)->width = map->width;
	(*game)->height = map->height;
	(*game)->cont = 0;
	(*game)->on_exit = 0;
	(*game)->move = 0;
	(*game)->collec = count_collectibles((*game)->map);
}

/*segun las coordenas se mueve el player*/
void	move_player(t_game *game, int dx, int dy)
{
	t_point	player;
	char	next_cell;

	player = obj_posit(game->map, 'P');
	next_cell = game->map->map[player.y + dy][player.x + dx];
	if (next_cell != '1')
	{
		if (game->on_exit)
			game->map->map[player.y][player.x] = 'E';
		else
			game->map->map[player.y][player.x] = '0';
		if (next_cell == 'C')
			game->cont++;
		if (next_cell == 'E' && game->cont == game->collec)
			close_window(game);
		if (next_cell == 'E')
			game->on_exit = 1;
		else
			game->on_exit = 0;
		game->map->map[player.y + dy][player.x + dx] = 'P';
		printf("player move --> %d\n", game->move++);
	}
}

int	mover_player(int key, t_game *game)
{
	if (key == D || key == Right)
		move_player(game, 1, 0);
	else if (key == A || key == Left)
		move_player(game, -1, 0);
	else if (key == W || key == Up)
		move_player(game, 0, -1);
	else if (key == S || key == Down)
		move_player(game, 0, 1);
	return (0);
}

int	render_next_frame(t_game *game)
{
	draw_map(game);
	return (0);
}
