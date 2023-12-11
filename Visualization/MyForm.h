#pragma once
#include "..\\GG\\Graphs.h"
#include <string>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;

namespace Visualization {
	Boolean directed = false;
	Boolean with_multiple_edges = false;
	Boolean weighted = false;

	Graphs::VectorOfVertices<int> vertices_000;
	Graphs::UndirectedGraph<int> graph_000(false, false);

	Graphs::VectorOfVertices<int> vertices_001;
	Graphs::UndirectedGraph<int> graph_001(false, true);

	Graphs::VectorOfVertices<int> vertices_010;
	Graphs::UndirectedGraph<int> graph_010(true, false);

	Graphs::VectorOfVertices<int> vertices_011;
	Graphs::UndirectedGraph<int> graph_011(true, true);

	Graphs::VectorOfVertices<int> vertices_100;
	Graphs::DirectedGraph<int> graph_100(false, false);

	Graphs::VectorOfVertices<int> vertices_101;
	Graphs::DirectedGraph<int> graph_101(false, true);

	Graphs::VectorOfVertices<int> vertices_110;
	Graphs::DirectedGraph<int> graph_110(true, false);

	Graphs::VectorOfVertices<int> vertices_111;
	Graphs::DirectedGraph<int> graph_111(true, true);


	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form {
	public:
		MyForm() {
			std::string filename = "output_graph.dot";
			std::string output_image = "site\\output_image.png";

			Graphs::create_dot_file(graph_000, filename);
			Graphs::create_picture(filename, output_image);
			InitializeComponent();
			this->web_browser->Refresh();
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm() {
			if (components) {
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ add_vertex;
	private: System::Windows::Forms::Button^ add_edge;
	private: System::Windows::Forms::TextBox^ box_vertex1;
	private: System::Windows::Forms::TextBox^ box_vertex2;
	private: System::Windows::Forms::WebBrowser^ web_browser;
	private: System::Windows::Forms::Button^ find_cycle;
	private: System::Windows::Forms::Button^ remove_vertex;
	private: System::Windows::Forms::Button^ remove_edge;
	private: System::Windows::Forms::Button^ make_undirected;
	private: System::Windows::Forms::Button^ make_directed;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ make_weighted;

	private: System::Windows::Forms::Button^ make_unweighted;
	private: System::Windows::Forms::Button^ make_with_multiple_edges;


	private: System::Windows::Forms::Button^ make_without_multiple_edges;

	private: System::Windows::Forms::Label^ label3;



	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void) {
			this->add_vertex = (gcnew System::Windows::Forms::Button());
			this->add_edge = (gcnew System::Windows::Forms::Button());
			this->box_vertex1 = (gcnew System::Windows::Forms::TextBox());
			this->box_vertex2 = (gcnew System::Windows::Forms::TextBox());
			this->web_browser = (gcnew System::Windows::Forms::WebBrowser());
			this->find_cycle = (gcnew System::Windows::Forms::Button());
			this->remove_vertex = (gcnew System::Windows::Forms::Button());
			this->remove_edge = (gcnew System::Windows::Forms::Button());
			this->make_undirected = (gcnew System::Windows::Forms::Button());
			this->make_directed = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->make_weighted = (gcnew System::Windows::Forms::Button());
			this->make_unweighted = (gcnew System::Windows::Forms::Button());
			this->make_with_multiple_edges = (gcnew System::Windows::Forms::Button());
			this->make_without_multiple_edges = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// add_vertex
			// 
			this->add_vertex->Location = System::Drawing::Point(1135, 12);
			this->add_vertex->Name = L"add_vertex";
			this->add_vertex->Size = System::Drawing::Size(135, 40);
			this->add_vertex->TabIndex = 5;
			this->add_vertex->Text = L"add_vertex";
			this->add_vertex->UseVisualStyleBackColor = true;
			this->add_vertex->Click += gcnew System::EventHandler(this, &MyForm::add_vertex_Click);
			// 
			// add_edge
			// 
			this->add_edge->Location = System::Drawing::Point(1135, 58);
			this->add_edge->Name = L"add_edge";
			this->add_edge->Size = System::Drawing::Size(135, 39);
			this->add_edge->TabIndex = 6;
			this->add_edge->Text = L"add_edge";
			this->add_edge->UseVisualStyleBackColor = true;
			this->add_edge->Click += gcnew System::EventHandler(this, &MyForm::add_edge_Click);
			// 
			// box_vertex1
			// 
			this->box_vertex1->Location = System::Drawing::Point(1011, 58);
			this->box_vertex1->Name = L"box_vertex1";
			this->box_vertex1->Size = System::Drawing::Size(100, 22);
			this->box_vertex1->TabIndex = 7;
			// 
			// box_vertex2
			// 
			this->box_vertex2->Location = System::Drawing::Point(1011, 86);
			this->box_vertex2->Name = L"box_vertex2";
			this->box_vertex2->Size = System::Drawing::Size(100, 22);
			this->box_vertex2->TabIndex = 8;
			// 
			// web_browser
			// 
			this->web_browser->Location = System::Drawing::Point(12, 12);
			this->web_browser->MinimumSize = System::Drawing::Size(20, 20);
			this->web_browser->Name = L"web_browser";
			this->web_browser->ScrollBarsEnabled = false;
			this->web_browser->Size = System::Drawing::Size(956, 529);
			this->web_browser->TabIndex = 9;
			this->web_browser->Url = (gcnew System::Uri(L"D:\\VisualStudioProjects\\GG\\Visualization\\site\\index.html", System::UriKind::Absolute));
			// 
			// find_cycle
			// 
			this->find_cycle->Location = System::Drawing::Point(1135, 193);
			this->find_cycle->Name = L"find_cycle";
			this->find_cycle->Size = System::Drawing::Size(135, 38);
			this->find_cycle->TabIndex = 10;
			this->find_cycle->Text = L"find_cycle";
			this->find_cycle->UseVisualStyleBackColor = true;
			this->find_cycle->Click += gcnew System::EventHandler(this, &MyForm::find_cycle_Click);
			// 
			// remove_vertex
			// 
			this->remove_vertex->Location = System::Drawing::Point(1135, 103);
			this->remove_vertex->Name = L"remove_vertex";
			this->remove_vertex->Size = System::Drawing::Size(135, 39);
			this->remove_vertex->TabIndex = 11;
			this->remove_vertex->Text = L"remove_vertex";
			this->remove_vertex->UseVisualStyleBackColor = true;
			this->remove_vertex->Click += gcnew System::EventHandler(this, &MyForm::remove_vertex_Click);
			// 
			// remove_edge
			// 
			this->remove_edge->Location = System::Drawing::Point(1135, 149);
			this->remove_edge->Name = L"remove_edge";
			this->remove_edge->Size = System::Drawing::Size(135, 38);
			this->remove_edge->TabIndex = 12;
			this->remove_edge->Text = L"remove_edge";
			this->remove_edge->UseVisualStyleBackColor = true;
			this->remove_edge->Click += gcnew System::EventHandler(this, &MyForm::remove_edge_Click);
			// 
			// make_undirected
			// 
			this->make_undirected->Location = System::Drawing::Point(975, 409);
			this->make_undirected->Name = L"make_undirected";
			this->make_undirected->Size = System::Drawing::Size(50, 30);
			this->make_undirected->TabIndex = 13;
			this->make_undirected->Text = L"No";
			this->make_undirected->UseVisualStyleBackColor = true;
			this->make_undirected->Click += gcnew System::EventHandler(this, &MyForm::make_undirected_Click);
			// 
			// make_directed
			// 
			this->make_directed->Location = System::Drawing::Point(1071, 409);
			this->make_directed->Name = L"make_directed";
			this->make_directed->Size = System::Drawing::Size(50, 30);
			this->make_directed->TabIndex = 14;
			this->make_directed->Text = L"Yes";
			this->make_directed->UseVisualStyleBackColor = true;
			this->make_directed->Click += gcnew System::EventHandler(this, &MyForm::make_directed_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(974, 390);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(76, 16);
			this->label1->TabIndex = 17;
			this->label1->Text = L"Is directed\?";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(974, 494);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(81, 16);
			this->label2->TabIndex = 18;
			this->label2->Text = L"Is weighted\?";
			// 
			// make_weighted
			// 
			this->make_weighted->Location = System::Drawing::Point(1071, 513);
			this->make_weighted->Name = L"make_weighted";
			this->make_weighted->Size = System::Drawing::Size(50, 30);
			this->make_weighted->TabIndex = 20;
			this->make_weighted->Text = L"Yes";
			this->make_weighted->UseVisualStyleBackColor = true;
			this->make_weighted->Click += gcnew System::EventHandler(this, &MyForm::make_weighted_Click);
			// 
			// make_unweighted
			// 
			this->make_unweighted->Location = System::Drawing::Point(975, 513);
			this->make_unweighted->Name = L"make_unweighted";
			this->make_unweighted->Size = System::Drawing::Size(50, 30);
			this->make_unweighted->TabIndex = 19;
			this->make_unweighted->Text = L"No";
			this->make_unweighted->UseVisualStyleBackColor = true;
			this->make_unweighted->Click += gcnew System::EventHandler(this, &MyForm::make_unweighted_Click);
			// 
			// make_with_multiple_edges
			// 
			this->make_with_multiple_edges->Location = System::Drawing::Point(1071, 461);
			this->make_with_multiple_edges->Name = L"make_with_multiple_edges";
			this->make_with_multiple_edges->Size = System::Drawing::Size(50, 30);
			this->make_with_multiple_edges->TabIndex = 23;
			this->make_with_multiple_edges->Text = L"Yes";
			this->make_with_multiple_edges->UseVisualStyleBackColor = true;
			this->make_with_multiple_edges->Click += gcnew System::EventHandler(this, &MyForm::make_with_multiple_edges_Click);
			// 
			// make_without_multiple_edges
			// 
			this->make_without_multiple_edges->Location = System::Drawing::Point(975, 461);
			this->make_without_multiple_edges->Name = L"make_without_multiple_edges";
			this->make_without_multiple_edges->Size = System::Drawing::Size(50, 30);
			this->make_without_multiple_edges->TabIndex = 22;
			this->make_without_multiple_edges->Text = L"No";
			this->make_without_multiple_edges->UseVisualStyleBackColor = true;
			this->make_without_multiple_edges->Click += gcnew System::EventHandler(this, &MyForm::make_without_multiple_edges_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(974, 442);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(131, 16);
			this->label3->TabIndex = 21;
			this->label3->Text = L"With multiple edges\?";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1282, 553);
			this->Controls->Add(this->make_with_multiple_edges);
			this->Controls->Add(this->make_without_multiple_edges);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->make_weighted);
			this->Controls->Add(this->make_unweighted);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->make_directed);
			this->Controls->Add(this->make_undirected);
			this->Controls->Add(this->remove_edge);
			this->Controls->Add(this->remove_vertex);
			this->Controls->Add(this->find_cycle);
			this->Controls->Add(this->web_browser);
			this->Controls->Add(this->box_vertex2);
			this->Controls->Add(this->box_vertex1);
			this->Controls->Add(this->add_edge);
			this->Controls->Add(this->add_vertex);
			this->Name = L"MyForm";
			this->Text = L"Graph";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void update_picture_graph() {
			std::string filename = "output_graph.dot";
			std::string output_image = "site\\output_image.png";

			auto graph = get_current_graph();
			Graphs::create_dot_file(*graph, filename);
			Graphs::create_picture(filename, output_image);
			this->web_browser->Refresh();
		}

		Graphs::IGraph<int>* get_current_graph() {
			Graphs::IGraph<int>* graph = nullptr;
			if (directed == false) {
				if (with_multiple_edges == false) {
					if (weighted == false) {
						graph = &graph_000;
					}
					else {
						graph = &graph_001;
					}
				}
				else {
					if (weighted == false) {
						graph = &graph_010;
					}
					else {
						graph = &graph_011;
					}
				}
			}
			else {
				if (with_multiple_edges == false) {
					if (weighted == false) {
						graph = &graph_100;
					}
					else {
						graph = &graph_101;
					}
				}
				else {
					if (weighted == false) {
						graph = &graph_110;
					}
					else {
						graph = &graph_111;
					}
				}
			}
			return graph;
		}

		Graphs::VectorOfVertices<int>* get_current_vertices() {
			Graphs::VectorOfVertices<int>* vertices = nullptr;
			if (directed == false) {
				if (with_multiple_edges == false) {
					if (weighted == false) {
						vertices = &vertices_000;
					}
					else {
						vertices = &vertices_001;
					}
				}
				else {
					if (weighted == false) {
						vertices = &vertices_010;
					}
					else {
						vertices = &vertices_011;
					}
				}
			}
			else {
				if (with_multiple_edges == false) {
					if (weighted == false) {
						vertices = &vertices_100;
					}
					else {
						vertices = &vertices_101;
					}
				}
				else {
					if (weighted == false) {
						vertices = &vertices_110;
					}
					else {
						vertices = &vertices_111;
					}
				}
			}
			return vertices;
		}
#pragma endregion

		private: System::Void add_vertex_Click(System::Object^ sender, System::EventArgs^ e) {
			auto graph = get_current_graph();
			auto& vertices = *get_current_vertices();
			int n = graph->get_count_vertices();
			vertices.push_back(Graphs::Vertex<int>(n));
			graph->add_vertex(vertices.back());
			update_picture_graph();
		}
		private: System::Void add_edge_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ text1 = this->box_vertex1->Text;
			String^ text2 = this->box_vertex2->Text;
			int v1, v2;
			if (!(Int32::TryParse(text1, v1) && Int32::TryParse(text2, v2))) {
				return;
			}
			auto graph = get_current_graph();
			auto& vertices = *get_current_vertices();
			int n = graph->get_count_vertices();
			if (v1 < n && v2 < n) {
				graph->add_edge({ vertices[v1], vertices[v2] });
				update_picture_graph();
			}
		}
		private: System::Void find_cycle_Click(System::Object^ sender, System::EventArgs^ e) {
			auto graph = get_current_graph();
			auto& vertices = *get_current_vertices();
			auto cycle = graph->get_the_cycle();
			auto set_cycle = Graphs::Edges<int>(begin(cycle), end(cycle));
			cycle.clear();
			std::string filename = "output_graph.dot";
			std::string output_image = "site\\output_image.png";

			Graphs::create_dot_file(*graph, filename, &set_cycle);
			Graphs::create_picture(filename, output_image);
			this->web_browser->Refresh();
		}
		private: System::Void remove_vertex_Click(System::Object^ sender, System::EventArgs^ e) {
			auto graph = get_current_graph();
			auto& vertices = *get_current_vertices();
			if (vertices.size() == 0) {
				return;
			}
			graph->remove_vertex(vertices.back());
			vertices.pop_back();
			update_picture_graph();
		}
		private: System::Void remove_edge_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ text1 = this->box_vertex1->Text;
			String^ text2 = this->box_vertex2->Text;
			int v1, v2;
			if (!(Int32::TryParse(text1, v1) && Int32::TryParse(text2, v2))) {
				return;
			}
			auto graph = get_current_graph();
			auto& vertices = *get_current_vertices();
			int n = graph->get_count_vertices();
			if (v1 < n && v2 < n) {
				graph->remove_edges_from_to(vertices[v1], vertices[v2]);
				update_picture_graph();
			}
		}

		private: System::Void make_undirected_Click(System::Object^ sender, System::EventArgs^ e) {
			directed = false;
			update_picture_graph();
		}
		private: System::Void make_directed_Click(System::Object^ sender, System::EventArgs^ e) {
			directed = true;
			update_picture_graph();
		}
		private: System::Void make_unweighted_Click(System::Object^ sender, System::EventArgs^ e) {
			weighted = false;
			update_picture_graph();
		}
		private: System::Void make_weighted_Click(System::Object^ sender, System::EventArgs^ e) {
			weighted = true;
			update_picture_graph();
		}
		private: System::Void make_without_multiple_edges_Click(System::Object^ sender, System::EventArgs^ e) {
			with_multiple_edges = false;
			update_picture_graph();
		}
		private: System::Void make_with_multiple_edges_Click(System::Object^ sender, System::EventArgs^ e) {
			with_multiple_edges = true;
			update_picture_graph();
		}
	};
}
