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

/**
 * @brief: Leetcode_142_环形链表_II
 * @link: https://leetcode.cn/problems/linked-list-cycle-ii/description/
 * @author: liangj.zhang
 * @date: 21/10/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Fast and Slow Pointers
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：快慢指针
 *      上面 // 注释，以前的写法并不标准，但也是一种解法；标准是不得修改链表节点；
 *      标准写法，基于：
 *          + 假设是循环链表：
 *              + a 是圈之外的部分；
 *              + b 是 slow 在圈内走的距离
 *              + c 是 圈的长度 - slow 在圈内走的距离
 *          快指针 与 慢指针相遇时，快指针，可能已经走了 k 圈了；
 *          2 * (a + b) = a + b + k * (b + c) ==> a + b = k * (b + c) ==> a - c = (k - 1) * (b + c)
 *          意味着，从相遇点开始，head 和 slow 一次一步，
 *          先走 c 步距离，此时，head 应该距离相遇点还有 a - c 的距离，slow 此时则在相遇点，
 *          a - c 是一圈 b + c 的倍数，
 *          所以，head 继续走 a - c，slow 与 head 终会在相遇点相遇；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：11 ms, 击败 39.6%
 *          + 空间效率：10.98 MB, 击败 98.93%
 */

#include <iostream>
// #include "RandomNumbers.h"
// #include "Leetcode/LinkedList.h"
#include "../../../../Include/SortTestHelper.h"
#include "../../../../Include/Leetcode/LinkedList/LinkedList.h"

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
    ListNode *detectCycle(ListNode *head) {
        
        ListNode *slow(head), *fast(head);
        bool meet = false;
        while (fast && fast->next) {

            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {

                meet = true;
                break;
            }
        }

        if (!meet) return NULL;

        slow = fast;
        while (slow != head) {

            slow = slow->next;
            head = head->next;
        }

        return slow;
    }
};

/*
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
*/

int main() {

    int e_cnt = 4;
    int* arr = SortTestHelper::generateRandomArray(e_cnt, 1, 100);
    SortTestHelper::printArray(arr, e_cnt);

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