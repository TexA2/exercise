#include <iostream>

using namespace std;

int findsmall(int arr[], int size)
{
	int small_index = 0;

	for (int i = 1; i < size; ++i)
	{
		if (arr[i] < arr[small_index])
			small_index = i;
	}

	int sol = arr[small_index];
	int temp = arr[size -1];
	arr[size-1] = arr[small_index];
	arr[small_index] = temp;

		return sol; 
}


int *sortmass(int arr[], int size)
{
	int *nw_arr = new int[size];

	for (int i = 0; i < size; ++i)
		*(nw_arr+i) = findsmall(arr, size-i);

	return nw_arr;
}

int main(){

	int size = 5;

	int arr[size] {5,4,3,2,1};

	int *sort_arr = sortmass(arr,size);

	for(int i = 0; i < size; ++i)
		cout << *(sort_arr+i) << ' ';
	cout << endl;


	return 0;
}
