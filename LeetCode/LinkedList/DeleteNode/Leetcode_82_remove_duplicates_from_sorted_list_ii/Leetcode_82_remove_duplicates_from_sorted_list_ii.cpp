/**
 * @brief: Leetcode_82_删除排序链表中的重复元素_II
 * @link: https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/description/
 * @author: liangj.zhang
 * @date: 29/10/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Delete Node
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：cur 指向已经处理过的最后一个节点，考虑其后两个节点 p / r；
 *              + 有重复值，先不断删除 r
 *              + 再删除 p
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：15.66 MB, 击败 6.29%
 * 
 *  + 【思路 1.2】：满足有重复值为前提（cur的后两个值是相同的），先保留值，然后不断的删除等 val 的节点；
 *      灵神的这种写法，更优雅；
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：15.61 MB, 击败 9.36%
 */

#include "../../../../Include/Leetcode/LinkedList/LinkedList.h"
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;
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

// 【思路 1.2】：写法同【思路 1】
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        
        ListNode dummy = ListNode(-101, head);
        ListNode* cur = &dummy;

        while (cur->next && cur->next->next) {

            int val = cur->next->val;
            if (cur->next->next->val == val) {
                
                while (cur->next && cur->next->val == val) {
                    
                    ListNode* p = cur->next;
                    cur->next = p->next;
                    delete p;
                }
            }
            else
                cur = cur->next;
        }

        return dummy.next;
    }
};

// 【思路 1】
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        
        ListNode dummy = ListNode(-101, head);
        ListNode* cur = &dummy;
        ListNode *p(NULL), *r(NULL);

        while (cur) {

            bool dup = false;
            p = cur->next;
            if (p)
                r = p->next;
            while (r && r->val == p->val) {

                dup = true;
                p->next = r->next;
                delete r;
                r = p->next;
            }

            if (dup) {  // 有重复值，进行删除 p，cur 还是停在前面已经处理过没有重复值的部分，不往后面走；

                cur->next = r;
                delete p;
            }
            else    // 没有重复值，cur 往后走
                cur = cur->next;
        }

        return dummy.next;
    }
};

int main() {

    vector<int> arr = {1,2,3,3,4,4,5};

    ListNode* head = new ListNode(arr.data(), arr.size());
    ListNode::print_list(head);

    ListNode* res = Solution().deleteDuplicates(head);
    ListNode::print_list(res);
}