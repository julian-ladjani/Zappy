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
	map_t *map = create_map(100, 100);
	print_map(map);
	return (0);
}