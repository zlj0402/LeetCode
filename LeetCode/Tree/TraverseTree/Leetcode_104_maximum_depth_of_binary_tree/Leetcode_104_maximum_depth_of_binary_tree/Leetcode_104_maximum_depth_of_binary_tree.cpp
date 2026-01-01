// 
// Created by liangj.zhang 2/11/2024
//

// Q: https://leetcode.cn/problems/maximum-depth-of-binary-tree/description
//
// type: traverse binary tree
//
// thought: 递归遍历

// 【写法 1】rank:
// 时间0ms,击败100%
// 内存17.32MB,击败69.9%

/**
 * @brief: Leetcode_104_二叉树的最大深度
 * @link: https://leetcode.cn/problems/maximum-depth-of-binary-tree/description/
 * @author: liangj.zhang
 * @date: 3/11/2025
 * 
 * @updated:
 *  + 1/1/2026: add 【写法 3】：BFS
 * 
 * @Difficulty: Easy
 * 
 * @Label: Tree
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【写法 1】：以前的写法，见上方；
 *  
 *  + 【写法 2】：递归返回时，比较左右子树高度；向上得到最大深度
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(h), h 为树的高度；最坏：O(n)，平均：O(log n)。
 *          + ps: 【写法 1】的复杂度分析是一样的
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：18.55 MB, 击败 90.33%
 * 
 *  + 【写法 3】：BFS
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：18.67 MB, 击败 55.57%
 */

// #include "Leetcode/Tree/Tree.h"
// using namespace Leetcode::Tree::BinaryTree;
#include <iostream>
#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using std::max;

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

// 【写法 3】：BFS -- 2026.1.1
class Solution {
private:
    static constexpr int MAXSIZE = 10001;
    static TreeNode* arr[MAXSIZE];
    
public:
    int maxDepth(TreeNode* root) {
        
        if (!root) return 0;

        int front{0}, rear{0};
        arr[rear++] = root;
        int ret = 0;

        while (front < rear) {

            int last_rear = rear;
            ++ret;
            while (front < last_rear) {

                TreeNode* cur = arr[front++];
                if (cur->left) arr[rear++] = cur->left;
                if (cur->right) arr[rear++] = cur->right;
            }
        }

        return ret;
    }
};

TreeNode* Solution::arr[MAXSIZE]{};

// 写法2：递归返回时，比较左右子树高度；向上得到最大深度
class Solution {
public:
    int maxDepth(TreeNode* root) {
        
        if (!root) return 0;
        int left_height = maxDepth(root->left);
        int right_height = maxDepth(root->right);

        return max(left_height, right_height) + 1;
    }
};

// 写法1：递归时，传递深度；向下得到最大深度
class Solution {
private:
    int max_depth;
    void traverseBinaryTree(TreeNode* node, int depth) {
        if (node == nullptr)
            return;
        if (max_depth < depth) max_depth = depth;
        traverseBinaryTree(node->left, depth + 1);
        traverseBinaryTree(node->right, depth + 1);
    }

public:
    int maxDepth(TreeNode* root) {
        max_depth = 0;
        traverseBinaryTree(root, 1);
        return max_depth;
    }
};