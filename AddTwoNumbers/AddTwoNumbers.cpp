// AddTwoNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

//回收 Node，避免New
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = nullptr; ListNode* tail = nullptr; ListNode* cur = new ListNode(0); ListNode* rec = cur;
		int carry = 0; int sum = 0; bool newNode = false;
		while (true) {
			sum = carry; newNode = sum > 0;
			if (l1 != nullptr) {
				sum += l1->val; rec->next = l1; rec = l1; l1 = l1->next; newNode = true;
			}
			if (l2 != nullptr) {
				sum += l2->val; rec->next = l2; rec = l2; l2 = l2->next; newNode = true;
			}
			if (!newNode) break;
			cur->val = sum % 10; carry = sum / 10;
			if (head == nullptr) head = cur;
			if (tail != nullptr) tail->next = cur; tail = cur; cur = cur->next;
		}
		tail->next = nullptr;
		return head;
	}
};

//内存分配版本
class Solution2 {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = nullptr; ListNode* tail = nullptr; ListNode* cur = nullptr;
		int carry = 0; int sum = 0; bool newNode = false;
		while (true) {
			sum = carry; newNode = sum > 0;
			if (l1 != nullptr) {
				sum += l1->val; l1 = l1->next; newNode = true;
			}
			if (l2 != nullptr) {
				sum += l2->val; l2 = l2->next; newNode = true;
			}
			if (!newNode) break;
			cur = new ListNode(sum % 10); carry = sum / 10;
			if (head == nullptr) head = cur;
			if (tail != nullptr) tail->next = cur; tail = cur;
		}
		return head;
	}
};

int main()
{
    return 0;
}

