/**
 * @brief: Leetcode_206_反转链表
 * @link: https://leetcode.cn/problems/reverse-linked-list/description/
 * @author: liangj.zhang
 * @date: 5/11/2024
 * 
 * @updated: 
 *      + 05/11/2025 -- add 带虚拟头结点思路
 *      + 11/10/2025 -- add 不带虚拟头结点思路
 * 
 * @Difficulty: Easy
 * 
 * @Label: Reverse LinkedList
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 * + 【思路 1】：单链表反转 -- 带虚拟头结点的方式 -- 5/11/2024
 *      +   dummy_head  ->  1  ->  2  ->  3  ->  4  ->  5
 *      +                  cur
 * 
 *      +                   2  ->  3  ->  4  ->  5
 *      +   dummy_head  ->  1  ↗
 * 
 *      +                                 3  ->  4  ->  5
 *      +   dummy_head  ->  2  ->  1  ↗
 * 
 *      +   dummy_head  ->  2  ->  1  ->  3  ->  4  ->  5
 *      +                         cur
 * 
 *      +                          3  ->  4  ->  5
 *      +   dummy_head  ->  2  ->  1  ↗
 * 
 *      +                                        4  ->  5
 *      +   dummy_head  ->  3  ->  2  ->  1  ↗
 *      +   以此类推...
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：12.7 MB，击败 69.25%
 * 
 * + 【思路 2】：单链表反转 -- 不带虚拟头结点的方式 -- 11/10/2025
 * + 初始状态：
 *      +   1  ->  2  ->  3  ->  4  ->  5  ->  NULL
 *      +   ⭡
 *      +  cur
 *      +  NULL
 *      +   ⭡
 *      +   p
 * 
 * + 第一次循环：
 *      +   1  ->  2  ->  3  ->  4  ->  5  ->  NULL
 *      +   ⭡      ⭡
 *      +  cur    next
 *      +  NULL
 *      +   ⭡
 *      +   p
 * 
 *      +          2  ->  3  ->  4  ->  5  ->  NULL
 *      +          ⭡
 *      +         next
 *      +   1  -> NULL
 *      +   ⭡      ⭡
 *      +  cur     p
 * 
 *      +          2  ->  3  ->  4  ->  5  ->  NULL
 *      +          ⭡
 *      +         cur
 *      +   1  -> NULL
 *      +   ⭡
 *      +   p
 * 
 * + 第二次循环：
 *      +          2  ->  3  ->  4  ->  5  ->  NULL
 *      +          ⭡      ⭡
 *      +         cur    next
 *      +   1  -> NULL
 *      +   ⭡
 *      +   p
 * 
 *      +                 3  ->  4  ->  5  ->  NULL
 *      +                 ⭡
 *      +                next
 *      +   2  ->  1  -> NULL
 *      +   ⭡      ⭡
 *      +  cur     p
 * 
 *      +                 3  ->  4  ->  5  ->  NULL
 *      +                 ⭡
 *      +                cur
 *      +   2  ->  1  -> NULL
 *      +   ⭡
 *      +   p
 *
 * + 以此类推...
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：13.22 MB, 击败 39.42%
 */

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

#include "../../../../Include/RandomNumbers.h"
#include "../../../../Include/Leetcode/LinkedList/LinkedList.h"
using namespace Leetcode::LinkedList;
using Leetcode::LinkedList::ListNode;

// 【思路 1】：单链表反转 -- 带虚拟头结点的方式
/*
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
*/

// 【思路 2】：单链表反转 -- 不带虚拟头结点的方式
class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        ListNode* cur = head;
        ListNode* next = NULL;
        ListNode* p = NULL; // 指向新链表的第一个节点
        while (cur) {

            next = cur->next;
            cur->next = p;
            p = cur;
            cur = next;
        }

        return p;
    }
};

int main() {
    int e_cnt = 5;
    int* arr = RandomNumbers::generateRandomArray(e_cnt, 0, 100);
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    ListNode::print_list((new Solution())->reverseList(head));
}