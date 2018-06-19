/*
** EPITECH PROJECT, 2018
** Julian's library
** File description:
** 	linked_list header
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//Warning : Use encapsulated functions with this defines !!!

#define LIST_END (-1)
#define LIST_FIRST (0)
#define LIST_ALL (-2)
#define LIST_BEFORE (-3)
#define LIST_AFTER (-4)

typedef enum {
	LIST_NOT_RELEASABLE,
	LIST_RELEASABLE,
} list_releasably_t;

typedef char list_byte_t;

typedef struct list_s {
	void *elem;
	list_releasably_t releasable;
	struct list_s *next;
	struct list_s *prev;
} list_t;

//basics

void list_dump(list_t *list, void (*dump_function)(void *));
list_t *list_sort(list_t *list,
	int (*comp_function)(const void *, const void *));
int list_size(list_t *list);
void list_swap(list_t *a, list_t *b);

//advanced

list_t *list_merge(list_t *a, list_t *b);
list_t *list_split(list_t *list, int pos);

//add

list_t *list_create(void *elem);
list_t *list_add_elem_at_pos(list_t *list, void *elem, int pos);
list_t *list_add_elem_at_pos_alloc(list_t *list, void *elem, int pos,
	size_t elem_size);
list_t *list_add_tab(list_t *list, list_byte_t *tab, size_t elem_size,
	size_t nb_elem);
list_t *list_add_elem_at_pos_releasably(list_t *list, void *elem, int pos,
	list_releasably_t releasably);

//delete

list_t *list_delete_after(list_t *elem, void (*clean_func)(void *elem));
list_t *list_delete_before(list_t *elem, void (*clean_func)(void *elem));
list_t *list_delete_elem(list_t *oelem, void (*clean_func)(void *elem));
list_t *list_delete_all(list_t *list, void (*clean_func)(void *elem));
list_t *list_delete_at_pos(list_t *list, int pos,
	void (*clean_func)(void *elem));

//clean

list_t *list_clean_after(list_t *elem);
list_t *list_clean_before(list_t *elem);
list_t *list_clean_elem(list_t *elem);
list_t *list_clean_all(list_t *list);
list_t *list_clean_at_pos(list_t *list, int pos);

//conditional

list_t *list_get_elem_if_exist(list_t *list, list_t *elem);
list_t *list_get_elem_if_not_exist(list_t *list, list_t *elem);
list_t *list_get_elem_by_search(list_t *list, void *criteria,
	int (*search_func)(void *elem, void *criteria));
int list_count_elem_by_search(list_t *list, void *criteria,
	int (*search_func)(void *elem, void *criteria));
list_t *list_get_next_elem_by_search(list_t *elem, void *criteria,
	int (*search_func)(void *elem, void *criteria));

//get

list_t *list_get_elem(list_t *list, list_t *elem);
list_t *list_get_elem_with_content(list_t *list, void *elem);
list_t *list_get_first(list_t *list);
list_t *list_get_elem_at_pos(list_t *list, int pos);

#endif //LINKED_LIST_H
