/*
** EPITECH PROJECT, 2018
** linked_list_advanced
** File description:
** 	linked_list_advanced file_dir
*/

#include "linked_list.h"

list_t *list_merge(list_t *a, list_t *b)
{
	list_t *a_last;

	if (a == NULL || b == NULL)
		return (a);
	a = list_get_elem_at_pos(a, LIST_FIRST);
	b = list_get_elem_at_pos(b, LIST_FIRST);
	if (list_get_elem(a, b) != NULL || list_get_elem(b, a) != NULL)
		return (a);
	a_last = list_get_elem_at_pos(a, LIST_END);
	a_last->next = b;
	b->prev = a_last;
	return (a);
}

list_t *list_split(list_t *list, int pos)
{
	list_t *elem_at_pos;

	if (list == NULL)
		return (NULL);
	list = list_get_elem_at_pos(list, LIST_FIRST);
	elem_at_pos = list_get_elem_at_pos(list, pos);
	if (elem_at_pos == NULL || elem_at_pos == list)
		return (list);
	if (elem_at_pos->prev)
		elem_at_pos->prev->next = NULL;
	elem_at_pos->prev = NULL;
	return (elem_at_pos);
}
