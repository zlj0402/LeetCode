/**
* @brief: Leetcode_114_二叉树展开为链表
* @link: https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/description
* @authhor: liangj.zhang
* @date: 20/6/2025
* 
* @Difficulty: Medium
* 
* @Label: Binary Tree
* 
* @thoughts:
*  【1】额外的数组保存，节点
*	分析：
*		时间效率：2 O(n)
*		空间效率：除了递归栈，主动使用的空间：O(n)
*	按先序遍历的顺序，将这个节点保存在一个 arr 中，
*	遍历完节点之后，从 arr 中遍历一遍，将各个节点关联起来；
* 
*	rank:
*		时间效率：0 ms, 击败 100%
*		空间效率：17.53 MB, 击败 20.51%
* 
*  【2】头插法
*	分析：
*		时间效率：O(n)
*		空间效率：只有递归栈会需要的空间，可以算作 O(1)
*	既然是按照先序遍历的顺序，那么 我们就按相反的方向，进行：
*		先序遍历：当前节点、左节点、右节点
*		相反的后续遍历：右节点、左节点、处理当前节点
* 
*	rank:
*		时间效率：0 ms, 击败 100%
*		空间效率：17.27 MB, 击败 53.96%
* 
*  【3】分治 -- 暂时没写
*	看的题解，看之前，想了 O(1) 的办法，想了很久；能想到单一的分治过程，做的内容：
*		将一颗子树，的右子树，放到左子树的最末端；
*	虽能想到，却没有在代码上处理好；
*	分析：
*		时间效率：O(n)，不知道每次找到最末端的过程需不需要算；
*		空间效率：O(1), 当然除外函数调用栈；
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include "Leetcode/Tree/Tree.h"
#include <vector>
using std::vector;
using Leetcode::Tree::BinaryTree::TreeNode;

class Solution {
private:
    TreeNode* head;

    void traverse(TreeNode* node) {

        if (!node)
            return;

        traverse(node->right);
        traverse(node->left);

        node->right = head;
        node->left = nullptr;
        head = node;
    }
public:
    void flatten(TreeNode* root) {

        head = nullptr;
        traverse(root);
    }
};

// 【1】
/*
class Solution {
private:
    void traverse(TreeNode* node, vector<TreeNode*>& l) {

        if (!node)
            return;
        l.push_back(node);
        traverse(node->left, l);
        traverse(node->right, l);
    }
public:
    void flatten(TreeNode* root) {

        if (!root) return;

        vector<TreeNode*> l;
        traverse(root, l);

        for (int i = 0; i < l.size() - 1; ++i) {

            l[i]->right = l[i + 1];
            l[i]->left = nullptr;
        }

    }
};
*/