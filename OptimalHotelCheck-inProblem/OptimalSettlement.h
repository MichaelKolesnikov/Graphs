#include "Hotel.h"
#include <unordered_map>
#include <queue>
#include "..\\GG\\Graphs.h"

namespace OptimalHotelCheck_inProblem {
	using namespace Graphs;

	using T = Guest;
	Hotel get_optimal_settlement(Hotel hotel, UndirectedGraph<T> guests) {
		UndirectedGraph<T> opportunity_graph;
		// queue<pair<Hotel, SetOfVertices<Guest>>> q;
		SetOfVertices<T> vertices = guests.get_vertices();
		for (const Vertex<T>& v1 : vertices) {
			for (const Vertex<T>& v2 : vertices) {
				if (guests.are_adjacent(v1, v2)) {
					if (guests.search_edge(v1, v2).value().get_weight() == 1) {
						opportunity_graph.add_edge_(v1, v2);
					}
				}
				else if (v1.get_object().get_gender() == v2.get_object().get_gender()) {
					opportunity_graph.add_edge_(v1, v2);
				}
			}
		}
	}
}