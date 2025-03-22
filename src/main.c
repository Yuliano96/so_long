/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:37:39 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/20 22:05:51 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_img 
{
    void	*player;
    void    *collec;
    void    *wall;
    void    *path;
    void    *ext;
    int		width;
    int		height;
    t_point	pos;
} t_img;

typedef struct s_win
{
    void	*mlx;
    void	*win;
    int		width;
    int		height;
    t_point	pos;
} t_win;

int close_window(t_win *win)
{
    mlx_destroy_window(win->mlx, win->win);
    exit(0);
}
void upload_img(t_img *img, t_win *win)
{
    img->player = mlx_xpm_file_to_image(win->mlx, "img/pirata.xpm", &img->width, &img->height);
    if (!img->player)
        close_window(win);
    img->ext = mlx_xpm_file_to_image(win->mlx, "img/tesoro.xpm", &img->width, &img->height);
    if (!img->ext)
        close_window(win);
    img->collec = mlx_xpm_file_to_image(win->mlx, "img/coleccionable.xpm", &img->width, &img->height);
	if (!img->collec)
		close_window(win);
    img->wall = mlx_xpm_file_to_image(win->mlx, "img/muro1.xpm", &img->width, &img->height);
	if (!img->wall)
		close_window(win);
    img->path = mlx_xpm_file_to_image(win->mlx, "img/fondo1.xpm", &img->width, &img->height);
	if (!img->path)
		close_window(win);
}

void	draw_player(t_map *map, t_win *win, t_img *img)
{
	img->pos = obj_posit(map, 'P');
	 mlx_put_image_to_window(win->mlx, win->win, img->player, img->pos.x * 64, img->pos.y * 64);
}

void	draw_exit(t_map *map, t_win *win, t_img *img)
{
	img->pos = obj_posit(map, 'E');
	mlx_put_image_to_window(win->mlx, win->win, img->ext, img->pos.x * 64, img->pos.y * 64);
}

void	draw_wall(t_map *map, t_win *win, t_img *img)
{
	t_point obj;
    
    obj.y = 0;
    while (obj.y < map->height)
    {
        obj.x = 0;
        while (obj.x < map->width)
        {
            
            if (map->map[obj.y][obj.x] == '1')
            {
                img->pos.y = obj.y;
                img->pos.x = obj.x;
                mlx_put_image_to_window(win->mlx, win->win, img->wall, img->pos.x * 64, img->pos.y * 64);
            }

            obj.x++;
        }
        obj.y++;
    }
}

    
void	draw_collec(t_map *map, t_win *win, t_img *img)
{
	t_point obj;

    obj.y = 0;
    while (obj.y < map->height)
    {
        obj.x = 0;
        while (obj.x < map->width)
        {
            
            if (map->map[obj.y][obj.x] == 'C')
            {
                img->pos.y = obj.y;
                img->pos.x = obj.x;
                mlx_put_image_to_window(win->mlx, win->win, img->collec, img->pos.x * 64, img->pos.y * 64);
            }

            obj.x++;
        }
        obj.y++;
    }
}

void draw_path(t_map *map, t_win *win, t_img *img)
{
	t_point obj;
    
    obj.y = 0;
    while (obj.y < map->height)
    {
        obj.x = 0;
        while (obj.x < map->width)
        {
            
            if (map->map[obj.y][obj.x] == '0')
            {
                img->pos.y = obj.y;
                img->pos.x = obj.x;
                mlx_put_image_to_window(win->mlx, win->win, img->path, img->pos.x * 64, img->pos.y * 64);
            }

            obj.x++;
        }
        obj.y++;
    }
}



int main(int argc, char **argv)
{
    t_map *map;
    t_img img;
	t_win win;

    map_validation(&map, argc, argv);
    win.mlx = mlx_init();
    win.width = map->width;
    win.height = map->height;

    win.win = mlx_new_window(win.mlx, win.width * 64, win.height * 64, "so_long");
    upload_img(&img, &win);
    draw_player(map,&win,&img);
	draw_wall(map,&win, &img);
	draw_collec(map,&win, &img);
	draw_exit(map, &win, &img);
	draw_path(map, &win, &img);
    // Manejar el cierre de la ventana
    mlx_hook(win.win, 17, 0, close_window, &win);

    // Iniciar el bucle principal
    mlx_loop(win.mlx);
    return (0);
}

/*// Función para manejar eventos de teclado
int key_hook(int keycode, t_img *img)
{
    if (keycode == 100) // Tecla 'd' (mueve a la derecha)
    {
        img->pos.x += 1;
        printf("Derecha\n");
    }
    else if (keycode == 97) // Tecla 'a' (mueve a la izquierda)
    {
        img->pos.x -= 1;
        printf("Izquierda\n");
    }
    else if (keycode == 119) // Tecla 'w' (mueve hacia arriba)
    {
        img->pos.y -= 1;
        printf("Arriba\n");
    }
    else if (keycode == 115) // Tecla 's' (mueve hacia abajo)
    {
        img->pos.y += 1;
        printf("Abajo\n");
    }

    return (0);
}

// Renderiza el siguiente frame
int render_next_frame(t_img *img)
{
    // Limpiar la ventana
    mlx_clear_window(img->mlx, img->win);

    mlx_put_image_to_window(img->mlx, img->win, img->img, img->pos.x * 64, img->pos.y * 64);

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
    int win_ancho;
    int win_alto;
    

    map_validation(&map, argc, argv);
    
    
    // Inicializar MiniLibX
    img.mlx = mlx_init();
    if (!img.mlx)
        return (1);
    win_ancho = ft_strlen(map -> map[0]) * 64;
    win_alto = map->count * 64;
    printf("altura de la ventana: %d\n", win_alto);
    printf("anchura de la ventana: %d\n", win_ancho);
    // Crear una ventana
    img.win = mlx_new_window(img.mlx, win_ancho, win_alto, "so_long");
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
	printf("posicion inicial: x: %d, y :%d\n", img.pos.x,img.pos.y);


    mlx_loop_hook(img.mlx, render_next_frame, &img);

    // Registrar la función de teclado
    mlx_key_hook(img.win, key_hook, &img);

    // Manejar el cierre de la ventana
    mlx_hook(img.win, 17, 0, close_window, &img);

    // Iniciar el bucle principal
    mlx_loop(img.mlx);
 
    return (0);
}
*/