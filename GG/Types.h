#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <memory>
#include <set>
#include <stdexcept>

namespace Graphs {
	using namespace std;

	template <class T>
	class Vertex;
	template <class T>
	class Edge;

	template <class T>
	class Vertex {
	private:
		static inline uint64_t vertex_id_free = 0;
		uint64_t vertex_id;
		shared_ptr<T> ptr_to_object;
	public:
		Vertex() : ptr_to_object(new T()), vertex_id(++vertex_id_free) {}
		Vertex(const T& object) : ptr_to_object(new T(object)), vertex_id(++vertex_id_free) {}

		T& get_object() const {
			return *ptr_to_object;
		}
		void change_object(T& object) {
			ptr_to_object = shared_ptr<T>(new T(object));
		}
		uint64_t get_code() const {
			return vertex_id;
		}

		Vertex<T> get_neighbor(const Edge<T>& edge) const {
			if (edge.vertex1 == *this) {
				return edge.vertex2;
			}
			return edge.vertex1;
		}

		bool operator==(const Vertex<T>& other) const {
			return this->get_code() == other.get_code();
		}
		bool operator!=(const Vertex<T>& other) const {
			return !(this->operator==(other));
		}
		bool operator<(const Vertex<T>& other) const {
			return this->get_code() < other.get_code();
		}

		bool is_incidental(const Edge<T>& edge) const {
			return *this == edge.vertex1 || *this == edge.vertex2;
		}
	};
	template <class T>
	struct VertexHash {
		std::size_t operator()(const Vertex<T>& vertex) const {
			return std::hash<uint64_t>()(vertex.get_code());
		}
	};
	template <class T>
	using SetOfVertices = set<Vertex<T>>;
	template <class T>
	using VectorOfVertices = vector<Vertex<T>>;
	template <class T>
	using DictOfVertices = unordered_map<T, Vertex<T>>;

	template <class T>
	class Edge {
	protected:
		static inline int edge_id_free = 0;
		int edge_id;
		int weight;
		bool weighted;
	public:
		Vertex<T> vertex1, vertex2;
		Edge() : edge_id(++edge_id_free), weighted(false) {}
		Edge(const Vertex<T>& vertex1, const Vertex<T>& vertex2, bool weighted = false, int weight = 1) : vertex1(vertex1), vertex2(vertex2), edge_id(++edge_id_free), weighted(weighted), weight(weight) {}

		Edge<T> get_reverse(bool equal = false) const {
			if (equal) {
				Edge<T> e = *this;
				Vertex<T> tmp = e.vertex1;
				e.vertex1 = e.vertex2;
				e.vertex2 = tmp;
				return e;
			}
			return Edge<T>(vertex2, vertex1);
		}

		uint64_t get_id() const {
			return edge_id;
		}
		int get_weight() const {
			if (weighted) {
				return this->weight;
			}
			return this->get_id();
		}

		bool is_loop(const Edge<T>& other) const {
			return other.vertex1 == other.vertex2;
		}

		bool is_positively_incidental(Vertex<T> vertex) {
			return vertex == vertex1;
		}
		bool is_negatively_incidental(Vertex<T> vertex) {
			return vertex == vertex2;
		}
		bool is_incidental(Vertex<T> vertex) {
			return this->is_positively_incidental(vertex) || this->is_negatively_incidental(vertex);
		}

		bool operator==(const Edge<T>& other) const {
			return this->edge_id == other.edge_id;
		}
		bool operator!=(const Edge<T>& other) const {
			return !this->operator==(other);
		}
		bool operator<(const Edge<T>& other) const {
			return this->edge_id < other.edge_id;
		}

		Vertex<T> get_neighbor(const Vertex<T>& vertex) const {
			if (vertex1 == vertex) {
				return vertex2;
			}
			return vertex1;
		}
	};
	template <class T>
	struct EdgeHash {
		std::size_t operator()(const Edge<T>& edge) const {
			return std::hash<uint64_t>()(edge.get_id());
		}
	};
	template <class T>
	using Edges = set<Edge<T>>;
	template <class T>
	using VectorOfEdges = vector<Edge<T>>;

	template <class T>
	using HandleILGraph = unordered_map<Vertex<T>, Edges<T>, VertexHash<T>>;
	template <class T>
	using HandleALGraph = unordered_map<Vertex<T>, VectorOfVertices<T>, VertexHash<T>>;

	template <class T>
	using Ancestors = unordered_map<Vertex<T>, Vertex<T>, VertexHash<T>>;
	template <class T>
	using EdgeOfOrigin = unordered_map<Vertex<T>, Edge<T>, VertexHash<T>>;
	template <class T>
	using Distances = unordered_map<Vertex<T>, int, VertexHash<T>>;
	template <class T>
	using Colors = unordered_map<Vertex<T>, int, VertexHash<T>>;
	template <class T>
	using EdgeColors = unordered_map<Edge<T>, string, EdgeHash<T>>;
	template <class T>
	using TypeForCheckUsingVertex = unordered_map<Vertex<T>, int, VertexHash<T>>;
	template <class T>
	using TypeForCheckUsingEdge = unordered_map<Edge<T>, bool, EdgeHash<T>>;
};