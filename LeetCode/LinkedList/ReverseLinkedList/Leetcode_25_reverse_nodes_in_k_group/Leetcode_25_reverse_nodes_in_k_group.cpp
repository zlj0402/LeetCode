/**
 * @brief: Leetcode_25_K个一组翻转链表
 * @link: https://leetcode.cn/problems/reverse-nodes-in-k-group/description/
 * @author: liangj.zhang
 * @date: 13/10/2025
 * 
 * @Difficulty: Hard
 * 
 * @Label: Reverse LinkedList
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：用带 dummy_head 的方式
 *      在写过下面两题：
 *          + 简单题：Leetcode_206_反转链表
 *          + 中等题：Leetcode_92_反转链表_II
 *      尤其是 Leetcode_92 这题之后，充分理解了带 dummy_head 和不带 dummy_head 两者之间的差别之后，
 *      写这题尤为简单，甚至接近一遍通过;（内循环的范围原来多带了个等号，立马就给它去掉通过了）
 *          + 带 dummy_head 的方式，一直是一条链；
 *          + 不带 dummy_head 的方式，虽分离的都是原来的节点，但是分离出的是另一条链；
 *      
 *      + 分析：
 *          + 时间复杂度：O(n)，最多遍历两边链表
 *          + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：16.09 MB, 击败 91.46%
 */

#include <iostream>
#include "../../../Include/Leetcode/LinkedList/LinkedList.h"
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        
        ListNode dummy = ListNode(-1, head);
        ListNode* dhead = &dummy;

        while (dhead) {

            // 能够翻转的前提条件：后续有 k 个节点
            int cnt = 0;
            ListNode* p = dhead;
            while (p && cnt++ < k)
                p = p->next;
            if (!p || cnt == k) break;

            // 翻转
            cnt = 0;
            p = dhead->next;
            while (++cnt < k) { // 原来错误的写法：while (++cnt <= k)

                ListNode* nextNode = p->next;
                p->next = nextNode->next;

                nextNode->next = dhead->next;
                dhead->next = nextNode;
            }
            dhead = p;
        }

        return dummy.next;
    }
};