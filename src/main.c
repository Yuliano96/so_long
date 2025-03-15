/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:37:39 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/15 20:25:57 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_img 
{
    void *mlx;
    void *win;
    void *img;
    int img_width;
    int img_height;
    t_point pos;
} t_img;

// Función para manejar eventos de teclado
int key_hook(int keycode, t_img *img)
{
    if (keycode == 100) // Tecla 'd' (mueve a la derecha)
    {
        img->pos.x += 15;
        printf("Derecha\n");
    }
    else if (keycode == 97) // Tecla 'a' (mueve a la izquierda)
    {
        img->pos.x -= 15;
        printf("Izquierda\n");
    }
    else if (keycode == 119) // Tecla 'w' (mueve hacia arriba)
    {
        img->pos.y -= 15;
        printf("Arriba\n");
    }
    else if (keycode == 115) // Tecla 's' (mueve hacia abajo)
    {
        img->pos.y += 15;
        printf("Abajo\n");
    }

    return (0);
}

// Renderiza el siguiente frame
int render_next_frame(t_img *img)
{
    // Limpiar la ventana
    mlx_clear_window(img->mlx, img->win);

    // Dibujar la imagen en la nueva posición
    mlx_put_image_to_window(img->mlx, img->win, img->img, img->pos.x, img->pos.y);

    return (0);
}

// Cierra la ventana y termina el programa
int close_window(t_img *img)
{
    mlx_destroy_window(img->mlx, img->win);
    exit(0);
    return (0);
}

int main(int argc, char **argv)
{
    t_img img;
    t_map *map;
    

    map_validation(&map, argc, argv);

    // Inicializar MiniLibX
    img.mlx = mlx_init();
    if (!img.mlx)
        return (1);

    // Crear una ventana
    img.win = mlx_new_window(img.mlx, ft_strlen(map->map[0]) * 64, map->count * 64, "so_long");
    if (!img.win)
        return (1);

    // Cargar la imagen XPM
    img.img = mlx_xpm_file_to_image(img.mlx, "pirata.xpm", &img.img_width, &img.img_height);
    if (!img.img)
    {
        printf("Error: No se pudo cargar la imagen\n");
        return (1);
    }
    printf("Ancho de la imagen: %d\n", img.img_width);
    printf("Altura de la imagen: %d\n", img.img_height);

    // Posición inicial de la imagen
    img.pos = search_player(map);  // Asegúrate de definir search_player
	printf("posicion inicial: (%d,%d)\n", img.pos.y,img.pos.x);

    // Registrar la función de renderizado
    mlx_loop_hook(img.mlx, render_next_frame, &img);

    // Registrar la función de teclado
    mlx_key_hook(img.win, key_hook, &img);

    // Manejar el cierre de la ventana
    mlx_hook(img.win, 17, 0, close_window, &img);

    // Iniciar el bucle principal
    mlx_loop(img.mlx);

    return (0);
}
