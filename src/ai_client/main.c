/*
** EPITECH PROJECT, 2018
** SfmlTests
** File description:
** main.c
*/

#include <stdio.h>
#include <malloc.h>
#include "../../include/parser.h"
#include "../../include/map.h"

int main(int ac, char **av)
{
	vec_t v = {(size_t) atoi(av[1]), (size_t) atoi(av[2])};
	int o = map_get_orientation(v);
	printf("%d : ", o);
	return (0);
}