//
// Created by liangj.zhang on 27/10/2024
//

// 单链表，竟然要删除倒数第n个；
// 不知道有多长，进阶却要一遍就完成，删除倒数的节点；
// 不知道有多长，一遍就完成，必须要借助额外空间了；
// 遍历完之后，就可以O(1)的效率完成；
// 不借助额外空间，遍历完之后还需要O(n)的时间复杂度来完成；
// 通过知道最后一个在哪，有多少个，再去找对应的位置，我觉得是跑不掉，这个逻辑的；

// 那就顺着借助额外的空间来做
// 节点数目最多30个,那就申请31个空间
// 每遍历一下放入地址，个数++

/**
 * @brief: Leetcode_19_删除链表的倒数第 N 个结点
 * @link: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/
 * @author: liangj.zhang
 * @date: 27/10/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Two Pointers、Delete Node
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：双指针
 *      ps: 以前的方式，是申请同等长的指针数组，空间复杂度，在实际应用中不太好，但解题以静态的 MAX_NODE 个数解，却不错；
 *      回到这题，
 *      倒数第 n 个节点，我们需要找到其前面一个节点；
 *      第一个指针 rear 走了 n 步，我们用一个新的指针 front 从最前面，之后一同一次一步往后移动；
 *      rear 走到最后，front 也就到达想删除节点的前一个，这样就能解决问题；
 *      需要注意的是边界问题，比如：
 *      删除的就是第一个节点 => 我们可以借助 dummy head；不借助也是有办法的；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：14.79 MB, 击败 33.08%
 */

#include "../../../../../Include/Leetcode/LinkedList/LinkedList.h"
#include <iostream>
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        ListNode dummy = ListNode(-1, head);
        ListNode* cur = &dummy;
        ListNode* p = NULL;
        int i = 0;
        while (cur->next != NULL) {
            
            if (++i <= n) {

                cur = cur->next;
                if (i == n) p = &dummy;
                continue;
            }
            
            p = p->next;
            cur = cur->next;
        }

        ListNode* tmp = p->next;
        if (tmp) {
            
            p->next = tmp->next;
            delete tmp;
        }

        return dummy.next;
    }
};

// 方式 1：申请等长数组
/*
class Solution {
private:
    int MAX_NODE = 31;
    ListNode* *addr = new ListNode*[MAX_NODE];
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy_head = new ListNode(-1, head);
        ListNode* cur = dummy_head;
        int i = -1;
        while (cur) {
            addr[++i] = cur;
            cur = cur->next;
        }

        ListNode* prev = addr[i - n];
        prev->next = prev->next->next;
        return dummy_head->next;
    }
};
*/

int main() {

    int e_cnt = 1;
    int arr[] = {1};
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    ListNode* res = Solution().removeNthFromEnd(head, 1);
    ListNode::print_list(res);
}