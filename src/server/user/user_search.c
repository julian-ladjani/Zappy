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

int user_no_team_search_criteria(void *user,
	__attribute__((unused)) void *name)
{
	if (user == NULL)
		return (0);
	if (((server_user_t *) user)->team == NULL)
		return (1);
	return (0);
}

server_user_t *find_user_by_id(server_config_t *server, int id)
{
	list_t *user_list = server->users;
	server_user_t *user;

	while (user_list) {
		user = user_list->elem;
		if (user && user->id == id)
			return (user);
		user_list = user_list->next;
	}
	return (NULL);
}

int find_nb_user_at_pos(server_config_t *server_config,
	ssize_t x, ssize_t y)
{
	list_t *user_list = server_config->users;
	server_user_t *user;
	int nb_user = 0;

	x = map_get_abs(x, server_config->map->width);
	y = map_get_abs(y, server_config->map->height);
	while (user_list) {
		user = user_list->elem;
		if (user && user->pos.x == x && user->pos.y == y)
			++nb_user;
		user_list = user_list->next;
	}
	return (nb_user);
}

int find_nb_user_at_pos_and_level(server_config_t *server_config,
	ssize_t x, ssize_t y, unsigned int level)
{
	list_t *user_list = server_config->users;
	server_user_t *user;
	int nb_user = 0;

	x = map_get_abs(x, server_config->map->width);
	y = map_get_abs(y, server_config->map->height);
	while (user_list) {
		user = user_list->elem;
		if (user && user->pos.x == x && user->pos.y == y) {
			if (user->level != level)
				return (0);
			++nb_user;
		}
		user_list = user_list->next;
	}
	return (nb_user);
}
