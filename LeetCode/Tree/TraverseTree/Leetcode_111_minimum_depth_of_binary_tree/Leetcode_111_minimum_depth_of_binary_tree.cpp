/**
 * @brief: Leetcode_111_二叉树的最小深度
 * @link: https://leetcode.cn/problems/minimum-depth-of-binary-tree/description/
 * @author: liangj.zhang
 * @date: 4/11/2025
 * 
 * @updated:
 *  + 1/1/2026: add 【思路 2 -- 写法 1】：bfs，vector<> 数组
 *  + 1/1/2026: add 【思路 2 -- 写法 2】：queue; chat 给的，我觉得很好，留下来，之后可以学习学习；
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
 *  + 【思路 2】：bfs -- 2026.1.1
 *      @again: [ ]
 *      看了 0 ms, 那条柱子; 没能第一时间想起来，留到下次做吧；
 *      从上到下，从做到右，遇到第一个左右节点都没有的节点，即可退出；
 *      ps: 内存循环的退出条件，是当前层的节点数遍历完；
 *          内存循环外，每次来个计数；
 * 
 *      ----
 *      下面两种写法的主要思路都是一样的，遇到第一个叶子节点，那它就反映了最低（小）的深度；
 * 
 *      + 【写法 1】：vector<> 数组
 *         + 分析：
 *              + 时间复杂度：O(n)
 *              + 空间复杂度：O(1)
 *         + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：143.33 MB, 击败 80.67%
 *      + 【写法 2】：queue，chat 给的，留下来学习学习；
 *          + 分析同上：
 *          + rank:
 *              + 时间效率：0 ms, 击败 100%
 *              + 空间效率：143.37, 击败 70.57%
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

// 【思路 2 -- 写法 1】：bfs，vector<> 数组
class Solution {
public:
    int minDepth(TreeNode* root) {
        
        if (!root) return 0;
        int ret = 0;

        vector<TreeNode*> arr, tmp;

        arr.push_back(root);
        while (arr.size()) {

            ++ret;
            tmp.clear();
            for (TreeNode* cur : arr) {

                if (cur->left) tmp.push_back(cur->left);
                if (cur->right) tmp.push_back(cur->right);

                if (!cur->left && !cur->right) return ret;
            }

            arr.swap(tmp);  // 交换了两人的资源，这样省了拷贝；
        }

        return ret;
    }
};

// 【思路 2 -- 写法 2】：queue; chat 给的，我觉得很好，留下来，之后可以学习学习；
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;

        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;

        while (!q.empty()) {
            ++depth;
            int sz = q.size();

            for (int i = 0; i < sz; ++i) {
                TreeNode* cur = q.front();
                q.pop();

                if (!cur->left && !cur->right)
                    return depth;

                if (cur->left)  q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
        }
        return depth;
    }
};


// 【思路 1】：递归
/*
class Solution {

public:
    int minDepth(TreeNode* root) {

        if (!root) return 0;
        
        int left_height = minDepth(root->left);
        int right_height = minDepth(root->right);

        return !(left_height && right_height) ? std::max(left_height, right_height) + 1 : std::min(left_height, right_height) + 1;
    }
};
*/