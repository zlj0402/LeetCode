/**
 * @brief: Leetcode_111_二叉树的最小深度
 * @link: https://leetcode.cn/problems/minimum-depth-of-binary-tree/description/
 * @author: liangj.zhang
 * @date: 4/11/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Tree
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：递归
 *      + 节点为 NULL，return 0
 *      + 节点自身存在，其下左右节点，至少有一个为 NULL 时，return 有子树那边的最小深度 => 即 return max(left, right) + 1, 都为 0，max 也能处理
 *      + 节点自身存在，其下左右节点都存在，return 左右子树最小的那边 + 1 => 即 return min(left, right) + 1
 *      
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(h), h 为树的高度；
 *      + rank:
 *          + 时间效率：11 ms, 击败 43.95%
 *          + 空间效率：143.32 MB, 击败 84.92%
 * 
 *  + 【思路 2】：bfs
 *      看了 0 ms, 那条柱子; 没能第一时间想起来，留到下次做吧；
 *      从上到下，从做到右，遇到第一个左右节点都没有的节点，即可退出；
 *      ps: 内存循环的退出条件，是当前层的节点数遍历完；
 *          内存循环外，每次来个计数；
 */

#include <iostream>
#include "../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using std::min;

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
public:
    int minDepth(TreeNode* root) {

        if (!root) return 0;
        
        int left_height = minDepth(root->left);
        int right_height = minDepth(root->right);

        return !(left_height && right_height) ? std::max(left_height, right_height) + 1 : std::min(left_height, right_height) + 1;
    }
};