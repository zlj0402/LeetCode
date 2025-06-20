/**
* @brief: Leetcode_21_合并两个有序链表
* @link: https://leetcode.cn/problems/merge-two-sorted-lists/description
* @author: liangj.zhang
* @date:
*   【1】- 23/10/2024
*   【2】- 20/6/2025
* 
* @Difficulty: Easy
* 
* @Label: LinkedList
* 
* @thoughts:
*   【1】- 23/10/2024 写的，看了下代码，分析如下:
*       选定一个链表为要返回的主链，另一个链表循环遍历，再在内部循环遍历主链表，找到合适插入的位置；
*       分析：
*           时间复杂度：O(m * n)，m/n 为链表的长度；
*           空间复杂度：O(1)
* 
*       rank:
*           时间效率：0 ms, 击败 100%
*           空间效率：19.36 MB, 击败 5.15%
* 
*   【2】- 20/6/2025 用一个 dummy_head，谁小，谁接在后面；
*       一个循环，比较两个链表的头结点，谁小，谁接在 head 后面，
*       然后，链表头结点指针往后偏移一位；
*       循环结束，必有一个已经完全遍历；
*       另一个链表，剩余部分直接接在 head 后面；（另一个为空，也不影响）
*       分析：
*           时间复杂度：O(m + n), m/n 为链表的长度，比上面的时间效率要高；
*           空间复杂度：O(1)
* 
*       rank:
*           时间效率：0 ms, 击败 100%
*           空间效率：19.05 MB, 击败 71.35%
*/

#include "Leetcode/ListTestHelper.h"
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;
using namespace Leetcode;
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

// 【2】
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        ListNode dummy_head;
        ListNode* head = &dummy_head;

        while (list1 && list2) {

            if (list1->val <= list2->val) {
                head->next = list1;
                list1 = list1->next;
            }
            else {
                head->next = list2;
                list2 = list2->next;
            }
            head = head->next;
        }

        head->next = list1 ? list1 : list2;

        return dummy_head.next;
    }
};

int main() {

    vector<int> nums1 = { -9,-5,-3,-2,-2,3,7 };
    ListNode* list1 = ListTestHelper::generateIntLinkedList(nums1.data(), nums1.size());
    ListTestHelper::print_list(list1);
    vector<int> nums2 = { -10,-8,-4,-3,-1,3 };
    ListNode* list2 = ListTestHelper::generateIntLinkedList(nums2.data(), nums2.size());
    ListTestHelper::print_list(list2);

    cout << (new Solution())->mergeTwoLists(list1, list2);
}

// 【1】
/*
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

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
private:
    void insert_node(ListNode* prev, ListNode* node) {
        // insert node after prev
        // prev is not nullptr
        node->next = prev->next;
        prev->next = node;
    }

public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr)
            return list2;
        if (list2 == nullptr)
            return list1;
        ListNode* dummy_head = new ListNode(-1, list1);
        //ListNode::print_list(dummy_head);
        //ListNode::print_list(list2);
        for (ListNode* p = list2; p != nullptr;) {
            ListNode* cur = dummy_head;
            ListNode* pp = p;
            p = p->next;
            while (cur->next != nullptr && cur->next->val < pp->val)
                cur = cur->next;
            insert_node(cur, pp);
        }

        return dummy_head->next;
    }
};

int main() {
    // 创建链表: 1 -> 2 -> 3
    ListNode* head = new ListNode(1);
    head->next = new ListNode(3);
    head->next->next = new ListNode(5);

    // 创建链表: 2 -> 4 -> 6
    ListNode* head2 = new ListNode(2);
    head2->next = new ListNode(4);
    head2->next->next = new ListNode(6);
    // 打印链表
    ListNode::print_list((new Solution())->mergeTwoLists(head, head2));  // 输出: 1 -> 2 -> 3

    return 0;
}
*/