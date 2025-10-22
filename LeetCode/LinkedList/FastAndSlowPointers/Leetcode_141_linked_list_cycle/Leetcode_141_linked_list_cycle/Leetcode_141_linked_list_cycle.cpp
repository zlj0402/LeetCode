//
// Created by liangj.zhang on 4/11/2024
//

// 很不好意思，先做了环形链表II才来做这题
// 我已经有了思路
// 双指针，slow，fast
// slow一次走一步，fast一次走两步
// fast为null，则不闭环
// slow和fast相等时，则说明闭环

/**
 * @brief: Leetcode_141_环形链表
 * @link: https://leetcode.cn/problems/linked-list-cycle/description/
 * @author: liangj.zhang
 * @date: 18/10/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label(worthy 1 - 5): 2
 * 
 * @thoughts:
 *  + 【思路 1】：快慢指针
 *      去年就用 C++ 写过，还是很简单的；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：4 ms, 击败 96.58%
 *          + 空间效率：10.56 MB, 击败 100%
 * 
 *  + 【思路 1.2】：快慢指针 + 剪枝
 *      写完之后，我觉得可以剪枝；slow / fast 都不变，加上：slow 行走时，
 *      如果值 <= 10000，那么将其往左偏移 16 位；
 *      遇到一个值大于 10000 的数，就可以确定有环了；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：7 ms, 击败 89.72%
 *          + 空间效率：11.52 MB, 击败 89.83%
 */

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

// 【思路 1.2】：加上剪枝
class Solution {
public:
    bool hasCycle(ListNode* head) {
        
        ListNode *slow(head), *fast(head);
        while (fast && fast->next) {

            if (fast->val > 100000 || slow->val > 100000) {
                return true;
            } else if (slow->val <= 100000)
                slow->val += 200000;

            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }

        return false;
    }
};

// 【思路 1】：快慢指针
/*
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
*/