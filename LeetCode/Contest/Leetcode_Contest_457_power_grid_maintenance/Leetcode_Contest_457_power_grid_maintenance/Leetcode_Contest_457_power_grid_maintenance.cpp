/**
* @brief: Leetcode_3607_电网维护
* @link: https://leetcode.cn/problems/power-grid-maintenance/description/
* @author: liangj.zhang 
* @date: 6/7/2025
* 
* @Difficulty: Medium
* 
* @Label: UnionFind + priority_queue/heap、 DFS + priority_queue/heap
* 
* @Again(worthy 0~5): 5
* 
* @brief content: 先维护一个分组（可以通过图求连通分量的过程、也可以是并查集的过程），
*       + [1] 操作，如果电站在线，可以直接返回，如果电站不在线，去每个组当中找到 id 最小的在线电站；
*       + [2] 操作，将值 id 的电站离线；
* 
* @thoughts：
*       + 感想，这题有一点，以前在三星考 Pro 的感觉了；1. 多个算法一起考（当然，这题的堆，可以直接用 priority_queue）；2. 边改变状态，边进行一次小耗时的操作，然后多次调用；
*       + 这是今天周赛 457 上的 Q2；没有提交上，只做出了第一道题 Q1；
* 
*       【0】DFS
*           第一眼以为，只要连通分量的方式求出分组，后面都好说；后面到每个分组，每个遍历一点，记录： 在线 & 最小 id 的电站（可以在初始化时完成连通分量的分组，就对每组进行排序，当时我这样都没有进行）；
*           作为第一种方式，自己在答题中，对于做题来说，过度构建了，没能让数据结构尽量简单，所以后面的 【2】【3】【4】，自己都标了 结构精简版；
* 
*           这种算法可称赞的点，只有连通分量的点；以这种方式，勉强以最末尾的时间效率，提交通过；(去看了一眼，提交记录，没有通过，这种方式 662 / 671 的位置，就超时了)
*           分析：
*               时间效率：
*                   + 初始化：O(N)，
*                   + queries: [2] 操作，最糟糕的情况：O(q * O(N))，q 是 vector<vector<int>>& queries.size()
*               空间效率：O(N)，就是常数有点大；最糟糕，也能是 O(N^2)
*                   + 有 visited -> O(N)，
*                   + um<int, PowerSta> ps 电站的id & 状态 -> O(N) * 2
*                   + um<int, vector<int>> vertexes; 稀疏图的记录关联 -> 最差 O(N^2)
*           rank: 超时；
* 
*       【1】DFS + priority_queue -- 此次，写法，也是继承 【1】，结构过度复杂
*           看了灵神的题解，认识到后半部，对分组有个合适的结构进行排序，是有必要的；因为：1 <= queries.length <= 2 * 105 -> 能调用达到 20万次；
*           + 以 DFS 的方式分组；
*           + priority_queue 的方式进行维护：
*               虽然状态改变的电站在 priority_queue 当中不能立即删除；
*               但，能在后续想要得到堆顶的电站的过程中，进行 pop()，知道 堆不为空 & 堆顶是一个在线电站为止；
*           
*           分析：
*               时间效率：
*                   + 初始化：进行 init -> O(N); + 关系绑定 -> O(c), c 为 connection 的 size; + 连通分量 O(N)  ==> 最终为 O(N)，常数大
*                   + queries: 每次 [2] 操作，最好 -> O(1)，最差总共 O(h * logh), h 为堆中的元素个数：0 <= h <= N 
*               空间效率：O(N)，就是常数大，最糟糕，接近 O(N^2)，因为点与点之间的关系多，达到稠密图的程度；
*                   
*           rank:
*               时间效率：424 ms, 击败 35.63%
*               空间效率：417.07 MB, 击败 14.65%
* 
*           这种写法中，最大的收获是，学会了在 priority_queue 当中实现自定义类指针的比较；之前还想特意多练练 STL 库，尤其 priority_queue 的机会不多；
* 
*       【2】dfs + set -- 精简结构版
*           + DFS 的方式进行分组；
*           + set 的方式进行维护：[2] 操作时，直接获得第一个元素；[1] 操作时，set<int> 中可以直接删除掉 offline 的电站；
* 
*           分析：
*               时间效率：
*                   + 初始化：和之前差不多，不过 set<int> 的每次插入是 O(logh), h 是每一组的元素个数；1 <= h <= N
*                   + queries:
*                       + [1] 操作：O(1)，直接得到第一个元素；
*                       + [2] 操作：直接操作对象是 offline 的电站 -> 从 set<int> 中，每次删掉元素时 O(logh), h 是每一组的元素个数；1 <= h <= N
*               空间效率：O(N)，最坏 O(N^2)，跟上面一样；
* 
*           rank:
*               时间效率：551 ms, 击败 22.98%
*               空间效率：433.08 MB, 击败 12.64%
* 
*       【3】dfs + priority_queue -- 精简结构版
*           相比 【1】 减少了一些不必要的结构；
*           + DFS 的方式进行分组；
*           + priority_queue 的方式进行维护
* 
*           分析：同 【1】 差不多吧，毕竟是一个思路，只不过结构简化了一下；
* 
*           rank:
*               时间效率：436 ms, 击败 33.62%
*               空间效率：403.30 MB, 击败 17.52%
* 
*       【4】UnionFind + priority_queue -- 精简结构版 -- 最好的解法
*           + 并查集的方式进行分组：先完成并查集，在从 [1, c] 遍历一遍，记录他们属于哪个 group；
*           + priority_queue 记录属于哪个组；
*           
*           分析：
*               时间复杂度：
*                   + 初始化阶段：UF 的构建 O(N) 并查集初始化； + O(c) 的遍历，c 是参数 connections 的 size；+ O(N) group 的统计； ==> 总的是 O(n)
*                   + queries:
*                       + [1] 操作：（才发现上面总结的，有时候将操作 1 和 2 弄反了）：最快 O(1)，最坏 O(logh), h 是每一组的元素个数；1 <= h <= N
*                       + [2] 操作：O(1)
*               空间复杂度：O(N) -> 这是明显提升的地方；不用像图一样，记录关系，最坏是 O(N^2);
*           
*           rank:
*               时间效率：104 ms, 击败 95.4%
*               空间效率：308.29 MB, 击败 95.11%
*           
*           summary: 和 【3】 的差别，除了空间效率上，时间上，其实是 dfs 每种情况都会进行判断，尽管只有 O(N) 进入判断的分支，但是判断却经历了 O(N^2)
*                       N 最多是 10万，即使一个 case，也会增加不少时间
*/


