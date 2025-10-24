/**
 * @brief: Leetcode_2130_链表最大孪生和
 * @link: https://leetcode.cn/problems/maximum-twin-sum-of-a-linked-list/description/
 * @author: liangj.zhang
 * @date: 24/10/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Fast and Slow Pointers、Reverse LinkedList
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：快慢指针 + 反转链表
 *      思路和 《Leetcode_234》是一样的，
 *      这次先尝试了，不带 “虚拟头结点” dhead（后半部分的前一个节点）的方式，不太行，dhead 会一直指向原来的下一个节点，比如：
 *      1 -> 2 -> 3 -> 4 -> 5 -> 6
 * 
 *      1 -> 2 -> 3 ↘
 *           6 -> 5 -> 4
 *      最后还是换了带 “虚拟头节点” dhead 的方式；就是本题的 void reverseLinkedList(ListNode* dhead)；
 *      
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：125.48 MB, 击败 36.69%
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
private:
    void reverseLinkedList(ListNode* dhead) {

        ListNode *cur(dhead->next);

        while (cur->next) {

            ListNode *next = cur->next;
            cur->next = next->next;

            next->next = dhead->next;
            dhead->next= next;
        }
    }
public:
    int pairSum(ListNode* head) {
        
        ListNode *slow(head), *fast(head);
        ListNode *last_slow(NULL);
        // // 遍历结束，slow 就在后半部分的前一个节点
        // while (fast && fast->next && fast->next->next) {

        //     slow = slow->next;
        //     fast = fast->next->next;
        // }
        // 遍历结束，slow 就在后半部分的前一个节点

        while (fast && fast->next) {

            last_slow = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        // 遍历结束，slow 在后半部分的第一个节点
        
        reverseLinkedList(last_slow);
        //ListNode::print_list(last_slow->next);

        fast = last_slow->next;
        slow = head;
        int max = 0;
        while (slow != last_slow->next) {

            if (max < slow->val + fast->val)
                max = slow->val + fast->val;
            
            slow = slow->next;
            fast = fast->next;
        }

        return max;
    }
};

int main() {

    int e_cnt = 4;
    // int* arr = SortTestHelper::generateRandomArray(e_cnt, 0, 100);
    int arr[] = {5, 4, 2, 1};
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    cout << (new Solution())->pairSum(head) << endl;
    ListNode::print_list(head);
}