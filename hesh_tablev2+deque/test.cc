#include <iostream>
#include "graf.h"

using namespace std;

//Создаем второй вариант хеш-таблицы
//создали очередь


// не удачный вариант нужно было в структуре  делать поле string или char*
// в данном варианте неудчано вышло потренировались
//
// сам алгоритм реализую на stl


int main()
{
	// проверка работы хеш-таблицы
	table *htable = new table[SIZE];

	(*htable)["Apple"]->add(15);
	(*htable)["Apple"]->add(5);
	htable[3].add(1);


	// проверка работы очереди
	deque ochered(5);
	ochered.add(3);
	ochered.add(7);
	ochered.pop();


	// на основе хеш-таблицы завести связи
	// и написать алгоритма поиска в ширину


	return 0;
}
