/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** create_map.c
*/

#include <math.h>
#include "map.h"

uint8_t map_get_orientation(vec_t dir)
{
	double angle;
	uint8_t piece;

	if (dir.x == 0 && dir.y == 0)
		return (0);
	angle = atan2(dir.y, dir.x);
	if (angle < 0)
		angle += 2 * M_PI;
	piece = (uint8_t) (8 * angle / (2 * M_PI));
	piece = (uint8_t) (piece >= 8 ? 8 : (8 - (piece + 1)));
	if (piece <= 2 || piece == 4 || piece == 5)
		return ((uint8_t) (6 - piece));
	if (piece == 6 || piece == 8)
		return (piece == 6 ? 8 : 6);
	return (piece);
}

uint8_t map_rotate_orientation(cardinal_dir_t dir, uint8_t orientation)
{
	if (orientation == 0)
		return (orientation);
	switch (dir) {
	case (NORTH):
		return (orientation);
	case (EAST):
		return ((uint8_t) ((orientation + 1) % 8 + 1));
	case (SOUTH):
		return ((uint8_t) ((orientation + 3) % 8 + 1));
	case (WEST):
		return ((uint8_t) ((orientation + 5) % 8 + 1));
	}
	return (orientation);
}
