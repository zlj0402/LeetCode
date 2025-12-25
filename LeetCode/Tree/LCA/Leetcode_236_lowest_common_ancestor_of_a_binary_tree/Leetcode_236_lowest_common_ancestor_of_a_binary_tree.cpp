/**
 * @brief: Leetcode_236_二叉树的最近公共祖先
 * @link: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/
 * @author: liangj.zhang
 * @date: 25/12/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Tree(post order)
 * 
 * @Retrospect(worthy 1 - 5): 5 -- classic
 * 
 * @thoughts:
 *  + 【思路 1】：dfs(postorder)
 *      这是算我正式的第一道 LCA, 看的灵神题解，思路很清晰，希望在忘记之后，下次还能写出这题；
 *      ----
 *      1. 当前节点是空节点
 *      2. 当前节点时 p(目标节点之一)
 *      3. 当前节点是 q(目标节点之一)
 *          -- 上面 3 种情况，直接返回
 *      4. 其他：
 *          4.1 左右子树都找到：return 当前节点
 *          4.2 只有左子树找到：return 递归左子树的结果
 *          4.3 只有右子树找到：return 递归右子树的结果
 *          4.4 左右子树都没有找到：return 空节点 --（当前遍历的方向，刚好不是两个节点所在的子树）
 *      
 *      + 分析：
 *          + 时间复杂度：最差 O(n)
 *          + 空间复杂度：最差 O(n)
 *      + rank:
 *          + 时间效率：12 ms, 击败 73.32%
 *          + 空间效率：16.80 MB, 击败 98.65%
 */

#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using namespace Leetcode::Tree::BinaryTree;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        // 1. 2. 3.
        if (!root || root == p || root == q) return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right)  // 4.1
            return root;
        else if (left)      // 4.2
            return left;
        
        return right;       // 4.3 4.4 合并
    }
};