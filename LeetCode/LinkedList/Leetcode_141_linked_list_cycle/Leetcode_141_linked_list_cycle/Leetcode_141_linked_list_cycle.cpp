//
// Created by liangj.zhang on 4/11/2024
//

// 很不好意思，先做了环形链表II才来做这题
// 我已经有了思路
// 双指针，slow，fast
// slow一次走一步，fast一次走两步
// fast为null，则不闭环
// slow和fast相等时，则说明闭环

#include "Leetcode/LinkedList/LinkedList.h"
using namespace Leetcode::LinkedList;


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode* head) {
        if (!head) return false;
        ListNode* slow, * fast;
        slow = head;
        fast = head->next;

        while (fast && slow != fast) {
            slow = slow->next;
            fast = fast->next;
            if (fast)
                fast = fast->next;
            else
                break;
        }

        return fast ? true : false;
    }
};