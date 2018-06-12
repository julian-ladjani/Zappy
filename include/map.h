/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map.h
*/

#ifndef PSU_ZAPPY_2017_MAP_H
#define PSU_ZAPPY_2017_MAP_H

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
	FODD = 0,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME
};

typedef size_t tile_t[7];

typedef struct map_s {
	size_t width;
	size_t height;
	size_t seed;
	tile_t **tiles;
} map_t;

map_t *create_map(size_t width, size_t height);
void free_map(map_t *map);
void print_map(map_t *map);

#endif /* PSU_ZAPPY_2017_MAP_H */
