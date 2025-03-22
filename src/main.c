/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:37:39 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/22 21:11:59 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void move_player(t_game *game, int dx, int dy)
{
    t_point player = obj_posit(game->map, 'P');
    char next_cell = game->map->map[player.y + dy][player.x + dx]; //posicion del player donde se va a mover

    if (next_cell != '1') // No moverse a una pared
    {
        if (game->on_exit)
            game->map->map[player.y][player.x] = 'E'; // Si el jugador estaba sobre 'E' (condicion especial)
        else
            game->map->map[player.y][player.x] = '0'; // Dejar suelo normal

        if (next_cell == 'C')
            game->cont++;

        if (next_cell == 'E' && game->cont == game->collec)
            close_window(game);

        if (next_cell == 'E') // si pisamos next_cell
			game->on_exit = 1;
		else
			game->on_exit = 0;
        game->map->map[player.y + dy][player.x + dx] = 'P'; //pisamos la  nueva posicion (next_cell)

        printf("Movimiento: (%d, %d)\n", dx, dy);
    }
}
int mover_player(int key, t_game *game)
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


int render_next_frame(t_game *game)
{
    draw_map(game);
    return (0);
}
int main(int argc, char **argv)
{
    t_map *map;
    t_game *game;
    if (map_validation(&map, argc, argv))
    {
        game = malloc(sizeof(t_game));
        if (!game)
        return (1);
    
    // Asignar memoria para img
        game->img = malloc(sizeof(t_img));
        if (!game->img)
        {
        free(game);
        return (1);
        }
    
    game->map = map;//asigno la direccion de memoria
    game->mlx = mlx_init();
    game->width = map->width;
    game->height = map->height;
    game->cont = 0;
    game->win = mlx_new_window(game->mlx, game->width * 64, game->height * 64, "so_long");
    game->collec = count_collectibles(game->map);
	game->on_exit = 0;
    upload_img(game);

	mlx_loop_hook(game->mlx, render_next_frame, game);
	mlx_key_hook(game->win, mover_player, game);
    
    // Manejar el cierre de la ventana
    mlx_hook(game->win, 17, 0, close_window, game);
    
    // Iniciar el bucle principal
    mlx_loop(game->mlx);
    }
    
    
    return (0);
}


