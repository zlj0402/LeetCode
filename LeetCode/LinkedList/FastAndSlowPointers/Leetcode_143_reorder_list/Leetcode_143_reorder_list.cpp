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

        while (cur->next) {

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

        ListNode *dhead = fast ? slow : last_slow;
        reverseLinkedList(dhead);
        ListNode::print_list(dhead);

        // cur 从后半段第一个节点开始
        ListNode *cur = dhead->next;
        ListNode *pre = head;
        while (cur) {

            ListNode* cur_next = cur->next;

            cur->next = pre->next;
            pre->next = cur;

            pre = cur->next;
            cur = cur_next;
        }
    }
};

int main() {
    int e_cnt = 5;
    // int* arr = SortTestHelper::generateRandomArray(e_cnt, 0, 100);
    int arr[] = {1, 2, 3, 4, 5};
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    (new Solution())->reorderList(head);
    ListNode::print_list(head);
}