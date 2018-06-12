/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** create_map.c
*/

#include "map.h"

tile_t create_tile(size_t x, size_t y)
{
	tile_t tile;

	tile.x = x;
	tile.y = y;
	tile.food = rand() % MAX_FOOD();
	tile.linemate = rand() % MAX_LINEMATE();
	tile.deraumere = rand() % MAX_DERAUMERE();
	tile.sibur = rand() % MAX_SIBUR();
	tile.mendiane = rand() % MAX_MENDIANE();
	tile.phiras = rand() % MAX_PHIRAS();
	tile.thystame = rand() % MAX_THYSTAME();
	return (tile);
}

map_t *create_map(size_t width, size_t height)
{
	map_t *map = malloc(sizeof(map_t));

	if (!map)
		return (NULL);
	map->width = width;
	map->heigth = height;
	map->seed = time(NULL);
	srand(map->seed);
	map->tiles = malloc(sizeof(tile_t) * width);
	if (!map->tiles)
		return (NULL);
	for (int x = 0; x < width; ++x) {
		map->tiles[x] = malloc(sizeof(tile_t) * height);
		if (!map->tiles[x])
			return (NULL);
		for (int y = 0; y < height; ++y)
			map->tiles[x][y] = create_tile(x, y);
	}
	return (map);
}

void free_map(map_t *map)
{
	if (!map)
		return;
	if (!map->tiles) {
		free(map);
		return;
	}
	for (int x = 0; x < map->width; ++x) {
		if (map->tiles[x])
			free(map->tiles[x]);
	}
	free(map->tiles);
	free(map);
}
