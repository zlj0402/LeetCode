/**
* @brief: Leetcode_105_从前序与中序遍历序列构造二叉树
* @link: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description
* @author: liangj.zhang
* @date: 21/6/2025
* 
* @Difficulty: Medium
* 
* @Label: Binary Tree
* 
* @Again(Worthy 0 - 5): 5
* 
* @thoughts:
*   这道题，好写一些的原因是，没有重复出现的数字，不然就不好写了；
*   - 用了一个 unordered_map 记录了各节点在原始序列中的位置；
*   + 当前的 前序遍历列表，第一个是当前子树的根节点 root；
*   + 从当前的 中序遍历列表，找到这个 root，那么这个 root 的左边到当前范围的左边，就是左子树部分，root 的右边到当前范围的右边，就是右子树部分；
*   + 左子树 / 右子树，的处理，和上面两步是一模一样的；递归处理；
* 
*   分析：
*       时间复杂度：
*           + 记录两个 vector<int> 序列的节点位置； 2 * O(n)
*           + 递归到每个节点 O(n)
*           总的是 O(n)
*       空间复杂度：
*           + 栈的调用：每个节点都会当做子树根节点处理一次，是 O(n) * (参数变量 4 + 局部变量 8+3 + 调用函数地址 1 + 栈指针管理 1)
*           总的还是 O(n)
* 
*   rank: 
*       时间效率：0 ms, 击败 100%
*       空间效率：27.47 MB, 击败 25.71%
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
#include "Leetcode/BTTestHelper.h"
#include<vector>
using std::vector;
using Leetcode::Tree::BinaryTree::TreeNode;
using namespace Leetcode;

#include <unordered_map>
#define um unordered_map
using std::unordered_map;

class Solution {
private:
    um<int, int> preHash;
    um<int, int> inHash;
    vector<int>* preorder;
    vector<int>* inorder;

    inline void mapHash(vector<int>& preorder, vector<int>& inorder) {

        preHash.clear(); inHash.clear();
        int i = -1;
        for (auto& e : preorder)
            preHash.insert({e, ++i});
        i = -1;
        for (auto& e : inorder)
            inHash.insert({e, ++i});
    }

    // [pre_start, pre_end], [in_start, in_end] 是当前的前序遍历数组区间，和当前的中序遍历数组区间
    TreeNode* __buildTree(int ps, int pe, int is, int ie) {

        if (ps > pe)
            return nullptr;

        int root = (*preorder)[ps];
        int in_pos = inHash[root];
        // [is, root)
        int left_len = in_pos - is;

        int next_left_ps = ps + 1;
        int next_left_pe = next_left_ps + left_len - 1;
        int next_right_ps = next_left_pe + 1;
        int next_right_pe = pe;

        int next_left_is = is;
        int next_left_ie = in_pos - 1;
        int next_right_is = in_pos + 1;
        int next_right_ie = ie;

        return  new TreeNode(root, __buildTree(next_left_ps, next_left_pe, next_left_is, next_left_ie),
            __buildTree(next_right_ps, next_right_pe, next_right_is, next_right_ie));
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

        mapHash(preorder, inorder);
        this->preorder = &preorder;
        this->inorder = &inorder;

        return __buildTree(0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};


int main() {

    vector<int> preorder = { 3,9,20,15,7 };
    vector<int> inorder = { 9,3,15,20,7 };

    TreeNode* root = (new Solution())->buildTree(preorder, inorder);
    BTTestHelper::preorder(root);
    BTTestHelper::inorder(root);
}