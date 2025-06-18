/**
* @brief: Leetcode_543_二叉树的直径
* @link: https://leetcode.cn/problems/diameter-of-binary-tree/description
* @author: liangj.zhang
* @date: 18/6/2025
* 
* @Difficulty: Easy
* 
* @Label: Binary Tree
* 
* @concept:
*   + 树的直径：二叉树直径长度 = 树中任意两结点最短路径的最大值
*       + 树结构中，两个节点之间的路径是唯一，是最短的
*       + 直径，求得是，所有子节点对，最长的那个；
* 
* @brief content: 找出二叉树中，左右子树的深度和的最大值（求出长度即可）（也即叶子结点之间的最大距离）；
* 
* @thoughts:
*  【1】递归 -- 看了题解之后写的
*   问题拆分：
*       + 如何找出两个叶子结点之间的最短路径长度；（肯定是叶子之间，才具有更长的可能，可以上假设如果取叶子结点的父节点，是不是可以再往下）
*           + 两个叶子之间的路径 = 该两节点公有的最早的 根节点左右儿子的深度之和
*       + 找出最长路径；
*           + 递归的时候，设置 max_depth 变量与 返回的左右子树的深度之和；
* 
*   rank:
*       + 时间效率：0 ms, 击败 100%
*       + 空间效率：23.07 MB, 击败 97.76%
*/



#include "Leetcode/Tree/Tree.h"
#include <vector>
using std::max;
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
    int max_root;

    int depth(TreeNode* node) {

        if (!node)
            return 0;

        int R = depth(node->right);
        int L = depth(node->left);

        if (max_root < L + R)
            max_root = L + R;

        return max(L, R) + 1;
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {

        max_root = 0;
        depth(root);

        return max_root;
    }
};
