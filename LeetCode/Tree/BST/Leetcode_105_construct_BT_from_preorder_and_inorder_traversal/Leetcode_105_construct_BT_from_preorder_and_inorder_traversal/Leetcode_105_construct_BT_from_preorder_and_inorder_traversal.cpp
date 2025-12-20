/**
 * @brief: Leetcode_105_从前序与中序遍历序列构造二叉树
 * @link: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description
 * @author: liangj.zhang
 * @date: 21/6/2025
 * 
 * @update:
 *   + 20/12/2025: 跟 21/6/2025 一样的方式，再写了一遍； -- 【写法2】
 *
 * @Difficulty: Medium
 * 
 * @Label: Binary Tree
 * 
 * @Again(Worthy 0 - 5): 5
 * 
 * @thoughts:
 * + 【思路 1】：利用 preOrder inOrder 特性； -- 【写法 1】
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
 * 
 * + 【思路 1】：写法 2
 *      有个当前范围后 preorder [pl, pr], inorder [il, ir]
 *      preorder 的第一个值，就是当前树的根，
 *      在 inorder 中知道该根的位置（通过值）in_idx 后，
 *      我们就能知道左右子树的情况；左子树 [il, in_idx - 1] 右子树 [in_idx + 1, ir]
 *      也会知道 左子树的个数 left_tree_size，
 *      根据 preorder 的特性，当前根之后是其整个左子树，再是整个右子树，我们知道子树个数，也就找到子树在 preorder 中的范围；
 *      新的范围就有了， 
 *          左子树：preorder[pl + 1, pl + left_tree_size] inorder[il, in_idx - 1]
 *          右子树：preorder[pl + left_tree_size + 1, pr] inorder[in_idx + 1, ir]
 *      可以开启递归了
 * 
 *      + 分析：
 *          + 时间复杂度：记录 inorder 中各 val 的位置：O(n), 递归每个节点一遍 O(n)
 *          + 空间复杂度：O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：26.94 MB, 击败 52.82%
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
    um<int, int> rec;
    vector<int>* pre;   // 不想每次递归，还多带一个指针参数

    TreeNode* __buildTree(int pl, int pr, int il, int ir) {

        if (pl > pr) return nullptr;

        int root_idx = pl;
        int root_val = (*pre)[root_idx];
        int in_idx = rec[root_val];

        int left_tree_size = in_idx - il;

        TreeNode* node = new TreeNode(root_val);
        node->left = __buildTree(pl + 1, pl + left_tree_size, il, in_idx - 1);
        node->right = __buildTree(pl + left_tree_size + 1, pr, in_idx + 1, ir);
        return node;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

        for (int i = 0; i < inorder.size(); ++i) 
            rec.insert({inorder[i], i});

        pre = &preorder;

        return __buildTree(0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};

/*
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
*/