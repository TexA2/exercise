#include <iostream>
#include <cstring>
using namespace std;

//напишите функцию reversit(), которая переворачивает строку
// Используйте циул for, который меняет местами первый и последний символы, затем следующие и т.д до последнего
// Строка должна передоваться  в функцию reversit() как аргемент.

void reversit(char str[]);

int main() {

	const int MAX = 20;
	char str[MAX];
	cin >> str;
	cout << str << endl;
	reversit(str);

	cout << str << endl;

	return 0;
}

void reversit(char str[])
{
	int len = strlen(str);
	for (int i=0; i <len/2 ; i++)
	{
		if (str[i] == '\0') break;
		char temp;
		temp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = temp;
	}
}
