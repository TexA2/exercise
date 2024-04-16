#include <iostream>
#ifndef MY_LIST

#define MY_LIST

struct list{
	int data;
	list *next;

	list():data{0},next{NULL}
	{}
};
void add(list **head, int data);
void pop(list **head);



#endif
