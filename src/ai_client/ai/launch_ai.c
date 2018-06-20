/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** launch_ai.c
*/

#include "client.h"
#include "ai_modes.h"

size_t get_ai_logic(ai_mode_t mode, ai_builder_t *ais)
{
	for (size_t i = 0; ais[i].logic; ++i)
		if (ais[i].type == mode)
			return (i);
	return (0);
}

void launch_ai(clt_config_t *clt)
{
	ai_builder_t ais[4] = {
		{SEARCHER, ai_searcher, condition_pre_incantation},
		{SHOUTER, ai_shouter, condition_end_incantation},
		{FOLLOWER, ai_follower, condition_end_incantation},
		{FOLLOWER, NULL, NULL}};
	size_t index = get_ai_logic(clt->specs->ai_mode, ais);

	while (clt->status != ZAPPY_CLT_DEAD) {
		if (ais[index].logic(clt) == ZAPPY_EXIT_FAILURE)
			return;
		if (ais[index].stop_condition(clt))
			index = get_ai_logic(clt->specs->ai_mode, ais);
	}
}
