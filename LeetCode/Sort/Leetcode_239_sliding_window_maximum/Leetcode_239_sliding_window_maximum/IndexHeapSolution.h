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
		int ptr, k;				// ptr -> ������˱߽��¼��k -> ���ڳ���
		int indexes[MAXSIZE];	// indexes �Ĵ�С��ֻ��Ҫ max_size + 1 �Ϳ����ˣ�indexes[i] ������Ϊ�� arr[] �е�Ԫ�ص�һ�����ԣ�������� heap �е�λ�ã��û�����Ҫ֪����
		int heap[MAXSIZE];		// heap[] �е�λ�ã����ⲿ����λ��һһ��Ӧ��heap[i] Ϊ���� i �ڶ��ڵ��±�
		// �ⲿ����һһ��Ӧ�Ļ����ⲿ����һ�㶼�Ǵ� idx 0 ��λ�ÿ�ʼ������ heap[] �����ǲ��ܴ� idx 1 �����λ�ÿ�ʼ�ˣ�
		int N;
		int size;	// �� Case �����ɵ����Ԫ��������������ʱ��Ҳ�� heap �Ĵ�Сһ����

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

		// idx Ϊ heap[] �е� idx, 
		// heap[idx] ��Ӧ arr[]/indexes[] ��ĳ��Ԫ�ص�λ�ã�
		// arr[heap[idx]] -> ��һ�� arr[] �е�Ԫ�أ�
		void up(int idx) {
			
			int eIdx = heap[idx];
			T e = arr[eIdx];
			// maxHeap �Ļ���Cmp Ϊ Cmp0�����ڵ�Ԫ�� < �ӽڵ�Ԫ�أ�����н���
			while (idx > 0 && Cmp(arr[heap[(idx - 1) >> 1]], e)) {

				heap[idx] = heap[(idx - 1) >> 1];
				indexes[heap[idx]] = idx;	// �������ϰ��죬������ indexes û����֮�仯
				idx = (idx - 1) >> 1;
			}
			heap[idx] = eIdx;
			indexes[eIdx] = idx;
		}

		// idx ͬ up ���� idx;
		void down(int idx) {
			
			int eIdx = heap[idx];	// ԭ�������д����int eIdx = indexes[idx];		// heap[] �����ŵ��� arr[] ��Ԫ�ص��±꣬indexes[] ֻ�Ǹ����ҵ�Ԫ���ڶ��ж�Ӧ��λ�ã�
			T e = arr[eIdx];
			int child;	// child ��ֵ�� heap[] �е� idx��heap[child] ֵ -> ��һ��Ԫ�ص��±�
			// heap[] �� N Ϊ���һ��Ԫ�أ�
			while ((child = (idx << 1) + 1) <= N) {

				if (child < N && Cmp(arr[heap[child]], arr[heap[child + 1]])) ++child;
				if (Cmp(e, arr[heap[child]])) {

					heap[idx] = heap[child];	// �ӽڵ�����
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

		// ���������캯���в��ܸ�ֵ��ֻ���ڹ���֮�󣬺�����ֵ��
		void reset(T* arr, int n, bool maxHeap, int k) {

			this->arr = arr;
			size = n;
			N = -1;	// Ϊ�߽�Ƚϵ�ʱ��idx <= N / idx < N�������� idx < N / idx < N - 1��
			Cmp = maxHeap ? Cmp0 : Cmp1;
			ptr = -1 * k;	// ������˱߽�
			this->k = k;

			for (int i = 0; i < k && i < n; ++i) 
				add(i);
		}

		// ����һ�� idx in arr[]/indexes[], from heap[0] top
		int move() {

			int hid = indexes[ptr];
			heap[hid] = ptr + k;	// ԭ�������д����heap[hid] = ptr + k - 1; �����Ҷ���һλ��Ӧ���� ptr + k 
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