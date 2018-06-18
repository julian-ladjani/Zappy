/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** eject.c
*/

#include "server_function.h"

static uint8_t eject_user(server_user_t *user, cardinal_dir_t dir, map_t *map)
{
	switch (dir) {
		case (NORTH):
			user->pos.y = map_get_abs(user->pos.y + 1,
				map->height);
			return (5);
		case (EAST):
			user->pos.x = map_get_abs(user->pos.x + 1,
				map->width);
			return (3);
		case (SOUTH):
			user->pos.y = map_get_abs(user->pos.y - 1,
				map->height);
			return (1);
		case (WEST):
			user->pos.x = map_get_abs(user->pos.x - 1,
				map->width);
			return (7);
	}
	return (0);
}

static void eject_other_ai(server_config_t *server, server_user_t *emitter)
{
	list_t *user_list = server->users;
	server_user_t *user;

	while (user_list) {
		user = user_list->elem;
		if (user && user != emitter
			&& user->pos.x == emitter->pos.x &&
			user->pos.y == emitter->pos.y) {
			dprintf(user->fd, "eject: %u\n",
				map_rotate_orientation(
					user->orientation,
					eject_user(user,
						emitter->orientation,
						server->map)));
		}
		user_list = user_list->next;
	}
}

uint8_t srv_cmd_eject(server_config_t *server, server_user_t *user,
	__attribute__((unused))cmdparams_t *cmd)
{
	char *msg;

	if (find_nb_user_at_pos(server, user->pos.x, user->pos.y) < 1) {
		dprintf(user->fd, "ko\n");
		return (1);
	}
	asprintf(&msg, "pex %d\n", user->id);
	send_msg_to_all_graphic(server, msg);
	eject_other_ai(server, user);
	dprintf(user->fd, "ok\n");
	user->wait += 7;
	free(msg);
	return (0);
}
