/**
 * @brief: Leetcode_1123_最深叶节点的最近公共祖先
 * @link: https://leetcode.cn/problems/lowest-common-ancestor-of-deepest-leaves/description/
 * @author: liangj.zhang
 * @date: 28/12/2028
 * 
 * @Difficulty: Meidum
 * 
 * @Label: LCA
 * 
 * @Retrospect(worthy 1 - 5): 5
 * 
 * @thoughts:
 *  + 【思路 1】：
 *      每条支路，到叶子节点之后，返回这条路径的深度，>>> 递归回去也是返回该路径的最大值 <<<；
 *      递归回去时，>>> 如果左右两条分支的最大深度不一样，取最大值 <<<
 *      + 如果，>>> 左右子树的深度相等，且与被记录的最大值相等，说明左右子树相对对方而言，在别的地方还有与他们相等的深度的分支；
 *      + 当前节点，就是[当前]发现最大深度的分支的 LCA；<<<(如果还有其他最大分支，会继续更新下去)
 * 
 *      + 分析：
 *          + 时间复杂度：O(n)
 *          + 空间复杂度：O(n) 可能是一条链
 *      + rank:
 *          + 时间效率：0 ms, 击败 100%
 *          + 空间效率：21.48 MB, 击败 91.48%
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

class Solution {
private:
    int max_depth;
    TreeNode* lca;

    int postOrder(TreeNode* root, int depth) {

        if (depth > max_depth) max_depth = depth;

        if (!root) return depth;

        int left = postOrder(root->left, depth + 1); 
        int right = postOrder(root->right, depth + 1);

        if (left == right && left == max_depth)
            lca = root;

        return std::max(left, right);
    }
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        
        max_depth = -1;
        postOrder(root, 0);

        return lca;
    }
};

int main() {

    string sarr = "[3,5,1,6,2,0,8,null,null,7,4]";
    TreeNode* root = buildTreeFromStringArray(sarr);
    cout << levelTraverse(root) << endl;

    TreeNode* ret = Solution().lcaDeepestLeaves(root);
    cout << levelTraverse(ret) << endl;
}