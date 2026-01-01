/**
 * @brief: Leetcode_107_二叉树的层序遍历_II
 * @link: https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/description/
 * @author: liangj.zhang
 * @date: 1/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS
 * 
 * @Retrospect(worthy 1 - 5): 3
 * 
 * @thoughts:
 *  + 【思路 1】：正常的从上到下的 BFS；最后将答案反转一下；
 *      这题新 get 反转的技巧，不用像下面的方式进行，新构造一个对象：
 *          vector<vector<int>>(ret.begin(), ret.end());
 *      直接使用 <algorithm> 当中的 reverse() 翻转方法，link: https://en.cppreference.com/w/cpp/algorithm/reverse.html
 *          reverse(ret.begin(), ret.end());
 *      ----
 *      跟 Leetcode_102 几乎一样，只是反转结果；
 *      理论上也没有从底下往上遍历的可能，BFS 能正常进行，是因为父节点，能找到子节点；
 *      但是反过来，子节点是没有办法知道它的父节点是谁，因为这点，就断绝了层序遍历的可能；
 *      其他方式如果能实现，那也绝对不是真正的层序遍历；
 * 
 *      + 分析：
 *          + 时间复杂度：BFS -> O(n), 反转结果 ret [vector<vector<int>>] -> O(h/2), h 是树的高度(h 肯定是小于 n 的) => O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：15.46 MB, 击败 92.86%
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

#include <vector>
#include <algorithm>
using std::vector;

class Solution {
private:
    static constexpr int MAXSIZE = 2001;
    static TreeNode* arr[MAXSIZE];
    
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {

        if (!root) return {};
        
        int front = 0, rear = 0;
        vector<vector<int>> ret;

        arr[rear++] = root;
        while (front < rear) {

            vector<int> tmp;
            tmp.reserve(2 * (rear - front));    // 一次性分配至少能容纳 2 * (rear - front) 个元素的空间 => 减少从 0 个元素开始存储导致的扩容；
            int last_rear = rear;

            while (front < last_rear) {

                TreeNode* cur = arr[front++];
                tmp.push_back(cur->val);
                if (cur->left) { arr[rear++] = cur->left; }
                if (cur->right) { arr[rear++] = cur->right; }
            }

            ret.push_back(std::move(tmp));  // 把 tmp 内部持有的资源（主要是那块堆内存）“转移”给 ret 里的元素，而不是拷贝一份。
        }

        reverse(ret.begin(), ret.end());
        return ret;
        // return vector<vector<int>>(ret.rbegin(), ret.rend());
    }
};

TreeNode* Solution::arr[MAXSIZE]{};