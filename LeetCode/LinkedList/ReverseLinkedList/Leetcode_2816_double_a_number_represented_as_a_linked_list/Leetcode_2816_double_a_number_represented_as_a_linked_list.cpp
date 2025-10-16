/**
 * @brief: Leetcode_2816_翻倍以链表形式表示的数字
 * @link: https://leetcode.cn/problems/double-a-number-represented-as-a-linked-list/description/
 * @author: liangj.zhang
 * @date: 16/10/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Reverse LinkedList
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：反转链表
 *      就像 《Leetcode_445_两数相加_II》一样，先反转，按正常顺序加，考虑进位，最后再反转一次；
 *      + 分析：
 *          + 时间复杂度：反转两次，遍历一次：3 * O(n) == O(n)
 *          + 空间复杂度：O(1)
 * 
 *      + rank:
 *          + 时间效率：2 ms, 击败 79.44%
 *          + 空间效率：122.81 MB, 击败 75.07%
 * 
 *  + 【思路 2】：一遍顺序遍历链表
 *      数翻倍，就像同样的链表加自己，头结点 > 4 的时候，才会产生一个新的节点；
 *      >>> 后续节点也是 > 4 的时候，才会向前面进 1；不然，不会进位；<<<
 * 
 *      留在以后写吧
 *      python 是这种写法，python 反转的写法留以后吧；
 */
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

#include "../../../../Include/Leetcode/LinkedList/LinkedList.h"
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

// 【思路 1】：反转链表
class Solution {
private:
    static ListNode* reverseLinkedList(ListNode* head) {

        ListNode* cur = head;
        ListNode* p = NULL;

        while (cur) {

            ListNode* next = cur->next;
            cur->next = p;

            p = cur;
            cur = next;
        }
        return p;
    }
public:
    ListNode* doubleIt(ListNode* head) {
        
        ListNode* cur = reverseLinkedList(head);
        ListNode* res_node(cur);
        // ListNode::print_list(cur);

        ListNode* last_cur = NULL;
        bool flag = false;
        while (cur) {

            cur->val *= 2;
            if (flag) {

                cur->val += 1;
                flag = false;
            }
            if (cur->val >= 10) {

                cur->val %= 10;
                flag = true;
            }
            last_cur = cur;
            cur = cur->next;
        }

        if (flag) {

            last_cur->next = new ListNode(1);
            last_cur = last_cur->next;
        }

        // ListNode::print_list(res_node);

        return reverseLinkedList(res_node);
    }
};

int main() {

    vector<int> arr = {1, 8, 9};
    ListNode* head = new ListNode(arr.data(), arr.size());
    ListNode::print_list(head);

    Solution().doubleIt(head);
}