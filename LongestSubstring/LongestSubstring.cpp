// LongestSubstring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

//hash表查找
class Solution {
public:
	int lengthOfLongestSubstring(const string& s) {
		int begin = 0; size_t max_len = 0; unordered_map<char, int> cache;
		for (size_t i = 0; i < s.length(); ++i) {
			auto it = cache.find(s[i]);
			if (it == cache.end()) {
				cache[s[i]] = i;
			}
			else {
				if (cache.size() > max_len) max_len = cache.size();
				for (int j = begin; j < it->second; ++j) {
					cache.erase(s[j]);
				}
				begin = it->second + 1; cache[it->first] = i;
			}
		}
		if (cache.size() > max_len) max_len = cache.size();
		return (int)max_len;
	}
};

//非hash表查找
class Solution2 {
public:
	int lengthOfLongestSubstring(const string& s) {
		size_t begin = 0; size_t max_len = 0;
		for (size_t i = 0; i < s.length(); ++i) {
			for (size_t j = begin; j < i; ++j) {
				if (s[j] == s[i]) {
					auto len = i - begin; if (len > max_len) max_len = len;
					begin = j + 1;
				}
			}
		}
		auto len = s.length() - begin; if (len > max_len) max_len = len;
		return (int)max_len;
	}
};

//无查找 ->别人的解决方案
class Solution3 {
public:
	int lengthOfLongestSubstring(string s) {
		vector<int> dict(256, -1);
		int maxLen = 0, start = -1;
		for (int i = 0; i != s.length(); i++) {
			if (dict[s[i]] > start)
				start = dict[s[i]];
			dict[s[i]] = i;
			maxLen = std::max(maxLen, i - start);
		}
		return maxLen;
	}
};

int main()
{
    return 0;
}

