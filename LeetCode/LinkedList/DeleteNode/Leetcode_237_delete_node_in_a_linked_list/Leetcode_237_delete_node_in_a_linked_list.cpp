/**
 * @brief: Leetcode_237_删除链表中的节
 * @link: https://leetcode.cn/problems/delete-node-in-a-linked-list/description/
 * @author: liangj.zhang
 * @date: 25/20/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Delete Node
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *  + 【思路 1】：复制下一个节点值，再删除下一个下节点；
 *          我应该最初看到这道题的时候，也没想出来；
 *          >>> 难道真有不用知道上一个节点，就能删掉当前节点，并连接上链表？没有； <<<
 *          脑筋急转弯的题，意识到上面一点就行了；
 *      + 分析：
 *          + 时间复杂度：O(1)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：3 ms, 击败 97.15%
 *          + 空间效率：12.07 MB, 击败 75.95%
 */

#include "../../../../Include/Leetcode/LinkedList/LinkedList.h"
#include <iostream>
using std::cout;
using std::endl;
using Leetcode::LinkedList::ListNode;

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
    void deleteNode(ListNode* node) {
        
        ListNode *next = node->next;
        node->val = next->val;
        node->next = next->next;
        delete next;
    }
};