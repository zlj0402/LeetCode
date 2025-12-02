/**
 * @brief: Leetcode_98_验证二叉搜索树
 * @link: https://leetcode.cn/problems/validate-binary-search-tree/description
 * @author: liangj.zhang
 * @date: 19/6/2025
 *
 * @updated: 
 *       + 2/12/2025: inOrder 两种写法 
 * 
 * @Difficulty: Medium
 * 
 * @Label: BST
 * 
 * @Retrospect(worthy 1 - 5): 5 -- Classic
 * 
 * @brief content: 验证一个树是否是二叉搜索树
 * 
 * @thoughs:
 *  + 【思路 1】：inOder 
 *	我们知道一个二叉搜索树，以中序遍历来输出的话，是顺序的结果；
 *	我们利用一个全局的 max_val 变量，来记录上一个遍历到的值；
 *	中序遍历的过程中：max_val 是应该每一次都会被更新的，如果有一次出现不是的情况，我们就知道结果；
 * 
 *	rank:
 *		时间效率：0 ms, 击败 100%
 *		空间效率：21.41 MB, 击败 85.28%
 *
 *   + 2/12/2025 -- inOrder 1
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：21.54 MB, 击败 48.37%
 *   + 2/12/2025 -- inOrder 2
 *      + rank:
 *          + 时间效率：0 ms，击败 100%
 *          + 空间效率：21.45 MB, 击败 72.2%
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
#include <climits>
using Leetcode::Tree::BinaryTree::TreeNode;

// inOrder 1 -- 2025.12.2
class Solution {
private:
    bool res;
    long long _last;

    void inOrder(TreeNode* root) {

        if (!res) return;

        if (root->left) inOrder(root->left);
        if (_last >= root->val)
            res = false;
        _last = root->val;
        if (root->right) inOrder(root->right);
    }
public:
    bool isValidBST(TreeNode* root) {
        
        res = true;
        _last = LONG_LONG_MIN;

        inOrder(root);

        return res;
    }
};

// inOrder 2 -- 2025.12.2
class Solution {
private:
    long long _last;
public:
    Solution() : _last(LONG_LONG_MIN) {}

    bool isValidBST(TreeNode* root) {
        
        if (!root) return true;

        if (!isValidBST(root->left))
            return false;
        if (root->val <= _last) return false;
        _last = root->val;
        if (!isValidBST(root->right))
            return false;
        
        return true;
    }
};

// 写法一 -- 2025.6.19
// class Solution {
// private:
//     bool flag = true;
//     long long max_val;

//     void traverse(TreeNode* node) {

//         if (!node || !flag)
//             return;

//         traverse(node->left);

//         if (node->val > max_val)
//             max_val = node->val;
//         else
//             flag = false;

//         traverse(node->right);
//     }
// public:
//     bool isValidBST(TreeNode* root) {

//         if (!root->left && !root->right) return true;

//         flag = true;
//         max_val = (long long)INT_MIN - 1;
//         traverse(root);
//         return flag;
//     }
// };