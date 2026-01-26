/**
 * @brief: Leetcode_257_二叉树的所有路径
 * @link: https://leetcode.cn/problems/binary-tree-paths/description/
 * @author: liangj.zhang
 * @date: 22/1/2026
 * 
 * @updated:
 *  + 24/1/2026: add 【思路 1 -- 写法 2】
 * 
 * @Difficulty: Easy
 * 
 * @Label: BackTracking
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1 -- 写法 1】：回溯，路径外部变量 -- 提前在当前节点上一层
 *      当前递归，处理当前节点的左右孩子节点；
 *      ---
 *      还有种写法，是当前递归处理当前节点，上面的做法相当于提前一层；-- 留作写法 2
 * 
 *      + 分析：
 *          + 时间复杂度：最好 O(N)[一条链的时候]，一般情况下 O(N log N)
 *                      + 一般 / 平衡二叉树：H = log N，L ≈ N/2 => O(NlogN)，此处忽略 dfs O(n)
 *                      + 最坏情况（链状树）: H = N, L = 1 => O(N)
 *                      --------
 *                      任意 k_i ≤ H,一共有 L 条路径(k_i 表示第 i 条根到叶路径上的节点数)
 *                      上界可以写成：O(L⋅H)
 *          + 空间复杂度：O(h) -> h 树的高度（没有算结果空间）
 * 
 *      + rank:
 *          + 时间效率：3 ms, 击败 43.46%
 *          + 空间效率：16.65 MB, 击败 87.77%
 * 
 *  + 【思路 1 -- 写法 2】：回溯，路径外变量 -- 当前节点，加入当前节点，不像写法一加入子节点的；
 *      注意事项，处理结束值时，需要提前一下在根节点位置，连接字符串，不能放在递归终止时，  
 *      因为如此，两个空节点都会结算，就会重复；
 * 
 *      + 分析：同【思路 1 -- 写法 1】
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：16.62 MB, 88.89%
 */

#include <vector>
#include <string>

using std::vector;
using std::string;

#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using namespace Leetcode::Tree::BinaryTree;

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
    string func(vector<TreeNode*>& path) {

        string s;
        for (int i = 0; i < path.size(); ++i) {
            s += std::to_string(path[i]->val);
            if (i != path.size() - 1)
                s += string("->");
        }
        return s;
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        
        vector<string> ret;
        vector<TreeNode*> path;

        auto dfs = [&](this auto&& dfs, TreeNode* root) -> void {

            if (!root->left && !root->right) {
                ret.push_back(func(path));
            }

            if (root->left) {

                path.push_back(root->left);
                dfs(root->left);
                path.pop_back();
            }

            if (root->right) {

                path.push_back(root->right);
                dfs(root->right);
                path.pop_back();
            }
        };

        path.push_back(root);
        dfs(root);
        path.pop_back();

        return ret;
    }
};


class Solution {
private:
    string func(vector<TreeNode*>& path) {

        string s;
        for (int i = 0; i < path.size(); ++i) {
            s += std::to_string(path[i]->val);
            if (i != path.size() - 1)
                s += string("->");
        }
        return s;
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
     
        vector<string> ret;
        vector<TreeNode*> path;

        auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {

            if (!node) return;

            path.push_back(node);

            if (!node->left && !node->right) {
                ret.push_back(func(path));
            }

            dfs(node->left);
            dfs(node->right);

            path.pop_back();
        };

        dfs(root);

        return ret;
    }
};