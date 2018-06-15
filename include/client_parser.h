/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client.h
*/

#ifndef PSU_ZAPPY_2017_CLIENT_PARSER_H
#define PSU_ZAPPY_2017_CLIENT_PARSER_H

#include "client.h"

typedef void (* clt_parse_func_t)(clt_params_t *params, char *arg);

typedef struct parse_client_s
{
	char *flag;
	clt_parse_func_t func;
} parse_client_t;

void parse_port(clt_params_t *params, char *arg);
void parse_machine(clt_params_t *params, char *arg);
void parse_team(clt_params_t *params, char *arg);

parse_client_t parsefunc[4] = {
	{"-p", parse_port},
	{"-h", parse_machine},
	{"-n", parse_team},
	{NULL, NULL}
};

#endif /* PSU_ZAPPY_2017_CLIENT_PARSER_H */