//
// Created by liangj.zhang on 30/10/2024
//

// 我的想法：
// 两次遍历
// 第一次遍历：构建新链表，但不赋值random；并map源节点和新节点
// 第二次遍历：同时遍历新旧链表，源节点对应的random，赋值给新节点的random

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

#include "RandomNumbers.h"
#include <unordered_map>
#define NULL 0
#define um unordered_map

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
private:
    um<Node*, Node*> addr_map;
public:
    Node* copyRandomList(Node* head) {
        Node* dummy_head = new Node(-1);
        Node* new_cur = dummy_head, * cur = head;

        for (; cur; new_cur = new_cur->next, cur = cur->next) {
            new_cur->next = new Node(cur->val);
            addr_map[cur] = new_cur->next;
        }
        for (new_cur = dummy_head->next, cur = head; cur; new_cur = new_cur->next, cur = cur->next) {
            new_cur->random = addr_map[cur->random];
        }
        return dummy_head->next;
    }
};