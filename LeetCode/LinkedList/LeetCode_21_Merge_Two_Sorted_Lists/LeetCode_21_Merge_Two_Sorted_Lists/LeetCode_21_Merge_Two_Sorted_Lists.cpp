// LeetCode_21_Merge_Two_Sorted_Lists.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

 // Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}

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
      void insert_node(ListNode* prev, ListNode* node) {
          // insert node after prev
          // prev is not nullptr
          node->next = prev->next;
          prev->next = node;
      }

  public:
      ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
          if (list1 == nullptr)
              return list2;
          if (list2 == nullptr)
              return list1;
          ListNode* dummy_head = new ListNode(-1, list1);
          //ListNode::print_list(dummy_head);
          //ListNode::print_list(list2);
          for (ListNode* p = list2; p != nullptr;) {
              ListNode* cur = dummy_head;
              ListNode* pp = p;
              p = p->next;
              while (cur->next != nullptr && cur->next->val < pp->val)
                  cur = cur->next;
              insert_node(cur, pp);
          }

          return dummy_head->next;
      }
  };

  int main() {
      // 创建链表: 1 -> 2 -> 3
      ListNode* head = new ListNode(1);
      head->next = new ListNode(3);
      head->next->next = new ListNode(5);

      // 创建链表: 2 -> 4 -> 6
      ListNode* head2 = new ListNode(2);
      head2->next = new ListNode(4);
      head2->next->next = new ListNode(6);
      // 打印链表
      ListNode::print_list((new Solution())->mergeTwoLists(head, head2));  // 输出: 1 -> 2 -> 3

      return 0;
  }
