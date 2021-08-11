#include "graph.hpp"

template <typename T> void Graph<T>::show() {
	for (const auto& u : adj) {
		cout <<"����"<< u.first << ": ";
		for (const auto& v : adj[u.first])
			cout << "(���ڶ���: " << v.vertex << ", �ߵ�Ȩ��: " << v.weight << ") ";
		cout <<endl;
	}
}

void test01(Graph<char> g)
{
    cout << "'A' �� 'D'֮��ߵ�Ȩ��Ϊ��" << g.get_weight('A', 'D') << endl;
    g.change_weight('A', 'D', 100);
    cout << "��'A' �� 'D'֮��ߵ�Ȩ�ظ���Ϊ100����Ȩ��Ϊ��" << g.get_weight('A', 'D') << endl;
    g.remove_weight('A', 'D');
    cout << "��'A' �� 'D'֮��ߵ�Ȩ��ɾ������Ȩ��Ϊ��" << g.get_weight('A', 'D') << endl;
    cout << "��'A' �� 'D'֮��ߵ�Ȩ����������Ϊ5" << endl;
    g.change_weight('A', 'D', 5);

    cout << "����������" << g.num_vertices() << endl;
    cout << "�ߵ�������" << g.num_edges() << endl;

    cout << "ͼ�а���'F'��" << (g.contains('F') ? "����" : "������") << endl;
    cout << "ͼ�а���'G'��" << (g.contains('G') ? "����" : "������") << endl;
    cout << "'A'��'D'������" << (g.adjacent('A', 'D') ? "����" : "������") << endl;
    cout << "'B'��'E'������" << (g.adjacent('B', 'E') ? "����" : "������") << endl;
    cout << "����'A'�Ķ���Ϊ�� " << g.degree('A') << endl;
    cout << "������Ϊ��" << g.largest_degree() << endl;

    auto vertices = g.get_vertices();
    cout << "ͼ�еĶ���ֱ�Ϊ��";
    for (auto u : vertices) cout << " " << u;
    cout << endl;

    map<char, int> nbrs = g.get_neighbours('F');
    cout << "����F���ڽӶ���ID����Ȩ��Ϊ��";
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
    cout << "��ӡͼ�ж��㼰���ڽӱ����ϸ��Ϣ����" << endl;
    g.show();
    cout << endl;
    
    test01(g);
    return 0;
}
