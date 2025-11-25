/**
 * @brief: Leetcode_1372_二叉树中的最长交错路径
 * @link: https://leetcode.cn/problems/longest-zigzag-path-in-a-binary-tree/description/
 * @author: liangj.zhang
 * @date: 25/11/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Tree(dfs)
 * 
 * @thoughts:
 *  + 【思路 1】：递归 & 剪枝
 *      遍历每个节点，拿这个节点，当新的一次 root 节点，进行题目中的那总交错版的 dfs 遍历；
 *      维护一个 set，因为一个节点的左右子树最多只会被走一遍，如果后续还有要走这个节点的，必定是重复的，我们通过 set 判断进行跳过；
 *      
 *      + 分析：
 *          + 时间复杂度：遍历 n 个节点 → O(n)，dfs 链访问总共 ≤2n  → O(n)，unordered_set 操作  → O(1) 均摊 ==> O(n)
 *          + 空间复杂度：两个 set ==> O(n)
 *      + rank:
 *          + 时间效率：151 ms, 击败 100%
 *          + 空间效率：141.98 MB, 击败 5.07%
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

#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;

#include <unordered_set>
using std::unordered_set;
#define us unordered_set

class Solution {
private:
    int _max;
    static us<TreeNode*> left_kink;
    static us<TreeNode*> right_kink;

    void dfs(TreeNode* root, bool left, int depth) {

        if (!root) return;

        if (depth > this->_max) this->_max = depth;

        // if (left) {

        //     left_kink.emplace(root->left);   // root 是 left_kink，下一个 root->left 应该放到 right_kink 当中，作为 右转折点；（这个出错原因，想了半天...
        //     dfs(root->left, false, depth + 1);
        // }
        // else {

        //     right_kink.emplace(root->right);
        //     dfs(root->right, true, depth + 1);
        // }
        if (left) {

            left_kink.emplace(root);
            dfs(root->left, false, depth + 1);
        }
        else {

            right_kink.emplace(root);
            dfs(root->right, true, depth + 1);
        }
    }

    // traverse
    void __longestZigZag(TreeNode* root) {
        
        if (!root) return;

        // root 有没有当过左转折点？没有 -> 进去当一回
        if (left_kink.find(root) == left_kink.end()) {

            //left_kink.emplace(root);
            dfs(root, true, 0);
        }

        // root 有没有当过右转折点？没有 -> 进去当一回
        if (right_kink.find(root) == right_kink.end()) {

            //right_kink.emplace(root);
            dfs(root, false, 0);
        }

        __longestZigZag(root->left);
        __longestZigZag(root->right);
    }

public:
    int longestZigZag(TreeNode* root) {

        left_kink.clear();
        right_kink.clear();
        this->_max = 0;

        __longestZigZag(root);

        return this->_max;
    }
};

us<TreeNode*> Solution::left_kink{};
us<TreeNode*> Solution::right_kink{};