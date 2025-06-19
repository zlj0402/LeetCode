/**
* @brief: Leetcode_108_将有序数组转换为二叉搜索树
* @link: https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/description
* @author: liangj.zhang
* @date: 19/6/2025
* 
* @Difficulty: Easy
* 
* @Label: BST
* 
* @brief content: 将一个有序数组，转换一个平衡的二叉搜索树
*       + 二叉搜索树：
*           + 节点的左子树只包含 小于 当前节点的数
*           + 节点的右子树只包含 大于 当前节点的数
*           + 所有左子树和右子树自身必须也是二叉搜索树
*       + 平衡的：
*           + 左子树的深度，与右子树的深度，差值小于 1；
* 
* @thought:
*	+ 平衡的二叉树，BST，该树的任意子树，都满足，一个节点的左节点比父节点小，右节点比父节点大；
*	+ 对于一个有序的数组，我们每次插入中间的数值，剩下的两边，也同样每次找中间值进行插入；
*		这样节点两边，左边都是比节点小，右边都是比节点大；任意子树都是如此；
*	
*	跟第一次写的思路，是一摸一样的，只是当时有些借助，刚复习的 BST 结构；重写的这个也上传一次
* 
*	rank:
*		+ 时间效率：0 ms, 击败 100%
*		+ 空间效率：21.37 MB, 击败 99.88%
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

class Solution {

private:
    TreeNode* root;

    TreeNode* __insert(TreeNode* node, TreeNode* newNode) {

        if (!node)
            return newNode;

        if (node->val > newNode->val) {
            node->left = __insert(node->left, newNode);
        }
        else {
            node->right = __insert(node->right, newNode);
        }
        return node;
    }

    void insert(int l, int r, vector<int>& nums) {

        if (l > r)
            return;

        int mid = (l + r) / 2;
        root = __insert(root, new TreeNode(nums[mid]));
        insert(l, mid - 1, nums);
        insert(mid + 1, r, nums);
    }

public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {

        if (nums.size() == 0) return nullptr;

        insert(0, nums.size() - 1, nums);

        return root;
    }
};