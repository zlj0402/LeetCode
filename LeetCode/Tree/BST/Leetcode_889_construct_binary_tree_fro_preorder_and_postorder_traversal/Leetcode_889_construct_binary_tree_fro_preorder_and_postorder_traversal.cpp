/**
 * @brief: Leetcode_889_根据前序和后序遍历构造二叉树
 * @link: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/description/
 * @author: liangj.zhang
 * @date: 23/12/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: BST
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：利用先序遍历和后序遍历的性质
 *      这题和 Leetcode_105/106 是一个性质
 *      稍微不同的点，是知道当前都节点，不能通过当前节点直接知道左右子树的节点数（原来可以在 inorder 中直接得到两边节点数）
 *          现在需要通过子树的根节点，来找到它所在另一个序列的位置，就能知道左右子树的个数情况；（动手走个实例，说的还不是很明了）
 *      但是原理，都是要知道节点两边子树的范围来写；然后递归下去；
 *      边界条件比 105/106 稍微多点；
 *      ---
 *      我还是觉得自己的代码乱了点，让 chat 简洁了下；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：28.11 MB, 击败 48.57%
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

#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using namespace Leetcode::Tree::BinaryTree;

#include <unordered_map>
#define um unordered_map
using std::unordered_map;

// 自己写的
/*
class Solution {
private:
    static um<int, int> rec_post;
    vector<int>* pre;
    vector<int>* post;

    TreeNode* __constructFromPrePost(int lpre, int rpre, int lpost, int rpost) {

        // if (lpre > rpre) return nullptr;

        int root_idx = lpre;
        int root_val = (*pre)[root_idx];
        TreeNode* node = new TreeNode(root_val);

        int left_tree_size{0}, right_tree_size{0};
        int left_node_idx = lpre + 1;

        if (left_node_idx > rpre) node->left = nullptr;
        else {

            int left_node_val = (*pre)[left_node_idx];
            int left_idx = rec_post[left_node_val]; // idx of left_node in postorder
            left_tree_size = left_idx - lpost + 1;  // 包含左子树根节点；
            node->left = __constructFromPrePost(lpre + 1, lpre + left_tree_size, lpost, lpost + left_tree_size - 1);
        }
        right_tree_size = (rpre - lpre) - left_tree_size;

        // int right_node_idx = rpost - 1;
        // if (right_tree_size == 0 || right_node_idx < lpost) node->right = nullptr;
        // // if (right_node_idx < lpost) node->right = nullptr;  // 可能 right_node_idx 和 lpost 为 0, 但是这是属于根节点的
        // else {
        //     node->right = __constructFromPrePost(rpre - right_tree_size + 1, rpre, rpost - right_tree_size, rpost - 1);
        // }
        if (right_tree_size <= 0) node->right = nullptr;  // 可能 right_node_idx 和 lpost 为 0, 但是这是属于根节点的
        else {
            node->right = __constructFromPrePost(rpre - right_tree_size + 1, rpre, rpost - right_tree_size, rpost - 1);
        }

        return node;
    }
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        
        int size = preorder.size();
        rec_post.clear();
        for (int i = 0; i < size; ++i) 
            rec_post[postorder[i]] = i;
            
        pre = &preorder;
        post = &postorder;

        return __constructFromPrePost(0, size - 1, 0, size - 1);
    }
};

um<int, int> Solution::rec_post{};
*/

// chat 简洁下
class Solution {
private:
    unordered_map<int, int> post_idx;
    vector<int>* pre;

    TreeNode* build(int lpre, int rpre, int lpost, int rpost) {
        if (lpre > rpre) return nullptr;

        TreeNode* root = new TreeNode((*pre)[lpre]);
        if (lpre == rpre) return root;

        int left_root_val = (*pre)[lpre + 1];
        int left_size = post_idx[left_root_val] - lpost + 1;

        root->left = build(lpre + 1,
                           lpre + left_size,
                           lpost,
                           lpost + left_size - 1);

        root->right = build(lpre + left_size + 1,
                            rpre,
                            lpost + left_size,
                            rpost - 1);

        return root;
    }

public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int n = preorder.size();
        pre = &preorder;
        post_idx.clear();

        for (int i = 0; i < n; ++i)
            post_idx[postorder[i]] = i;

        return build(0, n - 1, 0, n - 1);
    }
};

int main() {

    vector<int> preorder = {2, 1, 3};
    vector<int> postorder = {3, 1, 2};

    TreeNode* root = Solution().constructFromPrePost(preorder, postorder);
    root->preOrder();
}


