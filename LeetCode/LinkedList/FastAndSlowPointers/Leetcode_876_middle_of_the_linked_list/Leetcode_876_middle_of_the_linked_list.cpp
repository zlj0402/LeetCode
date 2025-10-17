/**
 * @brief: Leetcode_876_链表的中间节点
 * @link: https://leetcode.cn/problems/middle-of-the-linked-list/description/
 * @author: liangj.zhang
 * @date: 17/10/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Fast And Slow Pointers
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *  + 【思路 1】：快慢指针
 *      题目的条件，指出，最少一个节点
 *      初始状态，fast / slow 指针都指向头指针;
 *      slow 一次走一步，fast 一次走两步
 *      循环终止条件：fast && fast->next 不为 NULL，在图上画一画，很容易就明白了；
 *      比计数的方式，优雅一些；且少一边遍历
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：9.72 MB, 击败 87.68%
 */

#include "../../../../Include/Leetcode/LinkedList/LinkedList.h"
using Leetcode::LinkedList::ListNode;

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
public:
    ListNode* middleNode(ListNode* head) {
        
        ListNode *fast(head), *slow(head);
        while (fast && fast->next) {

            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
};