/*
** EPITECH PROJECT, 2018
** linked_list_add
** File description:
** 	linked_list_add file_dir
*/

#include "linked_list.h"

static list_t *list_add_elem_at_last(list_t *elem_at_pos, list_t *new_elem)
{
	new_elem->prev = elem_at_pos;
	new_elem->next = NULL;
	if (elem_at_pos->next != NULL)
		elem_at_pos->next->prev = new_elem;
	elem_at_pos->next = new_elem;
	return (list_get_elem_at_pos(elem_at_pos, LIST_FIRST));
}

list_t *list_add_elem_at_pos(list_t *list, void *elem, int pos)
{
	list_t *new_elem = malloc(sizeof(list_t));
	list_t *elem_at_pos;

	elem_at_pos = list_get_elem_at_pos(list, pos);
	if (new_elem == NULL)
		return (NULL);
	new_elem->prev = NULL;
	new_elem->next = NULL;
	new_elem->elem = elem;
	new_elem->releasable = LIST_NOT_RELEASABLE;
	if (elem_at_pos == NULL)
		return (new_elem);
	if (pos >= list_size(list) || pos == LIST_END)
		return (list_add_elem_at_last(elem_at_pos, new_elem));
	new_elem->prev = elem_at_pos->prev;
	new_elem->next = elem_at_pos;
	if (elem_at_pos->prev != NULL)
		elem_at_pos->prev->next = new_elem;
	elem_at_pos->prev = new_elem;
	return (list_get_elem_at_pos(list, LIST_FIRST));
}

list_t *list_add_elem_at_pos_releasably(list_t *list,
	void *elem,
	int pos,
	list_releasably_t releasably)
{
	list_t *new_elem = malloc(sizeof(list_t));
	list_t *elem_at_pos;

	elem_at_pos = list_get_elem_at_pos(list, pos);
	if (new_elem == NULL)
		return (NULL);
	new_elem->prev = NULL;
	new_elem->next = NULL;
	new_elem->elem = elem;
	new_elem->releasable = releasably;
	if (elem_at_pos == NULL)
		return (new_elem);
	if (pos >= list_size(list) || pos == LIST_END)
		return (list_add_elem_at_last(elem_at_pos, new_elem));
	new_elem->prev = elem_at_pos->prev;
	new_elem->next = elem_at_pos;
	if (elem_at_pos->prev != NULL)
		elem_at_pos->prev->next = new_elem;
	elem_at_pos->prev = new_elem;
	return (list_get_elem_at_pos(list, LIST_FIRST));
}

list_t *list_add_elem_at_pos_alloc(list_t *list,
	void *elem,
	int pos,
	size_t elem_size)
{
	list_byte_t *new_elem = NULL;

	if (elem != NULL) {
		new_elem = malloc(elem_size);
		memcpy(new_elem, elem, elem_size);
	}
	return (list_add_elem_at_pos_releasably(list, new_elem, pos,
		LIST_RELEASABLE));
}

list_t *list_add_tab(list_t *list,
	list_byte_t *tab,
	size_t elem_size,
	size_t nb_elem)
{
	for (size_t idx = 0; idx < nb_elem; idx++) {
		list = list_add_elem_at_pos_alloc(list, tab, LIST_END,
			elem_size);
		tab += elem_size;
	}
	return (list);
}