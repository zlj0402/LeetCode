#ifndef FUNCTESTHELPER_H
#define FUNCTESTHELPER_H

#include <iostream>
#include <vector>
#include <ctime>

using std::vector;
using std::string;


namespace FuncTestHelper {

    // ���Ժ�ʱ����ģ��
    template<typename Func>
    void testFuncTime(const string& funcName, Func func, vector<int> nums) {

        clock_t startTime = clock();
        int res = func(nums);
        clock_t endTime = clock();

        cout << funcName << " -> ���: " << res
            << "����ʱ: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
    }

}

#endif	//FUNCTESTHELPER_H