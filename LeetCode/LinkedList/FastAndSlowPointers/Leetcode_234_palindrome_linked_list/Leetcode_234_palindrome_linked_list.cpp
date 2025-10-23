/**
 * @brief: Leetcode_234_回文链表
 * @link: https://leetcode.cn/problems/palindrome-linked-list/description/
 * @author: liangj.zhang
 * @date: 23/10/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Reverse LinkedList、Fast and Slow Pointers
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：反转链表 + 快慢指针
 *      这题跟 《Leetcode_234_重排链表》一样，先 快慢指针 找到中点，再将后半部分反转；
 *      剩下的是属于本题的逻辑处理过程：比较前半部分和反转后的后半部分；
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：4 ms, 击败 68.75%
 *          + 空间效率：119.05 MB, 击败 51.95%
 */
#include <iostream>

#include "../../../../Include/SortTestHelper.h"
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

private:
    void reverseLinkedList(ListNode* dhead) {

        ListNode* cur = dhead->next;
        if (!cur) return;
        while (cur->next) {

            ListNode* next = cur->next;
            cur->next = next->next;

            next->next = dhead->next;
            dhead->next = next;
        }
    }
public:
    bool isPalindrome(ListNode* head) {
        
        ListNode *slow(head), *fast(head);

        ListNode* last_slow(NULL);
        while (fast && fast->next) {

            last_slow = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* dhead = fast ? slow : last_slow;
        reverseLinkedList(dhead);
        ListNode::print_list(head);

        ListNode *pre(head), *last(dhead->next);
        while (last) {

            if (pre->val != last->val)
                return false;
            
            pre = pre->next;
            last = last->next;
        }

        return true;
    }
};

int main() {

    int e_cnt = 2;
    // int* arr = SortTestHelper::generateRandomArray(e_cnt, 0, 100);
    int arr[] = {1, 2};
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    cout << (new Solution())->isPalindrome(head) << endl;
    ListNode::print_list(head);
}