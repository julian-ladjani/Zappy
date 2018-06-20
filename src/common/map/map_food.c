/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_create.c
*/

#include "map.h"

static void tile_add_bonus_food(tile_t *tile)
{
	(*tile)[FOOD] += (size_t) (random() % BONUS_FOOD());
}

void map_add_bonus_food(map_t *map)
{
	for (size_t y = 0; y < map->height; ++y) {
		map->tiles[y] = map->tiles[0] + map->width * y;
		for (size_t x = 0; x < map->width; ++x)
			tile_add_bonus_food(map->tiles[y] + x);
	}
}
