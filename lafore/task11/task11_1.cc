// как и в упражнени 1 главы 9 создайте класс publication хранящие название и ценупубликации.
// Создайте 2 поражденный класса book в который происходит именения счетика страниц
// и tape в кооторм проиходит измение записанных на касету минут.
// каждый класс дожен иметь методы getdata зписывающие данные от пользователя
// и putdata выводящие данные на экаран.

#include <iostream>
#include <string>
using namespace std;


class publication{
	private:
		string name;
		float cost;
	public:
		publication(string nameq, float costq): name(nameq), cost(costq)
		{}

		publication()
		{
			name = "noname";
			cost = 0.0;
		}

		void getdata();
		void putdata();
};

void publication::getdata()
{
	cout << "Введите название книги: ";

	string name;
	cin >> name;

	cout << "\nВведите стоимость книги: ";
	
	float cost;
	cin >> cost;

	this->name = name;
	this->cost = cost;
}


void publication::putdata()
{
	cout <<"Книга: " << name << "\nЦена: " << cost << " руб.\n";
}


class book : public publication{
	private:
		int count_str;  // счетчик страниц
	public:
		book() : publication()
	{ count_str = 0;}

		book(int s) : publication() , count_str(s)
	{}

		void getdata();
		void putdata();
};


void book::getdata()
{
	publication::getdata();
	cout << "\nВведите количество страниц: ";
	
	int count;
	cin >> count;
	count_str = count;
}

void book::putdata()
{
	publication::putdata();
	cout << "Кол-во страниц: " << count_str <<"\n"; 
}

class tape : public publication{
	private:
		float time;
	public:
		tape():publication()
		{time = 0.0; }

		tape(float timeq) : publication() , time(timeq)
		{}

		void getdata();
		void putdata();
};


void tape::getdata()
{
	publication::getdata();
	cout << "\nВведите прожолжительность книги минутах: ";

	float time;
	cin >> time;
	this->time = time;
}

void tape::putdata()
{
	publication::putdata();
	cout << "Продолжительность книги: " << time << " минут.\n";

}

int main(){

	tape q1;
	q1.getdata();
	q1.putdata();

	return 0;

}
