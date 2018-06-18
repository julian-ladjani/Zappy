/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command_exec.c
*/

#include "server_function.h"

static void initialise_user(server_config_t *server_config,
			server_user_t *user, server_team_t *team)
{
	user->type = ZAPPY_USER_AI;
	user->orientation = rand() % 4 + 1;
	user->x = rand() % server_config->map->width;
	user->y = rand() % server_config->map->height;
	user->level = 1;
	empty_tile(&user->inventory);
	user->inventory[FOOD] = 1260;
	user->id = server_config->new_user_id;
	server_config->new_user_id += 1;
	team->users = list_add_elem_at_pos(team->users, user, LIST_END);
}

static void join_team(server_config_t *server_config,
			server_user_t *user, server_team_t *team)
{
	char *msg = NULL;

	user->logged_state = ZAPPY_USER_CONNECTED;
	dprintf(user->fd, "%d\n%lu %lu\n", team ? get_team_free_slots(team) : 1,
		server_config->map->width, server_config->map->height);
	if (get_team_free_slots(team) > 0) {
		initialise_user(server_config, user, team);
		asprintf(&msg, "pnw #%d %u %u %d %u %s\n", user->id, user->x,
			user->y, user->orientation, user->level, team->name);
		send_msg_to_all_graphic(server_config, msg);
		free(msg);
	}
	if (!team) {
		user->type = ZAPPY_USER_GRAPHIC;
		user->id = -1;
	}

}

void try_to_join_team(server_config_t *server_config,
				server_user_t *user, cmdparams_t *cmdparams)
{
	list_t *team_list = server_config->teams;
	server_team_t *team;

	while (team_list) {
		team = (server_team_t *)list_get_elem_at_pos(team_list,
								LIST_FIRST);
		if (team && !strcmp(team->name, cmdparams->name))
			join_team(server_config, user, team);
		team_list = team_list->next;
	}
	if (!strcmp(ZAPPY_GRAPHIC_TEAM_NAME, cmdparams->name))
		join_team(server_config, user, NULL);
}
