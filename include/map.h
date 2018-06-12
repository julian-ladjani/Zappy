/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map.h
*/

#ifndef PSU_ZAPPY_2017_MAP_H
#define PSU_ZAPPY_2017_MAP_H

#include <stdlib.h>
#include <time.h>

#define MAX_FOOD() 10
#define MAX_LINEMATE() 8
#define MAX_DERAUMERE() 6
#define MAX_SIBUR() 6
#define MAX_MENDIANE() 4
#define MAX_PHIRAS() 4
#define MAX_THYSTAME() 2

typedef struct tile_s {
	size_t x;
	size_t y;
	size_t food;
	size_t linemate;
	size_t deraumere;
	size_t sibur;
	size_t mendiane;
	size_t phiras;
	size_t thystame;
	
} tile_t;

typedef struct map_s {
	size_t width;
	size_t height;
	size_t seed;
	tile_t tiles[][];
} map_t;

#endif /* PSU_ZAPPY_2017_MAP_H */
