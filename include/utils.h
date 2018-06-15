/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	utils header file
*/

#ifndef PSU_ZAPPY_2017_UTILS_H
#define PSU_ZAPPY_2017_UTILS_H

#include <stdlib.h>

//str_append

char *str_append(char *str, char *append);

//tab_cpy

char **tab_ncpy(char **dst, char **src, size_t len);
char **tab_mncpy(char **dst, char **src, size_t len);
size_t tab_len(char **tab);
char **tab_mcpy(char **dst, char **src);
char **tab_cpy(char **dst, char **src);

#endif //PSU_ZAPPY_2017_UTILS_H
