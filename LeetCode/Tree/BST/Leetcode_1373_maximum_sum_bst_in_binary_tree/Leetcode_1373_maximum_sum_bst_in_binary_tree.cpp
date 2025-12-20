/**
 * @brief: Leetcode_1373_二叉搜索子树的最大键值和
 * @link: https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/description/
 * @author: liangj.zhang
 * @date: 20/12/2025
 * 
 * @Difficulty: Hard
 * 
 * @Label: BST(postOrder)
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：BST 的后序遍历
 *      + 之前写 Leetcode_98 题，验证一棵 BST；当时认真做了这题，看了灵神的多种方式，最重要的最难的验证：postOrder
 *      我们在遍历的时候，把当前 BST 的 sum，向上传递；
 *      如果在结合左右子树的情况，当前还能构成 BST，此时就要比较，max 与 sum 就可以了；
 * 
 *      坑：
 *      1. 树节点有负数，下面的 BST 可能比上面的 BST 和要大；=> 所以每次成立，都要与 max 比较；
 *      2. 一个叶子节点一定有 《最大键值和》，且为 0；如果整棵树都是 BST，但都是负数，叶子节点的“子树”的键值和 0，此时是最大的；
 * 
 *      ps:
 *      最开始的时候没考虑到越往上可能越小（即以为越来越大），只需要在原来是，当前不是 BST 的时候，与 max 记录值比较一下就可以了；
 *      因为有负数，每次都需要比较，考虑有回到了最初情况；
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：最坏 O(n)
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：103.14 MB, 击败 52.90%
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

#include <tuple>

class Solution {
private:
    int max;

    // void update3(int lsum, int rsum, int root_val) {

    //     int new_sum = std::max(std::max(lsum, rsum), lsum + rsum + root_val);
    //     if (new_sum > max) max = new_sum;
    // }

    std::tuple<int, int, bool, int> postOrder(TreeNode* root) {

        if (!root) return {INT_MAX, INT_MIN, true, 0};

        auto [lmin, lmax, lflag, lsum] = postOrder(root->left);
        auto [rmin, rmax, rflag, rsum] = postOrder(root->right);

        // if ((lflag & rflag) && (lmax <= root->val && rmin >= root->val)) {   // 原来错误的写法：有相同值，不认为是 BST
        if ((lflag & rflag) && (lmax < root->val && rmin > root->val)) {   // take current root into account, also BST

            // 下面 return 当前树的 sum 没有问题；
            // 但是有可能 最大值在下面的子树，因为 下面都是正节点，上面变成都是负数节点，每次都要比较下
            // update3(lsum, rsum, root->val);  // 原来错误的写法：忽略了这一步 // 每一次 BST 成立都比较了，这次就不用在考虑左右单子树了
            int sum = lsum + rsum + root->val;
            if (sum > max) max = sum;
            return {std::min(lmin, root->val), std::max(rmax, root->val), true, sum};
        } 
        // 上面每次有新的 BST 就更新，也就没必要考虑当前不成立 BST，左右子树如何，因为上面已经考虑过了；
        // else if (lflag & rflag)   // left subtree & right subtree -> BST, but take current root into account -> not BST
        //     // max = std::max(lsum, rsum);
        //     // max = std::max(max, std::max(lsum, rsum));  // maybe, max is the largest => 等价下面写法
        //     update2(lsum, rsum);
        // else if (lflag)     // left subtree is BST, right subtree not
        //     if (max < lsum) max = lsum;
        // else if (rflag)     // right subtree is BST, left subtree not
        //     if (max < rsum) max = rsum;
        
        return {INT_MIN, INT_MAX, false, -1};
    }
public:
    int maxSumBST(TreeNode* root) {
        
        // max = INT_MIN;
        max = 0;    // 就算整棵树都是 BST，但是节点都是 negtive number, 不如空节点 return 的 0；
        // 有可能整棵树都满足BST，还需要对最后的 _sum 进行比较
        auto [_min, _max, _flag, _sum] = postOrder(root);
        if (_flag) if (max < _sum) max = _sum;
            
        return max;
    }
};

int main() {

    string s = "[-4, -2, -5]";

    TreeNode* root = buildTree(parseArray(s));

    int ret = Solution().maxSumBST(root);

    cout << ret;
}