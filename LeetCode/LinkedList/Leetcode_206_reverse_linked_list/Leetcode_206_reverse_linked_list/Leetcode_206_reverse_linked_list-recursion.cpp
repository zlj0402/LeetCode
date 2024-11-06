//
// Created by liangj.zhang on 6/11/2024
//

// ���ź��������ǿ����д�ģ���ȫ�����Ĵ���
// �ݹ���ͷ�۰�
// �����Է�ת���������µ�ʵ�ַ�ʽ

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
#include "RandomNumbers.h"
#include "Leetcode/LinkedList/LinkedList.h"
using namespace Leetcode::LinkedList;

class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* new_head =  reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return new_head;
    }
};

int main() {
    int e_cnt = 5;
    int* arr = RandomNumbers::getRandomArray(e_cnt, 0, 100);
    ListNode* head = new ListNode(arr, e_cnt);
    ListNode::print_list(head);

    ListNode::print_list((new Solution())->reverseList(head));
}