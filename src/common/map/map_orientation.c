/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** create_map.c
*/

#include <math.h>
#include "map.h"

static uint8_t map_get_orientation_norm_fix(double angle)
{
	if (angle <= (-3 * M_PI) / 4 + M_PI / 8 &&
		angle >= (-3 * M_PI) / 4 - M_PI / 8)
		return (4);
	if (angle <= -M_PI / 2 + M_PI / 8 && angle >= -M_PI / 2 - M_PI / 8)
		return (5);
	if (angle <= -M_PI / 4 + M_PI / 8 && angle >= -M_PI / 4 - M_PI / 8)
		return (6);
	if (angle <= M_PI / 8 && angle >= -M_PI / 8)
		return (7);
	return (8);
}

uint8_t map_get_orientation(vec_t dir)
{
	double angle;

	if (dir.x == 0 && dir.y == 0)
		return (0);
	angle = atan2(dir.y, dir.x);
	if (angle <= M_PI / 2 + M_PI / 8 && angle >= M_PI / 2 - M_PI / 8)
		return (1);
	if (angle <= (3 * M_PI) / 4 + M_PI / 8 &&
		angle >= (3 * M_PI) / 4 - M_PI / 8)
		return (2);
	if (angle >= M_PI - M_PI / 8 || angle <= -M_PI + M_PI / 8)
		return (3);
	return (map_get_orientation_norm_fix(angle));
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