#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;


// 【4】并查集 + priority_queue -- 精简结构版
#include <unordered_map>
#include <queue>
#include <functional>
using std::unordered_map;
using std::priority_queue;
using std::greater;
#define um unordered_map
#define pq priority_queue
#define MAXSTATION 100001


class UnionFind {

private:
    static int rank[MAXSTATION];
    static int parent[MAXSTATION];

public:
    UnionFind(int c, vector<vector<int>>& con) {

        for (int i = 1; i <= c; ++i) {

            parent[i] = i;
            rank[i] = 1;
        }

        for (int i = 0; i < con.size(); ++i) {

            int p = con[i][0];
            int q = con[i][1];
            unionElements(p, q);
        }
    }

    int find(int p) {

        if (parent[p] != p)
            parent[p] = find(parent[p]);

        return parent[p];
    }

    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    void unionElements(int p, int q) {

        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot)
            return;

        if (rank[pRoot] < rank[qRoot])
            parent[pRoot] = qRoot;
        else if (rank[pRoot] > rank[qRoot])
            parent[qRoot] = pRoot;
        else {
            ++rank[qRoot];
            parent[pRoot] = qRoot;
        }
    }
};

int UnionFind::parent[MAXSTATION] = {};
int UnionFind::rank[MAXSTATION] = {};

