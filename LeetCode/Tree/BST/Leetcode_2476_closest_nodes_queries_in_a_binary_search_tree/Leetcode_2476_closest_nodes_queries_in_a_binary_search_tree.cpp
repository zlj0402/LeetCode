/**
 * @brief: Leetcode_2476_二叉搜索树最近节点查询
 * @link: https://leetcode.cn/problems/closest-nodes-queries-in-a-binary-search-tree/description/
 * @author: liangj.zhang
 * @date: 15/12/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: binary search & BST
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：Binary Search + BST
 *      先 inOrder 的方式遍历一下搜索二叉树（BST），得到一个升序的序列
 *      题目要求得到，<= target 的最大值，和 >= target 的最小值；
 *      + >= target 的最小值 -> 即 lower_bound
 *      + <= target, 有了 lower_bound 返回的位置 pos，pos - 1 就是该答案；
 *      
 *      + 分析：
 *          + 时间复杂度：inOrder(O(n)) + q * O(logn)
 *          + 空间复杂度：inOrder(O(n)) 没说平衡二叉树 + 2 * O(q)
 * 
 *      + rank: 
 *          + 写法 1：
 *              + 时间效率：107 ms, 击败 21.63%
 *              + 空间效率：194.14 MB, 击败 17.29%
 *          + 写法 2：
 *              + 时间效率：55 ms, 击败 99.49%
 *              + 空间效率：186.51 MB, 击败 83.97%
 */

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

// 【思路 1 -- 写法 2】
class Solution {
private:
    static vector<int> rec;

    void in_order(TreeNode* root) {
        
        if (!root) return;
        in_order(root->left);
        rec.push_back(root->val);
        in_order(root->right);
    }

public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        
        rec.clear();
        in_order(root);
        int size = rec.size();
        int lower, upper;
        vector<vector<int>> ret{};

        for (auto e : queries) {

            int l{0}, r{size - 1};
            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (rec[mid] < e)
                    l = mid + 1;
                else
                    r = mid - 1;
            }
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

// 【思路 1 -- 写法 1】
/*
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
*/
vector<int> Solution::rec{};
vector<vector<int>> Solution::ret{};