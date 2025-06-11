#ifndef FUNCTESTHELPER_H
#define FUNCTESTHELPER_H

#include <iostream>
#include <vector>
#include <ctime>

using std::vector;
using std::string;


namespace FuncTestHelper {

    // 测试耗时函数模板
    template<typename Func>
    void testFuncTime(const string& funcName, Func func, vector<int> nums) {

        clock_t startTime = clock();
        int res = func(nums);
        clock_t endTime = clock();

        cout << funcName << " -> 结果: " << res
            << "；耗时: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
    }

}

#endif	//FUNCTESTHELPER_H