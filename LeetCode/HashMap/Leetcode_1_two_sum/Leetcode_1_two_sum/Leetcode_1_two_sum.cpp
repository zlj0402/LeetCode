//
// Created by liangj.zhang on 10/6/2025
// 
// URL: https://leetcode.cn/problems/two-sum/description/
//
// 这是我在面试完吉利外包之后，重新写的这道题；
// 
// 回顾面试：
// + 当时面试说到 unordered_map 和 map 的区别；提到了底层上的不同，hash 实现的 unordered_map
// + 随后就让做了 leetcode 上这题，两数之和；
// + 打开 leetcode 时，这道题已经是写过的；结合当时自己写的，可以知道以前也是用的 O(n^2) 的做法做的；
// 
// 思路：
//  1. 面试时 和 以前第一次写的思路 O(n^2)：
//      + 就是两层遍历；因为做多也就一万个数，时间上不会慢道离谱；
// 
//  2. 面试之后，回想面试官的提示，用 hash，当时一时半会没想起来，第一反应的 hash 做法；
//      + 用 unordered_map 遍历一次，将所有数都记录下来；
//      + 后面，再遍历一遍，查找 target - rec[i] 的时候，每次只用 O(1) 的时间，也挺快的；
//      + 似乎是可行的，当时写完，发现要考虑 >>>>>> 存在相同数的时候 <<<<<<
//      + 我将原来记录的 um<int, int> rec; // <val, idx> 改为了 um<int, vector<int>> rec; // <val, vector<idx>>
//      + 当 target - x.first 的时候，如果 target == ((target - x.first) << 1)，那么就是特殊情况，两值相等，
//      + 所以，ret 先 push_back(rec[x][0]); 后面根据是相等的 x.first 和 不是 x.first 两种情况;
//      + 理论上完全是没有问题的，但是在网页编译器上运行的时候，报了错误堆溢出的错误，似乎是将我代码插入后，系统补充的代码部分出了问题（因为报的代码行数，略大于我写的所有代码行数）；
//      + ERROR: AddressSanitizer: heap-buffer-overflow on address 0x5020000850d4 at pc 0x5619cbf7ea2d bp 0x7ffcd0bc8c10 sp 0x7ffcd0bc8c08
//                  READ of size 4 at 0x5020000850d4 thread T0
// 
//  3. 排名靠前的做法：
//      + 在边插入的时候，就来查找另一半，插入完之前，肯定能找到另一半；
//      + 所以，整个过程就是 O(n)；不用两遍 O(n);
//      + 比上面第 2 中方式还要快；
// 
// rank:
//  时间效率：3 ms, 击败 77.02%
//  空间效率：14.51MB, 击败 53.01%
//

#include <iostream>

#include <vector>
#include <unordered_map>
#define um unordered_map

using std::vector;
using std::unordered_map;

// 思路 1
/*
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        vector<int> ret;

        bool find = false;

        for (int i = 0; i < nums.size(); i++) {

            for (int j = i + 1; j < nums.size(); j++) {

                if (nums[i] + nums[j] == target) {

                    ret.push_back(i);
                    ret.push_back(j);
                    find = true;
                    break;
                }
            }

            if (find)
                break;
        }

        return ret;
    }
};
*/

// 思路 2
/*
class Solution {

private:
    um<int, vector<int>> rec;

public:
    vector<int> twoSum(vector<int>& nums, int target) {

        rec.clear();

        for (int i = 0; i < nums.size(); i++) {

            rec[nums[i]].push_back(i);
        }

        vector<int> ret;
        for (auto x : rec) {

            int y = target - x.first;

            if (rec.find(y) != rec.end()) {

                ret.push_back(x.second[0]);
                if (x.first == y)
                    ret.push_back(x.second[1]);
                else
                    ret.push_back(rec[y][0]);
                return ret;
            }
        }

        return ret;
    }
};
*/

// 思路3
class Solution {

public:
    vector<int> twoSum(vector<int>& nums, int target) {

        um<int, int> rec;

        for (int i = 0; i < nums.size(); i++) {

            int y = target - nums[i];
            if (rec.find(y) != rec.end())
                return { rec[y], i };

            rec[nums[i]] = i;
        }

        return {};
    }

};

int main() {

    vector<int> nums{ 2,7,11,15 };

    vector<int> ret = (new Solution())->twoSum(nums, 9);

    std::cout << ret[0] << " " << ret[1] << std::endl;
}
