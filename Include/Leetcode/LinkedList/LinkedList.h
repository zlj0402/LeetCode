#ifndef LEETCODE_LINKEDLIST_H
#define LEETCODE_LINKEDLIST_H

#include <iostream>

namespace Leetcode {
    namespace LinkedList {
        // Definition for singly-linked list.
        struct ListNode {
            int val;
            ListNode* next;
            ListNode() : val(0), next(nullptr) {}
            ListNode(int x) : val(x), next(nullptr) {}
            ListNode(int x, ListNode* next) : val(x), next(next) {}

            ListNode(int* arr, size_t length) {
                ListNode* dummy_head = new ListNode(-1, nullptr);
                ListNode* cur = dummy_head;
                for (size_t idx = 0; idx < length; idx++) {
                    cur->next = new ListNode(arr[idx]);
                    cur = cur->next;
                }
                this->val = dummy_head->next->val;
                this->next = dummy_head->next->next;
            }

            static void print_list(ListNode* head) {
                ListNode* cur = head;
                while (cur != nullptr) {
                    std::cout << cur->val << "->";
                    cur = cur->next;
                }
                std::cout << "null" << std::endl;
            }

            // Overloading output stream operators
            friend std::ostream& operator<<(std::ostream& os, const ListNode* head) {
                const ListNode* cur = head;
                while (cur != nullptr) {
                    os << cur->val;
                    if (cur->next != nullptr) {
                        os << "->";
                    }
                    cur = cur->next;
                }
                return os;
            }
        };
    }
}

#endif // LEETCODE_LINKEDLIST_H
