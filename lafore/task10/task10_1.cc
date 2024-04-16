// Напишите программу которая принимает группу числе от пользователя и помещает их в массив float.
// После того как числа будут помещенны в массив, программа должна подчитть их среднее арифметическое и вывести результат на дисплей.
// Используйте  указатели везде где , это возможною
#include <iostream>

using namespace std;

const int MAX = 10;

class Arr
{
	private:
		float *farr;
		int arr_len;
		int cur_pos;
	public:
		Arr(int len);
		~Arr();
		void push(float num);	// добавление числа в массив
		void display();			// вывод массива
		float mid_math();		// среднее арифметическое
		int len()
		{
			return arr_len;
		}

		int cur()
		{
			return cur_pos;
		}
};

Arr::Arr(int len = 2)
{
	float *ptr = new float[len];
	farr = ptr;
	arr_len = len;
	cur_pos = 0;
}

Arr::~Arr()
{
	delete []farr;
}


void Arr::push(float num)
{
	*(farr+cur_pos) = num;
	++cur_pos;
}

void Arr::display()
{
	for (int i = 0; i < arr_len; ++i)
		cout << *(farr+i) << " ";
		cout << endl;
}

float Arr::mid_math()
{
	float x {0.0};

	for (int i = 0; i < arr_len; ++i)
		x += *(farr+i);

	return x / arr_len;
}

int main(){
	int i;
	cout << "Введите длинну массива:" << " ";
	cin >> i;

	Arr mass_f(i);

	do
	{
		float num;
		cout << "Введите число: " << " ";
		cin >> num;
		mass_f.push(num);
	}
	while(mass_f.cur() < mass_f.len());

	mass_f.display();
	cout << "\n" <<  mass_f.mid_math();
	


	return 0;
}
