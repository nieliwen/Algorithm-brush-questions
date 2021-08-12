using namespace std; 
#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include "edge.hpp"
#include <limits.h>

template <typename T>
class Graph {
public:
	map<T, set<Edge<T>>> adj;  /* �ڽӱ� */

	bool contains(const T& u); /* �ж϶���u�Ƿ���ͼ�� */
	bool adjacent(const T& u, const T& v); /* �ж϶���u��v�Ƿ����� */

	void add_vertex(const T& u); /* ��Ӷ��� */
	void add_edge(const T& u, const T& v, int weight); /* ��ӱߺ�Ȩ�� */

	void change_weight(const T& u, const T& v, int weight); /* �޸�Ȩ�� */

	void remove_weight(const T& u, const T& v); /* �Ƴ�Ȩ�� */
	void remove_vertex(const T& u); /* �Ƴ����� */
	void remove_edge(const T& u, const T& v); /* �Ƴ��� */

	int degree(const T& u); /* �󶥵�Ķ��� */
	int num_vertices(); /* ��ͼ�ж�������� */
	int num_edges(); /* ��ͼ�бߵ�����*/
	int largest_degree(); /* ��ͼ�е������� */

	int get_weight(const T& u, const T& v); /* �õ�ĳ��������֮��ߵ�Ȩ�� */
	vector<T> get_vertices(); /* �õ�ͼ�����ж��� */
	map<T, int> get_neighbours(const T& u); /* �õ�����u�����б� */

	void show();

	void dft_recursion(const T& u, set<T>& visited, vector<T>& result); /* ������ȱ����ݹ鸨������ */
	vector<T> depth_first_rec(const T& u); /* ������ȱ����ݹ鷨 */
	vector<T> depth_first_itr(const T& u); /* ������ȱ���������*/
	vector<T> breadth_first(const T& u); /* ������ȱ��������� */

	Graph<T> prim(T v); /* prim��С�������㷨 */

	map<T, int> dijkstra(T start); /*  dijkstra���·���㷨 */

	vector<vector<T>>  get_connected_components(); /* ���ͼ�е���ͨ���� */
	void  print_connected_components(const vector<vector<T>>& connected_components); /* ��ӡ��ͨ���� */

};


template <typename T> void Graph<T>::show() {
	for (const auto& u : adj) {
		cout <<"����"<< u.first << ": ";
		for (const auto& v : adj[u.first])
			cout << "(���ڶ���: " << v.vertex << ", �ߵ�Ȩ��: " << v.weight << ") ";
		cout <<endl;
	}
}


/* �ж϶���u�Ƿ���ͼ�� */
template <typename T> bool Graph<T>::contains(const T& u) {
	return adj.find(u) != adj.end();
}
/* �ж϶���u��v�Ƿ����� */
template <typename T> bool Graph<T>::adjacent(const T& u, const T& v) {
	if (contains(u) && contains(v) && u != v) {
		for (auto edge : adj[u])
			if (edge.vertex == v)
				return true;
	}
	return false;
}
/* ��Ӷ��� */
template <typename T> void Graph<T>::add_vertex(const T& u) {
	if (!contains(u)) {
		set<Edge<T>> edge_list;
		adj[u] = edge_list;
	}
}
/* ��ӱߺ�Ȩ�� */
template <typename T> void Graph<T>::add_edge(const T& u, const T& v, int weight) {
	if (!adjacent(u, v)) {
		adj[u].insert(Edge<T>(v, weight));
		adj[v].insert(Edge<T>(u, weight));
	}
}
/* �޸�Ȩ�� */
template <typename T> void Graph<T>::change_weight(const T& u, const T& v, int weight) {
	if (contains(u) && contains(v)) {
		if (adj[u].find(Edge<T>(v)) != adj[u].end()) {
			adj[u].erase(Edge<T>(v));
			adj[u].insert(Edge<T>(v, weight));
		}

		if (adj[v].find(Edge<T>(u)) != adj[v].end()) {
			adj[v].erase(Edge<T>(u));
			adj[v].insert(Edge<T>(u, weight));
		}
	}
}
/* �Ƴ�Ȩ�� */
template <typename T> void Graph<T>::remove_weight(const T& u, const T& v) {
	if (contains(u) && contains(v)) {
		if (adj[u].find(Edge<T>(v)) != adj[u].end()) {
			adj[u].erase(Edge<T>(v));
			adj[u].insert(Edge<T>(v, 0));
		}

		if (adj[v].find(Edge<T>(u)) != adj[v].end()) {
			adj[v].erase(Edge<T>(u));
			adj[v].insert(Edge<T>(u, 0));
		}
	}
}
/* �Ƴ����� */
template <typename T> void Graph<T>::remove_vertex(const T& u) {
	if (contains(u)) {
		for (auto& vertex : adj) {
			if (vertex.second.find(Edge<T>(u)) != vertex.second.end())
				vertex.second.erase(Edge<T>(u));
		}
		adj.erase(u);
	}
}
/* �Ƴ��� */
template <typename T> void Graph<T>::remove_edge(const T& u, const T& v) {
	if (u == v || !contains(u) || !contains(v)) return;

	if (adj[u].find(Edge<T>(v)) != adj[u].end()) {
		adj[u].erase(Edge<T>(v));
		adj[v].erase(Edge<T>(u));
	}
}

