//
// Created by liangj.zhang on 12/5/2025
// URL: https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/submissions/629293547/
//

// 思路：最开始都没有注意到平衡二字，只想着不要弄成单链表的形式就行，给中间和开头两个位置的元素，交换一下位置，就结束问题了；
//      提交一次之后，发现右边是顺序插入的，右边直接是一个链表结构；
//      根节点左边，也是一个往右撇的，单链表了；
// 
//      平衡：要使得根节点左子树，与右子树两边深度是一样的；
// 
//      思路是，每次选取，数组的中间值插入，值两边的，就成为了左子树的数组，和右子树的数组；
//              只考虑左子树，再从剩下的顺序数组中，选取中间值，进行插入；
//              右子树类同；
//              这整个过程，跟归并排序的过程是一样的，都是对半；细节不一样，不重要；
// 
// condition: 
//      ps: 数组元素严格递增 => 没有重复的元素；相邻元素，右边必定大于左边；
// 
// rank: Great!!!
// 时间 0 ms, 击败 100%
// 存储 21.42 MB, 击败 99.69%
//

#include <iostream>
#include <vector>
#include "RandomNumbers.h"

using std::vector;
using std::cout;
using std::endl;


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


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
  

class Solution {
private:
    TreeNode* root;
    int count;

    void insert(int num) {
        
        TreeNode* newNode = new TreeNode(num);
        if (!root) {

            root = newNode;
            return;
        }
        root = __insert(root, newNode);
        count++;
    }

    TreeNode* __insert(TreeNode* cur, TreeNode* node) {

        if (cur == nullptr)
            return node;
        
        if (node->val < cur->val) {
            cur->left = __insert(cur->left, node);
        }
        else if (node->val > cur->val) {
            cur->right = __insert(cur->right, node);
        }
        // 严格递增 => 没有重复的元素

        return cur;
    }

    void merge(int* arr, int l, int r) {

        if (l > r)
            return;

        int mid = l + (r - l) / 2;
        
        insert(arr[mid]);
        cout << mid << " " << arr[mid] << endl;

        merge(arr, l, mid - 1);
        merge(arr, mid + 1, r);
    }

    void __inOrder(TreeNode* node) {

        if (!node)
            return;

        __inOrder(node->left);
        cout << node->val << " ";
        __inOrder(node->right);
    }

public:
    // 1 <= nums.length <= 10^4
    TreeNode* sortedArrayToBST(vector<int>& nums) {

        int size = nums.size();

        count = 0;
        root = nullptr;
        
        merge(nums.data(), 0, size - 1);
        cout << endl;

        return root;
    }

    // 中序遍历
    void inOrder() {
        __inOrder(root);
    }

};

int main() {
    
    int n = 5;
    int* arr = RandomNumbers::generateOrderedArray(n, true);
    //int* arr1 = RandomNumbers::copyIntArray(arr, n);
    RandomNumbers::printArray(arr, n);


    vector<int> nums = vector<int>(arr, arr + n);
    //swap(nums[0], nums[nums.size() / 2]);
    //RandomNumbers::printArray(nums.data(), n);
    
    Solution* sl = new Solution();
    sl->sortedArrayToBST(nums);
    sl->inOrder();
}
