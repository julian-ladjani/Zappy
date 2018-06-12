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
	char headings[8][3] = {"E", "NE", "N", "NW", "W", "SW", "S", "SE" };
	vec_t v = {(size_t) atoi(av[1]), (size_t) atoi(av[2])};
	int o = map_get_orientation(v, NORTH);
	printf("%d : %s\n", o, headings[o]);
	return (0);
}