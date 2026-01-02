/**
 * @brief: Leetcode_2583_二叉树中的第 K 大层和
 * @link: https://leetcode.cn/problems/kth-largest-sum-in-a-binary-tree/description/
 * @author: liangj.zhang
 * @date: 2/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS + priority_queue
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：BFS + priority_queue
 *      第 k 个数值，这类需求，我现在的第一想法就是 大小顶堆 维持 k 个数据；
 *      不用手写大小顶堆，就用 priority_queue;
 *      BFS：这几天都在写这类题，我已经很熟悉了，更何况 samsung 的 ADV 主要考的就是这类题；
 *      ----
 *      priority_queue 练手的一题
 *      
 *      + 分析：
 *          + 时间复杂度：O(n) + h * O(logk) [h -> 树的高度，k 是放入的节点数]
 *          + 空间复杂度：O(h)[priority_queue, 最多 O(n)] + O(n)[queue] => O(n)
 *      + rank:
 *          + 时间效率：24 ms, 击败 95.58%
 *          + 空间效率：254.70 MB, 击败 92.48%
 */

#include <iostream>
#include "../../../../../Include/Leetcode/Tree/Tree.h"
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
#include <queue>
using std::vector;
using std::queue;
using std::priority_queue;

template<class T>
class FixedSizePriQue {
private:
    priority_queue<T, vector<T>, std::greater<T>> min_heap;
    int max_size;

public:
    FixedSizePriQue(int max_size) : max_size(max_size) { }

    void push(T val) {

        if (min_heap.size() < max_size)
            min_heap.push(val);
        else if (min_heap.top() < val) {

            min_heap.pop();
            min_heap.push(val);
        }
    }

    T top() const { return min_heap.top(); }

    int size() const { return min_heap.size(); }
};

class Solution {
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        
        FixedSizePriQue<long long> fspq(k);
        queue<TreeNode*> q;

        q.push(root);   // 原来错误的写法，加这里后面 提前放入了 root->val，后面循环还会再放一次；
        int size;
        long long sum;
        while (!q.empty()) {
            
            size = q.size();
            sum = 0;
            for (int i = 0; i < size; ++i) {

                TreeNode* cur = q.front(); q.pop();
                sum += cur->val;
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            fspq.push(sum);
        }

        return fspq.size() < k ? -1 : fspq.top();
    }
};

int main() {

    TreeNode* root = buildTreeFromStringArray("[897935,796748,528909,null,null,null,905326,706311,null,null,282251,null,139169]");
    root->preOrder();

    Solution().kthLargestLevelSum(root, 4);
}