//
// Created by liangj.zhang 26/10/2024
//

// 看完题目描述，第一时间，想到的是哈希
// 第一种：先对值哈希，值确实相同，那就再哈希地址
// 第二种，就是只对地址哈希（地址可以转为unsigned long long，从linux list.h中看到的宏定义解读）
// 可是，我又看到下面，有没有办法，只用O(n)的空间复杂度，
// 陷入的短暂的沉思，看了前面讨论，多个快慢指针的黑粗的标题，多次出现在眼前
// 就往下看了几行描述，我就有些知道他们快慢指针的意思
// 按照这个思路来做做

// 快指针一次走两步，慢指针一次走一步
// 闭环他们肯定有相遇的时候，应为慢指针是一步一步走的，总有相遇的时候
// 1. 如果链表确实没有环，快指针走两步，走一步之后，要判断一下next是否为null
//    为null，就可以直接退出了
// 2. 题目要返回第一个入环的节点地址；我的想法是
//    慢指针，每走一步，改变节点的val值；因为题目中给了节点值的范围：-10^5 <= val <= 10^5
//    从100001开始；如果闭环，那慢指针走到大于范围的值，那就刚好走了一遍，可以结束
//                  如果不闭环，那快指针为null，或者下一个指向null，则可以结束

#include <iostream>
#include "RandomNumbers.h"
#include "Leetcode/LinkedList.h"

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
private:
    int VALUE_BORDER = 100000;
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;

        int i = 0;
        while (fast && (slow->val <= VALUE_BORDER)) {
            //fast = fast->next; -> 注释掉，那么外面判断是fast终止循环（即不闭环），条件为fast/fast->next != nullptr
            if (fast->next == nullptr) break;
            fast = fast->next->next;
            slow->val = VALUE_BORDER + (++i);
            slow = slow->next;
        }
        return (fast == nullptr || fast->next == nullptr) ? nullptr : slow;
    }
};

int main() {
    int e_cnt = 4;
    int* arr = RandomNumbers::getRandomArray(e_cnt, 1, 100);
    RandomNumbers::printArr(arr, e_cnt);

    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    ListNode* tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    ListNode* sec = head->next;
    tail->next = sec;
    ListNode* ret = (new Solution)->detectCycle(head);
    if (ret != nullptr)
        cout << (*ret).val << endl;
}