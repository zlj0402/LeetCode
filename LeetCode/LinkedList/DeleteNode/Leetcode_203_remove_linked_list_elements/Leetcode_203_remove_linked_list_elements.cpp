/**
 * @brief: Leetcode_203_移除链表元素
 * @link: https://leetcode.cn/problems/remove-linked-list-elements/description/
 * @author: liangj.zhang
 * @date: 30/10/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Delete Node
 * 
 * @Retrospect(worthy 1 - 5): 1
 * 
 * @thoughts:
 *  + 【思路 1】：考虑到可能会有删除第一节点的情况，使用 dummy head 的方式，比较适合
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：20.03 MB, 击败 8.41%
 */
#include "../../../../Include/Leetcode/LinkedList/LinkedList.h"
#include <iostream>
using std::cout;
using std::endl;
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
    ListNode* removeElements(ListNode* head, int val) {
        
        ListNode dummy(-1, head);
        ListNode* cur = &dummy;

        while (cur->next) {
            
            if (cur->next->val == val) {

                ListNode* tmp = cur->next;
                cur->next = tmp->next;
                delete tmp;
            }
            else {
                cur = cur->next;
            }
        }

        return dummy.next;
    }
};