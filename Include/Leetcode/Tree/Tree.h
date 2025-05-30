#ifndef LEETCODE_TREE_H
#define LEETCODE_TREE_H

namespace Leetcode {

	namespace Tree {
		
		namespace BinaryTree{

			// Definition for a binary tree node.
			struct TreeNode {
				int val;
				TreeNode* left;
				TreeNode* right;
				TreeNode() : val(0), left(nullptr), right(nullptr) {}
				TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
				TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
			};

		}

	}

}

#endif
