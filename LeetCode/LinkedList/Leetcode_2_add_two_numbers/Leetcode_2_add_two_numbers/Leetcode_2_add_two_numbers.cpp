// 
// Created by liangj.zhang on 28/10/2024
//

// 看到这道题，觉得还是挺简单的
// 首先，数字已经是倒序给出来了，后面高位相加，即使大于10，也能方便新增节点；
// 我的感觉，首先遍历一遍，知道两个链表的长度，这一步是省略不了的；

// 遍历链表，知道两个链表的长度
// 从较长的开始遍历到两个链表相同长度
// 从相同长度的地方，开始同时遍历
// 大于10进位，最后一位的话要增加一个节点；

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
    int l1_len = 0;
    int l2_len = 0;
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* cur = l1;
        for (cur = l1; cur && ++l1_len; cur = cur->next);
        for (cur = l2; cur && ++l2_len; cur = cur->next);
        bool l1_long = (l1_len >= l2_len);
        ListNode* ll = l1_long ? l1 : l2;
        ListNode* sl = l1_long ? l2 : l1;

        //ListNode::print_list(ll);
        //ListNode::print_list(sl);

        bool carry_bit = false;
        while (ll) {
            int sl_val = sl ? sl->val : 0;
            int val = ll->val + sl_val + (carry_bit ? 1 : 0);
            carry_bit = false;  // 注意carry_bit重置的额位置，应该是上一次carry_bit进位使用完之后，这次判断赋值之前!!!
            ll->val = val % 10;
            if (val >= 10) {
                carry_bit = true;
                if (ll->next == nullptr) {
                    ll->next = new ListNode(1);
                    break;
                }
            }
            ll = ll->next;
            if (sl) sl = sl->next;
        }
        return l1_long ? l1 : l2;
    }
};

int main() {
    int arr[7] = {9, 9, 9, 9, 9, 9, 9};
    int arr2[4] = { 9, 9, 9, 9 };
    ListNode* ll = new ListNode(arr, 7);
    ListNode::print_list(ll);
    ListNode* sl = new ListNode(arr2, 4);
    ListNode::print_list(sl);

    ListNode::print_list((new Solution())->addTwoNumbers(ll, sl));
}