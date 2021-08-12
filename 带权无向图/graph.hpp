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

	void dft_recursion(const T& u, set<T>& visited, vector<T>& result); /* 深度优先遍历递归辅助函数 */
	vector<T> depth_first_rec(const T& u); /* 深度优先遍历递归法 */
	vector<T> depth_first_itr(const T& u); /* 深度优先遍历迭代法*/
	vector<T> breadth_first(const T& u); /* 广度优先遍历迭代法 */

	Graph<T> prim(T v); /* prim最小生成树算法 */

	map<T, int> dijkstra(T start); /*  dijkstra最短路径算法 */

	vector<vector<T>>  get_connected_components(); /* 获得图中的连通分量 */
	void  print_connected_components(const vector<vector<T>>& connected_components); /* 打印连通分量 */

};


template <typename T> void Graph<T>::show() {
	for (const auto& u : adj) {
		cout <<"顶点"<< u.first << ": ";
		for (const auto& v : adj[u.first])
			cout << "(相邻顶点: " << v.vertex << ", 边的权重: " << v.weight << ") ";
		cout <<endl;
	}
}


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
/* 深度优先遍历递归辅助函数 */
template <typename T> void Graph<T>::dft_recursion(const T& u, set<T>& visited, vector<T>& result) {
	result.push_back(u);
	visited.insert(u);

	for (Edge<T> edge : adj[u])
		if (visited.find(edge.vertex) == visited.end())
			dft_recursion(edge.vertex, visited, result);
}
/* 深度优先遍历递归法 */
template <typename T> vector<T> Graph<T>::depth_first_rec(const T& u) {
	vector<T> result;
	set<T> visited;
	if (contains(u))  dft_recursion(u, visited, result);
	return  result;
}
/* 深度优先遍历迭代法*/
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

