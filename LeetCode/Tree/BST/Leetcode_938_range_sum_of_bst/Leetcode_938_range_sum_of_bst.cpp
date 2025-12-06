/**
 * @brief: Leetcode_938_二叉搜索树的范围和
 * @link: https://leetcode.cn/problems/range-sum-of-bst/description/
 * @author: liangj.zhang
 * @date: 7/12/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: BST
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：后序遍历
 *      需要注意的一点是，当前节点不满足条件时，其子节点还是有可能的，
 *          < low, 其右子树还是有可能的
 *          > hight, 其左子树还是有可能的
 *      ，还有一点就是return的时候，正常是返回当前节点值，+ 上左右子树返回来的值；但是要判断当前节点是否满足被加上的条件（low <= root->val <= high）
 *      
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：63.43 MB, 击败 86.19%
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

public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        
        if (!root) return 0;

        int left{0}, right{0};
        if (root->val < low) right = rangeSumBST(root->right, low, high);
        else if (root->val > high) left = rangeSumBST(root->left, low, high);
        else {

            left = rangeSumBST(root->left, low, high);
            right = rangeSumBST(root->right, low, high);
        }

        return ((root->val >= low && root->val <= high) ? root->val : 0) + left + right;
    }
};