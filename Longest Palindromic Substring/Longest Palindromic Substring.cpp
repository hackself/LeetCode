// Longest Palindromic Substring.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
/*
	Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:

Input: "babad"

Output: "bab"

Note: "aba" is also a valid answer.
Example:

Input: "cbbd"

Output: "bb"

我的分析:
	a-.-b-.-c-.-d ,"."代表虚折点,"字母"是实折点
	将字符串从中间开始，安装每个字符做"折叠",找到第一个最大"对称"的地方
	1.len 长的字符串，有 m = std::max(1,(len - 2) * 2  + 1) ,一定是奇数
	2.在第n个折点最前面的那个实折点的索引是 :p = n / 2 ,n点对折,最大可能的长度是: n + (n >= mid ? 1 : -1), n % 2 == 0 为true,表示是在实点。false表示在虚点.
	3.从中间开始对折，因为这样可能先找到最长的符合条件的子串，可以提前停止查找
	4.可以抽象成一个模板函数
*/

#include <string>
#include <iostream>
#include <algorithm>
#include <ostream>
using namespace std;

class Solution {
public:
	string longestPalindrome(string s) {
		int len = s.length(); int pts = std::max(1, ((int)len - 2) * 2 + 1);
		int mid = pts / 2 + 1; int max_begin = 0, max_len = 0;
		for (int i = 0; i < pts; ++i) {
			//0,1,2,3,4,5,6
			//0,-1,1,-2,2,-3,3
			//从中间到两边,
			int pt = mid + (i % 2 ? -(int)std::ceil(i / 2.0) : (int)std::ceil(i / 2.0));
			int index = pt / 2; int n = pt + (pt >= mid ? 1 : -1); int b = pt % 2 == 0 ? 1 : 0;
			if (n <= max_len) break; //后面找到的不可能比现在的长了

			int begin = 0, end = 0,m = n / 2;
			for (int j = 0; j < m; ++j) {
				int p_1 = index - j - b, p_2 = index + j + 1;
				if (p_1 < 0 || p_2 >= len || s[p_1] != s[p_2]) break;
				begin = p_1; end = p_2;
			}
			int cur_len = end - begin + 1;
			if (cur_len > max_len) {
				max_begin = begin; max_len = cur_len;
			}
		}
		return s.substr(max_begin, max_len);
	}
};

#include <vector>
#include <iterator>
class Solution2 {
public:
	template<typename T>
	T longestPalindrome(const T& s) {
		int len = s.end() - s.begin(); int pts = std::max(1, ((int)len - 2) * 2 + 1);
		int mid = pts / 2 + 1; int max_begin = 0, max_len = 0;
		for (int i = 0; i < pts; ++i) {
			int pt = mid + (i % 2 ? -(int)std::ceil(i / 2.0) : (int)std::ceil(i / 2.0));
			int index = pt / 2; int n = pt + (pt <= mid ? 1 : -1); int b = pt % 2 == 0 ? 1 : 0;
			if (n <= max_len) break; //后面找到的不可能比现在的长了

			int begin = 0, end = 0, m = n / 2;
			for (int j = 0; j < m; ++j) {
				int p_1 = index - j - b, p_2 = index + j + 1;
				if (p_1 < 0 || p_2 >= len || *(s.begin() + p_1) != *(s.begin() + p_2)) break;
				begin = p_1; end = p_2;
			}
			int cur_len = end - begin + 1;
			if (cur_len > max_len) {
				max_begin = begin; max_len = cur_len;
			}
		}
		auto it_begin = s.begin() + max_begin;
		return T(it_begin, it_begin + max_len);
	}
};

template<typename Container,typename Element = Container::value_type>
void printLongestPalindrome(initializer_list<Element> list) {
	auto ret = Solution2().longestPalindrome<Container>(list);
	std::copy(ret.begin(), ret.end(), ostream_iterator<Element>(cout));
	cout << endl;
}

template<typename Container>
void printLongestPalindrome(Container list) {
	typedef typename Container::value_type Element;
	auto ret = Solution2().longestPalindrome<Container>(list);
	std::copy(ret.begin(), ret.end(), ostream_iterator<Element>(cout));
	cout << endl;
}


int main()
{
	printLongestPalindrome(vector<int>{ 1, 2, 3, 4, 4, 3, 2, 1 });
	printLongestPalindrome<string>("123443213e231ssssss132e3123");
	system("pause");
    return 0;
}

