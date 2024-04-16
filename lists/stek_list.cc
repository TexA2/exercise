#include "list.h"

using namespace std;


// для выполнения заданий в главе нужен список который добавляет элементы
// в начало (голову) поэтому функции add достаточно 
// она будет написана в Си стиле
// Стек это список который добаляет элементы в голову
// но так же удаляет элементы из головы
// поэтому будет 2 функции add и pop

void add(list **head, int data)
{
	list* nw_list = new list;
	nw_list->data = data;
	nw_list->next = *head;
	*head = nw_list;
}

void pop(list **head)
{
	list *old_head = *head;

	if (*head != NULL)
		*head = (*head)->next;
	else
		return;

	delete old_head;
}

