/**
 * @brief: Leetcode_1080_根到叶路径上的不足节点
 * @link: https://leetcode.cn/problems/insufficient-nodes-in-root-to-leaf-paths/description/
 * @author: liangj.zhang
 * @date: 1/12/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Tree(recursion)
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：递归
 *      nnd, 没有自己写出来；看了灵神的代码；
 *      主要特殊的地方是：如果回退时，回退到的节点两节点都为空，那么这个节点也要删除；
 *      （到叶子结点，要比较一下，
 *          + 能满足条件，肯定会把当前节点return回去，
 *          + 只有没有满足条件的，才会return None，两边都没有，那么肯定是因为路径走到头时，没能满足条件）
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(h)，最坏为 O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：33.65 MB, 击败 91.1%
 */

#include <iostream>
#include "../../../../Include/Leetcode/Tree/Tree.h"
using std::cout;
using std::endl;
using namespace Leetcode::Tree::BinaryTree;
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

public:
    TreeNode* sufficientSubset(TreeNode* root, int left_val) {

        left_val -= root->val;

        if (!root->left && !root->right) return left_val > 0 ? nullptr : root;

        if (root->left) root->left = sufficientSubset(root->left, left_val);
        if (root->right) root->right = sufficientSubset(root->right, left_val);

        return (root->left || root->right) ? root : nullptr;
    }
};

// 原来错误的写法
// class Solution {
// private:
//     int limit;
//     bool __sufficientSubset(TreeNode* parent, bool ln, TreeNode* root, int sum) {

//         // if (!root->left && !root->right) {

//         //     if (sum >= this->limit) return true;
//         //     if (ln) parent->left = nullptr;
//         //     else parent->right = nullptr;
//         //     return false;
//         // }

        
//         if (!root->left && !root->right) return sum >= limit;

//         bool left{false}, right{false};

//         if (root->left) left = __sufficientSubset(root, true, root->left, sum + root->left->val);

//         if (root->right) right = __sufficientSubset(root, false, root->right, sum + root->right->val);

//         // 左子树根节点，右子树根节点，所在路径都没有通关的情况
//         if (!left && !right) {
            
//             if (root->left) parent->left = nullptr;
//             if (root->right) parent->right = nullptr;
//         }

//         return left || right;
//     }

// public:
//     TreeNode* sufficientSubset(TreeNode* root, int limit) {

//         if (!root->left && !root->right && root->val < limit) return nullptr;
        
//         this->limit = limit;
//         __sufficientSubset(nullptr, false, root, root->val);

//         return root;
//     }
// };

int main() {

    string s = "[5,4,8,11,null,17,4,7,1,null,null,5,3]";
    int limit = 22;

    TreeNode* root = buildTree(parseArray(s));

    TreeNode* ret = Solution().sufficientSubset(root, limit);

    cout << levelTraverse(root);
}