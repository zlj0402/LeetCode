// 
// Created by liangj.zhang 2/11/2024
//

// Q: https://leetcode.cn/problems/maximum-depth-of-binary-tree/description
//
// type: traverse binary tree
//
// thought: 递归遍历

// rank:
// 时间0ms,击败100%
// 内存17.32MB,击败69.9%

#include "Leetcode/Tree/Tree.h"
using namespace Leetcode::Tree::BinaryTree;

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

class Solution {
private:
    int max_depth;
    void traverseBinaryTree(TreeNode* node, int depth) {
        if (node == nullptr)
            return;
        if (max_depth < depth) max_depth = depth;
        traverseBinaryTree(node->left, depth + 1);
        traverseBinaryTree(node->right, depth + 1);
    }

public:
    int maxDepth(TreeNode* root) {
        max_depth = 0;
        traverseBinaryTree(root, 1);
        return max_depth;
    }
};