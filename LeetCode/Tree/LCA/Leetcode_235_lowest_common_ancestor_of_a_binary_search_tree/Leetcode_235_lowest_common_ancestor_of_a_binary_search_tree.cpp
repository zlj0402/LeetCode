/**
 * @brief: Leetcode_235_二叉搜索树的最近公共祖先
 * @link: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
 * @author: liangj.zhang
 * @date: 26/12/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: BST & LCA
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：脑子里想想动态的向下寻找 p q 节点的过程；
 *      开始分叉的点，就是他们最近的公共祖先；
 * 
 *      灵神的思路更清晰：
 *          1. 当前节点是空节点 （对于 BST 情况需要判断吗）
 *          2. p 和 q 都在左子树：返回递归左子树的结果
 *          3. p 和 q 都在右子树：返回递归右子树的结果
 *          4. 其他：
 *              4.1 p 和 q 分别在左右子树
 *              4.2 当前节点是 p
 *              4.3 当前节点是 q
 *              ----
 *              上面这 3 种，返回当前节点
 * 
 *      + 分析：
 *          + 时间复杂度：O(n) -- 是搜索二叉树，但没有保证平衡
 *          + 空间复杂度：O(n) -- 递归
 *      + rank:
 *          + 时间效率：25 ms, 击败 65.62%
 *          + 空间效率：23.00 MB, 击败 56.96%
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using namespace Leetcode::Tree::BinaryTree;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        // if (!root) return nullptr;  // （4.1）p q 两节点存在的话，是不会找到空节点的

        if (p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);  // 4.2
        else if (p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right, p, q); // 4.3

        return root;    // 如果开始分叉就是当前节点 // 4.1 4.2 4.3
    }
};