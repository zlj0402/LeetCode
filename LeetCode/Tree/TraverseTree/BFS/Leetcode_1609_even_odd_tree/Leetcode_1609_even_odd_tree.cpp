/**
 * @brief: Leetcode_1609_奇偶树
 * @link: https://leetcode.cn/problems/even-odd-tree/description/
 * @author: liangj.zhang
 * @date: 7/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS + vector/queue
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1 -- 写法 1.1】：BFS + vector：tmp/next 放在内循环
 *     相比 【思路 1 -- 写法 1.2】，放在内部循环，每次构造/析构造成的损耗是最主要的；
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：27 ms, 击败 16.78%
 *          + 空间效率：154.43 MB, 击败 21.48%
 * 
 *  + 【思路 1 -- 写法 1.2】：BFS + vector: tmp/next 放在外循环
 *      减少了内部的 vector 的构造和析构
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：148.23 MB, 击败 96.98%
 * 
 *  + 【思路 1 -- 写法 2】：BFS + queue
 *      相比 vector，遍历过程的常数略大，pop();
 *      空间在过程可能不停有扩容缩容，vector 扩容之后能复用；
 *      + 分析：
 *          + 时间复杂度：0 ms, 击败 100%
 *          + 空间复杂度：150.29% MB, 击败 35.91%
 */

#include "../../../../../Include/Leetcode/Tree/Tree.h"
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

#include <vector>
using std::vector;

// 【思路 1 -- 写法1.1】：BFS + vector
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        vector<TreeNode*> cur{root};
        int level = 0;
        bool even = true;

        while (!cur.empty()) {
            vector<TreeNode*> next; // 每次循环构造/析构很耗时 -> 这是跟 1.2 的主要区别；
            next.reserve(cur.size() * 2);

            int prev = even ? INT_MIN : INT_MAX;

            for (TreeNode* node : cur) {

                int v = node->val;

                if (even) {
                    if (v % 2 == 0 || v <= prev)
                        return false;
                }
                else {
                    if (v % 2 == 1 || v >= prev)
                        return false;
                }
                prev = v;

                if (node->left)  next.push_back(node->left);
                if (node->right) next.push_back(node->right);
            }

            cur.swap(next);
            ++level;
            even = !even;
        }
        return true;
    }
};

// 【思路 1 -- 写法1.2】：BFS + vector
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        vector<TreeNode*> cur{root}, next;
        int level = 0;
        bool even = true;

        while (!cur.empty()) {

            next.clear();
            int prev = even ? INT_MIN : INT_MAX;

            for (TreeNode* node : cur) {

                int v = node->val;

                if (even) {
                    if (v % 2 == 0 || v <= prev)
                        return false;
                }
                else {
                    if (v % 2 == 1 || v >= prev)
                        return false;
                }
                prev = v;

                if (node->left)  next.push_back(node->left);
                if (node->right) next.push_back(node->right);
            }

            cur.swap(next);
            ++level;
            even = !even;
        }
        return true;
    }
};

// 【思路 1 -- 写法2】：BFS + queue
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {

        queue<TreeNode*> q; q.push(root);
        int level = 0;
        bool even = true;

        while (!q.empty()) {

            size_t size = q.size();

            int prev = even ? INT_MIN : INT_MAX;

            for (int i = 0; i < size; ++i) {

                TreeNode* cur = q.front(); q.pop();
                int v = cur->val;

                if (even) {
                    if (v % 2 == 0 || v <= prev)
                        return false;
                }
                else {
                    if (v % 2 == 1 || v >= prev)
                        return false;
                }
                prev = v;

                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }

            ++level;
            even = !even;
        }
        return true;
    }
};


int main() {

    TreeNode* root = buildTreeFromStringArray("[1,10,4,3,null,7,9,12,8,6,null,null,2]");
    cout << levelTraverse(root) << endl;
    cout << Solution().isEvenOddTree(root);
}