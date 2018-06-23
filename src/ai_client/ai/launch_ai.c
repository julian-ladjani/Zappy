/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** launch_ai.c
*/

#include "client.h"
#include "ai_modes.h"

size_t get_ai_logic(ai_mode_t mode)
{
	for (size_t i = 0; ais[i].logic; ++i)
		if (ais[i].type == mode)
			return (i);
	return (0);
}

void launch_ai(clt_config_t *clt)
{
	size_t index = get_ai_logic(clt->specs->ai_mode);
	ai_mode_t ai_mode = SEARCHER;
	ai_mode_t last_ai_mode = SEARCHER;

	while (clt->status != ZAPPY_CLT_DEAD) {
		if (ais[index].logic(clt) == ZAPPY_EXIT_FAILURE)
			return;
		if (ai_mode != clt->specs->ai_mode) {
			if (clt->specs->ai_mode == LAST_MODE) {
				index = get_ai_logic(last_ai_mode);
				clt->specs->ai_mode = last_ai_mode;
			} else
				index = get_ai_logic(clt->specs->ai_mode);
			last_ai_mode = ai_mode;
			ai_mode = clt->specs->ai_mode;
		}
	}
}
