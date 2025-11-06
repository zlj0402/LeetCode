/**
 * @brief: Leetcode_112_路径总和
 * @link: https://leetcode.cn/problems/path-sum/description/
 * @author: liangj.zhang
 * @date: 6/11/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Tree(Traverse)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：递归
 *      + 【写法 1】：在叶子结点结算
 *          + 分析：
 *              + 时间复杂度：O(n)
 *              + 空间复杂度：O(h)，h 为树的高度
 *          + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：20.96 MB, 击败 92.86%
 * 
 *      + 【写法 2】：在空节点结算，但需要额外借助一个 parent 变量；
 *          + 分析：
 *              + 时间复杂度：O(n)
 *              + 空间复杂度：O(h)，h 为树的高度
 *          + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：21.05 MB, 击败 65.06%
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

// 【写法 2】：也是递归，在空节点结算；
class Solution {
private:
    bool find;

    void __hasPathSum(TreeNode* root, int left, TreeNode* parent) {

        if (!root) {

            if (!find && left == 0 && !parent->left && !parent->right)
                find = true;

            return;
        }

        if (!find) {
            
            __hasPathSum(root->left, left - root->val, root);
            __hasPathSum(root->right, left - root->val, root);
        }
    }

public:
    bool hasPathSum(TreeNode* root, int targetSum) {

        if (!root) return false;
        
        find = false;
        __hasPathSum(root, targetSum, NULL);

        return find;
    }
};

 // 【写法 1】：递归，在叶子结点结算
class Solution {
private:
    bool find;

    void __hasPathSum(TreeNode* root, int left) {

        if (!root->left && !root->right && left == 0) 
            find = true;

        if (!find) {
            
            if (root->left) __hasPathSum(root->left, left - root->left->val);
            if (root->right) __hasPathSum(root->right, left - root->right->val);
        }
    }

public:
    bool hasPathSum(TreeNode* root, int targetSum) {

        if (!root) return false;
        
        find = false;
        __hasPathSum(root, targetSum - root->val);

        return find;
    }
};