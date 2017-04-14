// MedianOfTwoSortedArrays.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
/*
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5

分析:需要合并两个数组
*/

//新建一个vector 来存放合并后的vector 【复杂度不满足条件】 O(nlog(n))
//std::merge 
class Solution {
public:
	double findMedianSortedArrays(const vector<int>& nums1,const vector<int>& nums2) {
		vector<int> nums; size_t i = 0, j = 0; int cur = 0;
		while (true) {
			if (i < nums1.size()) {
				if (j < nums2.size()) {
					if (nums1[i] == nums2[j]) {
						nums.emplace_back(nums1[i++]);
						nums.emplace_back(nums2[j++]);
					}
					else if (nums1[i] < nums2[j]) {
						nums.emplace_back(nums1[i++]);
					}
					else {
						nums.emplace_back(nums2[j++]);
					}
				}
				else {
					nums.emplace_back(nums1[i++]);
				}
			}
			else if (j < nums2.size()) {
				nums.emplace_back(nums2[j++]);
			}
			else 
				break;
		}

		if (nums.size() > 0)
		{
			if (nums.size() % 2 == 0) {
				size_t index = nums.size() / 2;
				return (nums[index - 1] + nums[index]) / 2.0;
			}
			else {
				return (double)nums[nums.size() / 2];
			}
		}
		return 0;
	}
};


//use std::merge
class Solution2 {
public:
	double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
		vector<int> nums(nums1.size() + nums2.size());
		std::merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(),nums.begin());
		if (nums.size() > 0){
			if (nums.size() % 2 == 0) {
				size_t index = nums.size() / 2;
				return (nums[index - 1] + nums[index]) / 2.0;
			}
			else {
				return (double)nums[nums.size() / 2];
			}
		}
		return 0;
	}
};

//选择第K小的元素 [[非递归,写得很纠结]]......
//use getKth log(m + n)
//将k分解成两个数m,n相加:循环去取两个数组的前m,n个数,判断是否符合 条件
class Solution3 {
public:
	int getKth(vector<int>& nums1, vector<int>& nums2, size_t k) {
		//总共有 n 种 分法
		if (k < (nums1.size() + nums2.size())) {

			if (nums1.size() == 0 || (k < nums2.size() && nums2[k] < nums1[0])) return nums2[k];
			if (nums2.size() == 0 || (k < nums1.size() && nums1[k] < nums2[0])) return nums1[k];
			if (nums1.size() > nums2.size()) std::swap(nums1, nums2);

			size_t n = std::min(k + 1, nums1.size()) + 1;
			for (size_t i = 0; i <= n; ++i) {
				auto j = k - i + 1;
				if ((i == nums1.size() && j == nums2.size()) ||
					(i == nums1.size() && j < nums2.size() && nums1[i - 1] <= nums2[j]) ||
					(j == nums2.size() && i < nums1.size() && nums2[j - 1] <= nums1[i]) || 
					(i < nums1.size() && j < nums2.size()  && nums1[i - 1] <= nums2[j] && nums2[j - 1] <= nums1[i]))
					return std::max(nums1[std::max(0,(int)(i - 1))],nums2[std::max(0,(int)(j - 1))]);
			}
		}
		return 0;
	}
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		auto size = nums1.size() + nums2.size();
		auto mid = size / 2;
		return size % 2 == 0 ? (getKth(nums1, nums2, mid - 1) + getKth(nums1, nums2, mid)) / 2.0 : getKth(nums1, nums2, mid);
	}
};

int main()
{
	std::cout << Solution3().findMedianSortedArrays(vector<int>({ 1 }), vector<int>({ 1 })) << endl;
	std::cout << Solution3().findMedianSortedArrays(vector<int>({ 1,3 }), vector<int>({ 2 })) << endl;
	std::cout << Solution3().findMedianSortedArrays(vector<int>({ 1,2 }), vector<int>({ 3,4 })) << endl;
	std::system("pause");
    return 0;
}

