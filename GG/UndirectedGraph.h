#pragma once
#include "IILGraph.h"
#include <algorithm>
#include <functional>

namespace Graphs {
	template <class T>
	class UndirectedGraph : public IILGraph<T> {
	protected:
		bool dfs_cycle(Vertex<T>& v) {
			this->vertex_used[v] = 1;
			for (Edge<T> e : this->get_incident_edges(v)) {
				if (this->edge_used.count(e) == 0) {
					this->edge_used[e] = 0;
				}
				if (!this->edge_used[e]) {
					this->edge_used[e] = 1;
					Vertex<T> u = v.get_neighbor(e);
					this->origin[u] = e;
					if (!this->vertex_used[u]) {
						if (dfs_cycle(u)) {
							return true;
						}
					}
					else {
						this->cycle_st = u;
						return true;
					}
				}
			}
			return false;
		}
		void dfs1(const Vertex<T>& vertex) {
			this->vertex_used[vertex] = true;
			this->connected_components.back().push_back(vertex);
			for (auto& v : this->get_neighbors(vertex)) {
				if (!this->vertex_used[v]) {
					dfs1(v);
				}
			}
		}
	public:
		UndirectedGraph(bool multiple_edges = false, bool weighted = false) {
			this->count_vertices = 0;
			this->count_edges = 0;
			this->directed = false;
			this->multiple_edges = multiple_edges;
			this->weighted = weighted;
		}

		bool add_edge(const Edge<T>& edge) override {
			this->add_vertex(edge.vertex1);
			this->add_vertex(edge.vertex2);

			if (this->multiple_edges) {
				this->ug[edge.vertex1].insert(edge);
				this->ug[edge.vertex2].insert(edge.get_reverse(true));
				++this->count_edges;
				return true;
			}
			else if (!this->are_adjacent(edge.vertex1, edge.vertex2)) {
				this->ug[edge.vertex1].insert(edge);
				this->ug[edge.vertex2].insert(edge.get_reverse(true));
				++this->count_edges;
				return true;
			}
			return false;
		}

		bool remove_vertex(const Vertex<T>& vertex) override {
			if (!this->search_vertex(vertex)) {
				return false;
			}
			this->remove_incident_edges(vertex);
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

			for (auto i : this->get_vertices()) {
				cycle_is_found = dfs_cycle(i);
				if (cycle_is_found) {
					break;
				}
			}
			return cycle_is_found;
		}

		IGraph<T>& Icopy() override {
			UndirectedGraph<T> copied(this->multiple_edges);
			for (Vertex<T> v : this->get_vertices()) {
				copied.add_vertex(v);
			}
			for (auto e : this->get_edges()) {
				copied.add_edge(e);
			}
			return copied;
		}
		UndirectedGraph<T> copy() {
			UndirectedGraph<T> copied(this->multiple_edges);
			for (Vertex<T> v : this->get_vertices()) {
				copied.add_vertex(v);
			}
			for (Edge<T> e : this->get_edges()) {
				copied.add_edge(e);
			}
			return copied;
		}

		bool is_connected() {
			int count_connected_components = 0;
			this->vertex_used.clear();
			for (auto& p : this->ug) {
				auto i = p.first;
				if (!this->vertex_used[i]) {
					if (count_connected_components == 1) {
						this->vertex_used.clear();
						return false;
					}
					this->simple_dfs(i);
					++count_connected_components;
				}
			}
			this->vertex_used.clear();
			return true;
		}

		bool is_bridge(const Edge<T>& edge) {
			if (!this->remove_edge(edge)) {
				return false;
			}
			bool answer = !this->is_connected();
			this->add_edge(edge);
			return answer;
		}

		vector<VectorOfVertices<T>> get_connected_components() override {
			this->connected_components.clear();
			this->vertex_used.clear();
			for (auto& i : this->get_vertices()) {
				if (!this->vertex_used[i]) {
					this->connected_components.push_back({});
					this->dfs1(i);
				}
			}
			return this->connected_components;
		}

		UndirectedGraph<T> finding_minimum_spanning_tree() {
			UndirectedGraph<T> span_tree = this->copy();
			auto set_edges = span_tree.get_edges();
			VectorOfEdges<T> edges(set_edges.begin(), set_edges.end());
			set_edges.clear();
			std::sort(edges.begin(), edges.end(), [](const Edge<T>& e1, const Edge<T>& e2) {return e1.get_weight() > e2.get_weight();});
			for (Edge<T> e : edges) {
				if (!span_tree.is_bridge(e)) {
					span_tree.remove_edge(e);
				}
			}
			return span_tree;
		}
	};
}