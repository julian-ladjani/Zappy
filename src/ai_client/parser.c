/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** parser.c
*/

#include <client_parser.h>

int parse_port(clt_params_t *params, char *arg)
{
	if (is_number(arg))
		params->port = atoi(arg);
	return (1);
}

int parse_machine(clt_params_t *params, char *arg)
{
	params->machine = arg;
}

int parse_team(clt_params_t *params, char *arg)
{
	params->team = arg;
}

clt_params_t *client_parse_arguments(int ac, char **av)
{
	clt_params_t *params = calloc(sizeof(clt_params_t),
					sizeof(clt_params_t));

	if (!params)
		return (NULL);
	for (int i = 0; i + 1 < ac; i += 2) {
		for (parse_client_t *p = parsefunc; p->flag; ++p) {
			if (strcmp(av[i], p->flag) == 0) {
				p->func(params, av[i + 1]);
				break;
			}
		}
	}
	if (!params->team || !params->machine || !params->port)
		return (NULL);
	return (params);
}