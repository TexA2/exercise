#include <iostream>

using namespace std;

//цель найти сумму элементов в массиве используя рекурсию

int summ(int arr[], int size)
{
	if (size < 2)
		return arr[0];
	return summ(arr, size -1) + arr[size-1];
}

int main()
{
	int arr[3] {1,6,3};
	cout << summ(arr,3) << endl;

	return 0;
}
