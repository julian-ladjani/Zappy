#include <stdint.h>

/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** is_str.c
*/

uint8_t is_number(const char *str)
{
	for (; *str; ++str)
		if (*str < '0' || *str > '9')
			return (0);
	return (1);
}