/**
 * @brief: Leetcode_143_重排链表
 * @link: https://leetcode.cn/problems/reorder-list/description/
 * @author: liangj.zhang
 * @date: 23/10/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Fast and Slow Pointers、Reverse LinkedList
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：快慢指针 + 反转链表
 *      能想到，分为上面两个过程后，在脑海中，动态的往前插入后部分的每个节点；
 *      当链表长度为偶数时，后部分会少一个节点，没有位置往前插入；
 *      当链表长度为奇数时，后半部比前半部少一个，能刚好全部往前插入；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：22.23 MB, 击败 95.27%
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

#include <iostream>

#include "../../../../Include/SortTestHelper.h"
#include "../../../../Include/Leetcode/LinkedList/LinkedList.h"

using namespace Leetcode::LinkedList;

class Solution {

private:
    // 不同以往，这里传递的是要反转部分的前一个节点 dhead;
    // 如果还以自己随便创建一个 dummy_head 的话，dhead (反转部分的前一个节点) 还是会一直指向反转前反转部分的原第一个节点；
    void reverseLinkedList(ListNode *dhead) {

        ListNode *cur = dhead->next;

        while (cur && cur->next) {

            ListNode *next = cur->next;
            cur->next = next->next;

            next->next = dhead->next;
            dhead->next = next;
        }
    }

public:
    void reorderList(ListNode* head) {
        
        ListNode *slow(head), *fast(head);
        ListNode *last_slow(NULL);
        while (fast && fast->next) {

            last_slow = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        // dhead 是要反转部分的前一个位置节点；
        ListNode *dhead = fast ? slow : last_slow;
        reverseLinkedList(dhead);
        ListNode::print_list(dhead->next);

        // cur 从后半段第一个节点开始
        ListNode *cur = dhead->next;
        ListNode *pre = head;
        while (pre != dhead) {

            // 先脱离后面的节点
            ListNode* cur_next = cur->next;
            dhead->next = cur_next;

            // 连接
            cur->next = pre->next;
            pre->next = cur;

            // 指向变动
            pre = cur->next;
            cur = cur_next;
        }
    }
};

int main() {

    int e_cnt = 4;
    // int* arr = SortTestHelper::generateRandomArray(e_cnt, 0, 100);
    int arr[] = {1, 2, 3, 4};
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    (new Solution())->reorderList(head);
    ListNode::print_list(head);
}