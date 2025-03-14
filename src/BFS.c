/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:51:27 by yuliano           #+#    #+#             */
/*   Updated: 2025/03/14 07:56:01 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>


char *map[] = {
    "11111",
    "1PC01",
    "111E1",
    "11111",
};

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

// Inicializa la cola
t_queue *init_cola(int size)
{
    t_queue *q = malloc(sizeof(t_queue));
    if (!q)
        return (NULL);
    q->points = malloc(sizeof(t_point) * size);
    if (!q->points)
    {
        free(q);
        return (NULL);
    }
    q->frente = 0;
    q->final = 0;
    q->size = size;
    return (q);
}

// Añadir a la cola
void añadir_cola(t_queue *q, int x, int y)
{
    q->points[q->final].x = x;
    q->points[q->final].y = y;
    q->final++;
}

// Extraer de la cola
t_point extraer_cola(t_queue *q)
{
    return (q->points[q->frente++]);
}

// Contar coleccionables en el mapa
int count_collectibles(char **map, int ancho, int alto)
{
    int count = 0;
    int i = 0;
    while (i < alto)
    {
        int j = 0;
        while (j < ancho)
        {
            if (map[i][j] == 'C')
                count++;
            j++;
        }
        i++;
    }
    return count;
}

// Crear copia del mapa para rastrear visitas
char **map_visi(char **map, int ancho, int alto)
{
    char **map_visited;
    int i, j;

    map_visited = (char **)malloc(sizeof(char *) * alto);
    if (!map_visited)
        return (NULL);
    i = 0;
    while (i < alto)
    {
        map_visited[i] = (char *)malloc(sizeof(char) * ancho);
        if (!map_visited[i])
        {
            while (--i >= 0)
                free(map_visited[i]);
            free(map_visited);
            return (NULL);
        }
        j = 0;
        while (j < ancho)
        {
            map_visited[i][j] = map[i][j];
            j++;
        }
        i++;
    }
    return (map_visited);
}

// Liberar memoria de BFS
void liberar_bfs(char ***map_visited, t_queue **cola, int alto)
{
    int i = 0;

    while (i < alto)
    {
        free((*map_visited)[i]);
        i++;
    }
    free(*map_visited);
    *map_visited = NULL;
    free((*cola)->points);
    free(*cola);
    *cola = NULL;
}

// BFS para validar el mapa
int bfs(char **map, int ancho, int alto, int start_x, int start_y)
{
    t_queue *q;
    char **map_visited;
    int collected = 0;
    int exit_found = 0;
    int total_collectibl;
    int i;

    int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    q = init_cola(ancho * alto);
    if (!q)
        return (0);
    total_collectibl = count_collectibles(map, ancho, alto);
    map_visited = map_visi(map, ancho, alto);
    if (!map_visited)
    {
        free(q->points);
        free(q);
        return (0);
    }

    añadir_cola(q, start_x, start_y);
    map_visited[start_y][start_x] = 'V'; // Marcamos la posición inicial del jugador

    while (q->frente < q->final)
    {
        t_point current = extraer_cola(q);
        // Verificar si se encontró la salida y todos los coleccionables
        if (exit_found && collected == total_collectibl)
        {
            liberar_bfs(&map_visited, &q, alto);
            return (1);
        }

        // Depuración: Mostrar coordenadas exploradas
        printf("Visitando: (%d, %d)\n", current.y, current.x);
        i = 0;
        while (i < 4)
        {
            int nx = current.x + dir[i][0];
            int ny = current.y + dir[i][1];

            if (nx >= 0 && ny >= 0 && nx < ancho && ny < alto)
            {
                if (map_visited[ny][nx] == '1' || map_visited[ny][nx] == 'V')
                {
                    i++;
                    continue;
                }

                if (map[ny][nx] == 'C')
                    collected++;
                if (map[ny][nx] == 'E')
                    exit_found = 1;

                añadir_cola(q, nx, ny);
                map_visited[ny][nx] = 'V';
            }
            i++;
        }
    }

    liberar_bfs(&map_visited, &q, alto);
    return (0);
}

int main()
{
    printf("Camino valido: %d\n", bfs(map, 5, 4, 1, 1));
    return (0);
}
