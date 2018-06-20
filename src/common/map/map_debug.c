/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_create.c
*/

#include "map.h"
#include "map_debug.h"

static void print_tile_row(tile_t *tile, uint8_t start, uint8_t end)
{
	char *end_color = "\e[0m";

	printf("|");
	for (uint8_t i = start; i < end; ++i) {
		if (i < 8 && (*tile)[i] > 0) {
			if ((*tile)[i] <= 9)
				printf("%s%s%c%ld%s", colors[i],
					compl_colors[i], OBJ_NAMES[i][0] - 32,
					(*tile)[i], end_color);
			else
				printf("%s%s%c+%s", colors[i], compl_colors[i],
					OBJ_NAMES[i][0] - 32, end_color);
		} else
			printf("  ");
	}
}

static void print_line(map_t *map)
{
	for (size_t x = 0; x < map->width; ++x)
		printf("+------");
	printf("+\n");
}

static void print_tile(map_t *map, size_t y, uint8_t i)
{
	for (size_t x = 0; x < map->width; ++x) {
		print_tile_row(map->tiles[y] + x,
				(uint8_t) (i * 3), (uint8_t) (i * 3 + 3));
	}
	printf("|\n");
}

void print_map(map_t *map)
{
	for (size_t i = 0; OBJ_NAMES[i] ;++i)
		printf("%s%s%s\e[0m\n", colors[i],
			compl_colors[i], OBJ_NAMES[i]);
	print_line(map);
	for (size_t y = 0; y < map->height; ++y) {
		for (uint8_t i = 0; i < 3; ++i)
			print_tile(map, y, i);
		print_line(map);
	}
}
