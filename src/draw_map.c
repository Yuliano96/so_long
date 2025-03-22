/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:31:27 by ypacileo          #+#    #+#             */
/*   Updated: 2025/03/22 17:16:54 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


// Cierra la ventana y libera memoria correctamente
int close_window(t_game *game)
{
	if (game->map)
        free_map(&game->map);

    if (game->img)
    {
        mlx_destroy_image(game->mlx, game->img->player);
        mlx_destroy_image(game->mlx, game->img->collec);
        mlx_destroy_image(game->mlx, game->img->wall);
        mlx_destroy_image(game->mlx, game->img->path);
        mlx_destroy_image(game->mlx, game->img->ext);
        free(game->img);
    }
    
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    
    free(game);
    exit(0);
}
// Carga las imágenes en memoria
void upload_img(t_game *game)
{
    game->img->player = mlx_xpm_file_to_image(game->mlx, "img/P.xpm", &game->img->width, &game->img->height);
    game->img->ext = mlx_xpm_file_to_image(game->mlx, "img/E.xpm", &game->img->width, &game->img->height);
    game->img->collec = mlx_xpm_file_to_image(game->mlx, "img/C.xpm", &game->img->width, &game->img->height);
    game->img->wall = mlx_xpm_file_to_image(game->mlx, "img/wall.xpm", &game->img->width, &game->img->height);
    game->img->path = mlx_xpm_file_to_image(game->mlx, "img/Fond.xpm", &game->img->width, &game->img->height);
    
    if (!game->img->player || !game->img->ext || !game->img->collec || !game->img->wall || !game->img->path)
        close_window(game);
}

// Dibuja un objeto basado en su posición en el mapa
void draw_object(t_game *game, char obj_char, void *img)
{
    t_point pos;
    pos.y = 0;
    while (pos.y < game->map->height)
    {
        pos.x = 0;
        while (pos.x < game->map->width)
        {
            if (game->map->map[pos.y][pos.x] == obj_char)
                mlx_put_image_to_window(game->mlx, game->win, img, pos.x * 64, pos.y * 64);
            pos.x++;
        }
        pos.y++;
    }
}


// Renderiza el mapa y los objetos
void draw_map(t_game *game)
{
    draw_object(game, 'P', game->img->player);
    draw_object(game, 'E', game->img->ext);
    draw_object(game, 'C', game->img->collec);
    draw_object(game, '1', game->img->wall);
    draw_object(game, '0', game->img->path);
}