#include <iostream>
#include "list.h"

using namespace std;
// задача подсчитать кол-во элементов в списке
//и сделать этот через рекурсию
//
//для сборки использовать list.h stek_list.cc


int size_list(list *head)
{
	if ( head == NULL)
		return 0;

	if (head->next == NULL)
		return 1;

	return size_list(head->next) + 1;
}

int main()
{
	list *node = new list;
	add(&node, 7);
	add(&node, 8);
	add(&node, 11);
	add(&node, 1);


	cout << size_list(node) << endl;


	return 0;
}
