//
// Created by liangj.zhang on 27/4/2025
// updated on 27/4/2025: add quickSort way to solve topK issue
//

// >>>>>>>>>>>>>>>>>>>>> TopK -- The Kth number <<<<<<<<<<<<<<<<<<<<<<

template<typename T>
class TopK_QuickSort {

private:
	T* arr;
	int n;

	int k;
	T topK;
	bool find;

	static bool Cmp0(const T& e, const T& pivot) {
		return e < pivot;
	}

	static bool Cmp1(const T& e, const T& pivot) {
		return e > pivot;
	}

	bool (*lCmp)(const T& e, const T& pivot);

	bool (*rCmp)(const T& e, const T& pivot);

	void __quickSort(int l, int r);

	int __partition(int l, int r);

	void __quickSort3Ways(int l, int r);

public:

	TopK_QuickSort(T arr[], int n) : arr(arr), n(n), find(false), k(1), topK(T{}), lCmp(Cmp0), rCmp(Cmp1) { }

	T quickSort(int k, bool ascending);
};


template<typename T>
T TopK_QuickSort<T>::quickSort(int k, bool ascending) {

	srand(time(NULL));

	this->k = k - 1;	// ԭ�������д����k = k - 1;
	find = false;
	topK = T{};

	// ���� topK ������Сֵ; ���� topK �������ֵ;
	lCmp = ascending ? Cmp0 : Cmp1;
	rCmp = ascending ? Cmp1 : Cmp0;
	//__quickSort(0, n - 1);
	__quickSort3Ways(0, n - 1);

	return topK;
}

// >>>>>>>>>>>>>>>>>>>>> ����� + ˫·�������� <<<<<<<<<<<<<<<<<<<<<<<<

// ��arr[l...r]���ֽ��п�������
template<typename T>
void TopK_QuickSort<T>::__quickSort(int l, int r) {

	// ԭ�������д����if (l >= r); 
	// �� l �� r ֮��ֻ��һ��Ԫ��ʱ�������Ԫ��ǡ���ǵ� k ��λ�ã���ʱ�� return; find û�б���ǣ�topK Ҳû��ȡֵ; ��ʱ������Сʱ�ĵ��ԣ�����Ҫ����
	if (l > r) 
		return;

	int p = __partition(l, r);

	if (k < p) {
		__quickSort(l, p - 1);
	}
	else if (k > p)
		__quickSort(p + 1, r);
	else {
		topK = arr[p];
		find = true;
		return;
	}
}

// ˫·���������partition
// ��arr[l...r]���ֽ���partition����
// ����p, ʹ��arr[l+1...i] =< arr[p] ; arr[j...r] >= arr[p]
template<typename T>
int TopK_QuickSort<T>::__partition(int l, int r) {

	// �����arr[l...r]�ķ�Χ��, ѡ��һ����ֵ��Ϊ�궨��pivot
	swap(arr[l], arr[rand() % (r - l + 1) + l]);
	T v = arr[l];

	// arr[l+1...i) <= v; arr(j...r] >= v
	int i = l + 1, j = r;
	while (true) {

		while (i <= r && lCmp(arr[i], v)) i++;
		while (j >= l + 1 && rCmp(arr[j], v)) j--;
		if (i >= j) break;
		swap(arr[i++], arr[j--]);
	}
	swap(arr[l], arr[j]);	// swap(arr[l], arr[i]); ���п��ܸ�arr[r+1] -> arr[n - 1 + 1] -> arr[n]������;

	return j;
}

// >>>>>>>>>>>>>>>>>>>>> ����� + ��·�������� <<<<<<<<<<<<<<<<<<<<<<<<

// ��arr[l...r]���ֽ��п�������
template<typename T>
void TopK_QuickSort<T>::__quickSort3Ways(int l, int r) {

	if (l > r)	// ͬ 2Ways һ���Ĵ���д����if (l >= r)
		return;

	// partition
	// �����arr[l...r]�ķ�Χ��, ѡ��һ����ֵ��Ϊ�궨��pivot
	swap(arr[l], arr[rand() % (r - l + 1) + l]);
	int v = arr[l];

	int lt = l;		// [l+1, lt] < v  after swap => [l, lt] < v
	int gt = r + 1;	// [gt, r] > v
	int i = lt + 1;	// [lt+1, i) == v

	while (i < gt) {

		if (lCmp(arr[i], v)) {
			// �� [l, r] ֮�䣬Ԫ��û��һ���ظ��ģ�i ���һ�������� Cmp ����������ʱ lt �� i �����ڵģ�lt + 1 == i����û��Ҫ����
			// �˴��ܼ��� arr ����û���ظ�Ԫ��ʱ�Ľ�����ʱ����·���ţ�����������ͬԪ�ض��ʱ��Ч�����������ϴ˴��޸ģ���һ���治ͬԪ��ʱ��Ч��Ҳ�õ�������
			if (i != lt + 1)
				swap(arr[i], arr[lt + 1]);
			lt++;
			i++;
			//swap(arr[i++], arr[++lt]);	// һ���㶨
		}
		else if (arr[i] == v) {			// ԭ������д����else if (!Cmp(arr[i], v))�����Խ�������Ϊ������ > ��������ǰ��û���������ȡ�� Cmp �������ж���ʱ�� <������ ==������ == ���жϷ�ǰ�棬�ɱ���˴�����
			i++;
		}
		else {
			swap(arr[i], arr[gt - 1]);
			gt--;
			//swap(arr[i], arr[--gt]);	// һ���㶨
		}
	}

	swap(arr[l], arr[lt--]);

	if (k <= lt)
		__quickSort3Ways(l, lt);
	else if (k >= gt)
		__quickSort3Ways(gt, r);
	else {
		topK = arr[lt + 1];
		find = true;
		return;
	}
}
