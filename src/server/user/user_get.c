/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_get source file
*/

#include "server_struct.h"
#include "server_function.h"

server_user_t *get_user_by_fd(server_config_t *server_config, int fd)
{
	list_t *elem = list_get_elem_by_search(server_config->users, &fd,
		user_fd_search_criteria);

	if (elem == NULL)
		return (NULL);
	return (elem->elem);
}
