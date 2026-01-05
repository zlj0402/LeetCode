/**
 * @brief: Leetcode_117_填充每个节点的下一个右侧节点指针_II
 * @link: https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/description/
 * @author: liangj.zhang
 * @date: 5/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：BFS + 链表
 *      Leetcode_116 的空间复杂度 O(1) 的办法是通用的，不论树是何种状态，只要是树就可以；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：7 ms, 击败 93.58%
 *          + 空间效率：18.64 MB, 击败 66.14%
 */

#define NULL 0
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    Node* connect(Node* root) {
        
        Node* cur = root;
        while (cur) {

            Node node{};
            Node* nxt = &node;
            while (cur) {

                if (cur->left) {

                    nxt->next = cur->left;
                    nxt = nxt->next;
                }
                if (cur->right) {

                    nxt->next = cur->right;
                    nxt = nxt->next;
                }
                cur = cur->next;
            }
            cur = node.next;
        }
        return root;
    }
};
