/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_create.c
*/

#include "map.h"

void empty_tile(tile_t *tile, size_t food)
{
	(*tile)[FOOD] = food;
	(*tile)[LINEMATE] = 0;
	(*tile)[DERAUMERE] = 0;
	(*tile)[SIBUR] = 0;
	(*tile)[MENDIANE] = 0;
	(*tile)[PHIRAS] = 0;
	(*tile)[THYSTAME] = 0;
}

static void fill_tile(tile_t *tile)
{
	(*tile)[FOOD] = (size_t) (random() % MAX_FOOD());
	(*tile)[LINEMATE] = (size_t) (random() % MAX_LINEMATE());
	(*tile)[DERAUMERE] = (size_t) (random() % MAX_DERAUMERE());
	(*tile)[SIBUR] = (size_t) (random() % MAX_SIBUR());
	(*tile)[MENDIANE] = (size_t) (random() % MAX_MENDIANE());
	(*tile)[PHIRAS] = (size_t) (random() % MAX_PHIRAS());
	(*tile)[THYSTAME] = (size_t) (random() % MAX_THYSTAME());
}

static void fill_tiles(map_t *map, char fill)
{
	for (size_t y = 0; y < map->height; ++y) {
		map->tiles[y] = map->tiles[0] + map->width * y;
		for (size_t x = 0; x < map->width; ++x)
			(fill) ? fill_tile(map->tiles[y] + x) :
				empty_tile(map->tiles[y] + x, 0);
	}
}

static uint8_t malloc_map(map_t *map)
{
	map->tiles = malloc(sizeof(tile_t *) * map->height);
	if (!map->tiles) {
		dprintf(2, "Invalid malloc\n");
		return (0);
	}
	map->tiles[0] = calloc(sizeof(tile_t) * map->height
			* (map->width + 0), sizeof(tile_t));
	if (!map->tiles[0]) {
		map_free(map);
		dprintf(2, "Invalid malloc\n");
		return (0);
	}
	return (1);
}

map_t *map_create(size_t width, size_t height, char fill)
{
	map_t *map = malloc(sizeof(map_t));

	if (!map) {
		dprintf(2, "Invalid malloc\n");
		return (NULL);
	}
	map->width = width;
	map->height = height;
	map->seed = (size_t) time(NULL);
	srandom((unsigned int) map->seed);
	if (!malloc_map(map))
		return (NULL);
	fill_tiles(map, fill);
	return (map);
}