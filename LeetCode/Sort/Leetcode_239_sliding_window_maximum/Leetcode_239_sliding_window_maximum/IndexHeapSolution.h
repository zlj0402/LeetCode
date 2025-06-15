#ifndef INDEXHEAPSOLUTION_H
#define INDEXHEAPSOLUTION_H

#include <vector>
using std::vector;

#define MAXSIZE 100001

namespace zlj_heap {

	template<typename T>
	class IndexHeapSort {

	private:

		T* arr = nullptr;
		int ptr, k;				// ptr -> 窗口左端边界记录；k -> 窗口长度
		int indexes[MAXSIZE];	// indexes 的大小，只需要 max_size + 1 就可以了；indexes[i] 可以认为是 arr[] 中的元素的一个属性，标记其在 heap 中的位置，用户不需要知道；
		int heap[MAXSIZE];		// heap[] 中的位置，跟外部数据位置一一对应，heap[i] 为数据 i 在堆内的下标
		// 外部数据一一对应的话，外部数据一般都是从 idx 0 的位置开始，所以 heap[] 中我们不能从 idx 1 方便的位置开始了；
		int N;
		int size;	// 此 Case 能容纳的最大元素数量，但最大的时候，也跟 heap 的大小一样；

		bool (*Cmp) (T e1, T e2);

		static bool Cmp0(T e1, T e2) {
			return e1 < e2;
		}

		static bool Cmp1(T e1, T e2) {
			return e1 > e2;
		}

		IndexHeapSort() = default;

		IndexHeapSort& operator=(const IndexHeapSort&) = delete;
		IndexHeapSort(const IndexHeapSort&) = delete;;

		// idx 为 heap[] 中的 idx, 
		// heap[idx] 对应 arr[]/indexes[] 中某个元素的位置；
		// arr[heap[idx]] -> 是一个 arr[] 中的元素；
		void up(int idx) {
			
			int eIdx = heap[idx];
			T e = arr[eIdx];
			// maxHeap 的话，Cmp 为 Cmp0，父节点元素 < 子节点元素，则进行交换
			while (idx > 0 && Cmp(arr[heap[(idx - 1) >> 1]], e)) {

				heap[idx] = heap[(idx - 1) >> 1];
				indexes[heap[idx]] = idx;	// 调试了老半天，想起来 indexes 没有随之变化
				idx = (idx - 1) >> 1;
			}
			heap[idx] = eIdx;
			indexes[eIdx] = idx;
		}

		// idx 同 up 参数 idx;
		void down(int idx) {
			
			int eIdx = heap[idx];	// 原来错误的写法：int eIdx = indexes[idx];		// heap[] 里面存放的是 arr[] 中元素的下标，indexes[] 只是辅助找到元素在堆中对应的位置；
			T e = arr[eIdx];
			int child;	// child 的值是 heap[] 中的 idx，heap[child] 值 -> 是一个元素的下标
			// heap[] 中 N 为最后一个元素；
			while ((child = (idx << 1) + 1) <= N) {

				if (child < N && Cmp(arr[heap[child]], arr[heap[child + 1]])) ++child;
				if (Cmp(e, arr[heap[child]])) {

					heap[idx] = heap[child];	// 子节点上移
					indexes[heap[child]] = idx;
					idx = child;
				}
				else break;
			}
			heap[idx] = eIdx;
			indexes[eIdx] = idx;
		}

		// eIdx in arr[]
		void add(int eIdx) {

			++ptr;
			heap[++N] = eIdx;
			up(N);
		}

		// eIdx in arr[]
		void del(int eIdx) {

			--ptr;
			int idx = indexes[eIdx];
			swap(heap[idx], heap[N--]);
			up(idx);
			down(idx);
		}

	public:

		static IndexHeapSort& getInstance() {

			static IndexHeapSort ihs;
			return ihs;
		}

		// 单例，构造函数中不能赋值，只能在构造之后，函数赋值；
		void reset(T* arr, int n, bool maxHeap, int k) {

			this->arr = arr;
			size = n;
			N = -1;	// 为边界比较的时候（idx <= N / idx < N，而不是 idx < N / idx < N - 1）
			Cmp = maxHeap ? Cmp0 : Cmp1;
			ptr = -1 * k;	// 窗口左端边界
			this->k = k;

			for (int i = 0; i < k && i < n; ++i) 
				add(i);
		}

		// 返回一个 idx in arr[]/indexes[], from heap[0] top
		int move() {

			int hid = indexes[ptr];
			heap[hid] = ptr + k;	// 原来错误的写法：heap[hid] = ptr + k - 1; 窗口右端下一位，应该是 ptr + k 
			indexes[ptr + k] = hid;
 			up(hid);
			down(hid);
			++ptr;

			int ret = heap[0];

			if (ptr > size - k)
				ret = -1;

			return ret;
		}

		int getTop() {
			return heap[0];
		}
	};

	IndexHeapSort<int>& ihs = IndexHeapSort<int>::getInstance();

	class Solution {
	public:
		vector<int> maxSlidingWindow(vector<int>& nums, int k) {

			if (k == 1) return nums;

			vector<int> ret;
			int size = nums.size();

			ihs.reset(nums.data(), size, true, k);

			int idx = ihs.getTop();
			ret.push_back(nums[idx]);
			for (int i = 1; i <= size - k; i++) {

				idx = ihs.move();
				ret.push_back(nums[idx]);
			}

			return ret;
		}
	};
}

#endif	//INDEXHEAPSOLUTION_H