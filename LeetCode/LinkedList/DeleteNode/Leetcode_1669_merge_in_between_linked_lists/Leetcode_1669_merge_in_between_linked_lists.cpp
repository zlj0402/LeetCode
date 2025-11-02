/**
 * @brief: Leetcode_1669_合并两个链表
 * @link: https://leetcode.cn/problems/merge-in-between-linked-lists/description/
 * @author: liangj.zhang
 * @date: 2/11/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Delete Node
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *  + 【思路 1】：在 list1 当中找到 a 下表索引的前一个节点，找到 b 下标索引的后一个节点；
 *      + condition: 1 <= a <= b < list1.length - 1     ==> 我们不必考虑边界，[a,b] 的范围是介于 (0, list1.length) 范围之内的；
 *      
 *      + 分析：
 *          + 时间复杂度：O(b + n), b -> 下表索引值, n -> list2 的长度
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：199 ms, 击败 93.51%
 *          + 空间效率：97.14 MB, 击败 72.99%
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
class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        
        ListNode* cur = list1;
        ListNode *pre(NULL), *next(NULL);
        int i = 0;

        while (++i < a) cur = cur->next;
        pre = cur;
        while (++i <= b + 1) cur = cur->next;
        next = cur->next;

        pre->next = list2;
        while (pre->next) pre = pre->next;
        pre->next = next;

        return list1;
    }
};