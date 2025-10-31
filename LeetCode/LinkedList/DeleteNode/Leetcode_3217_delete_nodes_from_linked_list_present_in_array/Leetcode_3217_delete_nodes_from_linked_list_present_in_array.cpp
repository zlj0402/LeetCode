/**
 * @brief: Leetcode_3217_从链表中移除在数组中存在的节点
 * @link: https://leetcode.cn/problems/delete-nodes-from-linked-list-present-in-array/description/
 * @author: liangj.zhang
 * @date: 31/10/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: HashMap & DeleteNode
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：HashMap & DeleteNode
 *      应该很自然的，能够想到 用 set 这种结构来存储一遍需要删除的数组中的值；
 *      + 如果，值的范围很小，优先使用固定的数组
 *      + 如果，值的范围很大，优先使用 STL 库的 set （set/unordered_set）
 *      解题，还有个优先处理的方式，就是静态的 set 集合，clear() 之后会保留空位数，下次重新放入值，不会进行重新申请空间；
 * 
 *      存入哈希之后，就变成单纯的删除元素了，回归 《Leetcode_203》
 * 
 *      ps: 对于 C++ 的写法，最坑的是在于，不用自己手动回收；（也没给个提示）
 *          自己手动回收之后，Leetcode 后台会再回收一次，所以会报错；
 *          在周赛的时候，看不懂报错，那就凉凉，耽误时间；
 *  
 *      + 分析：
 *          + 时间复杂度：O(m + n) -> m -> 数组长度，n -> 链表长度
 *          + 空间复杂度：O(m)
 *      + rank：
 *          + 时间效率：87 ms, 击败 95.32%
 *          + 空间效率：245.90 MB, 击败 94.88%
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

#include <unordered_set>
using std::unordered_set;
#define us unordered_set

class Solution {
private:
    static us<int> s;
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        
        s.clear();
        for (auto e : nums)
            s.insert(e);
        
        ListNode dummy = ListNode(-1, head);
        ListNode* cur = &dummy;
        while (cur->next) {

            if (s.find(cur->next->val) != s.end()) {

                ListNode* tmp = cur->next;
                cur->next = tmp->next;
                //delete tmp;
            }
            else
                cur = cur->next;
        }

        return dummy.next;
    }
};

us<int> Solution::s = us<int>(10000);