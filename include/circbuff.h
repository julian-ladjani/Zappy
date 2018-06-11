/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** circbuff.h
*/

#ifndef PSU_MYIRC_2017_CIRCBUFF_H
#define PSU_MYIRC_2017_CIRCBUFF_H

#define CIRCBUF_SIZE() 1024

typedef struct circbuf_s circbuf_t;
typedef long int (* filefunc_t)(int , circbuf_t *, unsigned int);
typedef void (* printfunc_t)(int , circbuf_t *);
typedef char *(* nextfunc_t)(circbuf_t *, char *);
typedef char *(* buffunc_t)(circbuf_t *);
typedef char *(* nbuffunc_t)(circbuf_t *, unsigned int);
typedef unsigned int (* spacefunc_t)(const circbuf_t *);
typedef long int (* nfreefunc_t)(circbuf_t *, unsigned int);
typedef void (* freefunc_t)(circbuf_t *);

struct circbuf_s
{
	char *buf;
	char *head;
	char *tail;
	unsigned int size;
	filefunc_t recv;
	printfunc_t send;
	nextfunc_t next;
	buffunc_t bufferise;
	nbuffunc_t nbufferise;
	buffunc_t get_buf;
	printfunc_t print;
	printfunc_t debug;
	freefunc_t free;
	freefunc_t free_space;
	nfreefunc_t free_nspace;
	spacefunc_t get_space;
	spacefunc_t get_used;
	spacefunc_t get_hspace;
	spacefunc_t get_tspace;
};

char *circbuf_bufferise(circbuf_t *cb);
char *circbuf_nbufferise(circbuf_t *cb, unsigned int n);
char *circbuf_get_buf(circbuf_t *cb);
char *circbuf_next(circbuf_t *cb, char *pos);
unsigned int circbuf_get_space(const circbuf_t *cb);
unsigned int circbuf_get_used_space(const circbuf_t *cb);
long int circbuf_recv(int fd, circbuf_t *cb, unsigned int size);
void circbuf_send(int fd, circbuf_t *cb);
circbuf_t *circbuf_create(unsigned int size);
void circbuf_free(circbuf_t *cb);
unsigned int circbuf_get_hspace(const circbuf_t *cb);
unsigned int circbuf_get_tspace(const circbuf_t *cb);
void circbuf_print(int fd, circbuf_t *cb);
void circbuf_print_debug(int fd, circbuf_t *cb);
long int circbuf_free_nspace(circbuf_t *cb, unsigned int size);
void circbuf_free_space(circbuf_t *cb);
long int circbuf_strstr(circbuf_t *cb, char *to_find);

#endif /* PSU_MYIRC_2017_CIRCBUFF_H */