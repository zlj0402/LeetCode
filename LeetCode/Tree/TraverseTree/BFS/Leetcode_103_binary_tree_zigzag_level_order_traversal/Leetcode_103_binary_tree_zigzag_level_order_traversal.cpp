/**
 * @brief: Leetcode_103_二叉树的锯齿形层序遍历
 * @link: https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/description/
 * @author: liangj.zhang
 * @date: 30/12/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：BFS, 理清过程；
 *      还是不要按着题目的要求的顺序，给节点赋值，来举例子，给我弄晕了；
 *      难度还是中等，就是理清的过程有点绕；
 *      例子：
 *                  3
 *                 / \
 *                9   20
 *               / \  / \
 *              1  2 15  7
 *             /\ /\  /\  /\
 *           13 9 5 1 7 2 4 8
 * 
 *      3
 *      |   // 顺存
 *      9, 20                       // 先 20，后 9
 *      |   // 倒存
 *      7, 15, 2, 1                 // 先 1，后 7
 *      |   // 顺存
 *      13, 9, 5, 1, 7, 2, 4, 8     // 先 13，后 8
 *      
 *      这种方式：每次倒着遍历，顺着存；（那应该有完全对立的另一种解题方式）
 *      ，还有只改变节点在 arr[] 中位置的方式；就是比较绕；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间负载的：虽是固定大小，其实也是 O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：14.65 MB, 击败 91.73%
 */

#include "../../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using namespace Leetcode::Tree::BinaryTree;
#include <vector>
using std::vector;

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
    static constexpr int MAXSIZE = 2001;
    static TreeNode* arr[MAXSIZE];
    int front, rear;
    bool reverse;

    void reverse_trav_xxx_save(vector<int>& tmp, bool sequence_save) {

        int last_rear{rear}, last_front{front};
        front = rear;
        while (--last_rear >= last_front) {

            TreeNode* cur = arr[last_rear];
            tmp.emplace_back(cur->val);

            if (sequence_save) {

                if (cur->left) arr[rear++] = cur->left;
                if (cur->right) arr[rear++] = cur->right;
            }
            else {
                
                if (cur->right) arr[rear++] = cur->right;
                if (cur->left) arr[rear++] = cur->left;
            }
        }
    }

public:
    Solution() : front(0), rear(0), reverse(false) {}
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        
        if (!root) return {};

        vector<vector<int>> ret;
        arr[rear++] = root;
        while (front < rear) {

            vector<int> tmp;
            tmp.reserve(2 * (rear - front));
            reverse_trav_xxx_save(tmp, (reverse = !reverse));
            
            ret.push_back(std::move(tmp));
        }

        return ret;
    }
};

TreeNode* Solution::arr[MAXSIZE]{};

int main() {

    TreeNode* root = buildTreeFromStringArray("[3,9,20,null,null,15,7]");
    Solution().zigzagLevelOrder(root);
}