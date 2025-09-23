"""
@brief: Leetcode_165_比较版本号
@link: https://leetcode.cn/problems/compare-version-numbers/description
@author: liangj.zhang
@date: 23/9/2025

@Difficulty: Medium

@Label: IO(String Split)

@Retrospect(worthy 1 - 5): 3

@thoughts:
    + 【思路 1】：使用字符串分割
        - 做这题，是因为它是今天的每日一题；
        - 再熟悉一下 IO 相关的方法使用；

        - 分析：
            + 时间复杂度：
                - 分割字符串：使用 split 遍历字符串，每个字符会被读取一次 => O(n1 + n2), 
                  其中 n1 = len(version1), n2 = len(version2)
                - 循环比较：最多循环 max(len(v1_st), len(v2_st)) 次，设为 k；
                  每次循环调用一次 int 转换；转换复杂度与待转换字符串长度成正比，设平均长度为 m；=> O(k * m)
                  k * m 实际上就是字符串总长度;
                - 总结：2 * O(n1 + n2) => O(n1 + n2)
            + 空间复杂度：
                - split 返回 list，里面存了拆分后的子串，整体额外空间 O(n1 + n2)

        - rank:
            时间效率：0 ms, 击败 100%
            空间效率：17.46 MB, 击败 63.43%

    + 【思路 2】：双指针扫描
        - 留着以后写
"""

class Solution:
    def compareVersion(self, version1: str, version2: str) -> int:
        v1_lst = version1.split('.')
        v2_lst = version2.split('.')

        # print(v1_lst)
        # print(v2_lst)
        v1_len = v1_lst.__len__()
        v2_len = v2_lst.__len__()
        max_len = max(v1_len, v2_len)
        for i in range(max_len):
            v1_val = int(v1_lst[i]) if i < v1_len else 0
            v2_val = int(v2_lst[i]) if i < v2_len else 0
            if v1_val > v2_val:
                return 1
            elif v1_val < v2_val:
                return -1
        return 0



def main():
    version1 = "1.2"
    version2 = "1.10"
    Solution().compareVersion(version1, version2)


if __name__ == "__main__":
    main()