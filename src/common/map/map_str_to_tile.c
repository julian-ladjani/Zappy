/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** create_map.c
*/

#include "parser.h"
#include "map.h"

void str_to_tile(char *str, tile_t *tile)
{
	for (unsigned int i = 0; obj_names[i]; ++i) {
		*tile[i] = count_str(str, obj_names[i]);
	}
}
