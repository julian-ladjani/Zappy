/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map.h
*/

#ifndef PSU_ZAPPY_2017_MAP_H
#define PSU_ZAPPY_2017_MAP_H

#define _GNU_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FOOD() 10
#define MAX_LINEMATE() 8
#define MAX_DERAUMERE() 6
#define MAX_SIBUR() 6
#define MAX_MENDIANE() 4
#define MAX_PHIRAS() 4
#define MAX_THYSTAME() 2

enum object {
	FOOD = 0,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME
};

typedef size_t tile_t[7];

typedef enum cardinal_dir {
	NORTH = 1,
	EAST = 2,
	SOUTH = 3,
	WEST = 4
} cardinal_dir;

typedef struct map_s {
	size_t width;
	size_t height;
	size_t seed;
	tile_t **tiles;
} map_t;

typedef struct vec_s {
	ssize_t x;
	ssize_t y;
} vec_t;

map_t *map_create(size_t width, size_t height);
void map_free(map_t *map);
void map_print(map_t *map);
uint8_t map_get_orientation(vec_t dir);
tile_t *map_get_tile(map_t *map, ssize_t x, ssize_t y);
char *tile_to_str(tile_t tile);
char *tile_to_str_quantity(tile_t tile);
char *str_append(char *str, char *append);

#endif /* PSU_ZAPPY_2017_MAP_H */
