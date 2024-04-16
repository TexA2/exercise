#include <iostream>
#include <ctime>
#include <cstdlib>



using namespace std;

int alg(int, int, int);

int main(){

	int g,p; // база и модуль

	cout << "Введите базу и модуль: "; 
	cin >> g >> p;

	int pKey1, pKey2;
	int oKey1, oKey2;

	srand(time(NULL) );	
	pKey1 = rand();

	srand(time(NULL) );
	pKey2 = rand();
		
	oKey1 = alg(g,pKey1,p);
	oKey2 = alg(g,pKey2,p);


	int Key1,Key2;

	Key1 = alg(oKey1,pKey1,p);
	Key2 = alg(oKey2,pKey2,p);

	cout << "Секретные ключи: " << Key1 << ' ' << Key2 << endl;

	return 0;
}

int alg(int g, int a, int p)
{
	int y = 1;

	while ( a > 0)
	{
		int r = a % 2;

		if (r == 1)
		{
			y = (y*g) % p;
		}
		g = g*g % p;
		a = a / 2;
	}
	return y;
}

