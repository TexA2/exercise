#include <iostream>
#include <vector>

using namespace std;

class Solution {
	public:
		static vector<int> sortedSquares(vector<int>& nums)
		{
        //Задача 1 возвести в квадрат
		//Задача 2 отсортировать

		//Решение 1 использовать stl функции for_each  с функтором который возводит в степень
		//Получится N+log(n)
		//Придумать решение где будет просто N

		//Решение 2
		// сложность O(n);
		int cur (nums.size());
		vector<int> sol(cur);
		vector<int>::iterator iter = nums.end();
		--iter;	
		int i = 0;

	while(cur > 0)
	{
		if (nums[i] < 0)
			{
				if ((nums[i]*-1) > *iter)
				{
					sol[--cur] = nums[i] * nums[i];
					++i;
					continue;
				}
			}

		sol[--cur] = *iter * *iter;
		--iter;
	}	

			return sol;
		}
};



int main(){

	vector<int> nums {-4,-1,0,3,10};
	nums = Solution::sortedSquares(nums);

	for(int i = 0; i < nums.size() ; ++i)
		cout << nums[i] << ' ';
		cout << endl;


	return 0;
}
