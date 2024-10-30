// 
// Created by liangj.zhang on 30/10/2024, infer 0 ms' code
//

// [head]		-> node1	-> node2
// 
// [head]		-> node1	-> node2
//    new_node0 �J
//
// head		-> new_node0	-> node1	-> node2
//
// head		-> new_node0	-> [node1]	-> node2
//							   new_node1 �J
//
// head		-> new_node0	-> node1  -> new_node1 -> node2
//
// head		-> new_node0	-> node1  -> new_node1 -> [node2]
// ...

// ��ʹ�ú�NULL��ֱ����nullptr��ʱ��Ч�ʾ�Ȼ������
// Chat:
//���ִ� C++ �У�ʹ�� `nullptr` ��� `NULL` ȷʵ������ߴ����Ч�ʺͰ�ȫ�ԡ������Ǽ���ԭ��
//
//1. * *���Ͱ�ȫ * *��`NULL` ʵ������һ�� `0` �ĺ궨�壬��ĳЩ�������лᱻ����������������ָ�롣����ܵ���һЩ��������Ҫ����Ĳ������������ͼ�顣�� `nullptr` ��һ�������Ŀ�ָ�����ͣ�`std::nullptr_t`��������������Ҫ������������Ƶ�������ֱ��ʶ����Ż�����
//
//2. * *���ٲ���Ҫ������ת�� * *����ʹ�� `NULL` ʱ��������������Ҫ��ָ�������֮�����ת������ȷ������ƥ�䡣��Щת�����ִ��������п���Ӱ�����ܡ�ʹ�� `nullptr` ��������Щת���������˱������Ż������еĸ����ԣ��Ӷ������Ч�ʡ�
//
//3. * *�Ż��������� * *��ʹ�� `nullptr` ʱ��������������ʶ�𲢽����Ż������ɸ���Ч�Ļ����롣��Ϊ `nullptr` ��ȷ��ʾ��ָ�룬�����������ڼĴ���������ڴ����ʱ�������õ��Ż�ѡ��
//
//������������Ȼ��ĳЩ����²����ܺ�С����ʹ�� `nullptr` ��һ�ָ��ִ�������Ч��ѡ��

// rank:
// ʱ��3ms,����95.24%
// �ڴ�14.23MB������90.68%

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

        // 1. ��ÿ��ԭ���Ľڵ���棬�����ȸ��Ƶ��½ڵ�
        for (cur = head; cur; cur = cur->next->next) {
            new_node = new Node(cur->val);
            new_node->next = cur->next;
            cur->next = new_node;
        }

        // 2. ����ԭ������Ҫ����ڶ���������Ϊ�ڵ��ڲ�������ָ��ָ��
        for (cur = head; cur; cur = cur->next->next) {
            new_node = cur->next;
            new_node->random = cur->random ? cur->random->next : NULL;
        }

        // 3. ���ԭ����������� 
        Node* ret_node = head->next;
        for (cur = head; cur; cur = cur->next) {
            new_node = cur->next;
            cur->next = new_node ? new_node->next : NULL;
            new_node->next = cur->next ? cur->next->next : NULL;
        }

        return ret_node;
    }
};