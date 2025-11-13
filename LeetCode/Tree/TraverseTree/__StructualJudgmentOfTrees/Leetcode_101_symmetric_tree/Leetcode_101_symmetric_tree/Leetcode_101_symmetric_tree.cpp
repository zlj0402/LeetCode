/**
* @brief: Leetcode_101_对称二叉树
* @link: https://leetcode.cn/problems/symmetric-tree/description
* @author: liangj.zhang
* @date: 18/6/2025
* 
* @Difficulty: Easy
* 
* @Label: Binary Tree
* 
* @brief content: 判断二叉树是否为对称的二叉树
* 
* @thoughts:
*   两个树互为镜像：
*       + 他们的根具有相同值
*       + 每个树的右子树都与另一个树左子树镜像对称
* 
*  【1】-- 迭代 + 栈
*       用了当时做，翻转二叉树没成功使用的方式（那题不适合，Leetcode_226_invert_binary_tree），用两个栈，对称操作，左边靠左往下延伸，右边靠右往下延伸
*       rank:
*           时间效率：0 ms, 击败 100%
*           空间效率：18.55 MB, 击败 5.04%
* 
*  【2】-- 递归
*       递归的时候，两棵树的根节点，比较值是否相同，再同样的操作，不过是 check(左树的左子树，右树的右子树) && check(左树的右子树，右树的左子树)
*       rank:
*           时间效率：0 ms, 击败 100%
*           空间效率：18.3 MB, 击败 16.59 %
* 
*   【2.2】-- 空间效率高，该怎么做？-- 参考 top 的代码
*       参考top的空间效率，原来是拆开条件，避免使用更多的栈空间
*       rank:
*           时间效率：0 ms, 击败 100%
*           空间效率：18.14 MB, 击败 56.62%
*   【2.3】-- 递归，剪枝版
*       这种比上面的 2.2 版空间效率还高一点
*       rank:
*           时间效率：0 ms, 击败 100%
*           空间效率：18.00 MB, 击败 88.88%
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
using Leetcode::Tree::BinaryTree::TreeNode;

//【2.3】-- 递归，剪枝版
class Solution {
private:
    bool ret;
    void __isSymmetric(TreeNode* p, TreeNode* q) {

        if (ret && (!p ^ !q)) ret = false;
        if (!p || !q) return;
        if (ret && p->val != q->val) ret = false;

        if (!ret) return;
        
        __isSymmetric(p->left, q->right);
        __isSymmetric(p->right, q->left);
    }

public:
    bool isSymmetric(TreeNode* root) {
        
        ret = true;
        __isSymmetric(root->left, root->right);
        return ret;
    }
};

// 【1】
//#include <stack>
//using std::stack;
//
//class Solution {
//public:
//    bool isSymmetric(TreeNode* root) {
//
//        stack<TreeNode*> lst;
//        stack<TreeNode*> rst;
//
//        lst.push(root->left);
//        rst.push(root->right);
//
//        TreeNode* lcur, * rcur;
//
//        while (!lst.empty() || !rst.empty()) {
//
//            TreeNode* lcur = lst.top(); lst.pop();
//            TreeNode* rcur = rst.top(); rst.pop();
//
//            // 只有都为 nullptr 的时候，lcur == rcur
//            if (lcur == rcur || (lcur && rcur && lcur->val == rcur->val));
//            else return false;
//
//            if (lcur) lst.push(lcur->right);
//            if (rcur) rst.push(rcur->left);
//
//            if (lcur) lst.push(lcur->left);
//            if (rcur) rst.push(rcur->right);
//        }
//
//        return lst.empty() && rst.empty() ? true : false;
//    }
//};

// 【2】
class Solution {
private:
    bool check(TreeNode* left, TreeNode* right) {

        // 都为 nullptr
        if (!left && !right) return true;
        // 其中一个为 nullptr
        if (!left || !right) return false;

        return (left->val == right->val) && check(left->left, right->right) && check(left->right, right->left);
    }

public:
    bool isSymmetric(TreeNode* root) {

        return check(root->left, root->right);
    }
};

// 【2.2】
//class Solution {
//private:
//    bool isSym(TreeNode* left, TreeNode* right)
//    {
//        if (left == NULL)
//            return right == NULL;
//        if (right == NULL)
//            return left == NULL;
//        if (left->val != right->val)
//            return false;
//        if (!isSym(left->left, right->right))
//            return false;
//        if (!isSym(left->right, right->left))
//            return false;
//        return true;
//    }
//
//public:
//    bool isSymmetric(TreeNode* root) {
//
//        return isSym(root->left, root->right);
//    }
//};