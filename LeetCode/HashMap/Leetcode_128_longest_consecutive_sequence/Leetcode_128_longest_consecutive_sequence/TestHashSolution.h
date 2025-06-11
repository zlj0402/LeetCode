#ifndef TESTHASHSOLUTION_H
#define TESTHASHSOLUTION_H

#include "HashSolution.h"
#include "FuncTestHelper.h"

namespace zlj02 {

    template<typename T>
    void test_hash_solution(vector<T> vec) {

        zlj_hash::Solution sol;
        FuncTestHelper::testFuncTime("¹þÏ£±í²Á³ý·½Ê½", [&](vector<int> arr) {
            return sol.longestConsecutive(arr);
            }, vec);
    }
}

#endif	//TESTHASHSOLUTION_H