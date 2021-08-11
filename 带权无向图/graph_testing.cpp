#include "graph.hpp"

template <typename T> void Graph<T>::show() {
	for (const auto& u : adj) {
		cout <<"顶点"<< u.first << ": ";
		for (const auto& v : adj[u.first])
			cout << "(相邻顶点: " << v.vertex << ", 边的权重: " << v.weight << ") ";
		cout <<endl;
	}
}

void test01(Graph<char> g)
{
    cout << "'A' 和 'D'之间边的权重为：" << g.get_weight('A', 'D') << endl;
    g.change_weight('A', 'D', 100);
    cout << "将'A' 和 'D'之间边的权重更改为100后，其权重为：" << g.get_weight('A', 'D') << endl;
    g.remove_weight('A', 'D');
    cout << "将'A' 和 'D'之间边的权重删除后，其权重为：" << g.get_weight('A', 'D') << endl;
    cout << "将'A' 和 'D'之间边的权重重新设置为5" << endl;
    g.change_weight('A', 'D', 5);

    cout << "顶点总数：" << g.num_vertices() << endl;
    cout << "边的总数：" << g.num_edges() << endl;

    cout << "图中包含'F'吗？" << (g.contains('F') ? "包含" : "不包含") << endl;
    cout << "图中包含'G'吗？" << (g.contains('G') ? "包含" : "不包含") << endl;
    cout << "'A'和'D'相邻吗？" << (g.adjacent('A', 'D') ? "相邻" : "不相邻") << endl;
    cout << "'B'和'E'相邻吗？" << (g.adjacent('B', 'E') ? "相邻" : "不相邻") << endl;
    cout << "顶点'A'的度数为： " << g.degree('A') << endl;
    cout << "最大度数为：" << g.largest_degree() << endl;

    auto vertices = g.get_vertices();
    cout << "图中的顶点分别为：";
    for (auto u : vertices) cout << " " << u;
    cout << endl;

    map<char, int> nbrs = g.get_neighbours('F');
    cout << "顶点F的邻接顶点ID及其权重为：";
    for (auto u : nbrs) cout << " (" << u.first << ": " << u.second <<")";
    cout << endl;
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
    
    test01(g);
    return 0;
}
