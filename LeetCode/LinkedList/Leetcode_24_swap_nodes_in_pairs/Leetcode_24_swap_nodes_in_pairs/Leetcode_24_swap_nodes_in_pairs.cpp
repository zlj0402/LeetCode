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

int main() {
    int e_cnt = 5;
    int* arr = RandomNumbers::getRandomArray(e_cnt, 0, 100);
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    ListNode::print_list((new Solution())->swapPairs(head));
}