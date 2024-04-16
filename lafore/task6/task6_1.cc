#include <iostream>
using namespace std;

// Создайте класс Int имитирующий стандартный int
// Единственное поле этого класса должно иметь тип int
// Создайте методы, которые будут устанавливат значение пол, ранвным нулю
// инициализировать его целым начением, выводить значения поля на экран и складывать два значения типа Int

class Int
{
	private:
		int num;

	public:
		Int():num(0)
		{}

		Int(int a) : num(a)
		{}

		void show() const
		{
			cout << num << endl;
		}

		void set(int a)
		{
			num = a;
		}

		int sum(Int b)
		{
			num = num + b.num;
			return num;
		}
};



int main()
{

	Int p1;
	Int p2(3);

	p1.show();
	p2.show();

	p1.set(5);
	p1.show();

	cout << p1.sum(p2) << endl;

	return 0;
}
