/**
 * @brief: Leetcode_2641_二叉树的堂兄弟节点_II
 * @link: https://leetcode.cn/problems/cousins-in-binary-tree-ii/description/
 * @author: liangj.zhang
 * @date: 11/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：BFS + vector
 *      存入一个节点时，就把该节点的孩子节点和传下去；
 *      同时在这个过程，也能算出下一层的总和； => 不用在下一层节点遍历时，额外遍历一遍；
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：7 ms, 击败 96.95%
 *          + 空间效率：294.92 MB, 击败 99.49%
 */

#include "../../../../../Include/Leetcode/Tree/Tree.h"
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

#include <tuple>
using std::tuple;

class Solution {
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        
        vector<tuple<TreeNode*, int>> arr{{root, root->val}}, tmp;  // 这里 root->val 表示，兄弟节点之和；
        int last_sum = root->val;   // 假定上一层之和；

        while (arr.size()) {

            int new_sum = 0;
            tmp.clear();    // 原来错误的写法，忘记这里的 clear() 
            for (auto [cur, sub_sum] : arr) {

                int _sum = (cur->left ? cur->left->val : 0) + 
                                    (cur->right ? cur->right->val : 0);
                if (cur->left) tmp.push_back({cur->left, _sum});
                if (cur->right) tmp.push_back({cur->right, _sum});
                cur->val = last_sum - sub_sum;
                new_sum += _sum;
            }
            arr.swap(tmp);
            last_sum = new_sum;
        }

        return root;
    }
};

int main() {

    TreeNode* root = buildTreeFromStringArray("[5,4,9,1,10,null,7]");
    TreeNode* res = Solution().replaceValueInTree(root);
    levelTraverse(res);
}