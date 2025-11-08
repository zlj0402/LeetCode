/**
 * @brief: Leetcode_1448_统计二叉树中好节点的数目
 * @link: https://leetcode.cn/problems/count-good-nodes-in-binary-tree/description/
 * @author: liangj.zhang
 * @date: 8/11/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Tree(Traverse)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：递归（dfs）
 *      这题用正常的 bfs 是不适合的，节点加入队列中，节点与其父节点的关系无法追溯，来进行比较大小；
 *      递归，能很好的将 pre_max 的关系传递下去；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(h), h 为树的高度
 * 
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：86.43 MB, 击败 52.23%
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
    int cnt;
    void __goodNodes(TreeNode* root, int pre_max) {

        if (!root) return;

        // 原来错误的写法 1：pre_max 更改的时机弄错了
        // if (root->val >= pre_max)
        //     ++this->cnt;
        // else
        //     pre_max = root->val;

        if (root->val >= pre_max) {
            
            ++this->cnt;
            if (root->val > pre_max) pre_max = root->val;
        }

        __goodNodes(root->left, pre_max);
        __goodNodes(root->right, pre_max);
    }
public:
    int goodNodes(TreeNode* root) {
     
        this->cnt = 0;
        __goodNodes(root, root->val);
        return this->cnt;
    }
};