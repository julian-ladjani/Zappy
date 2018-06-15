/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** parser.c
*/

#include <client_parser.h>

void parse_port(clt_params_t *params, char *arg)
{
	if (is_number(arg))
		params->port = atoi(arg);
}

void parse_machine(clt_params_t *params, char *arg)
{
	params->machine = arg;
}

void parse_team(clt_params_t *params, char *arg)
{
	params->team = arg;
}

static void client_parse_find_option(clt_params_t *params, char **arg)
{
	for (parse_client_t *p = parsefunc; p->flag; ++p) {
		if (strcmp(arg[0], p->flag) == 0) {
			p->func(params, arg[1]);
			break;
		}
	}
}

clt_params_t *client_parse_arguments(int ac, char **av)
{
	clt_params_t *params = calloc(sizeof(clt_params_t),
					sizeof(clt_params_t));

	if (!params)
		return (NULL);
	if (ac == 1 && strcmp("-help", av[0]) == 0)
		show_help_client();
	for (int i = 0; i + 1 < ac; i += 2)
		client_parse_find_option(params, av + i);
	if (!params->team || !params->machine || !params->port)
		return (NULL);
	return (params);
}