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
private:
    int limit;
    bool __sufficientSubset(TreeNode* parent, bool ln, TreeNode* root, int sum) {

        if (!root && parent) return !parent->left && !parent->right ? sum >= this->limit : false;   // parent 是子节点时，结算 sum；&& parent -> 排除根节点

        bool left = __sufficientSubset(root, true, root->left, sum + root->val);
        bool right = __sufficientSubset(root, false, root->right, sum + root->val);

        // if (!(left || right)) {

        //     if (ln)
        //         parent->left = nullptr;
        //     else
        //         parent->right = nullptr;
        // }

        if (!(left || right)) {

            root->left = nullptr;
            root->right = nullptr;
        }

        return left || right;
    }

public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {

        if (!root->left && !root->right && root->val < limit) return nullptr;
        
        this->limit = limit;
        __sufficientSubset(nullptr, false, root, 0);

        return root;
    }
};

int main() {

    string s = "1,2,-3,-5,null,4,null";
    int limit = -1;

    TreeNode* root = buildTree(parseArray(s));

    TreeNode* ret = Solution().sufficientSubset(root, limit);

    cout << levelTraverse(root);
}