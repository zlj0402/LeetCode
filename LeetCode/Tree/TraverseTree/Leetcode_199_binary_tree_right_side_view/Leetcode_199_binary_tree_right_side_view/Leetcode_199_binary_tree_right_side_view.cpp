/**
 * @brief: Leetcode_199_二叉树右视图
 * @link: https://leetcode.cn/problems/binary-tree-right-side-view/description
 * @author: liangj.zhang
 * @date: 19/6/2025
 *
 * @updated: 
 *   + 14/11/2025: 第二次写，一模一样的写法；
 *   + 3/1/2026：add 【思路 2】：BFS
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
 *   （在向下的过程中，就将深度传递开来； 不采用“回”的时候，将高度返回回来）
 *   
 *   + 分析：
 *       + 时间复杂度：O(n)
 *       + 空间复杂度：O(h), h 为树的高度
 * 
 *	+ rank: 
 *       + 第 1 次写：
 *		    时间效率：0 ms, 击败 100%
 * 		    空间效率：14.52 MB, 击败 97.22%
 *       + 第 2 次写：
 *           时间效率：0 ms, 击败 100%
 *           空间效率：14.46 MB, 击败 99.2%
 * 
 * + 【思路 2】：BFS
 *      BFS 层序遍历，先遍历右边节点，放入子节点时也先放入右节点；
 *      内循环遍历的第一个就是右边看到的该层的第一个节点；
 *      也可以正常的先遍历左节点，放入时也先放入左节点；内循环遍历的最后一个节点，就是该层从右边的第一个节点；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：14.73 MB, 击败 55.15%
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

#include <queue>
using std::queue;

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        
        if (!root) return {};
        queue<TreeNode*> q;
        vector<int> ret;

        q.push(root);
        while (!q.empty()) {

            int size = q.size();
            for (int i = 0; i < size; ++i) {

                TreeNode* cur = q.front(); q.pop();
                if (i == 0) ret.push_back(cur->val);

                if (cur->right) q.push(cur->right);
                if (cur->left) q.push(cur->left);
            }
        }
        return ret;
    }
};

// 第 2 次写：写完发现跟第一次完全一样的写法，不过这次一次就通过了；
class Solution {
private:
    int max_depth;
    static vector<int> rec;
    void __rightSideView(TreeNode* root, int depth) {

        if (!root) return;

        if (max_depth < depth) {
            
            rec.push_back(root->val);
            max_depth = depth;
        }
        __rightSideView(root->right, depth + 1);
        __rightSideView(root->left, depth + 1);
    }

public:
    vector<int> rightSideView(TreeNode* root) {
        
        max_depth = -1;
        rec.clear();
        __rightSideView(root, 0);
        return rec;
    }
};

vector<int> Solution::rec = vector<int>();

// 第 1 次写
/*
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
*/