/**
 * @brief: Leetcode_1302_层数最深叶子节点的和
 * @link: https://leetcode.cn/problems/deepest-leaves-sum/description/
 * @author: liangj.zhang
 * @date: 6/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：BFS
 *      每一层都计算和，循环结束之后的最后一次 sum，返回就是结果；
 *      ps:
 *      又熟悉一些层序遍历之后，已经写得像 Easy 题的感觉了；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：61.27 MB, 击败 18.26%
 * 
 *  + 【思路 2】：DFS
 *      dfs 的时候，记录最大深度，
 *      最大深度每次切换的时候，重新开始计算和 sum；
 *      小于当前最大深度就不会进行加法 -> 虽然和 BFS 一样时间复杂度都是 O(n)，但是常数小
 *      而且 dfs 递归时的空间复杂度是 O(h)，多数情况，使用的空间是比 BFS 要小的；
 *      ---
 *      下次遇到这题，用 dfs 再写；
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

#include <queue>
using std::queue;

class Solution {
public:
    int deepestLeavesSum(TreeNode* root) {
        
        queue<TreeNode*> q;
        q.push(root);

        int sum;
        while (!q.empty()) {
            
            int size = q.size();
            sum = 0;
            for (int i = 0; i < size; ++i) {

                TreeNode* cur = q.front(); q.pop();
                sum += cur->val;
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
        }

        return sum;
    }
};