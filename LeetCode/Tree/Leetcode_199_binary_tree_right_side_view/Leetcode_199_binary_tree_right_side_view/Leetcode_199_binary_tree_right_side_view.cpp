/**
* @brief: Leetcode_199_二叉树右视图
* @link: https://leetcode.cn/problems/binary-tree-right-side-view/description
* @author: liangj.zhang
* @date: 19/6/2025
* 
* @Difficulty: Medium
* 
* @Label: Binary Tree
* 
* @brief content: 从右边看，每一行谁在最右边
* 
* @thoughts:
*	从右边看，右边比左边更有优先级；
*	并且，记录的节点值，是从上往下；
*	那么，我们采用先序遍历，且右节点遍历顺序，早于左节点；
* 
*	rank: 
*		时间效率：0 ms, 击败 100%
*		空间效率：14.52 MB, 击败 97.22%
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

#include <vector>
#include "Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using std::vector;

class Solution {
private:
    int max_level;
    vector<int> res;

    void traverse(TreeNode* node, int level) {

        if (!node)
            return;

        if (level > max_level) {

            res.push_back(node->val);
            max_level = level;
        }

        traverse(node->right, level + 1);
        traverse(node->left, level + 1);
    }
public:
    vector<int> rightSideView(TreeNode* root) {

        max_level = 0;
        res.clear();
        traverse(root, 1);
        return res;
    }
};