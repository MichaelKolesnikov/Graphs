#pragma once
#include "Types.h"

namespace Graphs {
	template <class T>
	class IGraph {
	protected:
		int count_vertices;
		int count_edges;
		bool directed;
		bool multiple_edges;
		bool weighted;
	public:
		int get_count_vertices() const {
			return this->count_vertices;
		}
		int get_count_edges() const {
			return this->count_edges;
		}
		bool is_directed() const {
			return this->directed;
		}
		bool with_multiple_edges() const {
			return this->multiple_edges;
		}
		bool is_weighted() const {
			return this->weighted;
		}

		bool are_adjacent(const Vertex<T>& begin_vertex, const Vertex<T>& end_vertex) {
			for (Edge<T> e : this->get_incident_edges(begin_vertex)) {
				if (e.is_negatively_incidental(end_vertex)) {
					return true;
				}
			}
			return false;
		}

		virtual SetOfVertices<T> get_vertices() = 0;
		virtual Edges<T> get_edges() = 0;
		virtual int degree_of_vertex(const Vertex<T>& vertex) = 0;
		virtual Edges<T> get_incident_edges(const Vertex<T>& vertex) = 0;
		virtual SetOfVertices<T> get_neighbors(const Vertex<T>& vertex) = 0;

		virtual bool search_vertex(const Vertex<T>& vertex) = 0;
		virtual bool search_edge(const Edge<T>& edge) = 0;
		virtual optional<Edge<T>> search_edge(const Vertex<T>& vertex1, const Vertex<T>& vertex2) = 0;

		virtual bool add_vertex(const Vertex<T>& vertex) = 0;
		virtual bool add_edge(const Edge<T>& edge) = 0;
		bool add_edge_(const Vertex<T>& vertex1, const Vertex<T> vertex2) {
			Edge<T> e(vertex1, vertex2);
			return this->add_edge(e);
		}

		virtual bool remove_vertex(const Vertex<T>& vertex) = 0;
		virtual bool remove_edge(const Edge<T>& edge) = 0;
		int remove_edges_from_to(const Vertex<T>& vertex1, const Vertex<T>& vertex2) {
			int count = 0;
			for (Edge<T> e : this->get_incident_edges(vertex1)) {
				if (e.is_negatively_incidental(vertex2)) {
					count += this->remove_edge(e);
				}
			}
			return count;
		}
		int remove_edges_between(const Vertex<T>& vertex1, const Vertex<T>& vertex2) {
			return this->remove_edges_from_to(vertex1, vertex2) + this->remove_edges_from_to(vertex2, vertex1);
		}
		int remove_incident_edges(const Vertex<T>& vertex) {
			if (!this->search_vertex(vertex)) {
				return 0;
			}
			auto inc_edges = this->get_incident_edges(vertex);
			for (auto e : inc_edges) {
				this->remove_edge(e);
			}
			return inc_edges.size();
		}

		virtual bool check_connectivity() = 0;
		virtual vector<VectorOfVertices<T>> get_connected_components() = 0;
		virtual VectorOfVertices<T> get_connected_component_containing(const Vertex<T>& vertex) = 0;

		virtual bool has_cycle() = 0;
		virtual VectorOfEdges<T> get_the_cycle() = 0;

		virtual VectorOfEdges<T> shortest_way(const Vertex<T>& initial_vertex, const Vertex<T>& final_vertex) = 0;

		virtual IGraph<T>& Icopy() = 0;

		bool is_there_an_Eulerian_cycle() {
			// in in an undirected graph
			// Euler's theorem
			// ∃ Euler cycle <=> (k == 1 or G\{v | d(v) = 0}) and (∄ v in G : d(v) % 2 == 1)
			auto comps = this->get_connected_components();
			int cnt_big_comps = 0;
			for (auto& comp : comps) {
				cnt_big_comps += comp.size() > 1;
				if (cnt_big_comps > 1) {
					return false;
				}
			}
			for (auto v : this->get_vertices()) {
				if (this->degree_of_vertex(v) % 2 == 1) {
					return false;
				}
			}
			return true;
		}
		bool is_there_an_Eulerian_way() {
			// ∃ Euler way <=> (k == 1 or G\{v | d(v) = 0}) and size({v in G | d(v) % 2 == 1}) in {0, 2}
			auto comps = this->get_connected_components();
			int cnt_big_comps = 0;
			for (auto& comp : comps) {
				cnt_big_comps += comp.size() > 1;
				if (cnt_big_comps > 1) {
					return false;
				}
			}
			int number_of_odd_vertices = 0;
			for (auto v : this->get_vertices()) {
				number_of_odd_vertices += this->degree_of_vertex(v) % 2 == 1;
				if (number_of_odd_vertices > 2) {
					return false;
				}
			}
			if (number_of_odd_vertices == 1) {
				return false;
			}
			return true;
		}

		/*virtual Vertexes<T> find_the_Hamiltonian_cycle() = 0;
		virtual Vertexes<T> find_the_Hamiltonian_path() = 0;*/
	};
};