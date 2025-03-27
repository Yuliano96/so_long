/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:37:39 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/27 06:38:17 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	map = NULL;
	game = NULL;
	map_validation(&map, argc, argv);
	init_game(&game, map);
	game->win = mlx_new_window(game->mlx, \
	game->width * 64, game->height * 64, "so_long");
	if (!game->win)
	{
		free(game->img);
		free(game);
		map_error(&map, "Error\nNo se pudo crear la ventana\n");
	}
	upload_img(game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
	mlx_hook(game->win, 2, 1L << 0, mover_player, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
	return (0);
}