class Solution {
private:
    //UnionFind* uf;
    static bool online[MAXSTATION];
    //um<int, pq<int, vector<int>, greater<>>> groups;

public:
    vector<int> processQueries(int c, vector<vector<int>>& conn, vector<vector<int>>& queries) {

        //uf = new UnionFind(c, conn);
        UnionFind uf(c, conn);  // 避免使用动态分配内存
        vector<pq<int, vector<int>, greater<>>> groups(c + 1);  // 数组直接访问，跳过哈希、无冲突，速度极快; 这里直接申请足够多的位置，后面避免扩容
        for (int i = 1; i <= c; ++i) {

            int g = uf.find(i);
            groups[g].push(i);
            online[i] = true;
        }

        vector<int> ans;
        for (auto& it : queries) {

            int ops = it[0];
            int id = it[1];

            if (ops == 1) {

                if (online[id]) {

                    ans.push_back(id);
                    continue;
                }

                int g = uf.find(id);

                int ret = -1;
                while (!groups[g].empty() && !online[groups[g].top()])
                    groups[g].pop();

                if (!groups[g].empty())
                    ret = groups[g].top();
                
                ans.push_back(ret);
            }
            else if (ops == 2) {

                online[id] = false;
            }
        }

        return ans;
    }
};
bool Solution::online[MAXSTATION];

// 【3】dfs + priority_queue -- 精简结构版
/*
#include <unordered_map>
#include <functional>
#include <queue>
#define MAXSTATION 100001

using std::unordered_map;
using std::priority_queue;
#define um unordered_map
#define pq priority_queue

class Graph {
private:
    um<int, vector<int>> vertexes;
    int count;

    void init(int c) {

        for (int i = 1; i <= c; ++i) {

            visited[i] = false;
            //concom[i] = count;  // dfs 时会分组
            vertexes[i] = vector<int>();
        }
    }

    void dfs(int id, pq<int, vector<int>, greater<>>* heap) {

        for (auto& next_id : vertexes[id]) {

            if (!visited[next_id]) {

                visited[next_id] = true;
                (*heap).push(next_id);
                concom[next_id] = count;

                dfs(next_id, heap);
            }
        }
    }

public:
    static bool visited[MAXSTATION];
    static int concom[MAXSTATION];  // connected component: 连通分量 record
    um<int, pq<int, vector<int>, greater<>>> heap;    // count, heap

    Graph() {}


    Graph(int c, vector<vector<int>> con) {

        init(c);

        for (int i = 0; i < con.size(); ++i) {

            int a = con[i][0];
            int b = con[i][1];
            vertexes[a].push_back(b);
            vertexes[b].push_back(a);
        }

        count = -1;
        for (int i = 1; i <= c; ++i) {

            if (!visited[i]) {

                ++count;

                visited[i] = true;
                heap[count].push(i);
                concom[i] = count;

                dfs(i, &heap[count]);
            }
        }
    }

    int queires(int id) {

        if (visited[id])    // visited 二次利用，初始时，每个节点都会由 dfs 从 false 置为 true，表示访问过；后续作为是否在线，正好每一个电站，初始化时，都是在线状态；
            return id;

        // else
        int count = concom[id];

        int ret = -1;
        while (!heap[count].empty() && !visited[heap[count].top()]) 
                heap[count].pop();
        
        if (!heap[count].empty())
            ret = heap[count].top();

        return heap[count].size() == 0 ? -1 : ret;
    }

    void offline(int id) {

        visited[id] = false;
    }
};

bool Graph::visited[MAXSTATION] = {};
int Graph::concom[MAXSTATION] = {};


class Solution {
private:
    Graph* graph;

public:

    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {

        // 原来错误的写法，graph = Graph(c, connections); 
        // 在最初的写法中，还有动态分配的内存，这时候这样写很致命，Graph(c, connections) 是临时变量，地址虽然能复制过去，但是析构后的动态内存已经失效；
        graph = new Graph(c, connections);

        vector<int> ans;

        for (auto& query : queries) {

            int opr = query[0];
            int id = query[1];

            if (opr == 1) {

                int ret = graph->queires(id);
                ans.push_back(ret);
            }
            else if (opr == 2) {

                graph->offline(id);
            }
        }

        return ans;
    }
};*/

