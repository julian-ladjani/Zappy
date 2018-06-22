/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai_modes.h
*/

#ifndef PSU_ZAPPY_2017_AI_MODES_H
#define PSU_ZAPPY_2017_AI_MODES_H

#include "client.h"

typedef struct ai_logic_builder_s {
	ai_mode_t type;
	clt_func_t logic;
} ai_builder_t;

const ai_builder_t ais[4] = {
	{SEARCHER, ai_searcher},
	{SHOUTER, ai_shouter},
	{FOLLOWER, ai_follower},
	{DEBILOUS, NULL}};

#endif /* PSU_ZAPPY_2017_AI_MODES_H */