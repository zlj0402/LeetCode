#ifndef INDEXQUICKSORTSOLUTION_H
#define INDEXQUICKSORTSOLUTION_H

#include "SortTestHelper.h"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
using std::swap;

#include <ctime>

namespace zlj_kth_iqs {

    template<typename T>
    class IndexQuickSort {

    private:

        int k;
        int n;
        int start;
        int rank;
        T* arr = nullptr;;
        int* indexes = nullptr;;

        IndexQuickSort() = default;

        IndexQuickSort& operator=(const IndexQuickSort&) = delete;
        IndexQuickSort(const IndexQuickSort&) = delete;

        // ƫ���� [l, r]
        int partition(int l, int r) {

            swap(indexes[l], indexes[rand() % (r - l + 1) + l]);
            // indexes ��Ӧ������ʵ���±�
            T v = arr[indexes[l]];

            int i = l + 1;
            int j = r;
            while (true) {

                while (i <= j && arr[indexes[i]] < v) ++i;
                while (j >= i && arr[indexes[j]] > v) --j;
                if (i >= j) break;
                swap(indexes[i++], indexes[j--]);
            }
            swap(indexes[l], indexes[j]);

            // j -> ƫ����
            return j;
        }

        // ��ʵ�±� [l, r], ��ƫ����
        void quickSort(int l, int r) {

            if (l >= r)
                return;

            // partition ����ģ�Ӧ����ƫ������p Ҳ��ƫ������
            int p = partition(l - start, r - start);

            // rank Ҳ��ƫ���������λ [0, k - 1] -> k - 1
            // �ֶ����룬Ҫ����ȡ������� start Ϊ���� rank ƫ����, ҲӦ���ǽ��� [0, k - 1]
            if (p < rank)
                quickSort(p + start + 1, r);
            else
                quickSort(l, p + start - 1);
        }

    public:

        static IndexQuickSort& getInstance() {

            static IndexQuickSort iqs;
            return iqs;
        }

        // �ӳٹ��죬Ҳ�����ã�
        void reset(T* arr, int n, int k) {

            this->arr = arr;
            this->n = n;
            this->k = k;

            // �ͷž��������飨������ڣ�
            if (indexes) {
                delete[] indexes;
            }
            indexes = new int[k]; // ���·���
        }

        // get max value's index in [start, start + k - 1]
        int sort(int start) {

            if (!arr || !indexes) {

                // sort ֮ǰ��Ӧ���������ڲ����ݣ�
                //cout << "iqs' data inside not initialized" << endl;
                return -1;
            }

            srand(time(nullptr));

            this->start = start;
            rank = k - 1;

            for (int i = 0; i < k; ++i)
                indexes[i] = start + i;

            // [start, end]
            int end = start + k >= n ? n - 1 : start + k - 1;
            quickSort(start, end);

            return indexes[k - 1];
        }
    };

    IndexQuickSort<int>& iqs = IndexQuickSort<int>::getInstance();

    class Solution {
    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {

            if (k == 1) return nums;

            vector<int> ret;
            int size = nums.size();

            iqs.reset(nums.data(), size, k);
            int max_idx = iqs.sort(0);
            int max_num = nums[max_idx];
            ret.push_back(max_num);

            for (int i = 1; i < size - k + 1; ++i) {

                if (i > max_idx) {

                    max_idx = iqs.sort(i);
                    max_num = nums[max_idx];
                }
                else {
                    int new_idx = i + k - 1;
                    if (nums[new_idx] >= max_num) {

                        max_idx = new_idx;
                        max_num = nums[new_idx];
                    }
                }

                ret.push_back(max_num);
            }

            return ret;
        }
    };

    /*
    int main() {

        // ��֤���ŵ���ȷ��
        //int n = 15;
        //int* arr = SortTestHelper::generateRandomArray(n, 0, n);
        //SortTestHelper::printArray(arr, n);

        //int* arr1 = SortTestHelper::copyIntArray(arr, n);

        //int k = 10;
        //iqs.reset(arr1, n, k);

        //int max_idx = iqs.sort(0);
        //cout << "index: " << max_idx << endl;
        //cout << "value: " << arr1[max_idx] << endl;

        // -----------------------------------------------

        int n = 15;
        //int* arr = SortTestHelper::generateRandomArray(n, 0, n);
        //SortTestHelper::printArray(arr, n);

        //int* arr1 = SortTestHelper::copyIntArray(arr, n);

        int k = 3;

        //vector<int> nums2 = vector<int>(arr1, arr1 + n);
        vector<int> nums = { 11, 0, 2, 14, 2, 13, 3, 10, 13, 0 ,2, 7, 10, 11, 6 };
        for (auto& e : nums)
            cout << e << " ";
        cout << endl;

        vector<int> ret = (new Solution())->maxSlidingWindow(nums, k);
        for (auto& e : ret)
            cout << e << " ";
        cout << endl;
    }*/
}

#endif  //INDEXQUICKSORTSOLUTION_H