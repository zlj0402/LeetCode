/**
 * @brief: Leetcode_129_求根节点到叶节点数字之和
 * @link: https://leetcode.cn/problems/sum-root-to-leaf-numbers/description/
 * @author: liangj.zhang
 * @date: 7/11/2025
 * 
 * @Difficulty: Medium (我认为只有 Easy 级别)
 * 
 * @Label: Tree(Traverse)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：递归
 *      要在叶子节点处进行结算，不能等到进入空节点（不然要多借助一个递归的变量，记录上一次访问的节点）
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(h)，h 为树的高度
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：11.58 MB, 击败 86.67%
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
    int sum;

    void __sumNumbers(TreeNode* root, int val) {

        if (root && !root->left && !root->right)
            sum += val;
        
        if (root->left) __sumNumbers(root->left, val * 10 + root->left->val);
        if (root->right) __sumNumbers(root->right, val * 10 + root->right->val);

    }
public:
    int sumNumbers(TreeNode* root) {
        
        sum = 0;
        __sumNumbers(root, root->val);
        return sum;
    }
};