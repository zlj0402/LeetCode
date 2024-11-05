// 
// Created by liangj.zhang on 5/11/2024 
//

// 跟前面反转相邻节点，并不一样；但都要考虑当前节点，及后面两个节点
// 
// dummy_head  ->  1  ->  2  ->  3  ->  4  ->  5
//                cur
// 
//                 2  ->  3  ->  4
// dummy_head  ->  1  ↗
// 
//                               3  ->  4
// dummy_head  ->  2  ->  1  ↗


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include "RandomNumbers.h"
#include "Leetcode/LinkedList/LinkedList.h"
using namespace Leetcode::LinkedList;

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;

        ListNode* dummy_head = new ListNode(-1, head);
        ListNode* cur = head;

        while (cur->next) {
            ListNode* next_node = cur->next;
            cur->next = next_node->next;

            next_node->next = dummy_head->next;
            dummy_head->next = next_node;
        }
        return dummy_head->next;
    }
};

int main() {
    int e_cnt = 5;
    int* arr = RandomNumbers::getRandomArray(e_cnt, 0, 100);
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    ListNode::print_list((new Solution())->reverseList(head));
}