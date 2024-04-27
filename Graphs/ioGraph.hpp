#pragma once
#include "Graphs.hpp"
#include <iostream>
#include <fstream>
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
	void put_the_vertices_in_the_graph(IGraph<T>& g, DictOfVertices<T>& vertices) {
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
	void input_matrix(int n, IGraph<T>& g, VectorOfVertices<T>& v, istream& cin = std::cin) {
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
	void input_edges(int m, IGraph<T>& g, VectorOfVertices<T>& v, std::istream& cin = std::cin) {
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
	void output_vertices(VectorOfVertices<T>& vertices, bool size_ = false, ostream& cout = std::cout) {
		if (size_) {
			cout << vertices.size() << '\n';
		}
		for (auto& v : vertices) {
			cout << v.get_object() << ' ';
		}
		cout << '\n';
	}
	template <class T>
	void output_vertices(SetOfVertices<T>& vertices, bool size_ = false, ostream& cout = std::cout) {
		if (size_) {
			cout << "Count of vertexes = " << vertices.size() << '\n';
		}
		for (auto v : vertices) {
			cout << v.get_object() << ' ';
		}
		cout << '\n';
	}

	template <class T>
	void output_way(VectorOfEdges<T>& way, bool size_ = false, ostream& cout = std::cout) {
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
	bool output_cycle(VectorOfEdges<T>& cycle, bool size_ = false, ostream& cout = std::cout) {
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

	// template<class T>
	// void create_dot_file(
	// 	Graphs::IGraph<T>& graph,
	// 	const std::string& filename, 
	// 	const string& default_color = "black",
	// 	EdgeColors<T>* color = nullptr,
	// 	VertexColors<T>* vertex_color = nullptr,
	// 	const string& default_vertex_color = "black",
	// 	const string& final_command = ""
	// ) 
	// {
	// 	std::ofstream dotFile(filename);
	// 	string edge_s = " -- ";
	// 	if (graph.is_directed()) {
	// 		edge_s[2] = '>';
	// 		dotFile << "di";
	// 	}

	// 	dotFile << "graph G {" << std::endl;

	// 	for (const Vertex<T>& vertex : graph.get_vertices()) {
	// 		dotFile << vertex.get_object();
	// 		if (vertex_color) {
	// 			dotFile << "[color=" << (vertex_color->contains(vertex) ? vertex_color->at(vertex) : default_vertex_color) << "]";
	// 		}
	// 		dotFile << ";" << std::endl;
	// 	}

	// 	for (Edge<T> edge : graph.get_edges()) {
	// 		dotFile << edge.vertex1.get_object() << edge_s << edge.vertex2.get_object();
	// 		dotFile << " [";
	// 		if (graph.is_weighted()) {
	// 			dotFile << "label=" << edge.get_weight();
	// 		}
	// 		dotFile << "color=" << (color != nullptr && color->find(edge) != color->end() ? color->at(edge) : default_color);
	// 		dotFile << "]" << std::endl;
	// 		dotFile << ";" << std::endl;
	// 	}
	// 	dotFile << final_command << std::endl;
	// 	dotFile << "}" << std::endl;
	// 	dotFile.close();
	// }

	// std::wstring ConvertToWideString(const std::string& input) {
	// 	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &input[0], static_cast<int>(input.size()), NULL, 0);
	// 	std::wstring wide_string(size_needed, 0);
	// 	MultiByteToWideChar(CP_UTF8, 0, &input[0], static_cast<int>(input.size()), &wide_string[0], size_needed);
	// 	return wide_string;
	// }

	// void create_picture(std::string filename, std::string output_image) {
	// 	STARTUPINFOW si;
	// 	PROCESS_INFORMATION pi;
	// 	ZeroMemory(&si, sizeof(si));
	// 	si.cb = sizeof(si);
	// 	ZeroMemory(&pi, sizeof(pi));

	// 	std::wstring wide_filename = ConvertToWideString(filename);
	// 	std::wstring wide_output_image = ConvertToWideString(output_image);

	// 	std::wstring command = L"dot -Tpng " + wide_filename + L" -o " + wide_output_image;

	// 	if (CreateProcessW(NULL, const_cast<LPWSTR>(command.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
	// 		// ���� ���������� ��������
	// 		WaitForSingleObject(pi.hProcess, INFINITE);
	// 		CloseHandle(pi.hProcess);
	// 		CloseHandle(pi.hThread);
	// 	}
	// }
}