// 【2】dfs + set -- 精简结构版
/*
#include <unordered_map>
#include <set>
#define MAXSTATION 100001

using std::unordered_map;
using std::set;
#define um unordered_map

class Graph {
private:
    um<int, vector<int>> vertexes;
    int count;

    void init(int c) {

        for (int i = 1; i <= c; ++i) {

            visited[i] = false;
            //concom[i] = count;  // dfs 时会分组
            vertexes[i] = vector<int>();
        }
    }

    void dfs(int id, set<int>* heap) {

        for (auto& next_id : vertexes[id]) {

            if (!visited[next_id]) {

                visited[next_id] = true;
                (*heap).insert(next_id);
                concom[next_id] = count;

                dfs(next_id, heap);
            }
        }
    }

public:
    static bool visited[MAXSTATION];
    static int concom[MAXSTATION];  // connected component: 连通分量 record
    um<int, set<int>> heap;    // count, heap

    Graph() {}


    Graph(int c, vector<vector<int>> con) {

        init(c);

        for (int i = 0; i < con.size(); ++i) {

            int a = con[i][0];
            int b = con[i][1];
            vertexes[a].push_back(b);
            vertexes[b].push_back(a);
        }

        count = -1;
        for (int i = 1; i <= c; ++i) {

            if (!visited[i]) {

                ++count;

                visited[i] = true;
                heap[count].insert(i);
                concom[i] = count;

                dfs(i, &heap[count]);
            }
        }
    }

    int queires(int id) {

        if (visited[id])    // visited 二次利用，初始时，每个节点都会由 dfs 从 false 置为 true，表示访问过；后续作为是否在线，正好每一个电站，初始化时，都是在线状态；
            return id;

        // else
        int count = concom[id];

        int ret = -1;
        if (!heap[count].empty())
            ret = *heap[count].begin();

        return ret;
    }

    void offline(int id) {

        int count = concom[id];
        auto it = heap[count].find(id);

        if (visited[id] && it != heap[count].end())
            heap[count].erase(id);

        visited[id] = false;
    }
};

bool Graph::visited[MAXSTATION] = {};
int Graph::concom[MAXSTATION] = {};


class Solution {
private:
    Graph* graph;

public:

    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {

        // 原来错误的写法，graph = Graph(c, connections); 
        // 在最初的写法中，还有动态分配的内存，这时候这样写很致命，Graph(c, connections) 是临时变量，地址虽然能复制过去，但是析构后的动态内存已经失效；
        graph = new Graph(c, connections);  

        vector<int> ans;

        for (auto& query : queries) {

            int opr = query[0];
            int id = query[1];

            if (opr == 1) {

                int ret = graph->queires(id);
                ans.push_back(ret);
            }
            else if (opr == 2) {

                graph->offline(id);
            }
        }

        return ans;
    }
};*/

// 【1】dfs + priority_queue
/*
#include <unordered_map>
#include <queue>
#define MAXSTATION 100001

using std::unordered_map;
using std::priority_queue;
#define um unordered_map
#define pq priority_queue

class PowerSta {

public:
    int id;
    bool active; 
    int count;

    PowerSta() {}

    PowerSta(int id) : id(id), active(true) {}
};

struct Cmp {

    bool operator() (const PowerSta* a, const PowerSta* b) const {
        return a->id > b->id;
    }
};

class Graph {
private:
    static um<int, vector<int>> vertexes;
    static bool visited[MAXSTATION];
    static um<int, pq<PowerSta*, vector<PowerSta*>, Cmp>> heap;    // count, heap
    int count;

    void init(int c) {

        vertexes.clear();
        heap.clear();

        for (int i = 1; i <= c; ++i) {

            visited[i] = false;

            ps[i].active = true;
            ps[i].id = i;

            vertexes[i] = vector<int>();
        }
    }

public:
    static PowerSta ps[MAXSTATION];

    Graph() {}


    Graph(int c, vector<vector<int>> connections) {

        init(c);

        for (int i = 0; i < connections.size(); ++i) {

            int a = connections[i][0];
            int b = connections[i][1];
            vertexes[a].push_back(b);
            vertexes[b].push_back(a);
        }

        memset(visited, 0, c + 1);

        count = -1;
        for (int i = 1; i <= c; ++i) {

            if (!visited[i]) {

                ++count;

                visited[i] = true;
                ps[i].count = count;
                heap[count].push(&ps[i]);

                dfs(i, &heap[count]);
            }
        }
    }

    void dfs(int id, pq<PowerSta*, vector<PowerSta*>, Cmp>* heap) {

        for (auto& next_id : vertexes[id]) {

            if (!visited[next_id]) {

                visited[next_id] = true;
                ps[next_id].count = count;
                (*heap).push(&ps[next_id]);

                dfs(next_id, heap);
            }
        }
    }

    int queires(int id) {

        if (ps[id].active)
            return id;

        // else
        int count = ps[id].count;
        while (!heap[count].empty() && !(heap[count].top()->active))
            heap[count].pop();

        return heap[count].size() == 0 ? -1 : (*(heap[count].top())).id;
    }
};

um<int, vector<int>> Graph::vertexes = {};
bool Graph::visited[MAXSTATION] = {};
um<int, pq<PowerSta*, vector<PowerSta*>, Cmp>> Graph::heap = {};
PowerSta Graph::ps[MAXSTATION] = {};


class Solution {
private:
    Graph* graph;

    void offline(int id) {

        graph->ps[id].active = false;
    }
public:

    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {

        graph = new Graph(c, connections);

        vector<int> ans;

        for (auto& query : queries) {

            int opr = query[0];
            int id = query[1];

            if (opr == 1) {

                int ret = graph->queires(id);
                ans.push_back(ret);
            }
            else if (opr == 2) {

                offline(id);
            }
        }

        return ans;
    }
}; 
*/

