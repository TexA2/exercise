#include "graf.h"

int hesh_func(const char* str)
// простая хеш-функция
{
	int i = 0;
	while (*str != '\0')
		i += int(*str++);

	return i % SIZE;
}


void list::add(int n)
// добавление новоего элемента списка
{
	list *temp = this;

	while (temp->next != nullptr)
		temp = temp->next;

	list* nlist = new list(n);
	temp->next = nlist;
}


void deque::pop()
// удаление последнего первого элемента в списке
{
	if (head == nullptr)
		return;

	list *temp = head;

	if (temp->next != nullptr)
		head = temp->next;
	
	delete temp;
}


void deque::add(int n)
// добавление элемента в очередь
{
	head->add(n);
}


void table::add(int n)
// Создание первого элемента в таблице
//  если есть вызвать функцию добавление нового элемента списка
{
	if (head == nullptr)
	{
		list *nlist = new list(n);
		head = nlist;
		return;
	}

	head->add(n);
}
