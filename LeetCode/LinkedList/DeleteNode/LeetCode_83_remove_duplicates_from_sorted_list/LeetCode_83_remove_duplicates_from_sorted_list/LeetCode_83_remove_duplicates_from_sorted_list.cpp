/**
 * @brief: Leetcode_83_删除排序链表中的重复元素
 * @link: https://leetcode.cn/problems/remove-duplicates-from-sorted-list/description/
 * @author: liangj.zhang
 * @date: 28/10/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Delete Node
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：比较当前指针与下一个节点值
 *      ps: 原来自己的第一次写法，还是用额外空间来记录值；不知道当时有没有注意是已经排序的链表；
 *      今天写之前，可能是收了昨天写 Leetcode_19 的影响，第一想法用两个指针；
 *      行，肯定是可以的；但不如一个指针轻便；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：15.88 MB, 击败 62.14%
 */

#include <iostream>
#include <cstring>
using namespace std;

 // Definition for singly-linked list.

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

    static void print_list(ListNode* head) {
        ListNode* cur = head;
        while (cur != nullptr) {
            cout << cur->val << "->";
            cur = cur->next;
        }
        cout << "null" << endl;
    }
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {

        if (!head) return head;
        
        ListNode* cur = head;
        while (cur->next) {

            if (cur->val != cur->next->val) {

                cur = cur->next;
                continue;
            }

            ListNode* tmp = cur->next;
            cur->next = tmp->next;
            delete tmp;
        }

        return head;
    }
};

// 2024年第一次写的方式
/* 
class Solution {
private:
    bool map[201];

    void del_node(ListNode* cur) {
        cur->next = cur->next->next;
    }
public:

    ListNode* deleteDuplicates(ListNode* head) {
        memset(map, 0, sizeof(map));
        ListNode* dummy_head = new ListNode(-1, head);
        //ListNode::print_list(head);

        ListNode* cur = dummy_head;
        while (cur->next != nullptr) {
            int val = cur->next->val;
            // val occured before
            if (map[val + 100]) {
                del_node(cur);
            }
            // val did not occur before
            else {
                map[val + 100] = true;
                cur = cur->next;
            }
        }
        return dummy_head->next;
    }
};
*/

int main() {
    // 创建链表:
    ListNode* head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(5);
    ListNode::print_list((new Solution())->deleteDuplicates(head));
}