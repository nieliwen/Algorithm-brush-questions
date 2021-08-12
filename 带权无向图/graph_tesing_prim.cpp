#include "graph.hpp"

void test03(Graph<char> g) {
    cout << "���ɵ���С���������£�" << endl;
    Graph<char> result = g.prim('A');
    result.show();
}

template <typename T> void Graph<T>::show() {
	for (const auto& u : adj) {
		cout <<"����"<< u.first << ": ";
		for (const auto& v : adj[u.first])
			cout << "(���ڶ���: " << v.vertex << ", �ߵ�Ȩ��: " << v.weight << ") ";
		cout <<endl;
	}
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
    cout << "��ӡͼ�ж��㼰���ڽӱ����ϸ��Ϣ����" << endl;
    g.show();
    cout << endl;
    
    test03(g);

    return 0;
}

