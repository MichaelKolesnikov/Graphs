#pragma once
#include "IILGraph.h"
#include "ioGraph.h"
#include <memory>

namespace Graphs {
	template <class T>
	class DirectedGraph : public IILGraph<T> {
	private:
		Ancestors<T> parent;
		bool dfs_cycle_ts(Vertex<T>& v) {
			this->vertex_used[v] = 1;
			for (auto u : this->get_neighbors(v)) {
				if (this->vertex_used[u] == 0) {
					this->parent[u] = v;
					if (dfs_cycle_ts(u)) {
						return true;
					}
				}
				else if (this->vertex_used[u] == 1) {
					this->cycle_st = u;
					return true;
				}
			}
			this->vertex_used[v] = 2;
			return false;
		}
		void dfs_ts(const Vertex<T>& vertex) {
			this->vertex_used[vertex] = true;
			for (auto& u : this->get_neighbors(vertex)) {
				if (!this->vertex_used[u]) {
					dfs_ts(u);
				}
			}
			this->vector_of_vertices.push_back(vertex);
		}

		bool dfs_cycle(Vertex<T>& v) {
			this->vertex_used[v] = 1;
			for (Edge<T> e : this->ug[v]) {
				auto u = e.get_neighbor(v);
				this->origin[u] = e;
				if (this->vertex_used[u] == 0) {
					if (dfs_cycle(u)) {
						return true;
					}
				}
				else if (this->vertex_used[u] == 1) {
					this->cycle_st = u;
					return true;
				}
			}

			this->vertex_used[v] = 2;
			return false;
		}

		// connected components
		int col = 0;
		VectorOfVertices<T> ord;
		Colors<T> component;
		HandleALGraph<T> H;
		void dfs_1(Vertex<T>& v) {
			this->vertex_used[v] = true;
			for (const Edge<T>& e : this->ug[v]) {
				Vertex<T> u = e.vertex2;
				if (!this->vertex_used[u]) {
					dfs_1(u);
				}
			}
			ord.push_back(v);
		}
		void dfs_2(Vertex<T>& v) {
			component[v] = col;
			this->vertex_used[v] = true;
			for (Vertex<T>& u : H[v]) {
				if (!this->vertex_used[u]) {
					dfs_2(u);
				}
			}
			H[v].clear();
		}
	public:
		DirectedGraph(bool multiple_edges = false, bool weighted = false) {
			this->count_vertices = 0;
			this->count_edges = 0;
			this->directed = true;
			this->multiple_edges = multiple_edges;
			this->weighted = weighted;
		}

		void add_edge(const Edge<T>& edge) override {
			this->add_vertex(edge.vertex1);
			this->add_vertex(edge.vertex2);

			if (this->multiple_edges) {
				this->ug[edge.vertex1].insert(edge);
				++this->count_edges;
			}
			else if (!this->are_adjacent(edge.vertex1, edge.vertex2)) {
				this->ug[edge.vertex1].insert(edge);
				++this->count_edges;
			}
		}

		int remove_negatively_incident_edges(const Vertex<T>& vertex) {
			int answer = 0;
			for (auto& v : this->get_vertices()) {
				for (auto& e : this->get_incident_edges(v)) {
					if (e.vertex1 == vertex || e.vertex2 == vertex) {
						this->remove_edge(e);
						++answer;
					}
				}
			}
			return answer;
		}

		bool remove_vertex(const Vertex<T>& vertex) override {
			if (!this->search_vertex(vertex)) {
				return false;
			}
			this->remove_incident_edges(vertex);
			this->remove_negatively_incident_edges(vertex);
			this->ug.erase(vertex);
			--this->count_vertices;
			return true;
		}

		bool has_cycle() override {
			this->vertex_used.clear();
			this->edge_used.clear();
			this->vector_of_vertices.clear();
			this->origin.clear();

			bool cycle_is_found = false;
			for (auto pair_ : this->ug) {
				auto i = pair_.first;
				if (!this->vertex_used[i]) {
					cycle_is_found = dfs_cycle(i);
					if (cycle_is_found) {
						break;
					}
				}
			}
			return cycle_is_found;
		}

		DirectedGraph<T> get_inverted() {
			DirectedGraph<T> g;
			for (const Vertex<T>& v : this->get_vertices()) {
				g.add_vertex(v);
			}
			for (const Edge<T>& e : this->get_edges()) {
				g.add_edge(e.get_reverse());
			}
			return g;
		}

		VectorOfVertices<T> topological_sorting() {
			this->vertex_used.clear();
			this->parent.clear();
			bool cycle_is_found = false;
			for (auto i : this->get_vertices()) {
				if (!this->vertex_used[i]) {
					cycle_is_found = dfs_cycle_ts(i);
					if (cycle_is_found) {
						break;
					}
				}
			}
			if (cycle_is_found) {
				return {};
			}
			this->vertex_used.clear();
			this->vector_of_vertices.clear();
			for (auto v : this->get_vertices()) {
				if (!this->vertex_used[v]) {
					dfs_ts(v);
				}
			}
			std::reverse(begin(this->vector_of_vertices), end(this->vector_of_vertices));
			return this->vector_of_vertices;
		}

		IGraph<T>& Icopy() override {
			DirectedGraph<T> copied(this->multiple_edges, this->weighted);
			for (Vertex<T> v : this->get_vertices()) {
				copied.add_vertex(v);
			}
			for (Edge<T> e : this->get_edges()) {
				copied.add_edge(e);
			}
			return copied;
		}
		DirectedGraph<T> copy() {
			DirectedGraph<T> copied(this->multiple_edges, this->weighted);
			for (Vertex<T> v : this->get_vertices()) {
				copied.add_vertex(v);
			}
			for (Edge<T> e : this->get_edges()) {
				copied.add_edge(e);
			}
			return copied;
		}

		vector<VectorOfVertices<T>> get_connected_components() override {
			this->connected_components.clear();
			this->vertex_used.clear();
			ord.clear();
			ord.reserve(this->get_count_vertices());
			col = 0;
			component.clear();
			for (const auto& p : this->ug) {
				Vertex<T> v = p.first;
				if (!this->vertex_used[v]) {
					dfs_1(v);
				}
			}
			H.clear();
			this->vertex_used.clear();
			for (const auto& p : this->ug) {
				H[p.first] = {};
			}
			for (auto& pair : this->ug) {
				for (auto& e : pair.second) {
					H[e.vertex2].push_back(e.vertex1);
				}
			}
			for (int i = ord.size() - 1; i > -1; --i) {
				if (!this->vertex_used[ord[i]]) {
					dfs_2(ord[i]);
					++col;
				}
			}
			H.clear();
			this->vertex_used.clear();
			this->ord.clear();
			this->connected_components.resize(col);
			for (auto& p : this->ug) {
				this->connected_components[component[p.first]].push_back(p.first);
			}
			this->component.clear();
			return std::move(this->connected_components);
		}
	};
}
