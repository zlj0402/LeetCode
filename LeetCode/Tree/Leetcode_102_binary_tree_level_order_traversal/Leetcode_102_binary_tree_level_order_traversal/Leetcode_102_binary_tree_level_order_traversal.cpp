/**
* @brief: Leetcode_102_二叉树的层序遍历
* @link: https://leetcode.cn/problems/binary-tree-level-order-traversal/description
* @author: liangj.zhang
* @date: 18/6/2025
* 
* @Difficulty: Medium
* 
* @Label: Binary Tree、BFS
* 
* @brief content: 一层一层的遍历二叉树
* 
* @thoughts:
*  [1]
*   思路很清晰，用自己实现的队列，或者 STL 的 queue，来遍历；
*   三星的 Adventure 和 Professional 级别的考试，是一个常考类型，BFS 和 DFS 的过程，还是烙印在心里，虽然很久没有手写实现一个；这遍还是想熟悉 STL 库的使用，以后再手写吧；
*   难点，在于怎么分层；好在以前在 Pro 的考试之后，写过几题，体会过过程；
*   队列中，前后两个指针 front & rear，
*       + 有新的子元素加进来，用一个 cnt 计数，当前层节点遍历时，加入了多少下一层的元素；
*       + >>> 然后让 rear 在与 front 相遇之后，一次性指向下一层新元素的尾部；<<<
*       + 如果让 rear 来一个就往后移一位，那么 front 与 rear 值恒等相遇，只能在遍历完一遍树之后；
*   这次，是用的 queue，front 与 rear 只是一种伪标记了，没有真实的管理哪一部分是有效的节点；
*   只有理解了过程原理，才能实现的如此容易，一次就成功了；
*   下一次用手写堆；
*   
*   rank:
*       + 时间效率：0 ms, 击败 100%
*       + 空间效率：16.76 MB, 击败 63.34%
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

#include "Leetcode/Tree/Tree.h"
#include <vector>
using std::vector;
using Leetcode::Tree::BinaryTree::TreeNode;

#include <queue>
using std::queue;

// 【1】
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {

        if (!root) return {};

        queue<TreeNode*> q;
        int front, rear;
        front = rear = 0;

        q.push(root);
        ++rear;
        vector<vector<int>> ret;
        vector<int> tmp;
        
        int cnt = 0;
        while (!q.empty()) {

            TreeNode* cur = q.front(); q.pop();
            ++front;

            if (cur->left) { q.push(cur->left); ++cnt; }
            if (cur->right) { q.push(cur->right); ++cnt; }

            tmp.push_back(cur->val);
            if (front == rear) {

                ret.push_back(tmp);
                tmp.clear();
                rear += cnt;
                cnt = 0;
            }
        }

        return ret;
    }
};