/* �󶥵�Ķ��� */
template <typename T> int Graph<T>::degree(const T& u) {
	if (contains(u)) return adj[u].size();

	return -1; // ����Ϊ-1˵��ͼ��û�иö���
}

/* ��ͼ�ж�������� */
template <typename T> int Graph<T>::num_vertices() {
	return adj.size();
}

/* ��ͼ�бߵ�����*/
template <typename T> int Graph<T>::num_edges() {
	int count = 0;
	set<Edge<T>> vertex_set;

	for (auto vertex : adj) {
		vertex_set.insert(Edge<T>(vertex.first, 0));
		for (auto edge : vertex.second) {
			if (vertex_set.find(edge) != vertex_set.end()) continue;
			count++;
		}
	}
	return count;
}

/* ��ͼ�е������� */
template <typename T> int Graph<T>::largest_degree() {
	if (num_vertices() == 0) return 0;

	unsigned max_degree = 0;
	for (auto vertex : adj) {
		if (vertex.second.size() > max_degree)
			max_degree = vertex.second.size();
	}
	return max_degree;
}

/* �õ�ĳ��������֮��ߵ�Ȩ�� */
template <typename T> int  Graph<T>::get_weight(const T& u, const T& v) {
	if (contains(u) && contains(v)) {
		for (Edge<T> edge : adj[u])
			if (edge.vertex == v) return edge.weight;
	}
	return -1;  
}

/* �õ�ͼ�����ж��� */
template <typename T> vector<T> Graph<T>::get_vertices() {
	vector<T> vertices;
	for (auto vertex : adj)
		vertices.push_back(vertex.first);

	return vertices;
}

/* �õ�����u�����б� */
template <typename T> map<T, int> Graph<T>::get_neighbours(const T& u) {
	map<T, int> neighbours;

	if (contains(u)) {
		for (Edge<T> edge : adj[u])
			neighbours[edge.vertex] = edge.weight;
	}

	return neighbours;
}
/* ������ȱ����ݹ鸨������ */
template <typename T> void Graph<T>::dft_recursion(const T& u, set<T>& visited, vector<T>& result) {
	result.push_back(u);
	visited.insert(u);

	for (Edge<T> edge : adj[u])
		if (visited.find(edge.vertex) == visited.end())
			dft_recursion(edge.vertex, visited, result);
}
/* ������ȱ����ݹ鷨 */
template <typename T> vector<T> Graph<T>::depth_first_rec(const T& u) {
	vector<T> result;
	set<T> visited;
	if (contains(u))  dft_recursion(u, visited, result);
	return  result;
}
/* ������ȱ���������*/
template <typename T> vector<T> Graph<T>::depth_first_itr(const T& u) {
	vector<T> result;
	set<T> visited;
	stack<T> s;

	s.push(u);
	while (!s.empty()) {
		T v = s.top();
		s.pop();
		
		if (visited.find(v) != visited.end()) {
			continue;
		}
		visited.insert(v);
		result.push_back(v);

		for (auto w : adj[v]) {
			if (visited.find(w.vertex) == visited.end()) {
				s.push(w.vertex);
			}
		}
	}
	return  result;
}

