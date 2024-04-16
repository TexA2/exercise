#include <iostream>
#include <vector>

using namespace std;


// Формула Гауса подсчитываем сумму всех чисел идущих по порядку
// 1 2 3 4 5 6 ... 100

// N - кол во пар
// S - сумма первого и последнего числа

int Gaus(vector<int> &);


int main(){

	int len;

	cin >> len;

	vector<int> arr(len);

	int i = 1;	
	for(int &x : arr)
		x = i++;

	cout << '\n' << Gaus(arr) << endl;

	return 0;
}

int Gaus(vector<int> &arr)
{
	if (arr.size() < 1)
		return 0;

	bool chet;
	 chet = ( arr.size() % 2 == 0) ? true : false;

	if (chet)
	{
		int N = arr.size() / 2;
		int S = arr[0] + arr[arr.size()-1];
		return N*S;
	}

	int N = (arr.size() -1) / 2;
	int S = arr[0] + arr[arr.size() -2];

	return N*S+arr[arr.size()-1];
}
