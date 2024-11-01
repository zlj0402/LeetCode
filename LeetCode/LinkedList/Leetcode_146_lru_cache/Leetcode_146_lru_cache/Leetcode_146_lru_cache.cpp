//
// Created by liangj.zhang on 1/11/2024
// 

// 我的构思：
// size;
// get 要 O(1) 的时间复杂度，我能想到的只能是数组链表了；
// put也能以 O(1) 的时间复杂度进行
// 首先一个结构体Node{val, pre, next}
// 再一个数组 0 <= key <= 10000, 10002个长度
// get -> 直接数组下标读，判断；
// 存在，更新最新的使用，移动head指向最新；不存在，不用更新
// put -> size < capacity, 直接head插入；size == capacity, 从tail部位删除，从head插入；
// 移除时，给节点重置

// rank - great!!!: 自己想的数组循环链表，时间空间效率，都击败了接近100%的人
// 时间41ms，击败99.93%
// 内存162.94MB，击败99.76%


#define MAX_NODE 10002
#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    int val = -1;
    int pre = -1;
    int next = -1;
} nodes[MAX_NODE];

class LRUCache {
private:
    int size;
    int capacity;
    const int head = MAX_NODE - 1;

    inline void clear_node(int idx) {
        if (idx == head) return;
        nodes[idx].pre = -1;
        nodes[idx].next = -1;
    }

    inline void change_to_first(int idx) {
        nodes[nodes[idx].pre].next = nodes[idx].next;
        nodes[nodes[idx].next].pre = nodes[idx].pre;
        update_latest(idx);
    }

    inline void update_latest(int idx) {
        // do not update size here
        nodes[idx].next = nodes[head].next;
        nodes[nodes[head].next].pre = idx;

        nodes[idx].pre = head;
        nodes[head].next = idx;
    }

    inline void del_oldest() {
        // do not update size here
        int oldest = nodes[head].pre;
        nodes[nodes[oldest].pre].next = head;
        nodes[head].pre = nodes[oldest].pre;
        clear_node(oldest);
    }

    inline bool if_existed(int idx) {
        // check pre is ok -> clear_node function reset unused nodes
        // if existed before => pre != -1 => ~pre != 0 => ~pre
        // ps: ~-1 == 0 => key not existed
        return ~nodes[idx].pre;
    }

public:
    LRUCache(int capacity) {
        size = 0;
        this->capacity = capacity;
        //for (int i = 0; i <= MAX_NODE; i++) {
        //    nodes[i].val = -1;
        //    nodes[i].pre = -1;
        //    nodes[i].next = -1;
        //}
        //memset(nodes, -1, sizeof(Node) * capacity); // init all nodes!!!
        memset(nodes, -1, sizeof(nodes));
        nodes[head].pre = head; // set after init!!!
        nodes[head].next = head;
    }

    int get(int key) {
        cout << "get " << key << endl;
        if (if_existed(key)) {
            change_to_first(key);
        }
        print_list();
        return if_existed(key) ? nodes[key].val : -1;
    }

    void put(int key, int value) {
        cout << "put key: " << key << ",value: " << value << endl;
        // if existed before 
        if (if_existed(key)) {
            // size keep the same
            nodes[key].val = value;
            change_to_first(key);
        } // if not existed before
        else {
            if (size < capacity) {
                nodes[key].val = value;

                update_latest(key);

                size++;
            }
            else if (size == capacity) {
                del_oldest();
                nodes[key].val = value;
                update_latest(key);
            }
        }
        print_list();
    }

    void print_list() {
        cout << endl;
        int cur = head; 
        cout << "cur: " << cur << ", value: " << nodes[cur].val << ", pre: " << nodes[cur].pre << ", next: " << nodes[cur].next;
        cout << " -> " << endl;
        cur = nodes[cur].next;
        while (cur != head) {
            cout << "cur: " << cur << ", value: " << nodes[cur].val << ", pre: " << nodes[cur].pre << ", next: " << nodes[cur].next;
            cout << " -> " << endl;
            cur = nodes[cur].next;
        }
        cout << "null" << endl;
        cout << endl;
    }
};

int main() {
    LRUCache* lru = new LRUCache(2);

    for (int i = 0; i < 100; i++) {
        cout << nodes[i].val << " ";
    }

    lru->print_list();
    lru->put(1, 1);
    lru->put(2, 2);
    cout << lru->get(1) << endl;
    lru->put(3, 3);
    cout << lru->get(2) << endl;
    lru->put(4, 4);
    cout << lru->get(1) << endl;
    cout << lru->get(3) << endl;
    cout << lru->get(4) << endl;
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */