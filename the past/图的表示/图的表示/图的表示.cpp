// 图的表示.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Component.h"
#include "Path.h"
using namespace std;

//int main()
//{
//    int N = 20;
//    int M = 100;
//
//    srand(time(NULL));
//
//    // 稀疏图测试
//    SparseGraph g1(N, false);
//    for (int i = 0; i < M; i++) {
//        int a = rand() % N;
//        int b = rand() % N;
//        g1.addEdge(a, b);
//    }
//
//    for (int v = 0; v < N; v++) {
//        cout << v << ":";
//        SparseGraph::adjIterator adj(g1, v);
//        for (int w = adj.begin(); !adj.end(); w = adj.next())
//            cout << w << " ";
//        cout << endl;
//    }
//    
//    cout << endl;
//
//    //// 稠密图测试
//    //DenseGraph g2(N, false);
//    //for (int i = 0; i < M; i++) {
//    //    int a = rand() % N;
//    //    int b = rand() % N;
//    //    g2.addEdge(a, b);
//    //}
//
//    //// O(V^2)
//    //for (int v = 0; v < N; v++) {
//    //    cout << v << ":";
//    //    DenseGraph::adjIterator adj(g2, v);
//    //    for (int w = adj.begin(); !adj.end(); w = adj.next())
//    //        cout << w << " ";
//    //    cout << endl;
//    //}
//
//    return 0;
//}

//int main() {
//	//string filename = "testG1.txt";
//	//SparseGraph g1(13, false);
//	//ReadGraph<SparseGraph> readGraph1(g1, filename);
//	//Component<SparseGraph> component1(g1);
//	//cout << "TestG1.txt, Component Count: " << component1.count() << endl;
//	////g1.show();
//
//	cout << endl;
//
//	string filename2 = "testG2.txt";
//	SparseGraph g2 = SparseGraph(7, false);
//	ReadGraph<SparseGraph> readGraph2(g2, filename2);
//	g2.show();
//	//Component<SparseGraph> component2(g2);
//	//cout << "TestG2.txt, Component Count: " << component2.count() << endl;
//	////g2.show();
//
//	return 0;
//}

int main() {
	string filename = "testG2.txt";
	SparseGraph g = SparseGraph(7, false);
	ReadGraph<SparseGraph> read(g, filename);
	g.show();
	cout << endl;

	Path<SparseGraph> dfs(g, 0);
	cout << "DFS : ";
	dfs.showPath(6);

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