// 【0】DFS
/*
#include <unordered_map>

using std::unordered_map;
#define um unordered_map

class PowerSta {

public:
    int id;
    bool active;

    PowerSta() {}

    PowerSta(int id) : id(id), active(true) {

    }
};

class Graph {
private:
    um<int, vector<int>> vertexes;
    um<int, bool> visited;  // id, visited
    int query_ret;

public:
    um<int, PowerSta> ps;

    Graph() {}

    Graph(int c, vector<vector<int>> connections) {

        for (int i = 1; i <= c; ++i) {

            ps[i].id = i;
            ps[i].active = true;
            vertexes[i] = vector<int>();
        }

        for (int i = 0; i < connections.size(); ++i) {

            int a = connections[i][0];
            int b = connections[i][1];
            vertexes[a].push_back(b);
            vertexes[b].push_back(a);
        }
    }

    void dfs(int id) {

        for (auto& next_id : vertexes[id]) {

            if (!visited[next_id] && ps[next_id].active) {
                if (query_ret > next_id)
                    query_ret = next_id;
            }
            if (!visited[next_id]) {

                visited[next_id] = true;
                dfs(next_id);
            }
        }
    }

    int queires(int id) {

        visited.clear();
        query_ret = ps.size() + 1;

        for (auto& e : vertexes)
            visited[e.first] = false;

        if (ps[id].active)
            return id;

        // else
        visited[id] = true;
        dfs(id);

        return query_ret == ps.size() + 1 ? -1 : query_ret;
    }
};

class Solution {
private:
    Graph graph;

    void offline(int id) {

        graph.ps[id].active = false;
    }
public:

    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {

        graph = Graph(c, connections);

        vector<int> ans;

        for (auto& query : queries) {

            int opr = query[0];
            int id = query[1];

            if (opr == 1) {

                int ret = graph.queires(id);
                ans.push_back(ret);
            }
            else if (opr == 2) {

                offline(id);
            }
        }

        return ans;
    }
};
*/

//int main() {
//
//    vector<vector<int>> connections = { {1,2}, {2,3}, {3,4}, {4,5} };
//    vector<vector<int>> quries = { {1,3} , {2,1}, {1,1}, {2,2},{1,2} };
//
//    vector<int> ans = (new Solution())->processQueries(5, connections, quries);
//
//    for (auto& e : ans)
//        cout << e << " ";
//    cout << endl;
//}

int main() {

    vector<vector<int>> connections = { {2, 1} };
    vector<vector<int>> quries = { {1,1},{1,2},{2,2},{2,1},{2,2},{2,2},{2,1},{1,1},{2,2},{2,1},{1,1},{2,1},{2,2},{1,1},{1,2},{1,1},{1,1},{2,1},{1,1},{2,2},{2,2},{2,1},{1,2},{2,2},{1,1},{2,1},{2,2},{2,2},{1,1},{2,2} };

    vector<int> ans = (new Solution())->processQueries(2, connections, quries);

    for (auto& e : ans)
        cout << e << " ";
    cout << endl;
}