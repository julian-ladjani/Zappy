/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_create.c
*/

#include "map.h"

void map_print(map_t *map)
{
	for (size_t y = 0; y < map->height; ++y) {
		for (size_t x = 0; x < map->width; ++x)
			putchar('.');
		putchar('\n');
	}
}