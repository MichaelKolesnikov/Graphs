#include "..\\GG\\Graphs.h"
#include "Hotel.h"

using namespace std;
using namespace Graphs;

int main() {
	Graphs::Tree<int> tree;

	VectorOfVertices<int> v;
	create_vertices(v, 10);

	tree.add_vertex(v[0]);
	tree.add_child(v[0], v[1]);
	tree.add_child(v[0], v[2]);
	tree.add_child(v[1], v[4]);
	tree.add_child(v[0], v[9]);
	tree.add_child(v[0], v[10]);

	output_graph(tree);
}

