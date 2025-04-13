#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:

    void insertionSort(vector<int>& num, int l, int r) {
        
        for (int i = l + 1; i <= r; i++) {

            int j = i;
            int e = num[i];
            for (; j > l && e < num[j - 1]; j--)
                num[j] = num[j - 1];
            num[j] = e;
        }
    }

    // [l, mid] & [mid+1, r]
    void merge(vector<int>& num, int l, int mid, int r) {
        
        vector<int> tmp(r - l + 1);
        for (int i = l; i <= r; i++)
            tmp[i - l] = num[i];

        int i = 0;
        int j = mid - l + 1;
        for (int k = l; k <= r; k++) {
            
            if (j > r - l)
                num[k] = tmp[i++];
            else if (i > mid - l)
                num[k] = tmp[j++];
            else if (tmp[i] < tmp[j])
                num[k] = tmp[i++];
            else
                num[k] = tmp[j++];
        }
        tmp = vector<int>();
    }

    void mergeSort(vector<int>& num, int l, int r) {
        
        //if (l >= r)
        //    return;
        if (r - l <= 15) {
            insertionSort(num, l, r);
            return;
        }

        int mid = (l + r) / 2;
        mergeSort(num, l, mid);
        mergeSort(num, mid + 1, r);
        if (num.at(mid) > num.at(mid + 1))
            merge(num, l, mid, r);
    }

    vector<int>& sortArray(vector<int>& nums) {
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }
};

int main() {

    vector<int> nums = { -4,0,7,4,9,-5,-1,0,-7,-1 };
    vector<int> ret = (new Solution())->sortArray(nums);
    for (auto& i : ret)
        cout << i << " ";
    cout << endl;
}