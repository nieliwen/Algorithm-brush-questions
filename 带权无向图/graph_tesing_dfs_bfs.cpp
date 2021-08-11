#include "graph.hpp"

template <typename T> void Graph<T>::show() {
	for (const auto& u : adj) {
		cout <<"顶点"<< u.first << ": ";
		for (const auto& v : adj[u.first])
			cout << "(相邻顶点: " << v.vertex << ", 边的权重: " << v.weight << ") ";
		cout <<endl;
	}
}


void test02(Graph<char> g)
{
    auto dft = g.depth_first_rec('A');
    cout << "从顶点A进行深度优先遍历（递归）: {";
    for (auto u : dft) cout << u << " ";
    cout << "}" << endl;

    vector<char> dft_itr = g.depth_first_itr('A');
    cout << "从顶点A进行深度优先遍历（迭代）: {";
    for (auto u : dft_itr) cout << u << " ";
    cout << "}" << endl;

    auto bft = g.breadth_first('A');
    cout << "从顶点A进行广度优先遍历: {";
    for (auto u : bft) cout << u << " ";
    cout << "}" << endl;
} 
int main()
{
    Graph<char> g;
    g.add_vertex('A');
    g.add_vertex('B');
    g.add_vertex('C');
    g.add_vertex('D');
    g.add_vertex('E');
    g.add_vertex('F');
    g.add_vertex('G');

    g.add_edge('A', 'B', 7);
    g.add_edge('A', 'D', 5);
    g.add_edge('B', 'C', 8);
    g.add_edge('B', 'D', 9);
    g.add_edge('B', 'E', 7);
    g.add_edge('C', 'E', 5);
    g.add_edge('D', 'E', 15);
    g.add_edge('D', 'F', 6);
    g.add_edge('E', 'F', 8);
    g.add_edge('E', 'G', 9);
    g.add_edge('F', 'G', 11);

    g.add_vertex('H');
    g.add_edge('B', 'H', 9);
    g.add_edge('A', 'H', 10);
    g.add_edge('D', 'H', 11);
    g.add_edge('A', 'H', 12);
    g.remove_vertex('H');
    cout << "打印图中顶点及其邻接表的详细信息如下" << endl;
    g.show();
    cout << endl;
    
    test02(g);
    return 0;
}

