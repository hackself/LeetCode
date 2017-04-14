// TwoSum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
using namespace std;

//±©Á¦ Brute Force
class Solution {
public:
	vector<int> twoSum(const vector<int>& nums, int target) {
		vector<int> data;
		auto size = nums.size();
		if (size >= 2) {
			auto len = nums.size() - 1;
			for (size_t i = 0; i < len; ++i) {
				for (size_t j = i + 1; j < size; ++j) {
					if (target == (nums[i] + nums[j]))
					{
						data.emplace_back(i);
						data.emplace_back(j);
					}
				}
			}
		}
		return std::move(data);
	}
};

int main()
{
    return 0;
}

