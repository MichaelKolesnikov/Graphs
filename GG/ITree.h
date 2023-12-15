#include "IGraph.h"

namespace Graphs {
	template <class T>
	class ITree : public IGraph<T> {

		TypeForCheckUsingVertex<T> used;

		bool dfs_chain(const Vertex<T>& vertex) {
			if (!used[vertex]) {
				used[vertex] = true;
				auto ways = this->get_incident_edges(vertex);
				if (ways.size() > 2) {
					return false;
				}
				for (auto& e : ways) {
					bool some = dfs_chain((*ways.begin()).get_neighbor(vertex));
					if (!some) {
						return false;
					}
				}
			}
			return true;
		}
	public:
		ITree() {
			this->count_vertices = 0;
			this->count_edges = 0;
			this->directed = false;
			this->multiple_edges = false;
			this->weighted = false;
		}

		virtual bool remove_list(const Vertex<T>& vertex) = 0;

		virtual Vertex<T> get_root() = 0;

		virtual Edges<T> get_ways_to_children(const Vertex<T>& vertex) = 0;

		virtual Edge<T> get_way_from_ancestor(const Vertex<T>& vertex) = 0;

		virtual bool add_child(const Edge<T>& edge) = 0;
		virtual bool add_child(const Vertex<T>& ancestor, const Vertex<T>& child) = 0;

		bool is_list(const Vertex<T>& vertex) {
			return this->get_incident_edges(vertex).size() <= 1;
		}

		bool is_chain() {
			if (this->is_directed() || this->get_count_vertices() == 0) {
				return false;
			}
			return dfs_chain(this->get_root());
		}

		int degree_of_vertex(const Vertex<T>& vertex) {
			return this->get_incident_edges(vertex).size();
		}

		bool search_edge(const Edge<T>& edge) override {
			return this->are_adjacent(edge.vertex1, edge.vertex2);
		}

		// poorly defined tree functions from IGraph
		bool add_edge(const Edge<T>& edge) {
			return false;
		}
		bool add_edge(const Vertex<T>& vertex1, const Vertex<T> vertex2) {
			return false;
		}

		bool remove_vertex(const Vertex<T>& vertex) override {
			if (!this->is_list(vertex)) {
				return false;
			}
			return this->remove_list(vertex);
		}
		bool remove_edge(const Edge<T>& edge) {
			return false;
		}
		int remove_edges_from_to(const Vertex<T>& vertex1, const Vertex<T>& vertex2) {
			return 0;
		}
		int remove_edges_between(const Vertex<T>& vertex1, const Vertex<T>& vertex2) {
			return 0;
		}
		int remove_incident_edges(const Vertex<T>& vertex) {
			return 0;
		}

		bool check_connectivity() override {
			return !this->is_directed();
		}
		vector<VectorOfVertices<T>> get_connected_components() override {
			if (this->is_directed()) {
				vector<VectorOfVertices<T>> comps(this->get_count_vertices());
				SetOfVertices<T> vertices = this->get_vertices();
				for (auto& i : vertices) {
					comps.push_back({ i });
				}
				return comps;
			}
			else {
				auto s = this->get_vertices();
				VectorOfVertices<T> v(begin(s), end(s));
				return { v };
			}
		}
		VectorOfVertices<T> get_connected_component_containing(const Vertex<T>& vertex) override {
			if (!this->search_vertex(vertex)) {
				return {};
			}
			if (this->is_directed()) {
				return { vertex };
			}
			auto s = this->get_vertices();
			VectorOfVertices<T> v(begin(s), end(s));
			return v;
		}

		bool has_cycle() override {
			return false;
		}
		VectorOfEdges<T> get_the_cycle() override {
			return {};
		}

		bool is_there_an_Eulerian_cycle() {
			return false;
		}
		bool is_there_an_Eulerian_way() {
			return this->is_chain();
		}
	};
}