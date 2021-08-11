using namespace std; 
#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include "edge.hpp"


template <typename T>
class Graph {
public:
	map<T, set<Edge<T>>> adj;  /* 邻接表 */

	bool contains(const T& u); /* 判断顶点u是否在图中 */
	bool adjacent(const T& u, const T& v); /* 判断顶点u和v是否相邻 */

	void add_vertex(const T& u); /* 添加顶点 */
	void add_edge(const T& u, const T& v, int weight); /* 添加边和权重 */

	void change_weight(const T& u, const T& v, int weight); /* 修改权重 */

	void remove_weight(const T& u, const T& v); /* 移除权重 */
	void remove_vertex(const T& u); /* 移除顶点 */
	void remove_edge(const T& u, const T& v); /* 移除边 */

	int degree(const T& u); /* 求顶点的度数 */
	int num_vertices(); /* 求图中顶点的总数 */
	int num_edges(); /* 求图中边的总数*/
	int largest_degree(); /* 求图中的最大度数 */

	int get_weight(const T& u, const T& v); /* 得到某两个顶点之间边的权重 */
	vector<T> get_vertices(); /* 得到图中所有顶点 */
	map<T, int> get_neighbours(const T& u); /* 得到顶点u的所有边 */

	void show();
};

/*
template <typename T> void Graph<T>::show() {
	for (const auto& u : adj) {
		cout <<"顶点"<< u.first << ": ";
		for (const auto& v : adj[u.first])
			cout << "(相邻顶点: " << v.vertex << ", 边的权重: " << v.weight << ") ";
		cout <<endl;
	}
}
*/

/* 判断顶点u是否在图中 */
template <typename T> bool Graph<T>::contains(const T& u) {
	return adj.find(u) != adj.end();
}
/* 判断顶点u和v是否相邻 */
template <typename T> bool Graph<T>::adjacent(const T& u, const T& v) {
	if (contains(u) && contains(v) && u != v) {
		for (auto edge : adj[u])
			if (edge.vertex == v)
				return true;
	}
	return false;
}
/* 添加顶点 */
template <typename T> void Graph<T>::add_vertex(const T& u) {
	if (!contains(u)) {
		set<Edge<T>> edge_list;
		adj[u] = edge_list;
	}
}
/* 添加边和权重 */
template <typename T> void Graph<T>::add_edge(const T& u, const T& v, int weight) {
	if (!adjacent(u, v)) {
		adj[u].insert(Edge<T>(v, weight));
		adj[v].insert(Edge<T>(u, weight));
	}
}
/* 修改权重 */
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
/* 移除权重 */
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
/* 移除顶点 */
template <typename T> void Graph<T>::remove_vertex(const T& u) {
	if (contains(u)) {
		for (auto& vertex : adj) {
			if (vertex.second.find(Edge<T>(u)) != vertex.second.end())
				vertex.second.erase(Edge<T>(u));
		}
		adj.erase(u);
	}
}
/* 移除边 */
template <typename T> void Graph<T>::remove_edge(const T& u, const T& v) {
	if (u == v || !contains(u) || !contains(v)) return;

	if (adj[u].find(Edge<T>(v)) != adj[u].end()) {
		adj[u].erase(Edge<T>(v));
		adj[v].erase(Edge<T>(u));
	}
}

/* 求顶点的度数 */
template <typename T> int Graph<T>::degree(const T& u) {
	if (contains(u)) return adj[u].size();

	return -1; // 度数为-1说明图中没有该顶点
}

/* 求图中顶点的总数 */
template <typename T> int Graph<T>::num_vertices() {
	return adj.size();
}

/* 求图中边的总数*/
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

/* 求图中的最大度数 */
template <typename T> int Graph<T>::largest_degree() {
	if (num_vertices() == 0) return 0;

	unsigned max_degree = 0;
	for (auto vertex : adj) {
		if (vertex.second.size() > max_degree)
			max_degree = vertex.second.size();
	}
	return max_degree;
}

/* 得到某两个顶点之间边的权重 */
template <typename T> int  Graph<T>::get_weight(const T& u, const T& v) {
	if (contains(u) && contains(v)) {
		for (Edge<T> edge : adj[u])
			if (edge.vertex == v) return edge.weight;
	}
	return -1;  
}

/* 得到图中所有顶点 */
template <typename T> vector<T> Graph<T>::get_vertices() {
	vector<T> vertices;
	for (auto vertex : adj)
		vertices.push_back(vertex.first);

	return vertices;
}

/* 得到顶点u的所有边 */
template <typename T> map<T, int> Graph<T>::get_neighbours(const T& u) {
	map<T, int> neighbours;

	if (contains(u)) {
		for (Edge<T> edge : adj[u])
			neighbours[edge.vertex] = edge.weight;
	}

	return neighbours;
}
