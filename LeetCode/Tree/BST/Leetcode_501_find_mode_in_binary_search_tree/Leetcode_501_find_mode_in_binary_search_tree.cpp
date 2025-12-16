/**
 * @brief: Leetcode_501_二叉搜索树中的众数
 * @link: https://leetcode.cn/problems/find-mode-in-binary-search-tree/description/
 * @author: liangj.zhang
 * @date: 16/12/2025
 * 
 * @Difficulty: Easy
 * 
 * @Label: BST
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：BST
 *      update 的时机，是当前遍历值 root->val 与 last 不一样时；
 *          + 为此，先让 last 赋值为 BST 中的第一个值：findBSTFirstNode 【不同做法，可能不需要这样】
 *      中规中矩的 inOrder 遍历，做一次 update 或者 更新一下 last、cur_cnt;
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：最坏 O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：23.66 MB, 击败 87.96%
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

class Solution {
private:
    int last;
    int max_cnt;
    int cur_cnt;
    vector<int> max_num;

    TreeNode* findBSTFirstNode(TreeNode* root) {

        if (!root) return nullptr;
        TreeNode* ret = findBSTFirstNode(root->left);
        return ret ? ret : root;
    }

    inline void update() {

        if (max_cnt <= cur_cnt) {

            if (max_cnt < cur_cnt) {
                
                max_num.clear();
                max_cnt = cur_cnt;
            }
            max_num.push_back(last);
        }
        cur_cnt = 0;
    }

    void __findMode(TreeNode* root) {

        if (!root) return;

        __findMode(root->left);

        if (root->val != last)
            update();
        
        ++cur_cnt;
        last = root->val;

        __findMode(root->right);
    }

public:
    vector<int> findMode(TreeNode* root) {
        
        last = findBSTFirstNode(root)->val;
        max_cnt = -1;
        cur_cnt = 0;
        // max_num.clear(); // 这里可以不用 clear()

        __findMode(root);
        update();  // 遍历结束，还需要记录最后一个遍历的数值；

        return max_num;
    }
};