/* ������ȱ��������� */
template <typename T> vector<T> Graph<T>::breadth_first(const T& u) {
	vector<T>result;
	set<T> visited;
	queue<T> q;

	q.push(u);
	while (!q.empty()) {
		T v = q.front();
		q.pop();

		if (visited.find(v) != visited.end()) {
			continue;
		}

		visited.insert(v);
		result.push_back(v);

		for (Edge<T> edge : adj[v]) {
		//��һ���Ĳ��ҷ��ʿ���ʡ��
			if (visited.find(edge.vertex) == visited.end()) {
				q.push(edge.vertex);
			}
		}
	}
	return result;
}
/*
Prim�㷨����
����һ����ͨͼG
	����һ���յ�ͼT��������Ϊ��С��������
	��ͼG������ѡ��һ����ʼ����v����v���뵽��С������T�С�
	����С�������ж��������С��ԭͼ�еĶ�������ʱ��
		��E����Ϊ��������u,v�ı� edge<u,v>�ļ��ϣ����ж���u��G��u��T������v��G��v?T ��
		�Ӽ���E����ѡ�񶥵�u�Ͷ���v֮��Ȩ����С�ı�: edge<u,v> = min(E��) ��
		��T�����µĶ���v��Ȼ���γɱ�edge<u,v> ��
����T��
*/
/* prim��С�������㷨 */
template <typename T> Graph<T> Graph<T>::prim(T v) {
	// ��С�������Ĵ���
	Graph<T> min_spanning_tree;
	
	// ������������Ӷ���v
	min_spanning_tree.add_vertex(v);

	// ���ô�Ȩ�صĶ��У�����һ��Ԫ�أ�Ȩֵ�����д�С���������,С���ѡ�
	priority_queue<pair<int, pair<T, T>>, vector<pair<int, pair<T, T>>>, greater<pair<int, pair<T, T>>>> q;

	// ���ü���visited������Ѿ����ʹ��Ķ���
	set<T> visited;

	// ��ӣ���ӵ�Ԫ����һ��pair���ͣ���һ��ֵ��Ȩ�أ��ڶ���ֵҲ��pair
	// �ڶ���ֵ��pair�����һ��ֵ��u��ֻ���������д��ڵĶ��㣩, �ڶ���ֵ��v��ֻ����ԭͼ�д��ڵĵ㣩
	for (auto neighbour : adj[v]) {
		q.push(make_pair(neighbour.weight, make_pair(v, neighbour.vertex)));
	}

	while (!q.empty()) {
		// ����Ԫ�س���
		auto front = q.top();
		q.pop();

		// ��������������еĶ���u
		T u = front.second.first;

		// �����ԭͼ��, �������������еĶ���v
		T v = front.second.second;

		// �������v�Ѿ����ʹ�����������ѭ��
		if (visited.find(v) != visited.end()) continue;
		else visited.insert(v);

		// ��������������µĶ���v�Լ�v��u֮��ı�
		min_spanning_tree.add_vertex(v);
		min_spanning_tree.add_edge(u, v, front.first);

		// ���ν�����v��δ���ʹ����ھӷ������ȶ�����
		for (auto neighbour : adj[v]) {
			//��һ���Ĳ��ҷ��ʿ���ʡ��
			if (visited.find(neighbour.vertex) == visited.end()) {
				q.push(make_pair(neighbour.weight, make_pair(v, neighbour.vertex)));
			}
		}
	}
	return min_spanning_tree;
}
/*
Dijkstra�㷨����
����ͼG����ͼ���зǸ���Ȩ�غ���ʼ����start��
	1.���öԶ���start�ľ���Ϊ0����ͼ����������ľ���Ϊ�����
	2.�����ж�����Ϊδ����״̬��
	3.����ʼ����startΪu��
	4.��ͼ������δ���ʹ��Ķ���ʱ��
		1.����ǰ����u����Ϊ�ѷ���״̬��
		2.���ڵ�ǰ����δ���ʹ����ھӶ���v�����ν��ھӶ���v����ʼ����start�ľ��� 
		�루��ǰ����u����ʼ����ʼ��start�ľ��� + ��ǰ����u�����ھӶ���v�ľ��룩���бȽϣ����Խ�С��һ��Ϊ׼��
		3.ѡ�������С�ݶ������δ���ʶ��㣬����������Ϊ��ǰ���㡣
���⣬����������Ҫ�õ�������ȱ����㷨��ѡ�������С�ݶ������δ���ʶ�����Ҫ�õ����ȶ��У�priority_queue����
*/
/*  dijkstra���·���㷨 */
template <typename T> map<T,int> Graph<T>::dijkstra(T start) {
	// ����dis������ų�ʼ�㵽ͼ���κ�һ������ľ���
	map<T, int> dis;
	
	// ���ô�Ȩ�صĶ��У���ÿ��pair�ĵ�һ��Ԫ�ؽ��д�С���������
	priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> q;

	for (T vertex: get_vertices()) {
		// ���ó�ʼ���㵽�Լ��ľ���Ϊ0
		if(vertex == start) dis[start] = 0;
		// ���ó�ʼ���㵽��������ľ���Ϊ�����
		else dis[vertex] = INT_MAX;
	}

    // ���ü���visited������Ѿ����ʹ��Ķ���
	set<T> visited;

	// ��ӣ���ӵ�Ԫ����һ��pair���ͣ���һ��ֵ��Ȩ�أ��ڶ���ֵ�Ƕ���
	q.push(make_pair(0,start));

	while (!q.empty()) {
		// ����Ԫ�س���
		auto front = q.top();
		q.pop();

		// ��õ�ǰ����
		T u = front.second;

		// ����ö����Ѿ����ʹ�����������ѭ����������뵽����visited�б�ʾ�Ѿ����ʹ�
		if (visited.find(u) != visited.end()) continue;
		else visited.insert(u);

		// ��õ�����u�����·��"shortest_distance_to_u"������·�����뵽dis�����
		int shortest_distance_to_u = front.first;
		dis[u] = shortest_distance_to_u;

		// ���η��ʶ���u��δ���ʹ����ھ�
		for (auto v : adj[u]) {
			if (visited.find(v.vertex) == visited.end()) {
				// �Ӷ���u���ھ�v��·����Ϊ��distance_to_v��
				int distance_to_v = v.weight;
				q.push(make_pair(shortest_distance_to_u + distance_to_v,  v.vertex));
			} 
		}
	}
	return dis;
}
/*
��ͨ��������
����ͼ G��һ��������ͨ��ͼ��Ϊ G��һ����ͨ����������ͨ��֧����
��ͨͼֻ��һ����ͨ������������������ͨ������ͼ�ж����ͨ������
��ȡ������ͨ����
1.�����еĶ�����δȫ������ʱ��
	1.ѡ��һ��δ���ʵĶ���ʹ�ñ����㷨(������Ȼ��߹������)
	2.����������ܵ�������ж�����Ϊ�ѷ��ʣ����Ұ����Ƿŵ�һ����ͨ�����������С�
*/
/* ���ͼ�е���ͨ���� */
template <typename T> vector<vector<T>> Graph<T>::get_connected_components() {
	set<T> visited_vertices;
	vector<vector<T>> connected_components;

	for (auto vertex : adj) {

		// ��ÿһ��δ���ʹ��Ķ������������ȱ���
		if (visited_vertices.find(vertex.first) == visited_vertices.end()) {
			stack<T> s;
			s.push(vertex.first);

			// ����һ����ʱ����"connected_component"�����洢��ǰ��ͨ�����еĶ���
			vector<T> connected_component;
			
			// ������ȱ���
			while (!s.empty()) {
				T u = s.top();
				s.pop();

				// ��δ���ʹ��Ķ��������ͨ����"connected_component"��
				if (visited_vertices.find(u) == visited_vertices.end()) {
					connected_component.push_back(u);
					visited_vertices.insert(u);
				}

				// ��ǰ����δ���ʹ����ھ���ջ
				for (auto neighbour : adj[u])
					if (visited_vertices.find(neighbour.vertex) == visited_vertices.end())
						s.push(neighbour.vertex);
			}
			// ����ͨ�����ŵ���ͨ�����ļ���"connected_components"��
			connected_components.push_back(connected_component);

		}
	}

	return connected_components;
}
/* ��ӡͼ�е���ͨ���� */
template <typename T> void Graph<T>::print_connected_components(const vector<vector<T>>& connected_components ) {
	int number = connected_components.size();
	if(number == 1)  cout << "��ͼ����ͨͼ��ֻ��һ����ͨ����������������" << endl;
	else if (number > 1){
		cout << "ͼ�й���" << number << "����ͨ����" << endl;
		for (unsigned i = 0; i < connected_components.size(); i++) {
			cout << "��" << i + 1 << "����ͨ�����еĶ���ֱ�Ϊ:";
			for (unsigned j = 0; j < connected_components[i].size(); j++) {
				cout << " " << connected_components[i][j];
			}
			cout << endl;
		}
	}
}

