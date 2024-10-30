// 
// Created by liangj.zhang on 30/10/2024, infer 0 ms' code
//

// [head]		-> node1	-> node2
// 
// [head]		-> node1	-> node2
//    new_node0 ↗
//
// head		-> new_node0	-> node1	-> node2
//
// head		-> new_node0	-> [node1]	-> node2
//							   new_node1 ↗
//
// head		-> new_node0	-> node1  -> new_node1 -> node2
//
// head		-> new_node0	-> node1  -> new_node1 -> [node2]
// ...

// 不使用宏NULL，直接用nullptr的时间效率竟然更高了
// Chat:
//在现代 C++ 中，使用 `nullptr` 替代 `NULL` 确实可以提高代码的效率和安全性。下面是几个原因：
//
//1. * *类型安全 * *：`NULL` 实际上是一个 `0` 的宏定义，在某些上下文中会被当作整数，而不是指针。这可能导致一些编译器需要额外的操作来处理类型检查。而 `nullptr` 是一个真正的空指针类型（`std::nullptr_t`），编译器不需要做额外的类型推导，可以直接识别和优化它。
//
//2. * *减少不必要的类型转换 * *：当使用 `NULL` 时，编译器可能需要在指针和整数之间进行转换，以确保类型匹配。这些转换在现代编译器中可能影响性能。使用 `nullptr` 避免了这些转换，减少了编译器优化过程中的复杂性，从而提高了效率。
//
//3. * *优化代码生成 * *：使用 `nullptr` 时，编译器更容易识别并进行优化，生成更高效的汇编代码。因为 `nullptr` 明确表示空指针，编译器可以在寄存器分配和内存操作时做出更好的优化选择。
//
//综上所述，虽然在某些情况下差别可能很小，但使用 `nullptr` 是一种更现代、更高效的选择。

// rank:
// 时间3ms,击败95.24%
// 内存14.23MB，击败90.68%

#define NULL 0

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) return head;

        Node* cur, * new_node;

        // 1. 在每个原来的节点后面，插入先复制的新节点
        for (cur = head; cur; cur = cur->next->next) {
            new_node = new Node(cur->val);
            new_node->next = cur->next;
            cur->next = new_node;
        }

        // 2. 复制原链表（需要这个第二步，是因为节点内部有其他指针指向）
        for (cur = head; cur; cur = cur->next->next) {
            new_node = cur->next;
            new_node->random = cur->random ? cur->random->next : NULL;
        }

        // 3. 拆成原链表和新链表 
        Node* ret_node = head->next;
        for (cur = head; cur; cur = cur->next) {
            new_node = cur->next;
            cur->next = new_node ? new_node->next : NULL;
            new_node->next = cur->next ? cur->next->next : NULL;
        }

        return ret_node;
    }
};