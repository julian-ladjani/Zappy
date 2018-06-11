/*
** EPITECH PROJECT, 2018
** linked_list_create
** File description:
** 	linked_list_create file_dir
*/

#include "linked_list.h"

list_t *list_create(void *elem)
{
	return (list_add_elem_at_pos(NULL, elem, LIST_FIRST));
}
