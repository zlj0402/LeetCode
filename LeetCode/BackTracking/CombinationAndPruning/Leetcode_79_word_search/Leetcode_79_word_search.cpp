/**
 * @brief: Leetcode_79_单词搜索
 * @link: https://leetcode.cn/problems/word-search/description
 * @author: liangj.zhang
 * @date: 26/3/2026
 * 
 * @updated:
 *  + 27/3/2026: add 【思路 2】：回溯 + 剪枝
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
 * 
 *  + 【思路 2】：回溯 + 剪枝
 *      参考灵神的题解：https://leetcode.cn/problems/word-search/solutions/2927294/liang-ge-you-hua-rang-dai-ma-ji-bai-jie-g3mmm/?envType=study-plan-v2&envId=top-100-liked
 *      + 可行性剪枝：统计 board 当中字符的数量，和 word 当中字符的数量；如果 word 当中的某个字符数量 > board 当中字符的数量，那就不可能找到完整的 word；
 *      + 顺序剪枝：当最前面的字符数多于最后的字符数，以它开始遍历的话，就会有更多的递归的可能性；
 *          虽然上面说的有理，比如最后一个字符数 < 第一个字符数，但要是倒数第二个字符数又远多于第一个字符，会不会可能导致更多的可能性?
 *          当然数量更小的开头，可以明显的避免更多递归的可能；真实情况到了考虑第二字符时，也只有四个方向进行考虑，不会有过多的可能紧挨着第一个字符；
 *      + 分析：同上，剪枝效果，得根据 case 具体情况看，具体能剪掉多少，不可预知
 *      + rank:
 *          + 时间效率：3 ms, 击败 96.13%
 *          + 空间效率：10.44 MB, 击败 75.61%
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

#include <array>
#include <unordered_map>
using std::unordered_map;
using std::array;

#define um unordered_map

class Solution {
private:
    static constexpr int maxLength = 6;
    static bool visit[maxLength][maxLength];
    static constexpr array<std::pair<int, int>, 4> dir = 
        {std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(0, -1)};
public:
    bool exist(vector<vector<char>>& board, string word) {
        um<char, int> cnt;
        um<char, int> wordCnt;
        int m = board.size(); int n = board[0].size();
        // reset visit & record char cnt
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                visit[i][j] = false;
                ++cnt[board[i][j]];
            }
        }
        // record word char cnt
        for (auto c : word) {
            if (++wordCnt[c] > cnt[c])  // enhancement 1
                return false;
        }
        // enhancement 2
        int len = word.size();
        if (wordCnt[word[len - 1]] < wordCnt[word[0]])
            word = string(word.rbegin(), word.rend());  // 原来错误的写法：string(word.rend(), word.rbegin());

        bool find = false;
        auto dfs = [&](this auto&& dfs, int x, int y, int pLen) -> void {
            if (board[x][y] != word[pLen]) return;
            if (find || pLen == len - 1) {
                find = true;
                return;
            }

            visit[x][y] = true;
            for (auto [dx, dy] : dir) {
                int ax = x + dx;
                int ay = y + dy;
                if (ax >= 0 && ax < m && ay >= 0 && ay < n && !visit[ax][ay]) {
                    dfs(ax, ay, pLen + 1);
                }
            }
            visit[x][y] = false;
        };

        for (int i = 0; i < m; ++i) 
            for (int j = 0; j < n; ++j)
                dfs(i, j, 0);

        return find;
    }
};

bool Solution::visit[maxLength][maxLength]{};