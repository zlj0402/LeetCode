/**
* Created by liangj.zhang on 19/3/2025
* 
* 构建哈希，就像以前答Samsung的题一样，手动构建就行；
* 最近学习了linux内核，想学习他当中的list的构建
* 
* condition：
*   最多调用 10^4 次 add、remove 和 contains
* 
* thought:
*   数组不用很大1000多就中 -- 似乎不太行，#define MAXHASH 77777都是超时
*   + 需要考虑到，一个key可能多次添加；或者冲突的时候，按从小到大排列
* 
* rank:
*   时间46ms仅战胜15.05%
*   存储103.29MB仅战胜8.2%
* 
* 虽然，效率没那么高，但也算是第一次用list_head的结构来完成的第一题；
*/

#include <iostream>
#include <stddef.h>
#define MAXHASH 1333
#define NULL 0
using namespace std;

#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) \
        list_head name = LIST_HEAD_INIT(name)
#define list_for_each(pos, head) \
        for (pos=(head)->next; pos != head; pos=pos->next)
#define list_entry(ptr, type, member) \
        ((type *)((char *)ptr - (unsigned long)(offsetof(type, member))))
 //       ((type *)((char *)ptr - (unsigned long)(&((type *)0)->member)))

#define SET_T_INIT(node, val) \
        { val, LIST_HEAD_INIT(node->st) }

struct list_head {
    list_head *prev, *next;
};

static inline void __list_add(list_head* new_node, list_head* prev, list_head* next) {
    new_node->next = next;
    next->prev = new_node;
    prev->next = new_node;      // 原来错误版：prev->next = next;
    new_node->prev = prev;
}

// add new_node after tar:  tar -> new_node
static inline void list_add(list_head* new_node, list_head* tar) {
    __list_add(new_node, tar, tar->next);
}

static inline void __list_del(list_head* prev, list_head* next) {
    next->prev = prev;
    prev->next = next;
}

static inline void list_del(list_head* entry) {
    __list_del(entry->prev, entry->next);
    entry->prev = NULL;
    entry->next = NULL;
}

struct set_t {
    int val;
    list_head st;
};

class MyHashSet {
public:
    list_head hashmap[MAXHASH];

    MyHashSet() {
        for (int i = 0; i < MAXHASH; i++)
        {
            hashmap[i] = LIST_HEAD_INIT(hashmap[i]);
        }
    }

    void add(int key) {
        if (contains(key)) 
            return;

        int h = key % MAXHASH;
        set_t* p;
        list_head* pos;
        pos = &hashmap[h];

        set_t* new_node = new set_t;
        *new_node = SET_T_INIT(new_node, key);

        if (pos == pos->next) {
            list_add(&new_node->st, &hashmap[h]);
            return;
        }

        list_for_each(pos, &hashmap[h]) 
        {
            if (pos->next == &hashmap[h])
                list_add(&new_node->st, &hashmap[h]);

            p = list_entry(pos, set_t, st);
            if (key < p->val) {
                list_add(&new_node->st, pos->prev);
            }
        }
    }
    /**
            set_t* new_node = new set_t;
            *new_node = SET_T_INIT(new_node, key);
            //new_node->val = key;
            //new_node->st = LIST_HEAD_INIT(new_node->st);
            //if (hashmap[h].next == &hashmap[h]) {
            //    new_node->st.next = &hashmap[h];
            //    hashmap[h].prev = &new_node->st;

            //    new_node->st.prev = &hashmap[h];
            //    hashmap[h].next = &new_node->st;
            //}
    */

    void remove(int key) {
        if (!contains(key))
            return;

        int h = key % MAXHASH;
        set_t* p;
        list_head* pos;
        list_for_each(pos, &hashmap[h])
        {
            p = list_entry(pos, set_t, st);
            if (p->val == key) {
                list_del(pos);
                delete(p);
                return;
            }
        }
    }

    bool contains(int key) {
        bool flag = false;
        int h = key % MAXHASH;
        set_t* p;
        list_head* pos;

        if (hashmap[h].next == &hashmap[h])
            return flag;

        list_for_each(pos, &hashmap[h])
        {
            p = list_entry(pos, set_t, st);
            if (p->val > key)
                break;
            else if (p->val == key) {
                flag = true;
                break;
            }
        }

        return flag;
    }
};

int main(int argc, char* argv[])
{
    MyHashSet myHashSet = MyHashSet();
    myHashSet.add(1);      // set = [1]
    myHashSet.add(2);      // set = [1, 2]
    cout << "myHashSet.contains(1): " << myHashSet.contains(1) << endl; // 返回 True
    cout << "myHashSet.contains(3): " << myHashSet.contains(3) << endl; // 返回 False ，（未找到）
    myHashSet.add(2);      // set = [1, 2]
    cout << "myHashSet.contains(2): " << myHashSet.contains(2) << endl; // 返回 True
    myHashSet.remove(2);   // set = [1]
    cout << "myHashSet.contains(2): " << myHashSet.contains(2) << endl; // 返回 False ，（已移除）
}