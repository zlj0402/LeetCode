/**
 * @brief: Leetcode_513_找树左下角的值
 * @link: https://leetcode.cn/problems/find-bottom-left-tree-value/description/
 * @author: liangj.zhang
 * @date: 31/12/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：BFS，记录每一层第一个值；
 *      推出循环时的那个记录值就是结果；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(1)，但我申请这么大数组，其实也是 O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：24.22 MB, 击败 87.23%
 * 
 *  + 【思路 2】：DFS，记录最大深度变化时的那个值；
 *      DFS 理论上可以比 BFS 更先找到结果，但是递归有额外消耗；
 *      留着以后做吧；
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

class Solution {
private:
    static constexpr int MAXSIZE = 10001;
    static TreeNode* arr[MAXSIZE];
    int front, rear;
public:
    Solution() : front(0), rear(0) {}
    int findBottomLeftValue(TreeNode* root) {
        
        int ret;
        arr[rear++] = root;
        while (front < rear) {

            ret = arr[front]->val;
            int last_rear = rear;
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