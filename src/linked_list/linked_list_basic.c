/*
** EPITECH PROJECT, 2018
** linked_list_basic
** File description:
** 	linked_list_basic file_dir
*/

#include "linked_list.h"

int list_size(list_t *list)
{
	int size = 0;

	while (list != NULL) {
		list = list->next;
		size++;
	}
	return (size);
}

void list_swap(list_t *a, list_t *b)
{
	list_t *tmp;

	if (a == NULL || b == NULL)
		return;
	tmp = a->next;
	if (a->next != NULL)
		a->next->prev = b;
	a->next = b->next;
	if (b->next != NULL)
		b->next->prev = a;
	b->next = tmp;
	tmp = a->prev;
	if (a->prev != NULL)
		a->prev->next = b;
	a->prev = b->prev;
	if (b->prev != NULL)
		b->prev->next = a;
	b->prev = tmp;
}

list_t *list_sort(list_t *list,
	int (*comp_function)(const void *, const void *))
{
	list_t *elem;
	int cmp;

	elem = list_get_elem_at_pos(list, LIST_FIRST);
	while (elem != NULL && elem->next != NULL) {
		cmp = comp_function(elem->elem, elem->next->elem);
		if (cmp > 0) {
			list_swap(elem, elem->next);
			elem = list_get_elem_at_pos(list, LIST_FIRST);
		} else if (cmp > 0) {
			list_swap(elem->next, elem);
			elem = list_get_elem_at_pos(list, LIST_FIRST);
		} else
			elem = elem->next;
	}
	return (list_get_elem_at_pos(list, LIST_FIRST));
}

void list_dump(list_t *list, void (*dump_function)(void *))
{
	while (list != NULL) {
		dump_function(list->elem);
		list = list->next;
	}
}