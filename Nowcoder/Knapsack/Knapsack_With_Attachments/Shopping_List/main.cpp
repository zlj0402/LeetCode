#include <fstream>


#include <iostream>
#include <vector>
#define MAXGOODS 61
#define TIMES 10
#define MAXDP  30001/TIMES + 1
using namespace std;

struct Goods {

    int v;
    int w;
    int q;

    Goods() : v(v), w(w), q(q) {}

    Goods(int v, int w, int q) : v(v), w(w), q(q) {}

    int favor() { return v * w; }

    void init(int v, int w, int q) {
        
        this->v = v;
        this->w = w;
        this->q = q;
    };
};

Goods mg[MAXGOODS];
vector<vector<Goods>> attachments(MAXGOODS);
int dp[MAXDP];

int main() {

    for (int i = 0; i <= MAXDP; i++)
        dp[i] = 0;

    for (auto& g : attachments)
        g.clear();

    ifstream file("sample.txt");

    int budget;
    int m;

    int v, w, q;
    while (file >> budget >> m) { // 注意 while 处理多个 case

        budget /= TIMES;

        for (int i = 1; i <= m; i++) {

            file >> v >> w >> q;
            if (!q)
                mg[i].init(v / TIMES, w, q);
            else {
                mg[i].q = -1;
                attachments[q].push_back(Goods(v / TIMES, w, q));
            }

        }
    }

    for (int i = 1; i <= m; i++) {
        
        // 不是主件的位置，
        if (mg[i].q != 0) continue;
        
        // 单独主件
        int v0 = mg[i].v;
        int f0 = mg[i].favor();

        // 主件 + 附件1
        int v1 = 0, f1 = 0;
        if (attachments[i].size() >= 1) {
            v1 = v0 + attachments[i][0].v;
            f1 = f0 + attachments[i][0].favor();
        }
        
        // 主件 + 附件2
        int v2 = 0, f2 = 0;
        if (attachments[i].size() == 2) {
            v2 = v0 + attachments[i][1].v;
            f2 = f0 + attachments[i][1].favor();
        }

        // 主件 + 附件3
        int v3 = 0, f3 = 0;
        if (attachments[i].size() == 2) {
            v3 = v0 + attachments[i][0].v + attachments[i][1].v;
            f3 = f0 + attachments[i][0].favor() + attachments[i][1].favor();
        }

        for (int j = budget; j >= v0; j--) {
            
            dp[j] = max(dp[j], dp[j - v0] + f0);
            if (v1 && j >= v1) dp[j] = max(dp[j], dp[j - v1] + f1);
            if (v2 && j >= v2) dp[j] = max(dp[j], dp[j - v2] + f2);
            if (v3 && j >= v3) dp[j] = max(dp[j], dp[j - v3] + f3);
        }
    }

    cout << dp[budget] * TIMES << endl;
}
// 64 位输出请用 printf("%lld")
