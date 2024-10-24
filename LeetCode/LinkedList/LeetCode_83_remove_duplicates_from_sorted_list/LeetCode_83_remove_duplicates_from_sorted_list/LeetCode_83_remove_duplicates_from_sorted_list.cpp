#include <iostream>
#include <cstring>
using namespace std;

 // Definition for singly-linked list.

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

    static void print_list(ListNode* head) {
        ListNode* cur = head;
        while (cur != nullptr) {
            cout << cur->val << "->";
            cur = cur->next;
        }
        cout << "null" << endl;
    }
};

class Solution {
private:
    bool map[201];

    void del_node(ListNode* cur) {
        cur->next = cur->next->next;
    }
public:

    ListNode* deleteDuplicates(ListNode* head) {
        //memset(map, 1, sizeof(map));
       /* for (size_t i = 0; i < 201; i++) {
            cout << map[i];
        }
        cout << endl;
        return nullptr;*/
        ListNode* dummy_head = new ListNode(-1, head);
        ListNode::print_list(head);

        ListNode* cur = dummy_head;
        while (cur->next != nullptr) {
            int val = cur->next->val;
            // val occured before
            if (map[val + 100]) {
                del_node(cur);
            }
            // val did not occur before
            else {
                map[val + 100] = true;
                cur = cur->next;
            }
        }
        return dummy_head->next;
    }
};

int main() {
    // 创建链表:
    ListNode* head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(5);
    ListNode::print_list((new Solution())->deleteDuplicates(head));
}