//
// Created by liangj.zhang on 31/10/2024
//

// 我的想法
// 两个指针，dummy_head/tail
// 指向排序部分的头和尾
// 开始时，dummy_head 和 tail都指向相同位置dummy_head
// 遍历时：
// 如果 cur->val < tail->val:
// 1. 先让tail->next = cur->next;
// 2. cur->val 拿去和前面的比较，找到合适的位置进行插入
// 3. tail 不动；cur = tail->next;
// 如果 cur->val >= tail->val:
// cur和tail都往下走一步

#include "RandomNumbers.h"
#include "Leetcode/LinkedList.h"
using namespace Leetcode::LinkedList;

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
class Solution {
private:
    ListNode* dummy_head;
    ListNode* tail;

    ListNode* find_suitable_prev(ListNode* node) {
        ListNode* cur = dummy_head;

        while (cur->next && cur->next->val < node->val && cur->next != tail) {
            cur = cur->next;
        }

        return cur;
    }

public:
    ListNode* sortList(ListNode* head) {
        dummy_head = new ListNode(-100001, head);
        tail = dummy_head;
        ListNode* cur = tail->next;

        while (cur) {
            if (tail->val <= cur->val) {
                cur = cur->next;
                tail = tail->next;
            }
            else {
                tail->next = cur->next;
                ListNode* suitable_prev = find_suitable_prev(cur);
                cur->next = suitable_prev->next;
                suitable_prev->next = cur;
                cur = tail->next;
            }
        }
        return dummy_head->next;
    }
};

int main() {
    int e_cnt = 10;
    int* arr = RandomNumbers::getRandomArray(e_cnt, 0, 100);
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    ListNode::print_list((new Solution)->sortList(head));
}