/**
 * @brief: Leetcode_1026_节点与其祖先之间的最大差值
 * @link: https://leetcode.cn/problems/maximum-difference-between-node-and-ancestor/description/
 * @author: liangj.zhang
 * @date: 24/11/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Tree(dfs)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：dfs
 *      一条路径上的最大差值，那我们考虑这条路径上的最小最大值就好了；
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(h)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：13.41 MB, 击败 61.7%
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

#include <cmath>

class Solution {

private:
    int _max = 0;
    void __maxAncestorDiff(TreeNode* root, int min, int max) {

        if (root->val < min) min = root->val;
        if (root->val > max) max = root->val;
        if (_max < max - min) _max = max - min;

        if (root->left) __maxAncestorDiff(root->left, min, max);
        if (root->right) __maxAncestorDiff(root->right, min, max);
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        
        __maxAncestorDiff(root, root->val, root->val);
        return _max;
    }
};