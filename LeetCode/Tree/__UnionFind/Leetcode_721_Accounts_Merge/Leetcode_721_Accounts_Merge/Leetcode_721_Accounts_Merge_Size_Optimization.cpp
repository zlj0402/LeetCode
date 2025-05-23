//
// Created by liangj.zhang on 24/5/2025
//

// ˼·������ rank �Ż��� ѹ��·���� ���鼯
//      �����ҵ������ǣ�
//          1. ����ÿ�� account �е� email �˺�
//          2. �� unordered_map<email, vector<int>> ���洢һ�� email ��Ӧ�� account �� index;
//          3. ��������õ��� um<string, vector<int>>; ���鼯���� account 
//          4. ���� accounts �е�ÿ�� account, ���� find(account_index) �ҵ���ϵ���е� root => �õ�һ�� um<int, set<string>> ��ÿ�� email ���ᱻ���һ�顿
//          5. ���� um<int, set<string>>��ת���õ�һ�� vector<vector<string>>
//
// ps: д����ã�������ȫ���Բ��ã����� size ���Ż����� unionElements �У��ͽ��� email ���ռ���
// 
// rank:
// ʱ�䣺176 ms, ���� 8.17%
// �ռ䣺50.95 MB, ���� 7.73%
//


#include <iostream>
using std::cout;
using std::endl;

// --------------
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

#define um unordered_map

using std::vector;
using std::string;
using std::unordered_map;
using std::set;

class Solution {
private:
    int size;
    int* parent;
    int* Size;

    um<string, vector<int>> acc;
    um<int, set<string>> ret;

    bool isConnected(int p, int q) {

        return find(p) == find(q);
    }

    int find(int p) {

        if (p != parent[p])
            parent[p] = find(parent[p]);
        return parent[p];
    }

    void unionElements(int p, int q) {

        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot)
            return;

        if (Size[pRoot] < Size[qRoot]) {

            parent[pRoot] = qRoot;
            Size[qRoot] += Size[pRoot];

            ret[qRoot].insert(ret[pRoot].begin(), ret[pRoot].end());
            ret.erase(pRoot);
        }
        else {

            parent[qRoot] = pRoot;
            Size[pRoot] += Size[qRoot];

            ret[pRoot].insert(ret[qRoot].begin(), ret[qRoot].end());
            ret.erase(qRoot);
        }
    }

    //void printRelationship() {
    //    cout << "index: ";
    //    for (int i = 0; i < size; i++)
    //        cout << i << "\t";
    //    cout << endl;

    //    cout << "parent:";
    //    for (int i = 0; i < size; i++)
    //        cout << parent[i] << "\t";
    //    cout << endl;
    //}

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {

        // ��̬���� parent��rank
        size = accounts.size();
        parent = new int[size];
        Size = new int[size];

        // iterate
        int i = 0;
        for (auto it = accounts.begin(); it != accounts.end(); it++, i++) {

            parent[i] = i;
            Size[i] = 1;

            for (auto t = it->begin() + 1; t != it->end(); t++) {

                //cout << *t << " ";
                string email = *t;
                if (acc.count(email)) {
                    acc[email].push_back(i);
                }
                else {
                    acc[email] = vector<int>{ i };
                }
            }
            //cout << endl;

            ret[i] = set<string>(accounts.at(i).begin() + 1, accounts.at(i).end());
        }

        // union elements
        //cout << endl;
        for (auto it = acc.begin(); it != acc.end(); it++) {

            string email = it->first;
            int firstIdx = it->second[0];
            //cout << email << ": " << firstIdx << " ";
            for (size_t i = 1; i < it->second.size(); i++) {

                //cout << it->second.at(i) << " ";
                unionElements(firstIdx, it->second.at(i));
            }
            //cout << endl;
        }

        //printRelationship();

        vector<vector<string>> ret2;
        for (auto it : ret) {

            string name = *(accounts.at(it.first).begin());
            vector<string> tmp = vector<string>{ name };

            for (auto t : it.second) {
                tmp.push_back(t);
            }

            ret2.push_back(tmp);
        }

        // free parent��rank
        delete[] parent;
        delete[] Size;
        acc.clear();

        return ret2;
    }

};

int main() {

    //vector<vector<string>> accounts = {
    //    {"John", "johnsmith@mail.com", "john00@mail.com"},
    //    {"John", "johnnybravo@mail.com"},
    //    {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
    //    {"Mary", "mary@mail.com"}
    //};

    vector<vector<string>> accounts = {
        {"David", "David0@m.co", "David1@m.co"},
        {"David", "David3@m.co", "David4@m.co"},
        {"David", "David4@m.co", "David5@m.co"},
        {"David", "David2@m.co", "David3@m.co"},
        {"David", "David1@m.co", "David2@m.co"}
    };

    vector<vector<string>> ret = (new Solution())->accountsMerge(accounts);

    cout << endl;
    for (auto it : ret) {

        for (auto t : it)
            cout << t << " ";
        cout << endl;
    }

}