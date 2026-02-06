#include <vector>
#include <string>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::vector;
using std::string;

class Solution {
private:
    bool isValid(unsigned int& mask, string& s, string& res) {

        bool valid = true;
        int invalidIdx = 0;

        for (int i = 0; valid && i < s.size(); ++i) {
            ++invalidIdx;
            char c = s[i];
            res.push_back(c);
            unsigned int lastMask = mask;
        
            if ((mask ^= (1U << (c - 'a'))) < lastMask)
                valid = false;
        }

        if (valid) return true;

        delMask(mask, s, res, invalidIdx);
        return false;
    }

    void delMask(unsigned int& mask, string& s, string& res, int len) {

        for (int i = 0; i < len; ++i) {

            mask ^= (1U << (s[i] - 'a'));
            res.pop_back();
        }
    }
public:
    int maxLength(vector<string>& arr) {
        
        string res;
        size_t maxLen = 0;
        size_t size = arr.size();
        unsigned int mask = 0;

        std::function<void(int)> dfs = [&](int i) -> void {
        // auto dfs = [&](this auto&& dfs, int i) -> void {

            if (res.size() > maxLen) 
                maxLen = res.size();

            for (int j = i; j < size; ++j) {

                bool valid = isValid(mask, arr[j], res);
                dfs(j + 1);
                if (valid) delMask(mask, arr[j], res, arr[j].size());
            }
        };

        dfs(0);

        return maxLen;
    }
};

int main () {

    vector<string> arr = {"un","iq","ue"};
    Solution().maxLength(arr);
}

inline int countOnes(int num) {
    int cnt = 0;
    for (int i = 0; i < 26; ++i) cnt += ((num >> i) & 1);
    return cnt;
}

// inline bool check(int a, int b) {
//     if (a == 0 || b == 0) return 1;
//     for (int i = 0; i < 26; ++i) {
//         if (((a >> i) & 1) == 1 && ((b >> i) & 1) == 1) return 0;
//     }
//     return 1;
// }

int maxLen;
vector<int> mp;

void traceBack(int idx, int cur) {
    if (idx >= mp.size()) {
        maxLen = max(maxLen, countOnes(cur));
        return;
    }
    if ((cur & mp[idx])==0) {
        traceBack(idx + 1, cur | mp[idx]);
    }
    traceBack(idx + 1, cur);
}
class Solution {
public:
    int maxLength(vector<string>& arr) {
        mp.clear(); maxLen = 0;
        for (auto& s : arr) {
            if (s.size() > 26) continue;
            int tem = 0;
            bool valid = 1;
            for (char c : s) {
                if ((tem >> (c - 'a')) & 1) {
                    valid = 0; break;
                }
                tem |= (1 << (c - 'a'));
            }
            if (valid) mp.push_back(tem);
        }

        if (mp.empty()) return 0;
        if (mp.size() == 1) return countOnes(mp[0]);

        traceBack(0, 0);

        return maxLen;
    }
};