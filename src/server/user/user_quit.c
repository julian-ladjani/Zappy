/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_quit source file
*/

#include "server_struct.h"
#include "server_function.h"

static void user_quit_part_teams(server_user_t *user)
{
	if (user->team != NULL)
		user->team->users = list_delete_elem(
			list_get_elem_with_content(user->team->users, user),
			NULL);
	user->team = NULL;
}

void user_quit(server_config_t *server_config, server_user_t *user,
	char *message)
{
	char *str;

	if (server_config == NULL || user == NULL || message == NULL)
		return;
	printf("Connection - %d Quit With Message: %s\n", user->fd,
		message);
	if (user->type == ZAPPY_USER_AI && user->team != NULL) {
		map_add_inventory_on_tile(map_get_tile(server_config->map,
			user->pos.x, user->pos.y), &user->inventory);
		if ((size_t) user->team->slots >
			server_config->arguments->client_nb)
			user->team->slots -= 1;
		asprintf(&str, "pdi %d\n", user->id);
		send_msg_to_all_graphic(server_config, str);
		free(str);
	}
	user->logged_state = ZAPPY_USER_QUIT;
	user_quit_part_teams(user);
}
