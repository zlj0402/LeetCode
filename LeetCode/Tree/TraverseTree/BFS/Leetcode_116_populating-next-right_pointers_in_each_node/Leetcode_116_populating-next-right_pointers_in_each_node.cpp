/**
 * @brief: Leetcode_116_填充每个节点的下一个右侧节点指针
 * @link: https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/description/
 * @author: liangj.zhang
 * @date: 4/1/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: BFS
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  +【思路 1】：BFS
 *      层序遍历，很贴切的能找到横向的下一位；
 *      
 *      + 【写法 1】：queue 结构
 *          + 分析：
 *              + 时间复杂度：O(n)
 *              + 空间复杂度：O(n)
 *          + rank:
 *              + 时间效率：15 ms, 击败 70.56%
 *              + 空间效率：19.08 MB, 击败 9.21%
 *      + 【写法 2】：固定数组大小
 *          + 分析：同上
 *          + rank: 
 *              + 时间效率：13 ms, 击败 75.5%
 *              + 空间效率：18.80 MB, 击败 63.4%
 * 
 *  + 【思路 2】：BFS + 链表
 *      这个思路是看了灵神的题解，才意识到的，下次用这种方式：
 *      上一层既然是链表，想办法记住上一次的头，是不是就能不需要额外的 O(n) 空间了；
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

#include <queue>
using std::queue;
#define NULL 0

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

// 【思路 1 -- 写法 1】
class Solution {
public:
    Node* connect(Node* root) {

        queue<Node*> q;
        if (root) q.push(root);
        while (!q.empty()) {

            int size = q.size();
            for (int i = 0; i < size; ++i) {

                Node* cur = q.front(); q.pop();
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);

                if (i == size - 1) cur->next = nullptr;
                else cur->next = q.front();
            }
        }

        return root;
    }
};

// 【思路 1 -- 写法 2】
class Solution {
private:
    static int constexpr MAXSIZE = 4096;
    static Node* arr[MAXSIZE];

public:
    Node* connect(Node* root) {
        
        if (!root) return root;
        int front{0}, rear{0};
        arr[rear++] = root;

        while (front < rear) {

            int last_rear = rear;
            while (front < last_rear) {

                Node* cur = arr[front];
                if (++front < last_rear) cur->next = arr[front];
                else cur->next = nullptr;
                if (cur->left) arr[rear++] = cur->left;
                if (cur->right) arr[rear++] = cur->right;
            }
        }

        return root;
    }
};

Node* Solution::arr[MAXSIZE]{};