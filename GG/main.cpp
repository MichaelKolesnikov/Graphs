#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include "Graphs.h"
#include "ioGraph.h"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace Graphs;



int main() {
	string filename = "output_graph.dot";
	string output_image = "site\\output_image.png";

	int n = 5;
	VectorOfVertices<int> v;
	create_vertices(v, n);
	Graphs::UndirectedGraph<int> graph;
	put_the_vertices_in_the_graph(graph, v);
	graph.add_edge({ v[1], v[2] });
	graph.add_edge({ v[2], v[3] });
	graph.add_edge({ v[2], v[4] });
	graph.add_edge({ v[2], v[5] });

	create_dot_file(graph, filename);

	string command = "dot -Tpng " + filename + " -o " + output_image;
	system(command.c_str());

}
