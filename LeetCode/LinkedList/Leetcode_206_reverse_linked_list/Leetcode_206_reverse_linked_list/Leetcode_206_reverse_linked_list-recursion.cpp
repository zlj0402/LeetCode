//
// Created by liangj.zhang on 6/11/2024
//

// 很遗憾，这题是看题解写的，完全是题解的代码
// 递归真头疼啊
// 不过对反转链表有了新的实现方式

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

        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* new_head =  reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return new_head;
    }
};

int main() {
    int e_cnt = 5;
    int* arr = RandomNumbers::getRandomArray(e_cnt, 0, 100);
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    ListNode::print_list((new Solution())->reverseList(head));
}