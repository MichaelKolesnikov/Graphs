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

using namespace std;

class GraphApp : public Fl_Double_Window {
private:
    Fl_Input *vertex1_input, *vertex2_input, *weight_input;
    Fl_Button *add_vertex_button, *add_edge_button, *remove_vertex_button, *remove_edge_button, *find_cycle_button;
    Fl_Check_Button *directed_check, *weighted_check, *multiple_edges_check;
    Fl_Box* graph_display;
    Fl_PNG_Image* graph_image;

    bool directed = false;
    bool weighted = false;
    bool with_multiple_edges = false;
    Graphs::DictOfVertices<string> vertices_000, vertices_001, vertices_010, vertices_011, vertices_100, vertices_101, vertices_110, vertices_111;
    Graphs::UndirectedGraph<string> graph_000, graph_001, graph_010, graph_011, graph_100, graph_101, graph_110, graph_111;

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

    void update_graph_display() {
        std::string filename = "output_graph.dot";
        std::string output_image = "output_image.png";
        auto current_graph = get_current_graph();
        Graphs::create_dot_file(*current_graph, filename);
        Graphs::create_picture(filename, output_image);

        delete graph_image;
        graph_image = new Fl_PNG_Image(output_image.c_str());
        graph_display->image(graph_image);
        graph_display->redraw();
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
        find_cycle_button = new Fl_Button(230, 130, 120, 25, "Find Cycle");

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
        if (current_vertices->find(v1) != current_vertices->end() &&
            current_vertices->find(v2) != current_vertices->end()) {
            current_graph->add_edge({(*current_vertices)[v1], (*current_vertices)[v2], weighted, weight});
            update_graph_display();
        }
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
        std::string filename = "output_graph.dot";
        std::string output_image = "output_image.png";
        Graphs::create_dot_file(*current_graph, filename, "black", &colors);
        Graphs::create_picture(filename, output_image);
        delete graph_image;
        graph_image = new Fl_PNG_Image(output_image.c_str());
        graph_display->image(graph_image);
        graph_display->redraw();
    }

    void toggle_directed_cb() {
        auto current_vertices = get_current_vertices();
        auto current_graph = get_current_graph();
        directed = directed_check->value();
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
