#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<bool> g(10, false);
	for (int i = 0; i < g.size(); i++) {
		cout << g[i] << " ";
	}
	return 0;
}