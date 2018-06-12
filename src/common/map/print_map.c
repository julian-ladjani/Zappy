/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** create_map.c
*/

#include "../../../include/map.h"

void print_map(map_t *map)
{
	for (size_t y = 0; y < map->height; ++y) {
		for (size_t x = 0; x < map->width; ++x)
			putchar('.');
		putchar('\n');
	}
}