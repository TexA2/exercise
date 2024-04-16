#include <iostream>
#include <cmath>     // log

using namespace std;

int binary(int *src, int size, int sol)
{
	int low = 0;
	int hight = size - 1;
	int mid = hight / 2;

	while (low <= hight)
	{
		if ( *(src+mid) == sol )
			return mid;
		else if ( *(src+mid) > sol )
			hight = mid - 1;
		else if ( *(src+mid) < sol)
			low = mid + 1;

		mid = (hight + low) /2;
	}
	return -1; //число не найдено
}

int main() {

	int mass[] {1,2,4,6,7,11,18};

	int sol = binary(mass, 7, 1);
cout << sol << endl;
 sol = binary(mass, 7, 2);
cout << sol << endl;
 sol = binary(mass, 7, 4);
cout << sol << endl;
 sol = binary(mass, 7, 6);
cout << sol << endl;
 sol = binary(mass, 7, 11);
cout << sol << endl;
 sol = binary(mass, 7, 120);
	cout << sol << endl;


	return 0;
}
