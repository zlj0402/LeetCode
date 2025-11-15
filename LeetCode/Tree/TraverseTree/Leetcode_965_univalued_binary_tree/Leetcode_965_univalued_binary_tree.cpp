/**
 * @brief: Leetcode_965_单值二叉树
 * @link: https://leetcode.cn/problems/univalued-binary-tree/description/
 * @author: liangj.zhang
 * @date: 15/11/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Tree(dfs)
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *  + 【思路 1】：dfs（剪枝版）：纯遍历树，深度优先，广度优先都可以；这里采用递归的 dfs 方式；
 *      + 分析：
 *          + 时间复杂度：最坏 O(n)
 *          + 空间复杂度：最坏 O(h), h 为树的高度
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：12.52 MB, 击败 91.38%
 */

#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;

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
    int base;
    bool res;
    void __isUnivalTree(TreeNode* root) {

        if (!res || !root) return;
        if (res && base != root->val) { res = false; return; }

        __isUnivalTree(root->left);
        __isUnivalTree(root->right);
    }

public:
    bool isUnivalTree(TreeNode* root) {
        
        res = true;
        base = root->val;
        __isUnivalTree(root);
        return res;
    }
};