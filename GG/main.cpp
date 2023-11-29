#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include "Graphs.h"
#include "ioGraph.h"

using namespace std;
using namespace Graphs;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	

	// comps in dir
	if (0) {
		DirectedGraph<int> g(true);
		int n, m;
		cin >> n >> m;
		VectorOfVertices<int> v;
		create_vertices(v, n);
		put_the_vertices_in_the_graph(g, v);
		g.remove_vertex(v[0]);
		input_edges(m, g, v);
		v.clear();
		v.shrink_to_fit();
		auto comps = g.get_connected_components();
		cout << comps.size() << '\n';
		vector<int> answer(n + 1);
		for (int i = 0; i < comps.size(); ++i) {
			for (int j = 0; j < comps[i].size(); ++j) {
				answer[comps[i][j].get_object()] = i + 1;
			}
		}
		for (int i = 1; i <= n; ++i) {
			cout << answer[i] << ' ';
		}
		cout << flush;
	}
	// bfs
	else if (0) {
		UndirectedGraph<int> g;
		int n, a, b;
		cin >> n;
		VectorOfVertices<int> v;
		create_vertices(v, n);

		input_matrix(n, g, v);
		cin >> a >> b;
		auto way = g.shortest_way(v[a], v[b]);
		if (a != b && way.size() == 0) {
			cout << -1 << endl;
			return 0;
		}
		output_way(way, true);
		cout << flush;
	}
	// cycle search in undirected
	else if (0) {
		UndirectedGraph<int> g;
		int n, m;
		cin >> n;
		VectorOfVertices<int> v;
		create_vertices(v, n);
		input_matrix(n, g, v);

		auto cycle = g.get_the_cycle();
		if (cycle.size() == 0) {
			cout << "NO" << endl;
			return 0;
		}
		cout << "YES" << endl;
		output_cycle(cycle, true);
		cout << flush;
	}
	// comp of one
	else if (0) {
		UndirectedGraph<int> g(true);
		int n, m;
		cin >> n >> m;
		VectorOfVertices<int> v;
		create_vertices(v, n);
		put_the_vertices_in_the_graph(g, v);
		g.remove_vertex(v[0]);

		input_edges(m, g, v);

		auto comp = g.get_connected_component_containing(v[1]);
		sort(begin(comp), end(comp), [](Vertex<int> a, Vertex<int> b) {return a.get_object() < b.get_object();});
		output_vertices(comp, true);
		cout << flush;
	}
	// comps in undirected
	else if (0) {
		UndirectedGraph<int> g;
		int n, m;
		cin >> n >> m;
		VectorOfVertices<int> v;
		create_vertices(v, n);
		put_the_vertices_in_the_graph(g, v);
		g.remove_vertex(v[0]);

		input_edges(m, g, v);

		auto comps = g.get_connected_components();
		cout << comps.size() << '\n';
		for (auto& vv : comps) {
			output_vertices(vv, true);
		}
		cout << flush;
	}
	// ts
	else if (0) {
		DirectedGraph<int> g;
		int n, m;
		cin >> n >> m;
		VectorOfVertices<int> v;
		create_vertices(v, n);
		put_the_vertices_in_the_graph(g, v);
		g.remove_vertex(v[0]);

		input_edges(m, g, v);

		auto sorted = g.topological_sorting();
		if (sorted.size() == 0) {
			cout << -1 << endl;
			return 0;
		}
		output_vertices(sorted);
		cout << flush;
	}
	// minimum_spanning_tree
	else if (1) {
		int n, m, a, b, c;
		cin >> n >> m;
		VectorOfVertices<int> vertices;
		create_vertices(vertices, n);
		UndirectedGraph<int> g(false, true);
		for (int i = 0; i < m; ++i) {
			cin >> a >> b >> c;
			Edge<int> e(vertices[a], vertices[b], true, c);
			g.add_edge(e);
		}
		auto span_tree = g.finding_minimum_spanning_tree();
		int answer = 0;
		for (Edge<int> e : span_tree.get_edges()) {
			answer += e.get_weight();
		}
		cout << answer << endl;
	}

	return 0;
}
