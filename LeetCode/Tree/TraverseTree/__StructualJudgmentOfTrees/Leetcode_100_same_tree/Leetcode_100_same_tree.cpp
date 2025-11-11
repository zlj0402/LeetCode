/**
 * @brief: Leetcode_100_相同的树
 * @link: https://leetcode.cn/problems/same-tree/description/
 * @author: liangj.zhang
 * @date: 11/11/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: Tree(Structual Judgment Of Tress)
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：递归
 *      对方（p）传哪边，我（q）就传哪边，（步调一致），然后函数体内进行比较；
 *      + 分析：
 *          + 时间复杂度：最坏 O(n)，遇到不等的，就一直退出递归；
 *          + 空间复杂度：O(h)，最坏的情况，h 为树的高度
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：12.54 MB, 击败 76.45%
 */

#include "../../../../../Include/Leetcode/Tree/Tree.h"
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
    bool ret;
    void __isSameTree(TreeNode* p, TreeNode* q) {


        if (!p ^ !q) ret = false;   // 一个为空，一个不为空，必定不相同了
        if (ret && (!p || !q)) return;       // 避免有空的情况
        if (ret && p->val != q->val) ret = false;

        if (!ret) return;

        __isSameTree(p->left, q->left);
        __isSameTree(p->right, q->right);
    }
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {

        ret = true;
        __isSameTree(p, q);
        return ret;
    }
};