// 
// Created by liangj.zhang on 3/11/2024
// 

// 外公化疗肝受损，进ICU，动车的路上看了这题的题解
// 我是先有了自己的思路：一个链表遍历的时候，改变val(超过border 1 <= Node.val <= 10^5)，
// 另一条链表遍历的时候，遇到大于border的值，就知道有没有相交了；
// 我这种解题虽然能过，但是改变了节点值，算是改变了链表原来的状态吧
// 
// 题解：
// 一条链表headA长a，一条链表headB长b，公共长度为c
// ---插播：一个指针遍历两个链表
// --- p = headA;
// --- p = p != nullptr ? p->next : headB;
// 
// a --- b-c --- c ==> a + (b - c)
// b --- a-c --- c ==> b + (a - c)
// 一个链表headA开头，串headB
// 一个链表headB开头，串headA
// 两个指针A，B同时从两个串开头遍历，那么在最后，它们会在同一个节点位置相遇
// 时间复杂度为 O(m+n)
// 没有额外空间

#include "RandomNumbers.h"
#include "Leetcode/LinkedList/LinkedList.h"
using namespace Leetcode::LinkedList;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */


class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* A = headA;
        ListNode* B = headB;
        while (A != B) {
            // A = A != nullptr ? A->next : headB;
            // B = B != nullptr ? B->next : headA;
            if (A)
                A = A->next;
            else
                A = headB;

            if (B)
                B = B->next;
            else
                B = headA;
        }

        return A;
    }
};