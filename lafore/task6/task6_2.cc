#include <iostream>
using namespace std;


// Предствьте пункт взимания платежей за проезд по автостраде.
// Каждая проездаеющая машина должна заплатить 50 центов.
// Однако часть машин платит, а часть проезжает бесплатно.
// В кассе ведется учет сумарно проехавших машин и мумарна выручка от платы за проездю

// модель кассы
class tollBooth {
	private:
		unsigned int all_car; // учет всех проехавших машин
		double coin;		  // суммарная выручка от проехавших машин
	public:

		tollBooth() : all_car(0), coin(0)
		{}

		void payingCar()
		{
			++all_car;
			coin += 0.50;
		}

		void nopayCar()
		{
			++all_car;
		}

		void display() const
		{
			cout << "кол-во машин: " << all_car << endl;
			cout << "заработанно монет: " << coin << endl;
		}
};

int main() {
	tollBooth car;
	bool run = true;
	char key;

	while (run)
	{
		cout << "Введите 1 если машина оплатила проезд" << endl;
		cout << "Введите 2 если машина проехала бесплатно" << endl;
		cout << "Ввод: ";
		cin >> key;

		switch (key) 
		{
			case '1' : car.payingCar(); break;
			case '2' : car.nopayCar(); break;
			case '3' : car.display(); break;
			case 'x' : run = false; break;
			default:
				cout << "Неверный результат попробуйте снова";
		}
	}

	return 0;
}


