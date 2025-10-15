/**
 * @brief: Leetcode_445_两数相加_II
 * @link: https://leetcode.cn/problems/add-two-numbers-ii/description/
 * @author: liangj.zhang
 * @date: 15/10/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Reverse LinkedList
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：翻转链表
 *      翻转链表的时候，顺便得到链表的长度；借此找到最长的链表；
 *      后续的加法结果，复用该最长的链表；注意末端可能有进位产生的新节点;
 *      最后再反转一次链表，结果正序；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)，遍历链表
 *          + 空间复杂度：O(1)，进位最多新增一个节点；
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：74.47 MB, 击败 99.78%
 */

#include <iostream>
#include <vector>
#include "../../../Include/Leetcode/LinkedList/LinkedList.h"
using Leetcode::LinkedList::ListNode;
using std::cout;
using std::endl;
using std::vector;

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

// 【思路 1】：翻转链表
class Solution {
private:
    static std::pair<ListNode*, int> reverseLinkedList(ListNode* head);
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        std::pair<ListNode*, int> res;

        res = reverseLinkedList(l1);
        l1 = res.first;
        int len1(res.second);

        res = reverseLinkedList(l2);
        l2 = res.first;
        int len2(res.second);

        ListNode *max_lst = len1 >= len2 ? l1 : l2;
        ListNode *min_lst = len1 >= len2 ? l2 : l1;

        ListNode* res_lst(max_lst);
        ListNode* last_max_node(NULL);
        bool flag = false;  // 是否有进位
        while (max_lst && min_lst) {

            max_lst->val += min_lst->val;
            if (flag) {

                ++max_lst->val;
                flag = false;
            }
            if (max_lst->val >= 10) {

                flag = true;
                max_lst->val %= 10;
            }

            last_max_node = max_lst;
            max_lst = max_lst->next;
            min_lst = min_lst->next;
        }

        while (flag) {

            if (max_lst) {

                max_lst->val += 1;
                flag = false;

                if (max_lst->val >= 10) {

                    flag = true;
                    max_lst->val %= 10;
                    last_max_node = max_lst;
                    max_lst = max_lst->next;
                }
            }
            else {

                last_max_node->next = new ListNode(1);
                flag = false;
            }
        }

        return reverseLinkedList(res_lst).first;
    }
};

std::pair<ListNode*, int> Solution::reverseLinkedList(ListNode* head) {

    int len = 0;
    ListNode* cur = head;
    ListNode* p = NULL;

    while (cur && ++len) {

        ListNode* next = cur->next;
        cur->next = p;

        p = cur;
        cur = next;
    }

    return {p, len};
}

int main() {

    // int arr[] = {7,2,4,3};
    // vector<int> arr = {5};
    vector<int> arr = {1};
    // int arr2[] = {5,6,4};
    // vector<int> arr2 = {5};
    vector<int> arr2 = {9, 9};
    ListNode *l1 = new ListNode(arr.data(), arr.size());
    ListNode *l2 = new ListNode(arr2.data(), arr2.size());

    Solution().addTwoNumbers(l1, l2);
}