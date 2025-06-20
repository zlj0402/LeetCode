//
// Created by liangj.zhang on 20/6/2025
//

#ifndef LISTTESTHELPER_H
#define LISTTESTHELPER_H

#include "Leetcode/LinkedList/LinkedList.h"
#include <cassert>
using Leetcode::LinkedList::ListNode;

namespace Leetcode {

	namespace ListTestHelper {

		ListNode* generateIntLinkedList(int* arr, int n) {

			assert(n > 0);

			ListNode* head = new ListNode(arr[0]);
			ListNode* cur = head;
			for (int i = 1; i < n; ++i) {

				cur->next = new ListNode(arr[i]);
				cur = cur->next;
			}

			return head;
		}

		void print_list(ListNode* head) {
			ListNode* cur = head;
			while (cur != nullptr) {
				std::cout << cur->val << "->";
				cur = cur->next;
			}
			std::cout << "null" << std::endl;
		}
	}
}

#endif