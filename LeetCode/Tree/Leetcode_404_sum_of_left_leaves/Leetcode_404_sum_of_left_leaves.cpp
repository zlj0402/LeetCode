/**
 * @brief: Leetcode_404_左叶子之和
 * @link: https://leetcode.cn/problems/sum-of-left-leaves/description/
 * @author: liangj.zhang
 * @date: 5/11/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Tree(Traverse)
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *  + 【思路 1】：右子树，还是要遍历的，不然右子树下的左叶子结点怎么办；
 *   
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(h), h 为树的高度
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：15.9 MB, 击败 46.21%
 */

#include "../../../Include/Leetcode/Tree/Tree.h"
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

// 【思路 1】：右子树，还是要遍历的，不然右子树下的左叶子结点怎么办；
class Solution {

private:

    int sum;
    void __sumOfLeftLeaves(TreeNode* root, bool isLeft) {
        
        if (!root) return;

        if (isLeft && !root->left && !root->right)
            sum += root->val;

        __sumOfLeftLeaves(root->left, true);
        __sumOfLeftLeaves(root->right, false);
    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        
        if (!root) return 0;

        sum = 0;
        __sumOfLeftLeaves(root, false);

        return sum;
    }
};