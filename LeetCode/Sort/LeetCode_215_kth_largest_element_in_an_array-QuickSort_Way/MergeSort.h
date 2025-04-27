//
// Created by liangj.zhang on 13/4/2025 last update: 24/4/2025
// update 15/4/2025: add mergeSortBU
// update 24/4/2025: recover mergeSort stable sort property
//

#include "InsertionSort.h"

// ��arr[l...mid]��arr[mid+1...r]�����ֽ��й鲢
template<typename T>
void __merge(T arr[], int l, int mid, int r) {

	T* tmp = new T[r - l + 1];		// ԭ�������д�� r - 1 + 1�ˣ�����l��������û���ճ����Լ�����ģ���֪��ʲôʱ��д����;
	for (int i = l; i <= r; i++)
		tmp[i - l] = arr[i];

	int i = 0;
	int j = mid - l + 1;
	for (int k = l; k <= r; k++) {

		// �����벿��Ԫ���Ѿ�ȫ���������
		if (i > mid - l) {			// ԭ�������д����i > mid
			arr[k] = tmp[j++];
		} // ����Ұ벿��Ԫ���Ѿ�ȫ���������
		else if (j > r - l) {		// ԭ�������д����j > r
			arr[k] = tmp[i++];
		} // ��벿����ָԪ�� < �Ұ벿����ָԪ��
		else if (tmp[i] <= tmp[j]) {	// ԭ��д����tmp[i] < tmp[j] => ���ʹ�ù鲢�����Ϊ���ȶ�������
			arr[k] = tmp[i++];
		} // ��벿����ָԪ�� >= �Ұ벿����ָԪ��
		else {
			arr[k] = tmp[j++];
		}
	}
	delete[] tmp;
}

// �ݹ�ʹ�ù鲢����,��arr[l...r]�ķ�Χ��������
template<typename T>
void __mergeSort(T arr[], int l, int r) {

	if (l >= r)
		return;

	int mid = (l + r) / 2;
	__mergeSort(arr, l, mid);
	__mergeSort(arr, mid + 1, r);
	__merge(arr, l, mid, r);
}

template<typename T>
void mergeSort(T arr[], int n) {
	__mergeSort(arr, 0, n - 1);
}

// �ݹ�ʹ�ù鲢����,��arr[l...r]�ķ�Χ��������
template<typename T>
void __mergeSort2(T arr[], int l, int r) {

	//if (l >= r)
	//	return;
	if (r - l <= 15) {
		insertionSort(arr, l, r);
		return;
	}

	int mid = (l + r) / 2;
	__mergeSort(arr, l, mid);
	__mergeSort(arr, mid + 1, r);
	if (arr[mid] > arr[mid + 1])	// �Խ��������������Ч; arr[mid]��������arr[mid+1]���ұ���С;
		__merge(arr, l, mid, r);
}

template<typename T>
void mergeSort2(T arr[], int n) {
	__mergeSort2(arr, 0, n - 1);
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>> �Ե����ϵĹ鲢���� <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

template<typename T>
void mergeSortBU(T arr[], int n) {

	for (int sz = 1; sz < n; sz += sz) {

		// for (int i = 0; i < n; i += sz + sz) {
		// i + sz < n���Ұ벿�ֲ�������; ����벿������һ���ź���ģ��������ң����Ѿ�����Ҫ������;
		for (int i = 0; i + sz < n; i += sz + sz) {

			if (arr[i + sz - 1] > arr[i + sz])
				// ��arr[i...i+sz-1] �� arr[i+sz...i+2*sz-1] ���й鲢
				__merge(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1));
		}
	}
}