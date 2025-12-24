/**
 * @brief: Leetcode_1110_删点成林
 * @link: https://leetcode.cn/problems/delete-nodes-and-return-forest/description/
 * @author: liangj.zhang
 * @date: 24/12/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: BST(post order)
 * 
 * @Retrospect(worthy 1 - 5):
 * 
 * @thoughts:
 *  + 【思路 1】：数组记录val（1 ~ 1000）与其节点地址对应关系，删除节点时就可以找到关系
 *      如果不是有 val 的范围 1 ~ 1000，这题以这种做法写不出来；
 *      非最优解，虽然时间复杂度和最优解一个级别，但常数大，且要额外空间
 * 
 *      + 分析：
 *          + 时间复杂度：遍历树节点 O(n), 遍历 to_delete O(m), 删除 O(1) -> 牺牲空间换来的 => O(n + m)
 *          + 空间复杂度：O(n)，常数大
 *      + rank:
 *          + 时间效率：16 ms, 击败 71.68%
 *          + 空间效率：25.96 MB, 击败 96.08%
 * 
 *  + 【思路 2】：post order，从下到上剥离要分离的子树，唯独 post order 能做到题目的要求；
 *      如果以 pre order 进行删除，或者 inorder，会有子树无法进入；
 *      ---
 *      这个方法，是 chat 给的，我让其简化思路 1，它给我的这个，确实很巧妙；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n) + O(m)
 *          + 空间复杂度：最坏 O(n)，常数小
 *      + rank:
 *          看过题解这次就不做了，留以后，可以先 python 这次试试；
 */

#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
using namespace Leetcode::Tree::BinaryTree;

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
#include <unordered_set>
#define MAXLEN 1001
#define us unordered_set
using std::unordered_set;
using std::vector;

// 【思路 1】：数组记录val（1 ~ 1000）与其节点地址对应关系，删除节点时就可以找到关系
/*
class Solution {
private:
    static vector<TreeNode*> rec;
    static vector<int> parent;
    static us<TreeNode*> ans;

    void preOrder(TreeNode* root, int parent) {

        if (!root) return;

        int val = root->val;
        rec[val] = root;
        this->parent[val] = parent;

        preOrder(root->left, val);
        preOrder(root->right, val);
    }

    void add_and_disengage_with_children(int e) {

        // 双向断连 cur 与 children
        if (rec[e]->left) {

            ans.insert(rec[e]->left);
            this->parent[rec[e]->left->val] = 0;
            rec[e]->left = nullptr;
        }

        if (rec[e]->right) {

            ans.insert(rec[e]->right);
            this->parent[rec[e]->right->val] = 0;
            rec[e]->right = nullptr;
        }
    }

    void disengage_with_parent(int e) {
        // int parent = this->parent[e];
        TreeNode* p = rec[this->parent[e]];
        // 双向断连 cur 与 parent
        if (p->left && p->left->val == e) p->left = nullptr;
        else p->right = nullptr;
        this->parent[e] = 0;
    }

public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {

        rec.clear();
        parent.clear();
        ans.clear(); ans.insert(root);

        preOrder(root, 0);

        for (auto e : to_delete) {

            if (!rec[e]) continue;

            if (ans.find(rec[e]) != ans.end()) 
                ans.erase(rec[e]);
            else 
                disengage_with_parent(e);
            
            // 放入 child, 双向断连 cur 与 child
            add_and_disengage_with_children(e);

            // 不复存在与树中
            rec[e] = nullptr;
        }

        vector<TreeNode*> ret;
        for (auto node : ans) 
            ret.push_back(node);

        return ret;
    }
};

vector<TreeNode*> Solution::rec(MAXLEN, nullptr);
vector<int> Solution::parent(MAXLEN, 0);
us<TreeNode*> Solution::ans{};
*/

// 【思路 2】：post order，从下到上剥离要分离的子树，唯独 post order 能做到题目的要求；-- chat
class Solution {
public:
    unordered_set<int> del;
    vector<TreeNode*> ans;

    TreeNode* dfs(TreeNode* root) {
        if (!root) return nullptr;

        root->left  = dfs(root->left);
        root->right = dfs(root->right);

        if (del.count(root->val)) {
            if (root->left)  ans.push_back(root->left);
            if (root->right) ans.push_back(root->right);
            return nullptr;   // 告诉父节点：我被删了
        }

        return root;
    }

    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        del = unordered_set<int>(to_delete.begin(), to_delete.end());

        if (dfs(root))
            ans.push_back(root);

        return ans;
    }
};

int main() {

    string sarr = "[1,2,3,4,5,6,7]";
    string sto_delete = "[3]";

    vector<int> arr = parseArray(sarr);
    vector<int> to_delete = parseArray(sto_delete);
    for (auto e : arr)
        cout << e << " ";
    cout << endl;
    for (auto e : to_delete)
        cout << e << " ";
    cout << endl;

    TreeNode* root = buildTree(arr);
    
    Solution().delNodes(root, to_delete);
}