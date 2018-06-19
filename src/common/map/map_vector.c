/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** create_map.c
*/

#include "map.h"

static ssize_t get_dir(ssize_t from, ssize_t to, size_t size)
{
	if ((size_t) abs((int) (from - to)) * 2 < size)
		return (from - to);
	else
		return (size - from - to);
}

vec_t map_get_dir(map_t *map, vec_t from, vec_t to)
{
	vec_t vec = {get_dir(to.x, from.x, map->width),
			get_dir(to.y, from.y, map->height)};
	return (vec);
}

size_t map_get_abs(ssize_t n, size_t size)
{
	n = n % (ssize_t)size;
	return (n < 0 ? size + n : (size_t)n);
}

tile_t *map_get_tile(map_t *map, ssize_t x, ssize_t y)
{
	return (map->tiles[map_get_abs(y, map->height)]
		+ map_get_abs(x, map->width));
}