/* 广度优先遍历迭代法 */
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
		//这一步的查找访问可以省略
			if (visited.find(edge.vertex) == visited.end()) {
				q.push(edge.vertex);
			}
		}
	}
	return result;
}
/*
Prim算法步骤
给定一个连通图G
	创建一个空的图T，用来作为最小生成树。
	在图G中任意选择一个起始顶点v，把v加入到最小生成树T中。
	当最小生成树中顶点的数量小于原图中的顶点数量时：
		让E’作为两个顶点u,v的边 edge<u,v>的集合，其中顶点u∈G且u∈T，顶点v∈G但v?T 。
		从集合E’中选择顶点u和顶点v之间权重最小的边: edge<u,v> = min(E’) 。
		在T创建新的顶点v，然后形成边edge<u,v> 。
返回T。
*/
/* prim最小生成树算法 */
template <typename T> Graph<T> Graph<T>::prim(T v) {
	// 最小生成树的创建
	Graph<T> min_spanning_tree;
	
	// 在生成树中添加顶点v
	min_spanning_tree.add_vertex(v);

	// 设置带权重的队列，按第一个元素（权值）进行从小到大的排列,小顶堆。
	priority_queue<pair<int, pair<T, T>>, vector<pair<int, pair<T, T>>>, greater<pair<int, pair<T, T>>>> q;

	// 设置集合visited来存放已经访问过的顶点
	set<T> visited;

	// 入队：入队的元素是一个pair类型，第一个值是权重，第二个值也是pair
	// 第二个值的pair里面第一个值是u（只在生成树中存在的顶点）, 第二个值是v（只在在原图中存在的点）
	for (auto neighbour : adj[v]) {
		q.push(make_pair(neighbour.weight, make_pair(v, neighbour.vertex)));
	}

	while (!q.empty()) {
		// 队首元素出队
		auto front = q.top();
		q.pop();

		// 获得已在生成树中的顶点u
		T u = front.second.first;

		// 获得在原图中, 但不在生成树中的顶点v
		T v = front.second.second;

		// 如果顶点v已经访问过则跳过本此循环
		if (visited.find(v) != visited.end()) continue;
		else visited.insert(v);

		// 在生成树中添加新的顶点v以及v和u之间的边
		min_spanning_tree.add_vertex(v);
		min_spanning_tree.add_edge(u, v, front.first);

		// 依次将顶点v尚未访问过的邻居放入优先队列中
		for (auto neighbour : adj[v]) {
			//这一步的查找访问可以省略
			if (visited.find(neighbour.vertex) == visited.end()) {
				q.push(make_pair(neighbour.weight, make_pair(v, neighbour.vertex)));
			}
		}
	}
	return min_spanning_tree;
}
/*
Dijkstra算法步骤
给定图G，该图具有非负边权重和起始顶点start。
	1.设置对顶点start的距离为0，对图中其他顶点的距离为正无穷。
	2.对所有顶点标记为未访问状态。
	3.将初始顶点start为u。
	4.当图中任有未访问过的顶点时：
		1.将当前顶点u设置为已访问状态。
		2.对于当前顶点未访问过的邻居顶点v，依次将邻居顶点v到起始顶点start的距离 
		与（当前顶点u到起始到起始点start的距离 + 当前顶点u到该邻居顶点v的距离）进行比较，并以较小的一个为准。
		3.选择具有最小暂定距离的未访问顶点，并将其设置为当前顶点。
此外，遍历顶点需要用到广度优先遍历算法，选择具有最小暂定距离的未访问顶点需要用到优先队列（priority_queue）。
*/
/*  dijkstra最短路径算法 */
template <typename T> map<T,int> Graph<T>::dijkstra(T start) {
	// 设置dis用来存放初始点到图中任何一个顶点的距离
	map<T, int> dis;
	
	// 设置带权重的队列，按每个pair的第一个元素进行从小到大的排列
	priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> q;

	for (T vertex: get_vertices()) {
		// 设置初始顶点到自己的距离为0
		if(vertex == start) dis[start] = 0;
		// 设置初始顶点到其他顶点的距离为无穷大
		else dis[vertex] = INT_MAX;
	}

    // 设置集合visited来存放已经访问过的顶点
	set<T> visited;

	// 入队：入队的元素是一个pair类型，第一个值是权重，第二个值是顶点
	q.push(make_pair(0,start));

	while (!q.empty()) {
		// 队首元素出队
		auto front = q.top();
		q.pop();

		// 获得当前顶点
		T u = front.second;

		// 如果该顶点已经访问过则跳过本此循环，否则存入到集合visited中表示已经访问过
		if (visited.find(u) != visited.end()) continue;
		else visited.insert(u);

		// 获得到顶点u的最短路径"shortest_distance_to_u"，将此路径存入到dis结果中
		int shortest_distance_to_u = front.first;
		dis[u] = shortest_distance_to_u;

		// 依次访问顶点u尚未访问过的邻居
		for (auto v : adj[u]) {
			if (visited.find(v.vertex) == visited.end()) {
				// 从顶点u到邻居v的路径记为“distance_to_v”
				int distance_to_v = v.weight;
				q.push(make_pair(shortest_distance_to_u + distance_to_v,  v.vertex));
			} 
		}
	}
	return dis;
}
/*
连通分量定义
无向图 G的一个极大连通子图称为 G的一个连通分量（或连通分支）。
连通图只有一个连通分量，即其自身；非连通的无向图有多个连通分量。
获取所有连通分量
1.当所有的顶点尚未全部访问时：
	1.选择一个未访问的顶点使用遍历算法(深度优先或者广度优先)
	2.将这个顶点能到达的所有顶点标记为已访问，并且把他们放到一个连通分量的数组中。
*/
/* 获得图中的连通分量 */
template <typename T> vector<vector<T>> Graph<T>::get_connected_components() {
	set<T> visited_vertices;
	vector<vector<T>> connected_components;

	for (auto vertex : adj) {

		// 对每一个未访问过的顶点进行深度优先遍历
		if (visited_vertices.find(vertex.first) == visited_vertices.end()) {
			stack<T> s;
			s.push(vertex.first);

			// 定义一个临时变量"connected_component"用来存储当前连通分量中的顶点
			vector<T> connected_component;
			
			// 深度优先遍历
			while (!s.empty()) {
				T u = s.top();
				s.pop();

				// 将未访问过的顶点放入连通分量"connected_component"中
				if (visited_vertices.find(u) == visited_vertices.end()) {
					connected_component.push_back(u);
					visited_vertices.insert(u);
				}

				// 当前顶点未访问过的邻居入栈
				for (auto neighbour : adj[u])
					if (visited_vertices.find(neighbour.vertex) == visited_vertices.end())
						s.push(neighbour.vertex);
			}
			// 将连通分量放到连通分量的集合"connected_components"中
			connected_components.push_back(connected_component);

		}
	}

	return connected_components;
}
/* 打印图中的连通分量 */
template <typename T> void Graph<T>::print_connected_components(const vector<vector<T>>& connected_components ) {
	int number = connected_components.size();
	if(number == 1)  cout << "该图是连通图，只有一个连通分量，就是其自身" << endl;
	else if (number > 1){
		cout << "图中共有" << number << "个连通分量" << endl;
		for (unsigned i = 0; i < connected_components.size(); i++) {
			cout << "第" << i + 1 << "个连通分量中的顶点分别为:";
			for (unsigned j = 0; j < connected_components[i].size(); j++) {
				cout << " " << connected_components[i][j];
			}
			cout << endl;
		}
	}
}

