#include "ITree.h"

namespace Graphs {
	template <class T>
	class Tree : public ITree<T> {
	private:
		Vertex<T> root;
		WaysToAncestors<T> ways_from_ancestors;
		HandleILGraph<T> ways_to_children;
	public:
		Tree() : ITree<T>() {}
		Tree(bool directed, bool weighted = false) : ITree<T>() {
			this->directed = directed;
			this->weighted = weighted;
		}

		Vertex<T> get_root() override {
			return root;
		}

		Edges<T> get_ways_to_children(const Vertex<T>& vertex) override {
			return ways_to_children[vertex];
		}

		Edge<T> get_way_from_ancestor(const Vertex<T>& vertex) override {
			return ways_from_ancestors[vertex];
		}

		bool add_child(const Edge<T>& edge) override {
			if (this->search_vertex(edge.vertex1)) {
				if (this->search_vertex(edge.vertex2)) {
					return false;
				}
				++this->count_vertices;
				++this->count_edges;
				this->ways_to_children[edge.vertex1].insert(edge);
				this->ways_from_ancestors[edge.vertex2] = edge;
				return true;
			}
			if (!this->is_directed() && this->search_vertex(edge.vertex2)) {
				if (this->search_vertex(edge.vertex1)) {
					return false;
				}
				++this->count_vertices;
				++this->count_edges;
				this->ways_to_children[edge.vertex2].insert(edge);
				this->ways_from_ancestors[edge.vertex1] = edge;
				return true;
			}
			return false;
		}
		bool add_child(const Vertex<T>& ancestor, const Vertex<T>& child) override {
			Edge<T> e(ancestor, child, this->is_weighted());
			return this->add_child(e);
		}
		bool add_vertex(const Vertex<T>& vertex) override {
			if (this->count_vertices == 0) {
				root = vertex;
				ways_to_children[root] = {};
				++this->count_vertices;
				return true;
			}
			return false;
		}

		bool are_adjacent(const Vertex<T>& begin_vertex, const Vertex<T>& end_vertex) {
			return ways_from_ancestors.contains(end_vertex) && ways_from_ancestors[end_vertex].is_incidental(begin_vertex)
				|| ways_from_ancestors.contains(begin_vertex) && ways_from_ancestors[begin_vertex].is_incidental(end_vertex);
		}

		bool search_vertex(const Vertex<T>& vertex) override {
			return this->ways_from_ancestors.contains(vertex) || vertex == this->root;
		}
		
		optional<Edge<T>> search_edge(const Vertex<T>& vertex1, const Vertex<T>& vertex2) override {
			optional<Edge<T>> opt;
			if (ways_from_ancestors.contains(vertex2) && ways_from_ancestors[vertex2].is_incidental(vertex1)) {
				opt = ways_from_ancestors[vertex2];
			}
			else if (!this->is_directed() && ways_from_ancestors.contains(vertex1) && ways_from_ancestors[vertex1].is_incidental(vertex2)) {
				opt = ways_from_ancestors[vertex1];
			}
			return opt;
		}

		SetOfVertices<T> get_vertices() {
			auto vertices_r = ways_from_ancestors | std::views::keys;
			SetOfVertices<T> vertices(vertices_r.begin(), vertices_r.end());
			vertices.insert(root);
			return vertices;
		}
		Edges<T> get_edges() {
			auto edges_r = ways_from_ancestors | std::views::values;
			return Edges<T>(edges_r.begin(), edges_r.end());
		}
		Edges<T> get_incident_edges(const Vertex<T>& vertex) {
			auto edges = ways_to_children[vertex];
			if (!this->directed) {
				edges.insert(ways_from_ancestors[vertex]);
			}
			return edges;
		}
		SetOfVertices<T> get_neighbors(const Vertex<T>& vertex) {
			SetOfVertices<T> vertices;
			for (const Edge<T>& e : this->get_incident_edges(vertex)) {
				vertices.insert(e.get_neighbor(vertex));
			}
			return vertices;
		}

		VectorOfEdges<T> shortest_way(const Vertex<T>& initial_vertex, const Vertex<T>& final_vertex) override {
			if (initial_vertex == final_vertex) {
				return {};
			}
			VectorOfEdges<T> path;
			Vertex<T> cur = final_vertex;
			while (cur != root) {
				path.push_back(ways_from_ancestors[cur]);
				cur = ways_from_ancestors[cur].get_neighbor(cur);
				if (cur == initial_vertex) {
					std::reverse(begin(path), end(path));
					return path;
				}
			}
			if (this->directed) {
				return {};
			}
			VectorOfEdges<T> path2;
			cur = initial_vertex;
			while (cur != root) {
				path2.push_back(ways_from_ancestors[cur]);
				cur = ways_from_ancestors[cur].get_neighbor(cur);
			}
			int i = 0;
			while (path[path.size() - i] == path2[path2.size() - i]) {
				++i;
			}
			std::reverse(begin(path), end(path));
			path2.resize(path2.size() - i + 1);
			path.resize(i);
			path2.insert(path2.end(), path.begin(), path.end());
			return path2;
		}

		bool remove_list(const Vertex<T>& vertex) override {
			if (!this->is_list(vertex)) {
				return false;
			}
			Edge<T> e = get_way_from_ancestor(vertex);
			Vertex<T> ancestor = e.get_neighbor(vertex);
			ways_to_children[ancestor].erase(e);
			ways_from_ancestors.erase(vertex);
			return true;
		}

		IGraph<T>& Icopy() override {
			Tree<T> copied(this->is_directed(), this->is_weighted());
			copied.ways_to_children = ways_to_children;
			copied.ways_from_ancestors = ways_from_ancestors;
			return copied;
		}
	};
}