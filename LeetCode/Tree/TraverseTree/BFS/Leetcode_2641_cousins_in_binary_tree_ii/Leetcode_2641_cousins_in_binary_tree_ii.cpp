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
        
        vector<tuple<TreeNode*, bool, TreeNode*>> arr, tmp;
        int sum;

        while (arr.size()) {

            int size = arr.size();
            sum = 0;
            for (int i = 0; i < size; ++i) 
                sum += std::get<0>(arr[i])->val;
                
            for (int i = 0; i < size; ++i) {

                auto [cur, left, parent] = arr[i];
                if (cur->left) tmp.push_back({cur->left, true, cur});
                if (cur->right) tmp.push_back({cur->right, false, cur});

                if (left && i + 1 < size) {

                    auto [next, right, nparent] = arr[i + 1];
                    if (left == !right && nparent == parent) {

                        cur->val = sum - ();
                    }
                }
            }
        }
    }
};