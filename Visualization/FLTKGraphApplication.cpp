#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_PNG_Image.H>
#include <iostream>
#include <string>
#include "../Graphs/Graphs.hpp"
#include <random>

using namespace std;

std::string generate_random_color() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    int r = dis(gen);
    int g = dis(gen);
    int b = dis(gen);

    char color[8];
    snprintf(color, sizeof(color), "#%02X%02X%02X", r, g, b);
    return std::string(color);
}

class GraphApp : public Fl_Double_Window {
private:
    Fl_Input *vertex1_input, *vertex2_input, *weight_input;
    Fl_Text_Display* top_sort_result_text_display;
    Fl_Text_Buffer* top_sort_result_text_buffer;
    Fl_Button *add_vertex_button, *add_edge_button, *remove_vertex_button, *remove_edge_button,
        *find_cycle_button, *top_sort_button, *min_span_tree_button, *comps_button, *min_path_button, *find_cliques_button;
    Fl_Check_Button *directed_check, *weighted_check, *multiple_edges_check;
    Fl_Box* graph_display;
    Fl_PNG_Image* graph_image;

    bool directed = false;
    bool weighted = false;
    bool with_multiple_edges = false;
    Graphs::DictOfVertices<string> vertices_000, vertices_001, vertices_010, vertices_011, vertices_100, vertices_101, vertices_110, vertices_111;
    Graphs::UndirectedGraph<string> graph_000, graph_001, graph_010, graph_011;
    Graphs::DirectedGraph<string> graph_100, graph_101, graph_110, graph_111;
    Graphs::IGraph<string>* get_current_graph() {
        Graphs::IGraph<string>* graph = nullptr;
        if (directed == false) {
            if (with_multiple_edges == false) {
                if (weighted == false) {
                    graph = &graph_000;
                } else {
                    graph = &graph_001;
                }
            } else {
                if (weighted == false) {
                    graph = &graph_010;
                } else {
                    graph = &graph_011;
                }
            }
        } else {
            if (with_multiple_edges == false) {
                if (weighted == false) {
                    graph = &graph_100;
                } else {
                    graph = &graph_101;
                }
            } else {
                if (weighted == false) {
                    graph = &graph_110;
                } else {
                    graph = &graph_111;
                }
            }
        }
        return graph;
    }
    Graphs::DictOfVertices<string>* get_current_vertices() {
        Graphs::DictOfVertices<string>* vertices = nullptr;
        if (directed == false) {
            if (with_multiple_edges == false) {
                if (weighted == false) {
                    vertices = &vertices_000;
                } else {
                    vertices = &vertices_001;
                }
            } else {
                if (weighted == false) {
                    vertices = &vertices_010;
                } else {
                    vertices = &vertices_011;
                }
            }
        } else {
            if (with_multiple_edges == false) {
                if (weighted == false) {
                    vertices = &vertices_100;
                } else {
                    vertices = &vertices_101;
                }
            } else {
                if (weighted == false) {
                    vertices = &vertices_110;
                } else {
                    vertices = &vertices_111;
                }
            }
        }
        return vertices;
    }

    std::string filename = "output_graph.dot";
    std::string output_image = "output_image.png";
    void refresh_picture() {
        delete graph_image;
        graph_image = new Fl_PNG_Image(output_image.c_str());
        graph_display->image(graph_image);
        graph_display->redraw();
    }
    void update_graph_display() {
        auto current_graph = get_current_graph();
        Graphs::create_dot_file(*current_graph, filename);
        Graphs::create_picture(filename, output_image);
        this->refresh_picture();
    }

public:
    GraphApp() : Fl_Double_Window(800, 600, "FLTK Graph Application"),
                 graph_000(false, false), graph_001(false, true), graph_010(true, false),
                 graph_011(true, true), graph_100(false, false), graph_101(false, true),
                 graph_110(true, false), graph_111(true, true) {

        vertex1_input = new Fl_Input(100, 10, 120, 25, "Vertex 1:");
        vertex2_input = new Fl_Input(100, 40, 120, 25, "Vertex 2:");
        weight_input = new Fl_Input(100, 70, 120, 25, "Weight:");

        add_vertex_button = new Fl_Button(230, 10, 120, 25, "Add Vertex");
        add_edge_button = new Fl_Button(230, 40, 120, 25, "Add Edge");
        remove_vertex_button = new Fl_Button(230, 70, 120, 25, "Remove Vertex");
        remove_edge_button = new Fl_Button(230, 100, 120, 25, "Remove Edge");

        find_cycle_button = new Fl_Button(360, 10, 120, 25, "Find Cycle");
        min_span_tree_button = new Fl_Button(360, 70, 120, 25, "Span tree");
        comps_button = new Fl_Button(360, 100, 120, 25, "Comps");
        min_path_button = new Fl_Button(360, 100, 120, 25, "Min path");
        top_sort_button = new Fl_Button(230, 130, 120, 25, "Top sort");
        top_sort_button->deactivate();
        top_sort_result_text_display = new Fl_Text_Display(230, 160, 120, 40);
        top_sort_result_text_buffer = new Fl_Text_Buffer();
        top_sort_result_text_display->buffer(top_sort_result_text_buffer);
        find_cliques_button = new Fl_Button(360, 130, 120, 25, "Find clique");

        directed_check = new Fl_Check_Button(10, 130, 120, 25, "Directed");
        weighted_check = new Fl_Check_Button(10, 160, 120, 25, "Weighted");
        multiple_edges_check = new Fl_Check_Button(10, 190, 120, 25, "Multiple Edges");

        graph_display = new Fl_Box(10, 220, 780, 370);
        graph_display->box(FL_FLAT_BOX);
        graph_display->color(FL_WHITE);

        directed = false;
        weighted = false;
        with_multiple_edges = false;

        add_vertex_button->callback(static_add_vertex_cb, this);
        add_edge_button->callback(static_add_edge_cb, this);
        remove_vertex_button->callback(static_remove_vertex_cb, this);
        remove_edge_button->callback(static_remove_edge_cb, this);

        find_cycle_button->callback(static_find_cycle_cb, this);
        find_cliques_button->callback(static_find_cliques_cb, this);
        min_span_tree_button->callback(static_min_span_tree_cb, this);
        comps_button->callback(static_comps_cb, this);
        min_path_button->callback(static_min_path_cb, this);
        top_sort_button->callback(static_top_sort_cb, this);

        directed_check->callback(static_toggle_directed_cb, this);
        weighted_check->callback(static_toggle_weighted_cb, this);
        multiple_edges_check->callback(static_toggle_multiple_edges_cb, this);

        end();
        update_graph_display();
    }

