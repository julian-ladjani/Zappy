/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_search source file
*/

#include "server_struct.h"

int user_fd_search_criteria(void *user, void *fd)
{
	int *fd_int = fd;

	if (user == NULL || fd == NULL)
		return (0);
	if (((server_user_t *) user)->fd == *fd_int)
		return (1);
	return (0);
}

int user_nick_search_criteria(void *user, void *nick)
{
	char *nick_str = nick;

	if (user == NULL || nick == NULL)
		return (0);
	if (((server_user_t *) user)->nick == NULL)
		return (0);
	if (strcmp(((server_user_t *) user)->nick, nick_str) == 0)
		return (1);
	return (0);
}

int user_name_search_criteria(void *user, void *name)
{
	char *name_str = name;

	if (user == NULL || name == NULL)
		return (0);
	if (((server_user_t *) user)->name == NULL)
		return (0);
	if (strcmp(((server_user_t *) user)->nick, name_str) == 0)
		return (1);
	return (0);
}

int user_no_channel_search_criteria(void *user,
	__attribute__((unused)) void *name)
{
	if (user == NULL)
		return (0);
	if (((server_user_t *) user)->channels == NULL)
		return (1);
	return (0);
}