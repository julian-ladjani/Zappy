/*
** EPITECH PROJECT, 2018
** SfmlTests
** File description:
** main.c
*/

#include <stdio.h>
#include <malloc.h>
#include "../../include/parser.h"

int main(int ac, char **av)
{
	cmdparams_t *cmd = parse_arguments(av[1], ";", 1);
	for(unsigned int i = 0; i < cmd->nb_args; ++i)
		printf("[%s]\n", cmd->args[i]);
	free(cmd->args);
	free(cmd);
}