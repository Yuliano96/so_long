/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:31:27 by ypacileo          #+#    #+#             */
/*   Updated: 2025/03/27 06:20:37 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	if (game->map)
		free_map(&game->map);
	if (game->img)
	{
		if (game->img->player)
			mlx_destroy_image(game->mlx, game->img->player);
		if (game->img->collec)
			mlx_destroy_image(game->mlx, game->img->collec);
		if (game->img->wall)
			mlx_destroy_image(game->mlx, game->img->wall);
		if (game->img->path)
			mlx_destroy_image(game->mlx, game->img->path);
		if (game->img->ext)
			mlx_destroy_image(game->mlx, game->img->ext);
		free(game->img);
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
	exit(0);
}

// Carga las imágenes en memoria
void	upload_img(t_game *game)
{
	game->img->player = mlx_xpm_file_to_image(game->mlx, "img/P.xpm", \
	&game->img->width, &game->img->height);
	if (!game->img->player)
		close_window(game);
	game->img->ext = mlx_xpm_file_to_image(game->mlx, "img/E.xpm", \
	&game->img->width, &game->img->height);
	if (!game->img->ext)
		close_window(game);
	game->img->collec = mlx_xpm_file_to_image(game->mlx, "img/C.xpm", \
	&game->img->width, &game->img->height);
	if (!game->img->collec)
		close_window(game);
	game->img->wall = mlx_xpm_file_to_image(game->mlx, "img/wall.xpm", \
	&game->img->width, &game->img->height);
	if (!game->img->wall)
		close_window(game);
	game->img->path = mlx_xpm_file_to_image(game->mlx, "img/Fond.xpm", \
	&game->img->width, &game->img->height);
	if (!game->img->path)
		close_window(game);
}

/*dibuja un objeto en la ventana segun el mapa*/
void	draw_object(t_game *game, char obj_char, void *img)
{
	t_point	pos;

	pos.y = 0;
	while (pos.y < game->map->height)
	{
		pos.x = 0;
		while (pos.x < game->map->width)
		{
			if (game->map->map[pos.y][pos.x] == obj_char)
				mlx_put_image_to_window(game->mlx, game->win, \
				img, pos.x * 64, pos.y * 64);
			pos.x++;
		}
		pos.y++;
	}
}

// dibuja todo el mapa en la ventana
void	draw_map(t_game *game)
{
	draw_object(game, 'P', game->img->player);
	draw_object(game, 'E', game->img->ext);
	draw_object(game, 'C', game->img->collec);
	draw_object(game, '1', game->img->wall);
	draw_object(game, '0', game->img->path);
}
