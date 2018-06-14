/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command_parser.cpp
*/

#include "parser.h"

static unsigned int count_sep(const char *str, const char *sep)
{
	char *tmp = strstr(str, sep);
	return (tmp ? count_sep(tmp + strlen(sep), sep) + (tmp != str) : 0);
}

static cmdparams_t *new_cmdparams(const char *str, const char *sep)
{
	cmdparams_t *cmd = calloc(sizeof(cmdparams_t), sizeof(cmdparams_t));

	if (!cmd) {
		dprintf(2, "Invalid malloc in new_cmdparams\n");
		return (NULL);
	}
	cmd->nb_args = count_sep(str, sep);
	cmd->args = malloc(sizeof(char *) * (count_sep(str, sep)));
	if (!cmd->args) {
		dprintf(2, "Invalid malloc in new_cmdparams\n");
		return (NULL);
	}
	return (cmd);
}

static void parse_parameters(cmdparams_t *cmdparams, char *cmd, const char *sep)
{
	cmdparams->name = strtok(cmd, sep);
	for (unsigned int i = 0; i < cmdparams->nb_args; ++i) {
		cmdparams->args[i] = strtok(NULL, sep);
		if (!cmdparams->args[i]) {
			cmdparams->nb_args = i;
			break;
		}
	}
}

cmdparams_t *parse_arguments(char *cmd, const char *sep)
{
	cmdparams_t *cmdparams = new_cmdparams(cmd, sep);

	if (!cmdparams || !cmd)
		return (NULL);
	parse_parameters(cmdparams, cmd, sep);
	return (cmdparams);
}

void free_arguments(void *cmd)
{
	cmdparams_t *cmdparams = (cmdparams_t *)cmd;

	if(!cmdparams)
		return;
	if (cmdparams->args)
		free(cmdparams->args);
	free(cmdparams);
}
