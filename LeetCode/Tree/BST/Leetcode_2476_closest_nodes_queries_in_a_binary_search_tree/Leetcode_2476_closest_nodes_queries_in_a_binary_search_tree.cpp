#include "../../../../Include/Leetcode/Tree/Tree.h"
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

#include <vector>
using std::vector;

class Solution {
private:
    static vector<int> rec;
    static vector<vector<int>> ret;

    // return 第一个 >= target 的位置
    int lower_bound(int target) {

        int l{0}, r(rec.size() - 1);
        while (l <= r) {

            int mid = l + (r - l) / 2;
            if (rec[mid] < target)
                l = mid + 1;
            else
                r = mid - 1;
        }

        return l;
    }

    // return 第一个 > target 的位置
    int upper_bound(int target) {

        int l{0}, r(rec.size() - 1);
        while (l <= r) {
            
            int mid = l + (r - l) / 2;
            if (rec[mid] <= target)
                l = mid + 1;
            else
                r = mid - 1;
        }

        return l;
    }

    void in_order(TreeNode* root) {
        
        if (!root) return;
        in_order(root->left);
        rec.push_back(root->val);
        in_order(root->right);
    }

public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        
        rec.clear();
        ret.clear();
        in_order(root);
        int size = rec.size();
        int lower, upper;

        for (auto e : queries) {

            int l = lower_bound(e);
            lower = (l >= 0 && l < size) ? rec[l] : -1;

            if (lower == e)
                upper = e;
            else {
                int r = l - 1;
                upper = (r >= 0 && r < size) ? rec[r] : -1;
            }
            
            ret.push_back({upper, lower});
        }

        return ret;
    }
};

vector<int> Solution::rec{};
vector<vector<int>> Solution::ret{};