/**
 * @brief: Leetcode_2415_反转二叉树的奇数层
 * @link: https://leetcode.cn/problems/reverse-odd-levels-of-binary-tree/description/
 * @author: liangj.zhang
 * @date: 8/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS、DFS
 * 
 * @Retrospect(worthy 1 - 5): 3(BFS) + 3(DFS)
 * 
 * @thoughts:
 *  + 【思路 1】：BFS + vector
 *      这题是完美二叉树，那 DFS 肯定也是能行的；交换节点应该；
 *      最近写 BFS 写惯了，这次就先写 BFS;
 *      ---
 *      交换节点值，并不影响后续的节点记录；
 *      当前层遍历的时候，就像交换翻转一个有序数组就可以了； -- 这题以 vector 方式会方便些；
 *      要交换的对立面 opposite_idx = size - i
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：78.55 MB, 击败 65.81%
 * 
 *  + 【思路 2】：DFS
 *      交换节点，下次做；
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

#include "../../../../../Include/Leetcode/Tree/Tree.h"
using namespace Leetcode::Tree::BinaryTree;
using Leetcode::Tree::BinaryTree::TreeNode;

#include <vector>
using std::vector;

class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        
        vector<TreeNode*> arr{root}, tmp;
        bool even = true;

        while (arr.size()) {

            int size = arr.size();
            tmp.clear();
            for (int i = 0; i < size; ++i) {

                TreeNode* cur = arr[i];
                if (cur->left) tmp.push_back(cur->left);
                if (cur->right) tmp.push_back(cur->right);

                if (!even && i < size / 2) {

                    int op = size - 1 - i;  // oppsite
                    std::swap(cur->val, arr[op]->val);
                }
            }

            arr.swap(tmp);
            even = !even;
        }

        return root;
    }
};