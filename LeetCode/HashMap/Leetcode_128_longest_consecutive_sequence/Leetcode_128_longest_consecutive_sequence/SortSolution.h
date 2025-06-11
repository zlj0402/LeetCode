#ifndef SORTSOLUTION_H
#define SORTSOLUTION_H

#include <ctime>
#include <vector>

using std::vector;

namespace zlj_sort {

    template<typename T>
    void swap(T& lhs, T& rhs) {

        T tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }

    // ¡¾1¡¿
    template<typename T>
    int __partition(T arr[], int l, int r) {

        swap(arr[l], arr[rand() % (r - l + 1) + l]);
        T v = arr[l];

        int i = l + 1;
        int j = r;

        while (1) {

            while (i <= r && arr[i] < v) i++;
            while (j >= l + 1 && arr[j] > v) j--;
            if (i >= j)
                break;
            swap(arr[i++], arr[j--]);
        }
        swap(arr[l], arr[j]);

        return j;
    }

    template<typename T>
    void __quickSort(T arr[], int l, int r) {

        if (l > r)
            return;

        int p = __partition(arr, l, r);
        __quickSort(arr, l, p - 1);
        __quickSort(arr, p + 1, r);
    }

    template<typename T>
    void quickSort(T arr[], int n) {
        srand(time(nullptr));
        __quickSort(arr, 0, n - 1);
    }

    class Solution {
    public:
        int longestConsecutive(vector<int>& nums) {

            if (nums.size() == 0) return 0;

            quickSort(nums.data(), nums.size());

            int cnt = 1;
            int max_cnt = 1;
            for (int i = 1; i < nums.size(); i++) {

                if (nums[i - 1] == nums[i] - 1) {

                    cnt += 1;
                    if (cnt > max_cnt)
                        max_cnt = cnt;
                }
                else if (nums[i - 1] == nums[i]) {
                    continue;
                }
                else {
                    cnt = 1;
                }
            }

            return max_cnt;
        }
    };
}

#endif  //SORTSOLUTION_H