//
// Created by liangj.zhang on 27/10/2024
//

// 单链表，竟然要删除倒数第n个；
// 不知道有多长，进阶却要一遍就完成，删除倒数的节点；
// 不知道有多长，一遍就完成，必须要借助额外空间了；
// 遍历完之后，就可以O(1)的效率完成；
// 不借助额外空间，遍历完之后还需要O(n)的时间复杂度来完成；
// 通过知道最后一个在哪，有多少个，再去找对应的位置，我觉得是跑不掉，这个逻辑的；

// 那就顺着借助额外的空间来做
// 节点数目最多30个,那就申请31个空间
// 每遍历一下放入地址，个数++

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
    int MAX_NODE = 31;
    ListNode* *addr = new ListNode*[MAX_NODE];
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy_head = new ListNode(-1, head);
        ListNode* cur = dummy_head;
        int i = -1;
        while (cur) {
            addr[++i] = cur;
            cur = cur->next;
        }

        ListNode* prev = addr[i - n];
        prev->next = prev->next->next;
        return dummy_head->next;
    }
};