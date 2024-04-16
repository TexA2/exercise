// Создайте класс publication в котором хранятся названия(строка) и цена (флоат) книги.
// От этого класса наследуется еще два класса : book который содержит информациюо кол-во страниц в книге(инт)
// и type который сожежит время записи книгив минутах (флоат).
// В каждом из трех классов должен быть реализован метод getdata()
// через который можно получить данные от пользователя с клавиатуры и putdata()
// предназначенные для ввода этих данных
//

#include <iostream>
#include <string>

using namespace std;




class publication{
	private:
		string name;
		float price;
	public:
		//publucation(string name, price):name(name),price(price)
		//{}
		
		void getdata()
		{
			cout << "\nВведите название книги: ";
			cin >> name;

			cout << "\nВведите цену книги: ";
			cin >> price;
		}

		void putdata()
		{
			cout << "\n книга " << name << " цена: " << price << " руб." << endl;
		}
};

class book : public publication{
	private:
		int count_str;
	public:

		void getdata()
		{
			publication::getdata();
			cout << "\nВведите кол-во страниц: ";
			cin >> count_str;
		}

		void putdata()
		{
			publication::putdata();
			cout << "\n  кол-во страниц: " << count_str;
		}

};

class type : public publication{
	private:
		float time;
	public:
		void getdata()
		{
			publication::getdata();
			cout << "\nВведите время выдачи: ";
			cin >> time;
		}

		void putdata()
		{
			publication::putdata();
			cout <<"\n Время выдачи: " << time << endl;
		}

};



int main(){

	publication A;

	A.getdata();
	A.putdata();

	book B;
	B.getdata();
	B.putdata();

	type C;
	C.getdata();
	C.putdata();

	return 0;
}

