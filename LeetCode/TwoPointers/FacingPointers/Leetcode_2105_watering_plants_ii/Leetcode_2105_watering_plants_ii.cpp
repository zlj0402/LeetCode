/**
 * @brief: Leetcode_2105_给植物浇水_II
 * @link: https://leetcode.cn/problems/watering-plants-ii/description/
 * @author: liangj.zhang
 * @date: 2/9/2025
 * 
 * @Difficulty: Medium
 * 
 * @Label: Two Pointers(Facing)
 * 
 * @Retrospect(worthy 1 - 5): 2
 * 
 * @thoughts:
 *      就是简单的双指针，从两端遍历；
 *      水不够，就先填满，再扣除；记录下重新填满的次数就可以了；
 * 
 *      + 【思路 1】：相向双指针
 *          + 分析：
 *              + 时间复杂度：O(N)
 *              + 空间复杂度：O(1)
 * 
 *          + rank:
 *              + 时间效率：0 ms, 击败 100.00%
 *              + 空间效率：80.45 MB, 击败 11.77%
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Solution {

private:
    int refill_cnt;
    inline void watering(int &water_left, int& cost, int &capacity) {

        if (water_left < cost) {

            water_left = capacity;
            refill_cnt += 1;
        }
        water_left -= cost;
    }

public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        
        int l = 0;
        int r = plants.size() - 1;
        int cl = capacityA;
        int cr = capacityB;

        refill_cnt = 0;
        while (l <= r) {

            if (l == r) {

                if (cl >= cr) {
                    watering(cl, plants[l], capacityA);
                } else {
                    watering(cr, plants[r], capacityB);
                }
            } else {

                watering(cl, plants[l], capacityA);
                watering(cr, plants[r], capacityB);
            }
            ++l;
            --r;
        }

        return refill_cnt;
    }
};

int main() {

    // vector<int> plants{726,739,934,116,643,
    //                     648,473,984,482,85,
    //                     850,806,146,764,156,
    //                     66,186,339,985,237,
    //                     662,552,800,78,617,
    //                     933,481,652,796,594,
    //                     151,82,183,241,525,
    //                     221,951,732,799,483,
    //                     368,354,776,175,974,
    //                     187,913,842};
    vector<int> plants{2,2,3,3};
    int capacityA = 5;
    int capacityB = 5;

    Solution sol;

    cout << sol.minimumRefill(plants, capacityA, capacityB) << endl;
}