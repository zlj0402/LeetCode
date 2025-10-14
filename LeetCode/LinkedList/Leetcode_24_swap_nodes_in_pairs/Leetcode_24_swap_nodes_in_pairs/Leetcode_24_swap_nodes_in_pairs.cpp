//
// Created by liangj.zhang on 29/10/2024
//

// 看到这题，我的思路是：
// 两个指针，每次移动两步；
// 在后面位置的第二个节点，如果不是null，则进行正常赋值，完成交换就可以了；
// 更正...
// 需要三个指针，最后面的指针(bhd)，需要被前面节点(cur)的前一个节点(pre)指一下
// pre -> cur -> bhd

// rank: great
// 时间效率击败了100%
// 空间复杂度击败了91.74%；不清楚为什么将节点交换提取成一个内联函数，空间复杂度就降低了；很可能只是大家都差不多，运行时的小差异罢了；

/**
 * @brief: Leetcode_24_两两交换链表中的节点
 * @link: https://leetcode.cn/problems/swap-nodes-in-pairs/description/
 * @author: liangj.zhang
 * @date: 14/10/2025
 * 
 * @ps: 以前的答题思路也留下来不删除了，以后更新也放这条注释里
 * 
 * @Difficulty: Medium
 * 
 * @Label: Reverse LinkedList
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：带 dummy_head 的方式
 *      做过 《Leetcode_25_K个一组翻转链表》之后做这一题的，显然更容易点这道题；
 *      标准的 K个一组翻转，还得是 Leetcode_25;
 *      这道题，两个一组翻转，我们很容易下次翻转的前提条件，有足够的个数，这里是 2;
 *      所以可以简化为单循环就可以了;
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：10.89 MB, 击败 86%
 */

#include "../../../../Include/RandomNumbers.h"
#include "../../../../Include/Leetcode/LinkedList/LinkedList.h"
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
public:
    ListNode* swapPairs(ListNode* head) {
        
        ListNode dummy = ListNode(-1, head);
        ListNode* dhead = &dummy;

        ListNode* cur = dhead;
        while (cur) {

            ListNode* nextNode = cur->next;
            if (!nextNode) break;
            cur->next = nextNode->next;

            nextNode->next = dhead->next;
            dhead->next = nextNode;

            // dhead -> 下一次链表翻转范围的前一个节点
            dhead = cur;
            cur = dhead->next;
        }

        return dummy.next;
    }
};

/*
class Solution {
private:
    inline void swap_adjacent_nodes(ListNode* pre, ListNode* cur) {
        // cur && cur->next == true
        pre->next = cur->next;
        cur->next = cur->next->next;
        pre->next->next = cur;
    }
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummy_head = new ListNode(-1, head);
        ListNode* pre = dummy_head; 
        ListNode* cur = pre->next;

        while (cur && cur->next) {
            swap_adjacent_nodes(pre, cur);

            pre = cur;
            cur = cur->next;
        }
        return dummy_head->next;
    }
};
*/

int main() {
    int e_cnt = 5;
    int* arr = RandomNumbers::generateRandomArray(e_cnt, 0, 100);
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    ListNode::print_list((new Solution())->swapPairs(head));
}