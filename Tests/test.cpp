#include "pch.h"
#include "..\\GG\\Graphs.h"

using namespace Graphs;

TEST(CompCase, CompOfOne) {
	string s = "4 5\n2 2\n3 4\n2 3\n1 3\n2 4";
	istringstream in(s);
	UndirectedGraph<int> g(true);
	int n, m;
	in >> n >> m;
	VectorOfVertices<int> v;
	create_vertices(v, n);
	put_the_vertices_in_the_graph(g, v);
	g.remove_vertex(v[0]);

	input_edges(m, g, v, in);

	auto comp = g.get_connected_component_containing(v[1]);
	sort(begin(comp), end(comp), [](Vertex<int> a, Vertex<int> b) {return a.get_object() < b.get_object();});
	ostringstream out;
	output_vertices(comp, true, out);
	EXPECT_EQ(out.str(), "4\n1 2 3 4 \n");
}

TEST(TestCaseBFS, BFS) {
	UndirectedGraph<int> g;
	int n, a, b;
	std::string s = "10\n"
		"0 1 0 0 0 0 0 0 0 0\n"
		"1 0 0 1 1 0 1 0 0 0\n"
		"0 0 0 0 1 0 0 0 1 0\n"
		"0 1 0 0 0 0 1 0 0 0\n"
		"0 1 1 0 0 0 0 0 0 1\n"
		"0 0 0 0 0 0 1 0 0 1\n"
		"0 1 0 1 0 1 0 0 0 0\n"
		"0 0 0 0 0 0 0 0 1 0\n"
		"0 0 1 0 0 0 0 1 0 0\n"
		"0 0 0 0 1 1 0 0 0 0\n"
		"5 4";
	istringstream in(s);
	in >> n;
	VectorOfVertices<int> v;
	create_vertices(v, n);

	input_matrix(n, g, v, in);
	in >> a >> b;
	ostringstream out;
	auto way = g.shortest_way(v[a], v[b]);
	if (a != b && way.size() == 0) {
		out << -1 << endl;
	}
	else {
		output_way(way, true, out);
	}
	string answer = "2\n5 2 4 \n";
	EXPECT_EQ(out.str(), answer);
}

TEST(CycleCase, CycleInUndirected) {
	string input = "3\n0 1 1\n1 0 1\n1 1 0";
	istringstream in(input);
	ostringstream out;
	UndirectedGraph<int> g;
	int n, m;
	in >> n;
	VectorOfVertices<int> v;
	create_vertices(v, n);
	input_matrix(n, g, v, in);

	auto cycle = g.get_the_cycle();
	if (cycle.size() == 0) {
		out << "NO" << endl;
	}
	else {
		out << "YES" << endl;
		output_cycle(cycle, true, out);
	}
	string answer = "YES\n3\n1 3 2 \n";
	EXPECT_EQ(out.str(), answer);
}

TEST(CompsCase, CompsInDir) {
	std::string input =
		"10 19\n"
		"1 4\n"
		"7 8\n"
		"5 10\n"
		"8 9\n"
		"9 6\n"
		"2 6\n"
		"6 2\n"
		"3 8\n"
		"9 2\n"
		"7 2\n"
		"9 7\n"
		"4 5\n"
		"3 6\n"
		"7 3\n"
		"6 7\n"
		"10 8\n"
		"10 1\n"
		"2 9\n"
		"2 7";
	istringstream in(input);
	ostringstream out;
	DirectedGraph<int> g(true);
	int n, m;
	in >> n >> m;
	VectorOfVertices<int> v;
	create_vertices(v, n);
	put_the_vertices_in_the_graph(g, v);
	g.remove_vertex(v[0]);
	input_edges(m, g, v, in);
	v.clear();
	v.shrink_to_fit();
	auto comps = g.get_connected_components();
	out << comps.size() << '\n';
	vector<int> answer(n + 1);
	for (int i = 0; i < comps.size(); ++i) {
		for (int j = 0; j < comps[i].size(); ++j) {
			answer[comps[i][j].get_object()] = i + 1;
		}
	}
	for (int i = 1; i <= n; ++i) {
		out << answer[i] << ' ';
	}
	out << endl;
	string answer_s = "2\n1 2 2 1 1 2 2 2 2 1 \n";
	EXPECT_EQ(out.str(), answer_s);
}

TEST(CompsCase, CompsInUndir) {
	std::string input =
		"6 4\n"
		"3 1\n"
		"1 2\n"
		"5 4\n"
		"2 3";

	istringstream in(input);
	ostringstream out;

	UndirectedGraph<int> g;
	int n, m;
	in >> n >> m;
	VectorOfVertices<int> v;
	create_vertices(v, n);
	put_the_vertices_in_the_graph(g, v);
	g.remove_vertex(v[0]);

	input_edges(m, g, v, in);

	auto comps = g.get_connected_components();
	out << comps.size() << '\n';
	for (auto& vv : comps) {
		output_vertices(vv, true, out);
	}
	string answer =
		"3\n"
		"3\n"
		"1 2 3 \n"
		"2\n"
		"4 5 \n"
		"1\n"
		"6 \n";
	EXPECT_EQ(out.str(), answer);
}

TEST(TestTSCase, TS) {
	std::string input =
		"6 6\n"
		"1 2\n"
		"3 2\n"
		"4 2\n"
		"2 5\n"
		"6 5\n"
		"4 6";

	istringstream in(input);
	ostringstream out;

	DirectedGraph<int> g;
	int n, m;
	in >> n >> m;
	VectorOfVertices<int> v;
	create_vertices(v, n);
	put_the_vertices_in_the_graph(g, v);
	g.remove_vertex(v[0]);

	input_edges(m, g, v, in);

	auto sorted = g.topological_sorting();
	if (sorted.size() == 0) {
		out << -1 << endl;
	}
	else {
		output_vertices(sorted, false, out);
	}
	string answer = "4 6 3 1 2 5 \n";
	EXPECT_EQ(out.str(), answer);
}

TEST(TestCaseSpan, Span) {
	std::string input =
		"3 3\n"
		"1 2 1\n"
		"2 3 2\n"
		"3 1 3";

	istringstream in(input);
	ostringstream out;

	int n, m, a, b, c;
	in >> n >> m;
	VectorOfVertices<int> vertices;
	create_vertices(vertices, n);
	UndirectedGraph<int> g(false, true);
	for (int i = 0; i < m; ++i) {
		in >> a >> b >> c;
		Edge<int> e(vertices[a], vertices[b], true, c);
		g.add_edge(e);
	}
	auto span_tree = g.finding_minimum_spanning_tree();
	int answer = 0;
	for (Edge<int> e : span_tree.get_edges()) {
		answer += e.get_weight();
	}
	out << answer << endl;
	string answer_ = "3\n";
	EXPECT_EQ(out.str(), answer_);
}
