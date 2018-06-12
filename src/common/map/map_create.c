/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_create.c
*/

#include "map.h"

static void fill_tile(tile_t *tile)
{
	*tile[FOOD] = (size_t) (random() % MAX_FOOD());
	*tile[LINEMATE] = (size_t) (random() % MAX_LINEMATE());
	*tile[DERAUMERE] = (size_t) (random() % MAX_DERAUMERE());
	*tile[SIBUR] = (size_t) (random() % MAX_SIBUR());
	*tile[MENDIANE] = (size_t) (random() % MAX_MENDIANE());
	*tile[PHIRAS] = (size_t) (random() % MAX_PHIRAS());
	*tile[THYSTAME] = (size_t) (random() % MAX_THYSTAME());
}

static void fill_tiles(map_t *map)
{
	for (size_t y = 0; y < map->height; ++y) {
		map->tiles[y] = *map->tiles + map->width * y;
		for (size_t x = 0; x < map->width; ++x)
			fill_tile(map->tiles[y] + x);
	}
}

static uint8_t malloc_map(map_t *map)
{
	map->tiles = malloc(sizeof(tile_t) * map->height);
	if (!map->tiles) {
		dprintf(2, "Invalid malloc\n");
		return (0);
	}
	map->tiles[0] = malloc(sizeof(tile_t) * map->height * map->width);
	if (!map->tiles[0]) {
		map_free(map);
		dprintf(2, "Invalid malloc\n");
		return (0);
	}
	return (1);
}

map_t *map_create(size_t width, size_t height)
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
	fill_tiles(map);
	return (map);
}
