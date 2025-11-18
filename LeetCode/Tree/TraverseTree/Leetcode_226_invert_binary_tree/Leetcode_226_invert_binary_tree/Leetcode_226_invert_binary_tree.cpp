/**
* @brief: Leetcode_226_翻转二叉树
* @link: https://leetcode.cn/problems/invert-binary-tree/description
* @author: liangj.zhang
* @date: 18/6/2025
*
* @updated:
*   + 18/11/2025: add recursion way 【3】
* 
* @thoughts:
* 
* 【1】
*   一开始，是想着树应该是对称的，应该交换值就行了；
*   发现有不是对称的，[1, 2] 两节点输入；
* 
* 【2】-- 迭代遍历
*   上面是用了两个栈，左边是 pop 的时候，把左边节点的 left 和 right 先加入到栈中；（先右后左，stack.pop 的时候，左节点先出）
*                   右边 pop 的时候，把右边节点的 left 和 right 加入到栈中；（先左后右，stack.pop 的时候，右节点先出）
*   上面也紧接着发现，可能树，只有一个根节点，和一个根的左节点；
*   干脆，用一个 stack 试试了；
*   
*   没想到，就是交换就行了，主要还是因为树的对称性，我们只管交换；
*   + 先压栈，还是先交换节点，没有影响
*   + 单从动态视觉来看，先压栈，是先处理左边，更有序的感觉；
* 
*   rank:
*       时间效率：0 ms, 击败 100%
*       空间效率：12,42 MB, 击败 8.53%
* 
* 【3】-- 递归也可以 -- 18/11/2025
*   看了题解，递归也是可以解决的，以后再写吧
*   + 分析：
*       + 时间复杂度：O(n)
*       + 空间复杂度：O(h)
*   + rank:
*       + 时间效率：0 ms, 击败 100%
*       + 空间效率：12.16 MB, 击败 85.34%
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
#include <stack>
#include <iostream>
#include <cstdio>
using std::stack;
using Leetcode::Tree::BinaryTree::TreeNode;

// 【3】-- 递归也可以 -- 18/11/2025
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {

        if (!root) return NULL;

        // swap(root->left, root->right);
        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

// 【2】
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {

        if (!root) return root;

        stack<TreeNode*> st;

        st.push(root);
        TreeNode* cur;

        while (!st.empty()) {

            cur = st.top(); st.pop();

            if (cur->right) st.push(cur->right);
            if (cur->left) st.push(cur->left);

            TreeNode* left = cur->left;
            if (cur) cur->left = cur->right;
            if (cur) cur->right = left;
        }

        return root;
    }
};