    static void static_add_vertex_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->add_vertex_cb(); }
    static void static_add_edge_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->add_edge_cb(); }
    static void static_remove_vertex_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->remove_vertex_cb(); }
    static void static_remove_edge_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->remove_edge_cb(); }

    static void static_find_cycle_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->find_cycle_cb(); }
    static void static_find_cliques_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->find_cliques_cb(); }
    static void static_min_span_tree_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->min_span_tree_cb(); }
    static void static_comps_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->comps_cb(); }
    static void static_min_path_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->min_path_cb(); }
    static void static_top_sort_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->top_sort_cb(); }

    static void static_toggle_directed_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->toggle_directed_cb(); }
    static void static_toggle_weighted_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->toggle_weighted_cb(); }
    static void static_toggle_multiple_edges_cb(Fl_Widget* w, void* v) { ((GraphApp*)v)->toggle_multiple_edges_cb(); }

    void add_vertex_cb() {
        auto current_vertices = get_current_vertices();
        auto current_graph = get_current_graph();
        std::string vertex = vertex1_input->value();
        if (!vertex.empty() && current_vertices->find(vertex) == current_vertices->end()) {
            (*current_vertices)[vertex] = Graphs::Vertex<std::string>(vertex);
            current_graph->add_vertex((*current_vertices)[vertex]);
            update_graph_display();
        }
    }
    void add_edge_cb() {
        auto current_vertices = get_current_vertices();
        auto current_graph = get_current_graph();
        std::string v1 = vertex1_input->value();
        std::string v2 = vertex2_input->value();
        int weight = 1;
        if (weighted) {
            weight = std::stoi(weight_input->value());
        }
        if (current_vertices->find(v1) == current_vertices->end()) {
            (*current_vertices)[v1] = Graphs::Vertex<std::string>(v1);
            current_graph->add_vertex((*current_vertices)[v1]);
            update_graph_display();
        }
        if (current_vertices->find(v2) == current_vertices->end()) {
            (*current_vertices)[v2] = Graphs::Vertex<std::string>(v2);
            current_graph->add_vertex((*current_vertices)[v2]);
            update_graph_display();
        }
        current_graph->add_edge({(*current_vertices)[v1], (*current_vertices)[v2], weighted, weight});
        update_graph_display();
    }
    void remove_vertex_cb() {
        auto current_vertices = get_current_vertices();
        auto current_graph = get_current_graph();
        std::string vertex = vertex1_input->value();
        if (current_vertices->find(vertex) != current_vertices->end()) {
            current_graph->remove_vertex((*current_vertices)[vertex]);
            current_vertices->erase(vertex);
            update_graph_display();
        }
    }
    void remove_edge_cb() {
        auto current_vertices = get_current_vertices();
        auto current_graph = get_current_graph();
        std::string v1 = vertex1_input->value();
        std::string v2 = vertex2_input->value();
        if (current_vertices->find(v1) != current_vertices->end() &&
            current_vertices->find(v2) != current_vertices->end()) {
            current_graph->remove_edges_from_to((*current_vertices)[v1], (*current_vertices)[v2]);
            update_graph_display();
        }
    }

    void find_cycle_cb() {
        auto current_vertices = get_current_vertices();
        auto current_graph = get_current_graph();
        auto cycle = current_graph->get_the_cycle();
        std::unordered_map<Graphs::Edge<std::string>, std::string, Graphs::EdgeHash<std::string>> colors;
        for (auto& e : cycle) {
            colors[e] = "red";
        }
        Graphs::create_dot_file(*current_graph, filename, "black", &colors);
        Graphs::create_picture(filename, output_image);
        refresh_picture();
    }
    void find_cliques_cb() {
        auto g = get_current_graph();
        auto und = dynamic_cast<Graphs::UndirectedGraph<string>*>(g);
        auto clique = und->find_max_cliques()[0];

        Graphs::VertexColors<string> c;
        for (auto& v : clique) {
            c[v] = "red";
        }

        Graphs::create_dot_file(*und, filename, "black", static_cast<Graphs::EdgeColors<string>*>(nullptr), &c);
        Graphs::create_picture(filename, output_image);
        refresh_picture();
    }
    void min_span_tree_cb() {
        auto g = get_current_graph();
        auto& vertices = *get_current_vertices();
        auto graph = dynamic_cast<Graphs::UndirectedGraph<string>*>(g);
        auto span = graph->finding_minimum_spanning_tree();
        auto set_ = span.get_edges();
        auto colors = Graphs::EdgeColors<string>();
        for (auto& it : set_) {
            colors[it] = "green";
        }

        Graphs::create_dot_file(*graph, filename, "black", &colors);
        Graphs::create_picture(filename, output_image);
        refresh_picture();
    }
    void comps_cb() {
        auto g = get_current_graph();
        auto comps = g->get_connected_components();

        std::ofstream dotFile(filename);
        string edge_s = " -- ";
        if (g->is_directed()) {
            edge_s[2] = '>';
            dotFile << "di";
        }

        dotFile << "graph G {" << std::endl;

        int num_cluster = 0;
        for (auto& vv : comps) {
            dotFile << "subgraph cluster_" << ++num_cluster << " {" << endl;
            for (auto& v : vv) {
                dotFile << v.get_object() << ";\n";
            }
            dotFile << "}" << endl;
        }

        for (Graphs::Edge<string> edge : g->get_edges()) {
            dotFile << edge.vertex1.get_object() << edge_s << edge.vertex2.get_object();
            dotFile << " [";
            if (g->is_weighted()) {
                dotFile << "label=" << edge.get_weight();
            }
            dotFile << "]" << std::endl;
            dotFile << ";" << std::endl;
        }
        dotFile << "}" << std::endl;
        dotFile.close();

        Graphs::create_picture(filename, output_image);
        refresh_picture();
    }
    void min_path_cb() {
        string s1 = vertex1_input->value();
        string s2 = vertex2_input->value();
        auto graph = get_current_graph();
        auto vertices = get_current_vertices();
        if (vertices->find(s1) == vertices->end() || vertices->find(s2) == vertices->end()) {
            return;
        }
        auto path = graph->shortest_way(vertices->at(s1), vertices->at(s2));

        auto colors = Graphs::EdgeColors<string>();
        for (auto& it : path) {
            colors[it] = "yellow";
        }
        Graphs::create_dot_file(*graph, filename, "black", &colors);
        Graphs::create_picture(filename, output_image);
        refresh_picture();
    }
    void top_sort_cb() {
        auto graph = get_current_graph();
        auto dg = dynamic_cast<Graphs::DirectedGraph<string>*>(graph);
        auto ts = dg->topological_sorting();
        if (ts.size() == 0) {
            this->top_sort_result_text_buffer->text("Impossible");
            return;
        }
        std::stringstream ss;
        ss << "{rank=same; ";
        for (auto v : ts) {
            ss << v.get_object() << "; ";
        }
        ss << "}";
        std::string additional_command = ss.str();
        top_sort_result_text_buffer->text(additional_command.c_str());

        Graphs::create_dot_file(*graph, filename, "black", static_cast<Graphs::EdgeColors<string>*>(nullptr), static_cast<Graphs::VertexColors<string>*>(nullptr), "", additional_command);
        Graphs::create_picture(filename, output_image);

        refresh_picture();
    }

    void toggle_directed_cb() {
        auto current_vertices = get_current_vertices();
        auto current_graph = get_current_graph();
        directed = directed_check->value();
        if (directed) {
            find_cliques_button->deactivate();
            top_sort_button->activate();
        } else {
            find_cliques_button->activate();
            top_sort_button->deactivate();
        }
        current_graph = get_current_graph();
        update_graph_display();
    }
    void toggle_weighted_cb() {
        auto current_vertices = get_current_vertices();
        auto current_graph = get_current_graph();
        weighted = weighted_check->value();
        current_graph = get_current_graph();
        update_graph_display();
    }
    void toggle_multiple_edges_cb() {
        auto current_vertices = get_current_vertices();
        auto current_graph = get_current_graph();
        with_multiple_edges = multiple_edges_check->value();
        current_graph = get_current_graph();
        update_graph_display();
    }
};

int main(int argc, char* argv[]) {
    GraphApp* app = new GraphApp();
    app->show();
    return Fl::run();
}
