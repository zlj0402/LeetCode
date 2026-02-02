#include <vector>
#include <numeric>
using std::vector;

class Solution {
public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        
        int rowCnt = matrix.size();
        int colCnt = matrix[0].size();

        vector<int> matSum(rowCnt, 0);
        for (int i = 0; i < rowCnt; ++i) {
            matSum[i] = std::accumulate(matrix[i].begin(), matrix[i].end(), 0);
        }

        int maxColumns = -1;
        vector<int> mat(rowCnt, 0);

        auto dfs = [&](auto&&dfs, int i, int selected) -> void {

            if (selected == numSelect) {

                int cnt = 0;
                for (int i = 0; i < rowCnt; ++i) 
                    if (matSum[i] == mat[i])
                        ++cnt;

                if (cnt > maxColumns)
                    maxColumns = cnt;
                return;
            }

            for (int j = i; j < colCnt; ++j) {
                
                for (int k = 0; k < rowCnt; ++k) mat[k] += matrix[k][j];
                dfs(dfs, j + 1, selected + 1);
                for (int k = 0; k < rowCnt; ++k) mat[k] -= matrix[k][j];
            }
        };

        dfs(dfs, 0, 0);
        return maxColumns;
    }
};

int main() {


    vector<vector<int>> matrix = {{0,0,0},{1,0,1},{0,1,1},{0,0,1}};
    int numSelect = 2;
    Solution().maximumRows(matrix, numSelect);
}