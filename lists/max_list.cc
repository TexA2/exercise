#include <iostream>
#include "list.h"

using namespace std;


// Задача найти наибольшее число в списке
// используя рекурсию
// g++ list.h stek_list.cc max_list.cc

int max_data(list *head)
{
	if (head == NULL)
		return 0;

	if (head->next == NULL)
		return head->data;

	return head->data > max_data(head->next)? head->data : max_data(head->next);

}

int main()
{
	list *head = new list;
	add(&head, 511);
	add(&head, 8);
	add(&head, 11);
	add(&head, 1);

	cout << max_data(head) << endl;

	return 0;
}
