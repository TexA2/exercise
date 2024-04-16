#include <iostream>
#include <vector>


using namespace std;

class Solution {
public:
 static void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
	    //Решение 1 использовать stl merge и sort
		//Решение 2
		int it1 = m - 1;
        int it2 = n - 1;
        int size = m + n - 1;
        
        while (it2 >= 0) {
            if (it1 >= 0 && nums1[it1] > nums2[it2]) {
                nums1[size--] = nums1[it1--];
            } else {
                nums1[size--] = nums2[it2--];
            }
        }
    }
};


int main(){

	vector<int> nums1 {1,2,3,0,0,0};
	vector<int> nums2 {2,5,6};
	int m = 3, n = 3;
	Solution::merge(nums1,m,nums2,n);
	for (int i = 0; i < m+n; ++i)
		cout << nums1[i] << " ";

	
		cout << endl;


	return 0;
}
