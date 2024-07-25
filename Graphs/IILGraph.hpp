#pragma once
#include "IGraph.hpp"
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

		DistanceMatrixBetweenVertices<T> dist;
		MatrixOfPathsBetweenVertices<T> next;

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
				set_of_vertices.insert(vertex.get_neighbor(e));
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
			for (Edge<T> e : this->ug[edge.vertex1]) {
				if (e.is_negatively_incidental(edge.vertex2)) {
					return true;
				}
			}
			return false;
		}
		optional<Edge<T>> search_edge(const Vertex<T>& vertex1, const Vertex<T>& vertex2) override {
			optional<Edge<T>> answer;
			if (!(ug.count(vertex1) > 0 && ug.count(vertex2) > 0)) {
				return answer;
			}
			for (Edge<T> e : this->ug[vertex1]) {
				if (e.is_negatively_incidental(vertex2)) {
					answer = e;
					return answer;
				}
			}
			return answer;
		}

		bool add_vertex(const Vertex<T>& vertex) override {
			if (ug.count(vertex) > 0) {
				return false;
			}
			++this->count_vertices;
			ug[vertex] = {};
			return true;
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
			return Graphs::Distances<T>();
		}

		void calculate_FloydWarshall() {
			dist.clear();
			next.clear();

			for (Edge<T> e : this->get_edges()) {
				dist[e.to_pair_of_vertices()] = e.get_weight();
				next[e.to_pair_of_vertices()] = e.vertex2;
				if (!this->directed) {
					dist[e.get_reverse().to_pair_of_vertices()] = e.get_weight();
					next[e.get_reverse().to_pair_of_vertices()] = e.vertex1;
				}
			}
			for (auto& p : this->ug) {
				auto v = p.first;
				dist[{v, v}] = 0;
				next[{v, v}] = v;
			}
			for (auto& p1 : this->ug) {
				Vertex<T> k = p1.first;
				for (auto& p2 : this->ug) {
					Vertex<T> i = p2.first;
					for (auto& p3 : this->ug) {
						Vertex<T> j = p3.first;

						PairOfVertices<T> e1 = { i, j };
						PairOfVertices<T> e2 = { i, k };
						PairOfVertices<T> e3 = { k, j };
						
						if (!(dist.find(e2) != dist.end()) || dist[e2] == INT_MAX) {
							dist[e2] = INT_MAX;
							continue;
						}
						if (!(dist.find(e3) != dist.end()) || dist[e3] == INT_MAX) {
							dist[e3] = INT_MAX;
							continue;
						}

						if (!(dist.find(e1) != dist.end()) || dist[e1] > dist[e2] + dist[e3]) {
							dist[e1] = dist[e2] + dist[e3];
							next[e1] = next[e2];
						}
					}
				}
			}
		}

		DistanceMatrixBetweenVertices<T> get_dists_Floyd() {
			return this->dist;
		}

		VectorOfEdges<T> get_path_from_Floyd(const Vertex<T>& vertex1, const Vertex<T>& vertex2) {
			if (this->ug.find(vertex1) == this->ug.end()) {
				return {};
			}
			if (this->ug.find(vertex2) == this->ug.end()) {
				return {};
			}
			if (this->next.find({ vertex1, vertex2 }) == this->next.end()) {
				return {};
			}
			/*ostringstream my_out;
			for (auto& p : this->next) {
				PairOfVertices<T> pair_ = p.first;
				Vertex<T> v = p.second;
				my_out << pair_.vertex1.get_object() << ' ' << pair_.vertex2.get_object() << ' ' << v.get_object() << endl;
			}
			string s = my_out.str();*/
			Vertex<T> st = vertex1, next_v;
			Edge<T> e;
			VectorOfEdges<T> path;
			while (st != vertex2) {
				next_v = this->next[{st, vertex2}];
				optional<Edge<T>> opt = this->search_edge(st, next_v);
				e = opt.value();
				path.push_back(e);
				st = next_v;
			}
			return path;
		}

		VectorOfEdges<T> shortest_way(const Vertex<T>& initial_vertex, const Vertex<T>& final_vertex) override {
			if (initial_vertex == final_vertex) {
				return {};
			}

			if (this->weighted) {
				this->calculate_FloydWarshall();
				return this->get_path_from_Floyd(initial_vertex, final_vertex);
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
