#pragma once
#ifndef INSERTIONSORT_INSERTIONSORT_H
#define INSERTIONSORT_INSERTIONSORT_H

// ≤Â»Î≈≈–ÚÀ„∑®£®÷ÿ‘ÿ£©
template <typename T>
void insertionSort(T arr[], int l, int r) {

    for (int i = l + 1; i <= r; i++) {

        T e = arr[i];
        int j;
        for (j = i; j > l && arr[j - 1] > e; j--)
            arr[j] = arr[j - 1];
        arr[j] = e;
    }
}

#endif