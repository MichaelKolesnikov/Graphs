#pragma once
#include "IILGraph.hpp"
#include <algorithm>
#include <functional>

namespace Graphs {
    template <class T>
    class UndirectedGraph : public IILGraph<T> {
    protected:
        bool dfs_cycle(Vertex<T>& v) {
            this->vertex_used[v] = 1;
            for (Edge<T> e : this->get_incident_edges(v)) {
                if (this->edge_used.count(e) == 0) {
                    this->edge_used[e] = 0;
                }
                if (!this->edge_used[e]) {
                    this->edge_used[e] = 1;
                    Vertex<T> u = v.get_neighbor(e);
                    this->origin[u] = e;
                    if (!this->vertex_used[u]) {
                        if (dfs_cycle(u)) {
                            return true;
                        }
                    } else {
                        this->cycle_st = u;
                        return true;
                    }
                }
            }
            return false;
        }
        void dfs_for_connected_components(const Vertex<T>& vertex) {
            this->vertex_used[vertex] = true;
            this->connected_components.back().push_back(vertex);
            for (auto& v : this->get_neighbors(vertex)) {
                if (!this->vertex_used[v]) {
                    dfs_for_connected_components(v);
                }
            }
        }

        std::vector<SetOfVertices<T>> _cliques;

        void bron_kerbosch(SetOfVertices<T> current_set_of_cliques, SetOfVertices<T> candidates, SetOfVertices<T> not_) {
            if (candidates.size() == 0 && not_.size() == 0) {
                this->_cliques.push_back(current_set_of_cliques);
                return;
            }
            Vertex<T> u;
            if (candidates.empty()) {
                u = *not_.begin();
            } else {
                u = *candidates.begin();
            }
            SetOfVertices<T> neighbors = this->get_neighbors(u);
            VectorOfVertices<T> result;

            std::set_difference(
                candidates.begin(), candidates.end(),
                neighbors.begin(), neighbors.end(),
                std::back_inserter(result));

            for (auto& v : result) {
                SetOfVertices<T> new_current_set_of_cliques = current_set_of_cliques;
                new_current_set_of_cliques.insert(v);
                neighbors = this->get_neighbors(v);
                VectorOfVertices<T> new_candidates;
                std::set_intersection(
                    begin(candidates), end(candidates),
                    begin(neighbors), end(neighbors),
                    std::back_inserter(new_candidates));
                VectorOfVertices<T> new_not;
                std::set_intersection(
                    begin(not_), end(not_),
                    begin(neighbors), end(neighbors),
                    std::back_inserter(new_not));
                this->bron_kerbosch(new_current_set_of_cliques, set(begin(new_candidates), end(new_candidates)), set(begin(new_not), end(new_not)));
                candidates.erase(v);
                not_.insert(v);
            }
        }

    public:
        UndirectedGraph(bool multiple_edges = false, bool weighted = false) {
            this->count_vertices = 0;
            this->count_edges = 0;
            this->directed = false;
            this->multiple_edges = multiple_edges;
            this->weighted = weighted;
        }

        bool add_edge(const Edge<T>& edge) override {
            this->add_vertex(edge.vertex1);
            this->add_vertex(edge.vertex2);

            if (this->multiple_edges) {
                this->ug[edge.vertex1].insert(edge);
                this->ug[edge.vertex2].insert(edge.get_reverse(true));
                ++this->count_edges;
                return true;
            } else if (!this->are_adjacent(edge.vertex1, edge.vertex2)) {
                this->ug[edge.vertex1].insert(edge);
                this->ug[edge.vertex2].insert(edge.get_reverse(true));
                ++this->count_edges;
                return true;
            }
            return false;
        }

        bool remove_vertex(const Vertex<T>& vertex) override {
            if (!this->search_vertex(vertex)) {
                return false;
            }
            this->remove_incident_edges(vertex);
            this->ug.erase(vertex);
            --this->count_vertices;
            return true;
        }

        bool has_cycle() override {
            this->vertex_used.clear();
            this->edge_used.clear();
            this->vector_of_vertices.clear();
            this->origin.clear();
            bool cycle_is_found = false;

            for (auto i : this->get_vertices()) {
                cycle_is_found = dfs_cycle(i);
                if (cycle_is_found) {
                    break;
                }
            }
            return cycle_is_found;
        }

        IGraph<T>& Icopy() override {
            UndirectedGraph<T>& copied = *(new UndirectedGraph<T>(this->multiple_edges));
            for (Vertex<T> v : this->get_vertices()) {
                copied.add_vertex(v);
            }
            for (auto e : this->get_edges()) {
                copied.add_edge(e);
            }
            return copied;
        }
        UndirectedGraph<T> copy() {
            UndirectedGraph<T> copied(this->multiple_edges);
            for (Vertex<T> v : this->get_vertices()) {
                copied.add_vertex(v);
            }
            for (Edge<T> e : this->get_edges()) {
                copied.add_edge(e);
            }
            return copied;
        }

        bool is_connected() {
            int count_connected_components = 0;
            this->vertex_used.clear();
            for (auto& p : this->ug) {
                auto i = p.first;
                if (!this->vertex_used[i]) {
                    if (count_connected_components == 1) {
                        this->vertex_used.clear();
                        return false;
                    }
                    this->simple_dfs(i);
                    ++count_connected_components;
                }
            }
            this->vertex_used.clear();
            return true;
        }

        bool is_bridge(const Edge<T>& edge) {
            if (!this->remove_edge(edge)) {
                return false;
            }
            bool answer = !this->is_connected();
            this->add_edge(edge);
            return answer;
        }

        vector<VectorOfVertices<T>> get_connected_components() override {
            this->connected_components.clear();
            this->vertex_used.clear();
            for (auto& i : this->get_vertices()) {
                if (!this->vertex_used[i]) {
                    this->connected_components.push_back({});
                    this->dfs_for_connected_components(i);
                }
            }
            return this->connected_components;
        }

        UndirectedGraph<T> finding_minimum_spanning_tree() {
            UndirectedGraph<T> span_tree = this->copy();
            auto set_edges = span_tree.get_edges();
            VectorOfEdges<T> edges(set_edges.begin(), set_edges.end());
            set_edges.clear();
            std::sort(edges.begin(), edges.end(), [](const Edge<T>& e1, const Edge<T>& e2) { return e1.get_weight() > e2.get_weight(); });
            for (Edge<T> e : edges) {
                if (!span_tree.is_bridge(e)) {
                    span_tree.remove_edge(e);
                }
            }
            return span_tree;
        }

        std::vector<SetOfVertices<T>> find_max_cliques(size_t max_size = INT_MAX) {
            SetOfVertices<T> current_set_of_cliques;
            SetOfVertices<T> candidates = this->get_vertices();
            SetOfVertices<T> not_;
            this->_cliques = {};
            this->bron_kerbosch(current_set_of_cliques, candidates, not_);
            return this->_cliques;
        }
    };
}