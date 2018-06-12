/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** parser.h
*/

#ifndef PSU_ZAPPY_2017_CMD_PARSER_H
#define PSU_ZAPPY_2017_CMD_PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct command_parameters_s
{
	char **args;
	char *name;
	int from;
	unsigned int nb_args;
} cmdparams_t;

typedef enum access_mode_s
{
	ZPY_CONNECTED,
	ZPY_WHATEVER,
	ZPY_NOT_CONNECTED
} access_mode_t;

cmdparams_t *parse_arguments(char *cmd, const char *sep, int from);
void free_arguments(cmdparams_t *cmd);

#endif /* PSU_ZAPPY_2017_CMD_PARSER_H */