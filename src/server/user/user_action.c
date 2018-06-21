/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_action source file
*/

#include <sys/param.h>
#include "server_struct.h"
#include "linked_list.h"
#include "server_function.h"


void user_disconect_when_quit_state(server_config_t *server)
{
	list_t *users = list_get_first(server->users);
	server_user_t *user;

	while (users != NULL) {
		user = users->elem;
		if (user != NULL && user->logged_state == ZAPPY_USER_QUIT)
			close_socket_poll_with_user(server, user);
		users = users->next;
	}
}

static void user_action_user_wait_action(server_config_t *server,
	server_user_t *user, unsigned int nb_tick)
{
	user->inventory[0] = MAX(0, ((int) user->inventory[0]) - nb_tick);
	if (user->inventory[0]) {
		dprintf(user->fd, "dead\n");
		user_quit(server, user, "IA No Food die");
	}
	if (user->wait != 0 || user->incanting == 0)
		return;
	incantation_end(server, user);
}

void user_action_sup_wait(server_config_t *server, unsigned int nb_tick)
{
	list_t *users = list_get_first(server->users);
	server_user_t *user;

	while (users != NULL) {
		user = users->elem;
		if (user != NULL && user->type == ZAPPY_USER_AI) {
			user->wait = MAX(0, user->wait - nb_tick);
			user_action_user_wait_action(server, user, nb_tick);
		}
		users = users->next;
	}
}

static void user_action_egg_wait_raise_null(server_config_t *server,
	server_egg_t *egg)
{
	char *str;
	if (egg->wait != 0)
		return;
	egg->team->slots++;
	asprintf(&str, "eht %d\n", egg->id);
	send_msg_to_all_graphic(server, str);
	free(str);
}

void user_action_egg_sup_wait(server_config_t *server, unsigned int nb_tick)
{
	list_t *eggs = list_get_first(server->eggs);
	server_egg_t *egg;

	while (eggs != NULL) {
		egg = eggs->elem;
		if (egg != NULL && egg->wait != 0) {
			egg->wait = MAX(0, egg->wait - nb_tick);
			user_action_egg_wait_raise_null(server, egg);
		}
		eggs = eggs->next;
	}
}