#ifndef LEETCODE_TREE_H
#define LEETCODE_TREE_H

#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <climits>
#include <iostream>
using std::queue;
using std::vector;
using std::string;
using std::stringstream;
using std::cout;
using std::endl;

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

				private:
				// 前序遍历（访问自己）
				void __preOrder() {

					cout << this->val << " ";     // 访问当前节点
					if (this->left)  this->left->__preOrder();
					if (this->right) this->right->__preOrder();
				}

				public:
				// 前序遍历（访问自己）
				void preOrder() {

					__preOrder();
					cout << endl;
				}
			};

			vector<int> parseArray(const string& text, int nullFlag = INT_MIN) {
				vector<int> arr;
				string s = text;

				// 去掉 []
				if (s.front() == '[') s.erase(0, 1);
				if (s.back()  == ']') s.pop_back();

				stringstream ss(s);
				string token;

				while (getline(ss, token, ',')) {
					// 去空格
					while (!token.empty() && token.front() == ' ') token.erase(0, 1);

					if (token == "null" || token == "NULL")
						arr.push_back(nullFlag);
					else
						arr.push_back(stoi(token));
				}
				return arr;
			}

			TreeNode* buildTree(const vector<int>& arr, int nullFlag = INT_MIN) {
				if (arr.empty() || arr[0] == nullFlag) return nullptr;

				TreeNode* root = new TreeNode(arr[0]);
				queue<TreeNode*> q;
				q.push(root);

				int i = 1;
				while (!q.empty() && i < arr.size()) {
					TreeNode* node = q.front();
					q.pop();

					if (i < arr.size() && arr[i] != nullFlag) {
						node->left = new TreeNode(arr[i]);
						q.push(node->left);
					}
					i++;

					if (i < arr.size() && arr[i] != nullFlag) {
						node->right = new TreeNode(arr[i]);
						q.push(node->right);
					}
					i++;
				}
				return root;
			}

			string levelTraverse(TreeNode* root, int nullFlag = INT_MIN) {
				if (!root) return "[]";

				vector<string> out;
				queue<TreeNode*> q;
				q.push(root);

				// 记录“最后一个非空节点”在 out 中的索引
				int lastNonNullIndex = -1;

				while (!q.empty()) {
					TreeNode* node = q.front();
					q.pop();

					if (node) {
						out.push_back(std::to_string(node->val));
						lastNonNullIndex = out.size() - 1;  // 更新最后的非空节点位置

						q.push(node->left);
						q.push(node->right);
					} else {
						out.push_back("null");
					}
				}

				// 规则：如果最后一个节点是左孩子，需要补一个 null
				// 注意：我们不能简单删除尾部 null，要按照“兄弟 null 保留”规则来裁剪

				// —— 核心裁剪逻辑 ——
				// lastNonNullIndex 是最后的有效内容
				// 如果刚好落在左孩子，out[lastNonNullIndex+1] 就是右兄弟，应保留

				int lastOutIndex = lastNonNullIndex;

				// 若下一个是有效的“右兄弟 null”，就再多保留一个
				if (lastOutIndex + 1 < out.size()) {
					// 保留这个“兄弟 null”
					lastOutIndex++;
				}

				// 裁剪
				out.resize(lastOutIndex + 1);

				// 拼接
				string s = "[";
				for (int i = 0; i < out.size(); i++) {
					s += out[i];
					if (i != out.size() - 1) s += ",";
				}
				s += "]";
				return s;
			}

		}

	}

}

#endif
