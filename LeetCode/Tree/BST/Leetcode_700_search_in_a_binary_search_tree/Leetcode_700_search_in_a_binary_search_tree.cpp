/**
 * @breif: Leetcode_700_二叉搜索树中的搜索
 * @link: https://leetcode.cn/problems/search-in-a-binary-search-tree/description/
 * @author: liangj.zhang
 * @date: 4/12/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: BST
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：BST 的查找
 *      就类似 map/set STL 库的简略查找实现，查找是 O(logn)
 *      Code 十分简略，赞^^
 * 
 *      + 分析：
 *          + 时间复杂度：O(logn)
 *          + 空间负载的：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：34.70 MB, 击败 63.91%
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

#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        
        // if (!root) return nullptr;

        // if (root->val == val) return root;
        // 还能更简单
        if (!root || root->val == val) return root;

        return searchBST(root->val < val ? root->right : root->left, val);
    }
};