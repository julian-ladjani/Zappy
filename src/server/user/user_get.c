/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_get source file
*/

#include "server_struct.h"
#include "server_function.h"

server_user_t *get_user_by_name(server_user_t *users, int nb_user, char *name)
{
	for (int i = 0; i < nb_user; i++) {
		if (strcasecmp(users[i].name, name) == 0)
			return (&(users[i]));
	}
	return (NULL);
}

server_user_t *get_user_by_fd(server_config_t *server_config, int fd)
{
	list_t *elem = list_get_elem_by_search(server_config->users, &fd,
		user_fd_search_criteria);

	if (elem == NULL)
		return (NULL);
	return (elem->elem);
}

int check_user_pass(server_user_t *user, char *password)
{
	if ((password == NULL || password[0] == '\0') &&
		(user->password == NULL || user->password[0] == '\0'))
		return (ZAPPY_EXIT_SUCCESS);
	if (password == NULL || user->password == NULL)
		return (ZAPPY_EXIT_FAILURE);
	if (strcmp(user->password, password) == 0)
		return (ZAPPY_EXIT_SUCCESS);
	return (ZAPPY_EXIT_FAILURE);
}