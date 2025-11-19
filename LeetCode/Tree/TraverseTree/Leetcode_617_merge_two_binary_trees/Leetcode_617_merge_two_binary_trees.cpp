/**
 * @brief: Leetcode_617_合并二叉树
 * @link: https://leetcode.cn/problems/merge-two-binary-trees/description/
 * @author: liangj.zhang
 * @date: 19/11/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Tree(dfs)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + thoughts:
 *   + 【思路 1】：递归 -- C++ -- 2025.11.19
 *      因为可能需要将当前层节点，赋给上一层；所以我们最好是在 参数 root1 root2 的角度，考虑其子节点；
 *      保证每次传入的参数，都是不为 nullptr 的情况；
 *          + 两个左子节点都不为 nullptr，则继续递归；其他情况略过；
 *          + 两个右子节点都不为 nullptr，则继续递归；其他情况略过；
 *      + 分析：
 *          + 时间复杂度：最多 O(max(m, n))，m, n 分别为 root1, root2 的节点数
 *          + 空间复杂度：最多 O(max(hm, hn))，hm, hn 分别为 root1, root2 树的高度
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：32.29 MB, 击败 97.99%
 * 
 *      + 写法2：看到也能在当前层，处理当前层的事情；-- Python 实现了 -- 2025.11.19
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
    void __mergeTrees(TreeNode* root1, TreeNode* root2) {
        // promise that root1 && root2 -> true

        if (root1->left && root2->left) {

            root1->left->val += root2->left->val;
            __mergeTrees(root1->left, root2->left);
        }
        else if (!root1->left && root2->left) {

            root1->left = root2->left;
            root2->left = nullptr;
        }

        if (root1->right && root2->right) {

            root1->right->val += root2->right->val;
            __mergeTrees(root1->right, root2->right);
        }
        else if (!root1->right && root2->right) {

            root1->right = root2->right;
            root2->right = nullptr;
        }
    }

public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        
        if (!root1 && !root2) return nullptr;
        else if (!root1) return root2;
        else if (!root2) return root1;

        root1->val += root2->val;
        __mergeTrees(root1, root2);

        return root1;
    }
};