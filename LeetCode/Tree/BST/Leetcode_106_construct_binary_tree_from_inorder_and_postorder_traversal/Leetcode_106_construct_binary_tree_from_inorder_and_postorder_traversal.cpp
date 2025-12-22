/**
 * @brief: Leetcode_106_从中序与后序遍历序列构造二叉树
 * @link: https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/
 * @author: liangj.zhang
 * @date: 22/12/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: BST
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：利用 BST 的中序遍历和后序遍历性质
 *      好在前面先写过 Leetcode_105, 通过 先序和中序 恢复一颗二叉树；
 *      明白 Leetcode_105 的原理，这里就是同样的做法；
 *      + 相同点：
 *          我们还是需要从头结点开始；
 *          从下往上，无法判断左右子树的个数，以及当前树，是作为上一层的右子树，还是左子树
 *      + 不同点：
 *          就是由相同点造成，我们需要从后往前遍历 postorder，
 *          这样看，就是一个先序遍历，再是右子树，再到左子树
 *      立马 Leetcode_105 的感觉就来了；
 *  
 *      写 Leetcode_105 的时候就有点不够熟悉，但好歹知道了原理；今天是对着 Leetcode_105 写的；
 *      明天不对着，用 python 写；
 * 
 *      + 分析：
 *          + 时间复杂度：遍历记录 inorder -> O(n)，递归每个节点作为他们当前的根 -> O(n)
 *          + 空间复杂度：记录 inorder 数值和下标 -> O(n)
 * 
 *      + rank：
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：26.80 MB, 击败 74.58%
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

class Solution {
private:
    static um<int, int> rec;
    vector<int>* post;

    TreeNode* __buildTree(int pl, int pr, int il, int ir) {

        if (pl > pr) return nullptr;

        int root_idx = pr;
        int root_val = (*post)[root_idx];
        int in_idx = rec[root_val];

        int right_tree_size = ir - in_idx;

        TreeNode* node = new TreeNode(root_val);
        node->right = __buildTree(pr - right_tree_size, pr - 1, in_idx + 1, ir);
        node->left = __buildTree(pl, pr - right_tree_size - 1, il, in_idx - 1);

        return node;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        
        rec.clear();
        for (int i = 0; i < inorder.size(); ++i)
            rec[inorder[i]] = i;

        post = &postorder;

        return __buildTree(0, postorder.size() - 1, 0, inorder.size() - 1);
    }
};

um<int, int> Solution::rec{};

int main() {

    vector<int> inorder = {9,3,15,20,7};
    vector<int> postorder = {9,15,7,20,3};
    Solution().buildTree(inorder, postorder);
}