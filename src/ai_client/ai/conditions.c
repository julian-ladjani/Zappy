/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** conditions.c
*/

#include <client.h>

int tilecmp(tile_t *t1, tile_t *t2)
{
	int rslt = 0;

	for (unsigned int i = 1; i < 7; ++i) {
		if ((*t1)[i] < (*t2)[i])
			return (-1);
		rslt |= ((*t2)[i] - (*t1)[i]);
	}
	return (rslt != 0);
}

int condition_end_incantation(clt_config_t *clt)
{
	static int last_level = 0;

	if (last_level != clt->specs->level) {
		last_level = clt->specs->level;
		return (1);
	}
	return (0);
}

int condition_pre_incantation(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	tile_t *ref = (tile_t *) (INCANTATION_OBJ + clt->specs->level);

	if (tilecmp(tile, ref) == 0 && ref[PLAYER] > tile[PLAYER]) {
		return (1);
	}
	return (0);
}