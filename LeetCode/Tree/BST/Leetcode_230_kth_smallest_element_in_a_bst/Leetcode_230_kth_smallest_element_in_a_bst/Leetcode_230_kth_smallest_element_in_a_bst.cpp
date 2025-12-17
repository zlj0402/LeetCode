/**
* @brief: Leetcode_230_二叉搜索树中第 K 小的元素
* @link: https://leetcode.cn/problems/kth-smallest-element-in-a-bst/description
* @author: liangj.zhang
* @date: 19/6/2025
* 
* @Difficulty: Medium
* 
* @Label: BST
* 
* @thoughts:
*	忽略题目后面的进阶要求，对于熟悉 BST 中序遍历过程的人来说，这题只能算得上 Easy；
* 
*	rank:
*		+ 时间效率：0 ms, 击败 100%
*		+ 空间效率：23.86 MB, 击败 73.31%
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
using Leetcode::Tree::BinaryTree::TreeNode;

class Solution {
private:
    int val;
    int cnt;
    int k;

    void traverse(TreeNode* node) {

        // val 还是 -1 的话，就不会直接 return
        if (!node || ~val)
            return;

        traverse(node->left);
        if (++cnt == k)
            val = node->val;
        traverse(node->right);
    }

public:
    int kthSmallest(TreeNode* root, int k) {

        val = -1;
        cnt = 0;
        this->k = k;

        traverse(root);

        return val;
    }
};