/**
 * @brief: Leetcode_79_单词搜索
 * @link: https://leetcode.cn/problems/word-search/description
 * @author: liangj.zhang
 * @date: 27/3/2026
 * 
 * @Difficulty: Medium
 * 
 * @Label: Backtracking & dfs
 * 
 * @Retrospect(worthy 1 - 5): 4
 * 
 * @thoughts:
 *  + 【思路 1】：回溯
 *      梦回 samsung adv 考试；
 *      易错点，见代码注释
 *  
 *      + 分析：
 *          + 时间复杂度：O( m * n * 4 * 3^(L−1) ) == O(mn*3^(L - 1))，除了第一步没有越界，有 4 个方向，因为不能走走过的格子，后续只有 3 个方向；
 *          + 空间复杂度：递归深度 O(L) + visit 数组 O(mn) == O(mn + L), L 是 word 的长度
 *      + rank:
 *          + 时间效率：259 ms, 击败 77.16%
 *          + 空间效率：10.11 MB, 击败 99.85%
 */

#include <vector>
#include <string>
using std::string;
using std::vector;

class Solution {
private:
    static constexpr int maxLength = 6;
    static bool visit[maxLength][maxLength];
    static constexpr int Tx[] = {-1, 0, 1, 0};
    static constexpr int Ty[] = {0, 1, 0, -1};

    static bool inRange(int x, int y, int m, int n) {
        if (x < 0 || x >= m || y < 0 || y >= n) return false;
        return true;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board[0].size();
        int n = board.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                visit[i][j] = false;
            }
        }

        int len = word.size();
        bool find = false;
        auto dfs = [&](this auto&& dfs, int y, int x, int pLen) -> void {
            if (find || board[y][x] != word[pLen - 1]) return;  // 原来错误的写法：board[y][x] != word[pLen]
            if (pLen == len) {
                find = true;
                return;
            }

            for (int i = 0; i < 4; ++i) {
                int ax = x + Tx[i];
                int ay = y + Ty[i];

                if (inRange(ax, ay, m, n) && !visit[ay][ax] && board[ay][ax] == word[pLen]) {
                    visit[ay][ax] = true;
                    dfs(ay, ax, pLen + 1);
                    visit[ay][ax] = false;
                }
            }            
        };

        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < m; ++x) {
                visit[y][x] = true; // 原来错误的写法：忘记外面置标志
                dfs(y, x, 1);   // 原来错误的写法： dfs(y, x, 0);
                visit[y][x] = false;
            }
        }

        return find;
    }
};

bool Solution::visit[maxLength][maxLength]{};