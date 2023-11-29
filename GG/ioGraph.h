#pragma once
#include "IGraph.h"
#include <iostream>
#include <memory>

namespace Graphs {
	using namespace std;

	template <class T>
	unordered_map<int, Vertex<T>> create_map_vertices(int start, int end) {
		unordered_map<int, Vertex<T>>& v;
		for (int i = start; i <= end; ++i) {
			v[i] = i;
		}
		return v;
	}
	template <class T>
	void put_the_vertices_in_the_graph(IGraph<T>& g, unordered_map<int, Vertex<T>>& vertices) {
		for (auto& p : vertices) {
			g.add_vertex(p.second);
		}
	}
	template <class T>
	void input_matrix(int n, IGraph<T>& g, unordered_map<int, Vertex<T>>& v) {
		int one;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cin >> one;
				if (one) {
					g.add_edge_(v[i], v[j]);
				}
			}
		}
	}
	template <class T>
	void input_edges_map(int m, IGraph<T>& g, unordered_map<int, Vertex<T>>& v) {
		int a, b;
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			g.add_edge_(v[a], v[b]);
		}
	}

	void create_vertices(VectorOfVertices<int>& vertices, int n) {
		vertices.resize(n + 1);
		for (int i = 0; i <= n; ++i) {
			vertices[i] = i;
		}
	}
	template <class T>
	void put_the_vertices_in_the_graph(IGraph<T>& g, VectorOfVertices<T>& vertices) {
		for (auto& p : vertices) {
			g.add_vertex(p);
		}
	}
	template <class T>
	void input_matrix(int n, IGraph<T>& g, VectorOfVertices<T>& v) {
		int one;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cin >> one;
				if (one) {
					g.add_edge_(v[i], v[j]);
				}
			}
		}
	}
	template <class T>
	void input_edges(int m, IGraph<T>& g, VectorOfVertices<T>& v) {
		int a, b;
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			g.add_edge_(v[a], v[b]);
		}
	}

	template <class T>
	void output_graph(IGraph<T>& g) {
		cout << "Graph {\n\t";
		cout << "|V| = " << g.get_count_vertices() << ", ";
		cout << "|E| = " << g.get_count_edges() << ", ";
		cout << "d = " << g.is_directed() << ", ";
		cout << "m = " << g.with_multiple_edges() << ", ";
		cout << "w = " << g.is_weighted() << ", ";
		cout << "\n\tV: ";
		for (auto v : g.get_vertices()) {
			cout << v.get_object() << ' ';
		}
		cout << "\n\tE: ";
		for (auto e : g.get_edges()) {
			cout << '(' << e.vertex1.get_object() << ", " << e.vertex2.get_object() << "), ";
		}
		cout << "\n}";
		cout << '\n';
	}

	template <class T>
	void output_vertices(VectorOfVertices<T>& vertices, bool size_ = false) {
		if (size_) {
			cout << vertices.size() << '\n';
		}
		for (auto& v : vertices) {
			cout << v.get_object() << ' ';
		}
		cout << '\n';
	}
	template <class T>
	void output_vertices(SetOfVertices<T>& vertices, bool size_ = false) {
		if (size_) {
			cout << "Count of vertexes = " << vertices.size() << '\n';
		}
		for (auto v : vertices) {
			cout << v.get_object() << ' ';
		}
		cout << '\n';
	}

	template <class T>
	void output_way(VectorOfEdges<T>& way, bool size_ = false) {
		if (size_) {
			cout << way.size() << '\n';
		}
		if (way.size() == 0) {
			return;
		}
		cout << way[0].vertex1.get_object() << ' ';
		for (Edge<int>& e : way) {
			cout << e.vertex2.get_object() << ' ';
		}
		cout << '\n';
	}
	template <class T>
	bool output_cycle(VectorOfEdges<T>& cycle, bool size_ = false) {
		if (cycle.size() == 0) {
			return false;
		}
		if (size_) {
			cout << cycle.size() << '\n';
		}
		if (cycle.size() == 1) {
			cout << cycle[0].vertex1.get_object() << ' ' << cycle[0].vertex2.get_object() << '\n';
			return true;
		}
		auto cur_v = cycle[0].vertex1;
		if (cycle[1].is_incidental(cur_v)) {
			cur_v = cycle[0].get_neighbor(cur_v);
		}
		for (int i = 0; i < cycle.size(); ++i) {
			cout << cur_v.get_object() << ' ';
			cur_v = cycle[i].get_neighbor(cur_v);
		}
		cout << '\n';
		return true;
	}
}
