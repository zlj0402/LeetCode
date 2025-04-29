//
// Created by liangj.zhang on 29/4/2025
//

// 这题是看完 liuyubobobo 老师堆排那章之后的练习题
// 本次的方式，直接采用快排的方式，整体排好，再获得前 k 个值
// 本来，一开始想的是，利用快排的思想，每次获得第 k 个值，结果这种方式直接超时
// 不如直接排一遍来得快，甚至比堆排获取前 k 个值，还快一点

// rank 
// 时间 7 ms, 击败 61.52%
// 内存 23.05 MB, 击败 51.56%

// 对arr[l...r]部分进行快速排序
template<typename T>
void __quickSort4(T arr[], int l, int r) {

	if (l >= r)
		return;

	// partition
	// 随机在arr[l...r]的范围中, 选择一个数值作为标定点pivot
	swap(arr[l], arr[rand() % (r - l + 1) + l]);
	int v = arr[l];

	int lt = l;		// [l+1, lt] < v  after swap => [l, lt] < v
	int gt = r + 1;	// [gt, r] > v
	int i = lt + 1;	// [lt+1, i) == v

	while (i < gt) {

		if (arr[i] < v) {
			if (i != lt + 1)
				swap(arr[i], arr[lt + 1]);
			lt++;
			i++;
			//swap(arr[i++], arr[++lt]);	// 一步搞定
		}
		else if (arr[i] > v) {
			swap(arr[i], arr[gt - 1]);
			gt--;
			//swap(arr[i], arr[--gt]);	// 一步搞定
		}
		else {
			i++;
		}
	}

	swap(arr[l], arr[lt--]);

	__quickSort4(arr, l, lt);
	__quickSort4(arr, gt, r);
}

template<typename T>
void quickSort4(T arr[], int n) {

	srand(time(NULL));
	__quickSort4(arr, 0, n - 1);
}

class Solution {
public:
    vector<int> smallestK(vector<int>& arr, int k) {
        quickSort4(arr.data(), arr.size());
        vector<int> vec;
        for (int i = 0; i < k; i++)
            vec.push_back(arr[i]);
        return vec;
    }
};
