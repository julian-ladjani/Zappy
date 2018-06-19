/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** fork.c
*/

#include "server_function.h"

static server_egg_t *create_egg(server_user_t *user)
{
	server_egg_t *egg = malloc(sizeof(egg));

	if (!egg)
		return (NULL);
	egg->pos = user->pos;
	egg->team = user->team;
	egg->wait = 642;
	egg->id = 0;
	return (egg);
}

uint8_t srv_cmd_fork(server_config_t *server, server_user_t *user,
	__attribute__((unused))cmdparams_t *cmd)
{
	server_egg_t *egg = create_egg(user);
	char *msg;

	if (!egg) {
		dprintf(user->fd, "ko\n");
		return (1);
	}
	server->eggs = list_add_elem_at_pos(server->eggs, egg, LIST_END);
	asprintf(&msg, "pfk %d\nenw %d %d %lu %lu\n", user->id, egg->id,
		user->id, egg->pos.x, egg->pos.y);
	send_msg_to_all_graphic(server, msg);
	dprintf(user->fd, "ok\n");
	user->wait += 42;
	free(msg);
	return (0);
}
