/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command_exec.c
*/

#include "server_function.h"

static void initialise_user(server_config_t *server, server_user_t *user,
			server_team_t *team, server_egg_t *egg)
{
	user->type = ZAPPY_USER_AI;
	user->orientation = (cardinal_dir_t) rand() % 4 + 1;
	if (!egg) {
		user->pos.x = (ssize_t) rand() % server->map->width;
		user->pos.y = (ssize_t) rand() % server->map->height;
	} else {
		user->pos = egg->pos;
	}
	user->level = 1;
	empty_tile(&user->inventory, 1260);
	user->id = user->fd;
	user->incanting = 0;
	user->team = team;
	team->users = list_add_elem_at_pos(team->users, user, LIST_END);
}

static server_egg_t *search_egg_ready_for_team(list_t *eggs,
	server_team_t *team)
{
	server_egg_t *egg;

	while (eggs) {
		egg = eggs->elem;
		if (egg && egg->team == team && egg->wait <= 0)
			return (egg);
		eggs = eggs->next;
	}
	return (NULL);
}

static void join_message(server_config_t *server, server_user_t *user,
	server_team_t *team, server_egg_t *egg)
{
	char *msg = NULL;

	if (egg) {
		asprintf(&msg, "ebo %u\n", egg->id);
		send_msg_to_all_graphic(server, msg);
		free(msg);
	}
	asprintf(&msg, "pnw #%d %lu %lu %d %u %s\n", user->id, user->pos.x,
		user->pos.y, user->orientation, user->level, team->name);
	send_msg_to_all_graphic(server, msg);
	free(msg);
	if (egg) {
		asprintf(&msg, "edi %u\n", egg->id);
		send_msg_to_all_graphic(server, msg);
		free(msg);
	}
}

static void join_team(server_config_t *server,
	server_user_t *user, server_team_t *team)
{
	server_egg_t *egg = search_egg_ready_for_team(server->eggs, team);

	user->logged_state = ZAPPY_USER_CONNECTED;
	dprintf(user->fd, "%d\n%lu %lu\n",
		team ? get_team_free_slots(team) : 1,
		server->map->width, server->map->height);
	if (get_team_free_slots(team) > 0) {
		initialise_user(server, user, team, egg);
		map_add_bonus_food(server->map);
		join_message(server, user, team, egg);
	}
	if (!team) {
		user->type = ZAPPY_USER_GRAPHIC;
		user->id = -1;
	}
	if (egg) {
		server->eggs = list_delete_elem(
			list_get_elem_with_content(server->eggs, egg), NULL);
		free(egg);
	}
}

void try_to_join_team(server_config_t *server_config,
	server_user_t *user, cmdparams_t *cmdparams)
{
	list_t *team_list = server_config->teams;
	server_team_t *team;

	while (team_list) {
		team = team_list->elem;
		if (team && !strcmp(team->name, cmdparams->name))
			join_team(server_config, user, team);
		team_list = team_list->next;
	}
	if (!strcmp(ZAPPY_GRAPHIC_TEAM_NAME, cmdparams->name))
		join_team(server_config, user, NULL);
}
