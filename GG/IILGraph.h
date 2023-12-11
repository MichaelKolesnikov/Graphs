#pragma once
#include "IGraph.h"
#include <memory>
#include <stack>
namespace Graphs {
	template <class T>
	class IILGraph : public IGraph<T> {
	protected:
		HandleILGraph<T> ug;

		TypeForCheckUsingVertex<T> vertex_used;
		TypeForCheckUsingEdge<T> edge_used;
		SetOfVertices<T> set_of_vertices;
		vector<Vertex<T>> vector_of_vertices;
		vector<VectorOfVertices<T>> connected_components;
		Edges<T> some_edges;
		
		EdgeOfOrigin<T> origin;
		Distances<T> distances;
		Vertex<T> cycle_st;

		void simple_dfs(const Vertex<T>& start_vertex) {
			stack<Vertex<T>> stack;

			stack.push(start_vertex);

			while (!stack.empty()) {
				Vertex<T> current_vertex = stack.top();
				stack.pop();

				vertex_used[current_vertex] = true;

				for (const auto& e : this->ug[current_vertex]) {
					Vertex<T> neighbor = e.get_neighbor(current_vertex);
					if (!vertex_used[neighbor]) {
						stack.push(neighbor);
					}
				}
			}
		}

		void dfs2(const Vertex<T>& vertex) {
			vertex_used[vertex] = true;
			vector_of_vertices.push_back(vertex);
			for (auto& v : this->get_neighbors(vertex)) {
				if (!vertex_used[v]) {
					dfs2(v);
				}
			}
		}

	public:
		SetOfVertices<T> get_vertices() override {
			set_of_vertices.clear();
			for (auto& pair : ug) {
				set_of_vertices.insert(pair.first);
			}
			return std::move(set_of_vertices);
		}
		Edges<T> get_edges() override {
			edge_used.clear();
			some_edges.clear();
			for (auto& pair : ug) {
				for (auto& e : pair.second) {
					if (!edge_used[e]) {
						edge_used[e] = true;
						some_edges.insert(e);
					}
				}
			}
			edge_used.clear();
			return std::move(some_edges);
		}
		int degree_of_vertex(const Vertex<T>& vertex) override {
			return ug[vertex].size();
		}
		Edges<T> get_incident_edges(const Vertex<T>& vertex) override {
			return ug[vertex];
		}
		SetOfVertices<T> get_neighbors(const Vertex<T>& vertex) override {
			set_of_vertices.clear();
			for (auto& e : this->get_incident_edges(vertex)) {
				set_of_vertices.insert(this->get_neighbour(vertex, e));
			}
			return std::move(set_of_vertices);
		}

		VectorOfEdges<T> get_the_cycle() override {
			if (!this->has_cycle()) {
				return {};
			}
			VectorOfEdges<T> path;
			Vertex<T> cur_v = cycle_st;
			do {
				Edge<T> e = origin.at(cur_v);
				path.push_back(e);
				cur_v = e.get_neighbor(cur_v);
			}
			while (cur_v != cycle_st);
			return path;
		}

		bool search_vertex(const Vertex<T>& vertex) override {
			return ug.count(vertex) > 0;
		}
		bool search_edge(const Edge<T>& edge) override {
			if (!(ug.count(edge.vertex1) > 0 && ug.count(edge.vertex2) > 0)) {
				return false;
			}
			for (Vertex<T> v : this->get_neighbors(edge.vertex1)) {
				if (v.is_incidental(edge)) {
					return true;
				}
			}
			return false;
		}

		void add_vertex(const Vertex<T>& vertex) override {
			if (ug.count(vertex) > 0) {
				return;
			}
			++this->count_vertices;
			ug[vertex] = {};
		}

		bool remove_edge(const Edge<T>& edge) override {
			if (!(this->search_edge(edge))) {
				return false;
			}
			ug[edge.vertex1].erase(edge);
			if (!this->directed) {
				ug[edge.vertex2].erase(edge);
			}
			--this->count_edges;
			return true;
		}

		bool check_connectivity() override {
			auto comps = this->get_connected_components();
			return comps.size() <= 1;
		}
		
		VectorOfVertices<T> get_connected_component_containing(const Vertex<T>& vertex) override {
			vector_of_vertices.clear();
			vertex_used.clear();
			dfs2(vertex);
			vertex_used.clear();
			return vector_of_vertices;
		}

		Distances<T> distances_to_all(const Vertex<T>& initial_vertex) {
			if (!this->weighted) {
				// bfs
				vertex_used.clear();
				distances.clear();
				origin.clear();

				queue<Vertex<T>> q;
				q.push(initial_vertex);
				vertex_used[initial_vertex] = true;
				while (!q.empty()) {
					auto v = q.front();
					q.pop();
					for (Edge<T> e : this->get_incident_edges(v)) {
						Vertex<T> to = e.get_neighbor(v);
						if (!vertex_used[to]) {
							vertex_used[to] = true;
							q.push(to);
							distances[to] = distances[v] + 1;
							origin[to] = e;
						}
					}
				}
				return distances;
			}
			else {
				// Dijkstra's algorithm
				return {};
			}
		}

		VectorOfEdges<T> shortest_way(const Vertex<T>& initial_vertex, const Vertex<T>& final_vertex) override {
			if (initial_vertex == final_vertex) {
				return {};
			}

			auto distances = this->distances_to_all(initial_vertex);
			if (vertex_used[final_vertex]) {
				VectorOfEdges<T> path;
				for (auto v = final_vertex; v != initial_vertex; v = origin[v].get_neighbor(v)) {
					path.push_back(origin[v]);
				}
				std::reverse(begin(path), end(path));
				return path;
			}
			return {};
		}
	};
};
