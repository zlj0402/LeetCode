#ifndef HASHSOLUTION_H
#define HASHSOLUTION_H

#include <unordered_set>
#include <vector>
#define us unordered_set

using std::unordered_set;
using std::vector;

namespace zlj_hash {

    // ¡¾2.2¡¿
    class Solution {

    public:
        int longestConsecutive(vector<int>& nums) {

            if (nums.size() == 0) return 0;

            vector<int> arr;

            us<int> rec = us<int>(nums.begin(), nums.end());

            int cnt = 1;
            int max_cnt = 1;

            while (!rec.empty()) {

                arr.clear();
                cnt = 1;

                int num = *rec.begin();

                int tmp = num;
                arr.push_back(tmp);

                while (1) {

                    if (rec.find(--tmp) != rec.end()) {

                        cnt++;
                        if (max_cnt < cnt)
                            max_cnt = cnt;
                        arr.push_back(tmp);
                    }
                    else
                        break;
                }

                tmp = num;
                while (1) {

                    if (rec.find(++tmp) != rec.end()) {

                        cnt++;
                        if (max_cnt < cnt)
                            max_cnt = cnt;
                        arr.push_back(tmp);
                    }
                    else
                        break;
                }

                for (auto& e : arr)
                    rec.erase(e);
            }


            return max_cnt;
        }
    };

    // ¡¾2.1¡¿
    /*
    #include <unordered_map>
    #define um unordered_map

    using std::unordered_map;

    class Solution {

    private:
        um<int, bool> rec;

    public:
        int longestConsecutive(vector<int>& nums) {

            if (nums.size() == 0) return 0;

            rec.clear();

            for (auto& num : nums) {

                rec.insert({num, false});
            }

            int cnt = 1;
            int max_cnt = 1;
            for (auto& item : rec) {

                int num = item.first;

                if (rec[num]) continue;

                rec[num] = true;

                cnt = 1;

                int tmp = num;
                while (1) {

                    if (rec.find(--tmp) != rec.end()) {

                        rec[tmp] = true;
                        cnt++;
                        if (cnt > max_cnt)
                            max_cnt = cnt;
                    }
                    else
                        break;
                }

                tmp = num;
                while (1) {

                    if (rec.find(++tmp) != rec.end()) {

                        rec[tmp] = true;
                        cnt++;
                        if (cnt > max_cnt)
                            max_cnt = cnt;
                    }
                    else
                        break;
                }
            }

            return max_cnt;
        }
    };
    */
}

#endif  //HASHSOLUTION_H