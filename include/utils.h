/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	utils header file
*/

#ifndef PSU_ZAPPY_2017_UTILS_H
#define PSU_ZAPPY_2017_UTILS_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//str_append

char *str_append(char *str, const char *append);
char *str_append_number(char *str, const unsigned int num);

//tab_cpy

char **tab_ncpy(char **dst, char **src, size_t len);
char **tab_mncpy(char **dst, char **src, size_t len);
size_t tab_len(char **tab);
char **tab_mcpy(char **dst, char **src);
char **tab_cpy(char **dst, char **src);

//epurstr

typedef int (*checker_t)(char c);
void epurstr(char *str, checker_t);

#endif //PSU_ZAPPY_2017_UTILS_H
