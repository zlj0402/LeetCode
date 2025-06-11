#ifndef TESTSORTSOLUTION_H
#define TESTSORTSOLUTION_H

#include "SortSolution.h"
#include "FuncTestHelper.h"


namespace zlj01 {

    template<typename T>
    void test_sort_solution(vector<T> vec) {

        zlj_sort::Solution sol;
        FuncTestHelper::testFuncTime("���ŷ�ʽ", [&](vector<int> arr) {
            return sol.longestConsecutive(arr);
            }, vec);
    }
}

#endif  //TESTSORTSOLUTION_H