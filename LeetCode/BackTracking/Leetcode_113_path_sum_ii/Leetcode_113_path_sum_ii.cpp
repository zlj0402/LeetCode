/**
 * @brief: Leetcode_113_路径总和_II
 * @link: https://leetcode.cn/problems/path-sum-ii/description/
 * @author: liangj.zhang
 * @date: 24/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Backtracking & Tree
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1 -- 写法1】：回溯，外部变量 -- 普通函数递归
 *      这倒是一次性写对，唯一注意的是：叶子节点时比较值，不能放在递归终止条件进行，会有重复；
 *      + 分析：
 *          + 时间复杂度：节点遍历 O(n) + 每一条路径拷贝 O(H)
 *                       假设最坏情况，每一条路径都需要拷贝，平衡二叉树，H->O(logN), 路径数L -> O(N/2)
 *                       拷贝最坏情况：O(NlogN)
 *          + 空间复杂度：O(H)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：20.41 MB, 击败 96.23%
 * 
 *  + 【思路 1 -- 写法2】：回溯，外部变量 -- lambda 递归函数
 *      错误写法，已经备注在代码旁了；
 *      + 分析：同上
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：20.51 MB, 击败 75.13%
 */

#include"../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using namespace Leetcode::Tree::BinaryTree;

#include <vector>
using std::vector;

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

// 思路1 -- 写法 1
/*
class Solution {
private:
    static vector<vector<int>> ret;
    static vector<int> path;

    void dfs(TreeNode* root, int sum, int targetSum) {

        if (!root) return;

        path.push_back(root->val);

        if (!root->left && !root->right && sum + root->val == targetSum)
            ret.push_back(path);

        dfs(root->left, sum + root->val, targetSum);
        dfs(root->right, sum + root->val, targetSum);

        path.pop_back();
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {

        ret.clear();
        path.clear();
        dfs(root, 0, targetSum);

        return ret;
    }
};

vector<vector<int>> Solution::ret;
vector<int> Solution::path;
*/

// 思路1 -- 写法2
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        
        vector<vector<int>> ret;
        vector<int> path;

        auto dfs = [&](this auto&&dfs, TreeNode* node, int sum) -> void {

            if (!node) return;

            path.push_back(node->val);

            if (!node->left && !node->right && sum + node->val == targetSum)    // 错误写法1：原来这个整体我写在了递归终止条件中了，有一个重复的问题，要是叶子节点满足条件，它的两个左右空节点，都能使得path被记录一次；
                ret.push_back(path);                                            // 错误写法2：提前到这里写，sum 要加上这里的 node->val，虽然 path 加进去了，但是 sum 没有加入值；

            dfs(node->left, sum + node->val);
            dfs(node->right, sum + node->val);

            path.pop_back();
        };

        dfs(root, 0);

        return ret;
    }
};


int main() {

    TreeNode* root = buildTreeFromStringArray("5,4,8,11,null,13,4,7,2,null,null,5,1");

    levelTraverse(root);

    Solution().pathSum(root, 22);
}