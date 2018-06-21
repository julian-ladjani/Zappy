/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** fork.c
*/

#include "server_function.h"

static server_egg_t *search_egg_by_id(list_t *egg_list, unsigned int id)
{
	server_egg_t *egg;

	while (egg_list) {
		egg = egg_list->elem;
		if (egg->id == id)
			return (egg);
		egg_list = egg_list->next;
	}
	return (NULL);
}

static unsigned int get_new_egg_id(server_config_t *server)
{
	unsigned int id = 0;

	while (id < 0xffffffff) {
		if (!search_egg_by_id(server->eggs, id))
			return (id);
		++id;
	}
	return (0xffffffff);
}

static server_egg_t *create_egg(server_user_t *user, unsigned int id)
{
	server_egg_t *egg = malloc(sizeof(server_egg_t));

	if (!egg)
		return (NULL);
	egg->pos = user->pos;
	egg->team = user->team;
	egg->wait = 642;
	egg->id = id;
	return (egg);
}

uint8_t srv_cmd_fork(server_config_t *server, server_user_t *user,
	__attribute__((unused))cmdparams_t *cmd)
{
	server_egg_t *egg = create_egg(user, get_new_egg_id(server));
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
