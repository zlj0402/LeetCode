/**
 * @brief: Leetcode_2487_从链表中移除节点
 * @link: https://leetcode.cn/problems/remove-nodes-from-linked-list/description/
 * @author: liangj.zhang
 * @date: 1/11/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Reverse LinkedList、Delete Node
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：反转链表 + 过滤节点，再反转链表
 *      视觉上，将数字看成对应的高度的柱子；
 *      题目的要求，转变就是，留下的柱子，其左边没有比柱子自己还矮的；
 *      从右向左投影的话，就是从最右边柱子开始，向 y 轴投影：
 *          让其先在 y 轴上留下印记，< 已经留下印记的柱子，它凸显不出来；
 *          只留下，>= 先留下印记的柱子，它才有资格留下（投影的顺序，是从右往左，依次投影）
 *      解题的话，就是先反转链表，从反转后的第一个节点，遍历链表，只留下 >= 当前节点的节点；
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：157.71 MB, 击败 87.50%
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
private:
    ListNode* reverseLinkedList(ListNode* head) {
        
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
    ListNode* removeNodes(ListNode* head) {
        
        head = reverseLinkedList(head);
        ListNode* cur = head;

        while (cur->next) {
            
            if (cur->next->val >= cur->val) 
                cur = cur->next;
            else
                cur->next = cur->next->next;
        }

        return reverseLinkedList(head);
    }
};

int main() {

    vector<int> arr = {5, 2, 13, 3, 8};
    // vector<int> arr = {138,466,216,67,642,978,264,136,463,331,60,600,223,275,856,809,167,101,846,165,575,276,409,590,733,200,839,515,852,615,8,584,250,337,537,63,797,900,670,636,112,701,334,422,780,552,912,506,313,474,183,792,822,661,37,164,601,271,902,792,501,184,559,140,506,94,161,167,622,288,457,953,700,464,785,203,729,725,422,76,191,195,157,854,730,577,503,401,517,692,42,135,823,883,255,111,334,365,513,338,65,600,926,607,193,763,366,674,145,229,700,11,984,36,185,475,204,604,191,898,876,762,654,770,774,575,276,165,610,649,235,749,440,607,962,747,891,943,839,403,655,22,705,416,904,765,905,574,214,471,451,774,41,365,703,895,327,879,414,821,363,30,130,14,754,41,494,548,76,825,899,499,188,982,8,890,563,438,363,32,482,623,864,161,962,678,414,659,612,332,164,580,14,633,842,969,792,777,705,436,750,501,395,342,838,493,998,112,660,961,943,721,480,522,133,129,276,362,616,52,117,300,274,862,487,715,272,232,543,275,68,144,656,623,317,63,908,565,880,12,920,467,559,91,698};
    ListNode* head = new ListNode(arr.data(), arr.size());
    ListNode::print_list(head);

    ListNode* res = Solution().removeNodes(head);
    ListNode::print_list(res);

    cout << "pause" << endl;
    while(1);
}