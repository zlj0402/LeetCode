/**
 * @brief: Leetcode_987_二叉树的垂序遍历
 * @link: https://leetcode.cn/problems/vertical-order-traversal-of-a-binary-tree/description/
 * @author: liangj.zhang
 * @date: 9/11/2025
 * 
 * @Difficulty: Hard（实话说是，Hard 里简单的）
 * 
 * @Label: Tree(Traverse) + HashMap/Set
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：dfs + hashmap/multiset
 *      我的第一想法就是这个，先 dfs 遍历一遍，加上 行列的记录；
 *      将一个值的信息封装成 col,row,val => E(x, y, z)，重载运算符 <，
 *      放入一个总的 multiset 里，或者是 hashmap，列作为 key， multiset<pair<row, val>> 作为 val;
 *      其实这都差不多，我才用的是 一个总的 multiset
 * 
 *      + 值得回顾的点是：比较方式的几种写法，后续都会补上：
 *          1. operator< 重载
 *          2. 使用 std::tie 实现运算符重载
 *          3. 自定义 set 的比较器；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)，dfs 一遍，分组时一遍 + multiset 中的排序 O(nlogn) => O(nlogn)
 *          + 空间复杂度：O(n) * (2 ~ 3) == O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：15.66 MB, 57.58%
 */
#include <vector>
#include "../../../../Include/Leetcode/Tree/Tree.h"
using Leetcode::Tree::BinaryTree::TreeNode;
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

#include <set>
#include <tuple>
using std::multiset;

class E {
public:
    int x, y, z;    // x 是 列值，y 是横轴值，z 是 value
    E(int x, int y, int z) : x(x), y(y), z(z) {}
};

struct Cmp{

    bool operator()(const E& a, const E& b) const {

        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
};

class Solution {

private:
    static vector<int> tmp;
    static multiset<E, Cmp> rec;
    static vector<vector<int>> ans;

    void __verticalTraversal(TreeNode* root, int y, int x) {

        if (!root) return;

        rec.insert(E(x, y, root->val));
        __verticalTraversal(root->left, y + 1, x - 1);
        __verticalTraversal(root->right, y + 1, x + 1);
    }
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        
        rec.clear();
        ans.clear();

        __verticalTraversal(root, 0, 0);

        int last_x = rec.begin()->x;    // 原来错误的写法：没取第一个值作为初始值，多 push 一个空的 vector<>
        tmp.clear();
        for (auto& e : rec) {

            if (last_x != e.x) {

                ans.push_back(tmp);
                tmp.clear();
                last_x = e.x;
            }
            tmp.emplace_back(e.z);
        }
        ans.push_back(tmp); // 原来错误的写法：忘记 push 最后一组

        return ans;
    }
};

vector<int> Solution::tmp = vector<int>();
vector<vector<int>> Solution::ans = vector<vector<int>>();
multiset<E, Cmp> Solution::rec = multiset<E, Cmp>();

/*
class E {
public:
    int x, y, z;    // x 是 列值，y 是横轴值，z 是 value
    E(int x, int y, int z) : x(x), y(y), z(z) {}

    bool operator<(const E& e) const {

        // 【写法 1.1】最原始的比较方式
        if (x != e.x) return x < e.x;
        if (y != e.y) return y < e.y;
        return z < e.z;

        // return false;

        // 【写法 1.2】标准的运算符重载
        // return (x < e.x) ? true :
        //        (x > e.x) ? false :
        //        (y < e.y) ? true :
        //        (y > e.y) ? false :
        //        (z < e.z);
        
        // 【写法 1.3】<tuple>, std::tie()
        return std::tie(x, y, z) < std::tie(e.x, e.y, e.z);
    }
};

class Solution {
private:
    static vector<int> tmp;
    static multiset<E> rec;
    static vector<vector<int>> ans;

    void __verticalTraversal(TreeNode* root, int y, int x) {

        if (!root) return;

        rec.insert(E(x, y, root->val));
        __verticalTraversal(root->left, y + 1, x - 1);
        __verticalTraversal(root->right, y + 1, x + 1);
    }
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        
        rec.clear();
        ans.clear();

        __verticalTraversal(root, 0, 0);

        int last_x = rec.begin()->x;    // 原来错误的写法：没取第一个值作为初始值，多 push 一个空的 vector<>
        tmp.clear();
        for (auto& e : rec) {

            if (last_x != e.x) {

                ans.push_back(tmp);
                tmp.clear();
                last_x = e.x;
            }
            tmp.emplace_back(e.z);
        }
        ans.push_back(tmp); // 原来错误的写法：忘记 push 最后一组

        return ans;
    }
};

vector<int> Solution::tmp = vector<int>();
vector<vector<int>> Solution::ans = vector<vector<int>>();
multiset<E> Solution::rec = multiset<E>();
*/