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
	clt_func_t stop_condition;
} ai_builder_t;

#endif /* PSU_ZAPPY_2017_AI_MODES_H */