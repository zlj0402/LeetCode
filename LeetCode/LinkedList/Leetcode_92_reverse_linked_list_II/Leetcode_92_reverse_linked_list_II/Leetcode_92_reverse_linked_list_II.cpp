//
// Created by liangj.zhang on 25/10/2024
//

// notice:
// left/right -> 指的是第几个元素，生活中的第几个(没有第0个说法)

// idea1
// 昨天看的题，今天开始学习前，想到了一个办法，好像是昨天洗澡的时候，突然想到
// 1. 给list加一个dummy_head
// 2. 遍历的时候，保留 a.反转链表前一个节点(可能是dummy_head)；b.反转链表后面的位置
// 3. 中间的反转链表，新建一个头插的链表；要记一个tail节点，方便与原链表后面部分进行连接，省一个遍历
// 4. return dummy_head->next
// -----------------------------------
// dummy_head -> node1 -> node2
//     0      ->   1   ->   2

/**
 * @ps: 以前的思路留着不删，但看下面的代码那么长，还是有点绕晕了当时；
 * @brief: Leetcode_92_反转链表_II
 * @link: https://leetcode.cn/problems/reverse-linked-list-ii/description/
 * @author: liangj.zhang
 * @date: 12/10/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Reverse LinkedList
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：用带 dummy_head 的方式
 *      + 不带 dummy_head 的话，额外要做：
 *          + 记住 left 节点前面一个节点；
 *          + 记住 right 节点后面一个节点；（后面这个节点就需要，先遍历一遍，多一遍O(n)，俺不乐意）
 *      + >>> 不带 dummy_head 的话，虽都是那些节点，但分离节点的过程是脱离原来的链表的；<<<
 *      + >>>  带 dummy_head 的方式，分离的节点，一直都是在原来的链子上面，一条链；<<<
 * 
 *      + 分析：
 *          + 时间复杂度：O(right)
 *          + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：10.95 MB, 击败 80.36%
 */

// #include "RandomNumbers.h"
#include "../../../../Include/Leetcode/LinkedList/LinkedList.h"
#include "../../../../Include/RandomNumbers.h"
using namespace Leetcode::LinkedList;

// Definition for singly-linked list.
//  struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode *next) : val(x), next(next) {}
//  };

// 【思路 1】：用带 dummy_head 的方式 -- 12/10/2025
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {

        if (left == right) return head;
        
        ListNode dummy_head = ListNode(-1, head);
        int i = 0;

        ListNode* cur = &dummy_head;
        // 得到 left 的前一个节点;
        while (++i < left) {
            cur = cur->next;
        }
        // 离开 while loop 后，i == left

        ListNode* dhead = cur;  // 翻转的链表之前的节点
        cur = dhead->next;        // 翻转范围的第一个节点
        while (cur->next && ++i <= right) {

            ListNode* nextNode = cur->next;
            cur->next = nextNode->next; // 当前 cur 节点 & 下节点 nextNode，都指向 下下节点 nextNode->next;

            nextNode->next = dhead->next;
            dhead->next = nextNode;     // 将下节点 nextNode 插入到 dhead 之后;
        }

        return dummy_head.next;
    }
};
 
/*
// 12/10/2025
class Solution {
private:
    ListNode* pre_last_node = nullptr;
    ListNode* last_first_node = nullptr;
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // 发现，节点开始操作的位置在期望的后一个；所以加了下面的修改
        left = left - 1;
        right = right - 1;

        ListNode* dummy_head = new ListNode(-1, head);
        ListNode* cur = dummy_head;
        int i = 0;
        // iterate to left's previous node
        while (i < left) {
            i++;
            cur = cur->next;
        }
        pre_last_node = cur;    // lately, if need to judge it is dummy_head or not
        ListNode* new_dummy_head = new ListNode(-2);
        ListNode* new_tail = new_dummy_head;
        // iterate to right's position
        while (i <= right) {
            i++;
            int val = cur->next->val;
            cur = cur->next;
            new_dummy_head->next = new ListNode(val, new_dummy_head->next);
            if (i == left + 1) new_tail = new_dummy_head->next;
        }
        last_first_node = cur->next;

        // ------------------------------ link ------------------------------
        pre_last_node->next = new_dummy_head->next;
        new_tail->next = last_first_node;

        return dummy_head->next;
    }
};
*/

int main() {
    int e_cnt = 1;
    int *arr = RandomNumbers::getRandomArray(e_cnt, 1, 100);
    RandomNumbers::printArr(arr, e_cnt);

    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    ListNode::print_list((new Solution)->reverseBetween(head, 1, 1));
}