#pragma once
#include "..\\GG\\Graphs.h"
#include <sstream>
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace msclr::interop;

namespace Visualization {
	using namespace std;
	bool directed = false;
	bool with_multiple_edges = false;
	bool weighted = false;

	Graphs::DictOfVertices<string> vertices_000;
	Graphs::UndirectedGraph<string> graph_000(false, false);

	Graphs::DictOfVertices<string> vertices_001;
	Graphs::UndirectedGraph<string> graph_001(false, true);

	Graphs::DictOfVertices<string> vertices_010;
	Graphs::UndirectedGraph<string> graph_010(true, false);

	Graphs::DictOfVertices<string> vertices_011;
	Graphs::UndirectedGraph<string> graph_011(true, true);

	Graphs::DictOfVertices<string> vertices_100;
	Graphs::DirectedGraph<string> graph_100(false, false);

	Graphs::DictOfVertices<string> vertices_101;
	Graphs::DirectedGraph<string> graph_101(false, true);

	Graphs::DictOfVertices<string> vertices_110;
	Graphs::DirectedGraph<string> graph_110(true, false);

	Graphs::DictOfVertices<string> vertices_111;
	Graphs::DirectedGraph<string> graph_111(true, true);

	Graphs::IGraph<string>* get_current_graph() {
		Graphs::IGraph<string>* graph = nullptr;
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
	Graphs::DictOfVertices<string>* get_current_vertices() {
		Graphs::DictOfVertices<string>* vertices = nullptr;
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


	/// <summary>
	/// —водка дл€ TestForm
	/// </summary>
	public ref class TestForm : public System::Windows::Forms::Form {
	public:
		TestForm(void) {
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
		~TestForm() {
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
	private: System::Windows::Forms::Label^ directed_label;
	private: System::Windows::Forms::Label^ weighted_label;
	private: System::Windows::Forms::Button^ make_weighted;
	private: System::Windows::Forms::Button^ make_unweighted;
	private: System::Windows::Forms::Button^ make_with_multiple_edges;
	private: System::Windows::Forms::Button^ make_without_multiple_edges;
	private: System::Windows::Forms::Label^ multiple_label;
	private: System::Windows::Forms::Label^ is_directed;
	private: System::Windows::Forms::Label^ is_with_multiple_edges;
	private: System::Windows::Forms::Label^ is_weighted;
	private: System::Windows::Forms::TextBox^ text_box_weight_of_edge;
	private: System::Windows::Forms::Label^ current_graph_label;
	private: System::Windows::Forms::Button^ top_sort_button;
	private: System::Windows::Forms::TextBox^ top_sort_result;
	private: System::Windows::Forms::RichTextBox^ adjacency_matrix_box;

	private: System::Windows::Forms::RichTextBox^ list_edges_box;
	private: System::Windows::Forms::Label^ adjacency_matrix_label;
	private: System::Windows::Forms::Label^ list_edges_label;
	private: System::Windows::Forms::Button^ adjacency_matrix_button;
	private: System::Windows::Forms::Button^ list_edges_button;
	private: System::Windows::Forms::Button^ min_span_tree_button;
	private: System::Windows::Forms::Button^ comps;
	private: System::Windows::Forms::Button^ min_path_button;


	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

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
			this->directed_label = (gcnew System::Windows::Forms::Label());
			this->weighted_label = (gcnew System::Windows::Forms::Label());
			this->make_weighted = (gcnew System::Windows::Forms::Button());
			this->make_unweighted = (gcnew System::Windows::Forms::Button());
			this->make_with_multiple_edges = (gcnew System::Windows::Forms::Button());
			this->make_without_multiple_edges = (gcnew System::Windows::Forms::Button());
			this->multiple_label = (gcnew System::Windows::Forms::Label());
			this->is_directed = (gcnew System::Windows::Forms::Label());
			this->is_with_multiple_edges = (gcnew System::Windows::Forms::Label());
			this->is_weighted = (gcnew System::Windows::Forms::Label());
			this->text_box_weight_of_edge = (gcnew System::Windows::Forms::TextBox());
			this->current_graph_label = (gcnew System::Windows::Forms::Label());
			this->top_sort_button = (gcnew System::Windows::Forms::Button());
			this->top_sort_result = (gcnew System::Windows::Forms::TextBox());
			this->adjacency_matrix_box = (gcnew System::Windows::Forms::RichTextBox());
			this->list_edges_box = (gcnew System::Windows::Forms::RichTextBox());
			this->adjacency_matrix_label = (gcnew System::Windows::Forms::Label());
			this->list_edges_label = (gcnew System::Windows::Forms::Label());
			this->adjacency_matrix_button = (gcnew System::Windows::Forms::Button());
			this->list_edges_button = (gcnew System::Windows::Forms::Button());
			this->min_span_tree_button = (gcnew System::Windows::Forms::Button());
			this->comps = (gcnew System::Windows::Forms::Button());
			this->min_path_button = (gcnew System::Windows::Forms::Button());
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
			this->add_vertex->Click += gcnew System::EventHandler(this, &TestForm::add_vertex_Click);
			// 
			// add_edge
			// 
			this->add_edge->Location = System::Drawing::Point(1135, 58);
			this->add_edge->Name = L"add_edge";
			this->add_edge->Size = System::Drawing::Size(135, 39);
			this->add_edge->TabIndex = 6;
			this->add_edge->Text = L"add_edge";
			this->add_edge->UseVisualStyleBackColor = true;
			this->add_edge->Click += gcnew System::EventHandler(this, &TestForm::add_edge_Click);
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
			this->web_browser->ScriptErrorsSuppressed = true;
			this->web_browser->Size = System::Drawing::Size(956, 529);
			this->web_browser->TabIndex = 9;
			this->web_browser->Url = (gcnew System::Uri(L"D:\\VisualStudioProjects\\GG\\Visualization\\site\\index.html", System::UriKind::Absolute));
			// 
			// find_cycle
			// 
			this->find_cycle->Location = System::Drawing::Point(1135, 103);
			this->find_cycle->Name = L"find_cycle";
			this->find_cycle->Size = System::Drawing::Size(135, 38);
			this->find_cycle->TabIndex = 10;
			this->find_cycle->Text = L"find_cycle";
			this->find_cycle->UseVisualStyleBackColor = true;
			this->find_cycle->Click += gcnew System::EventHandler(this, &TestForm::find_cycle_Click);
			// 
			// remove_vertex
			// 
			this->remove_vertex->Location = System::Drawing::Point(1276, 12);
			this->remove_vertex->Name = L"remove_vertex";
			this->remove_vertex->Size = System::Drawing::Size(135, 39);
			this->remove_vertex->TabIndex = 11;
			this->remove_vertex->Text = L"remove_vertex";
			this->remove_vertex->UseVisualStyleBackColor = true;
			this->remove_vertex->Click += gcnew System::EventHandler(this, &TestForm::remove_vertex_Click);
			// 
			// remove_edge
			// 
			this->remove_edge->Location = System::Drawing::Point(1276, 59);
			this->remove_edge->Name = L"remove_edge";
			this->remove_edge->Size = System::Drawing::Size(135, 38);
			this->remove_edge->TabIndex = 12;
			this->remove_edge->Text = L"remove_edge";
			this->remove_edge->UseVisualStyleBackColor = true;
			this->remove_edge->Click += gcnew System::EventHandler(this, &TestForm::remove_edge_Click);
			// 
			// make_undirected
			// 
			this->make_undirected->Location = System::Drawing::Point(975, 409);
			this->make_undirected->Name = L"make_undirected";
			this->make_undirected->Size = System::Drawing::Size(50, 30);
			this->make_undirected->TabIndex = 13;
			this->make_undirected->Text = L"No";
			this->make_undirected->UseVisualStyleBackColor = true;
			this->make_undirected->Click += gcnew System::EventHandler(this, &TestForm::make_undirected_Click);
			// 
			// make_directed
			// 
			this->make_directed->Location = System::Drawing::Point(1071, 409);
			this->make_directed->Name = L"make_directed";
			this->make_directed->Size = System::Drawing::Size(50, 30);
			this->make_directed->TabIndex = 14;
			this->make_directed->Text = L"Yes";
			this->make_directed->UseVisualStyleBackColor = true;
			this->make_directed->Click += gcnew System::EventHandler(this, &TestForm::make_directed_Click);
			// 
			// directed_label
			// 
			this->directed_label->AutoSize = true;
			this->directed_label->Location = System::Drawing::Point(974, 390);
			this->directed_label->Name = L"directed_label";
			this->directed_label->Size = System::Drawing::Size(76, 16);
			this->directed_label->TabIndex = 17;
			this->directed_label->Text = L"Is directed\?";
			// 
			// weighted_label
			// 
			this->weighted_label->AutoSize = true;
			this->weighted_label->Location = System::Drawing::Point(974, 494);
			this->weighted_label->Name = L"weighted_label";
			this->weighted_label->Size = System::Drawing::Size(81, 16);
			this->weighted_label->TabIndex = 18;
			this->weighted_label->Text = L"Is weighted\?";
			// 
			// make_weighted
			// 
			this->make_weighted->Location = System::Drawing::Point(1071, 513);
			this->make_weighted->Name = L"make_weighted";
			this->make_weighted->Size = System::Drawing::Size(50, 30);
			this->make_weighted->TabIndex = 20;
			this->make_weighted->Text = L"Yes";
			this->make_weighted->UseVisualStyleBackColor = true;
			this->make_weighted->Click += gcnew System::EventHandler(this, &TestForm::make_weighted_Click);
			// 
			// make_unweighted
			// 
			this->make_unweighted->Location = System::Drawing::Point(975, 513);
			this->make_unweighted->Name = L"make_unweighted";
			this->make_unweighted->Size = System::Drawing::Size(50, 30);
			this->make_unweighted->TabIndex = 19;
			this->make_unweighted->Text = L"No";
			this->make_unweighted->UseVisualStyleBackColor = true;
			this->make_unweighted->Click += gcnew System::EventHandler(this, &TestForm::make_unweighted_Click);
			// 
			// make_with_multiple_edges
			// 
			this->make_with_multiple_edges->Location = System::Drawing::Point(1071, 461);
			this->make_with_multiple_edges->Name = L"make_with_multiple_edges";
			this->make_with_multiple_edges->Size = System::Drawing::Size(50, 30);
			this->make_with_multiple_edges->TabIndex = 23;
			this->make_with_multiple_edges->Text = L"Yes";
			this->make_with_multiple_edges->UseVisualStyleBackColor = true;
			this->make_with_multiple_edges->Click += gcnew System::EventHandler(this, &TestForm::make_with_multiple_edges_Click);
			// 
			// make_without_multiple_edges
			// 
			this->make_without_multiple_edges->Location = System::Drawing::Point(975, 461);
			this->make_without_multiple_edges->Name = L"make_without_multiple_edges";
			this->make_without_multiple_edges->Size = System::Drawing::Size(50, 30);
			this->make_without_multiple_edges->TabIndex = 22;
			this->make_without_multiple_edges->Text = L"No";
			this->make_without_multiple_edges->UseVisualStyleBackColor = true;
			this->make_without_multiple_edges->Click += gcnew System::EventHandler(this, &TestForm::make_without_multiple_edges_Click);
			// 
			// multiple_label
			// 
			this->multiple_label->AutoSize = true;
			this->multiple_label->Location = System::Drawing::Point(974, 442);
			this->multiple_label->Name = L"multiple_label";
			this->multiple_label->Size = System::Drawing::Size(131, 16);
			this->multiple_label->TabIndex = 21;
			this->multiple_label->Text = L"With multiple edges\?";
			// 
			// is_directed
			// 
			this->is_directed->AutoSize = true;
			this->is_directed->Location = System::Drawing::Point(1195, 416);
			this->is_directed->Name = L"is_directed";
			this->is_directed->Size = System::Drawing::Size(25, 16);
			this->is_directed->TabIndex = 24;
			this->is_directed->Text = L"No";
			// 
			// is_with_multiple_edges
			// 
			this->is_with_multiple_edges->AutoSize = true;
			this->is_with_multiple_edges->Location = System::Drawing::Point(1195, 468);
			this->is_with_multiple_edges->Name = L"is_with_multiple_edges";
			this->is_with_multiple_edges->Size = System::Drawing::Size(25, 16);
			this->is_with_multiple_edges->TabIndex = 25;
			this->is_with_multiple_edges->Text = L"No";
			// 
			// is_weighted
			// 
			this->is_weighted->AutoSize = true;
			this->is_weighted->Location = System::Drawing::Point(1195, 520);
			this->is_weighted->Name = L"is_weighted";
			this->is_weighted->Size = System::Drawing::Size(25, 16);
			this->is_weighted->TabIndex = 26;
			this->is_weighted->Text = L"No";
			// 
			// text_box_weight_of_edge
			// 
			this->text_box_weight_of_edge->Location = System::Drawing::Point(1011, 114);
			this->text_box_weight_of_edge->Name = L"text_box_weight_of_edge";
			this->text_box_weight_of_edge->Size = System::Drawing::Size(100, 22);
			this->text_box_weight_of_edge->TabIndex = 27;
			// 
			// current_graph_label
			// 
			this->current_graph_label->AutoSize = true;
			this->current_graph_label->Location = System::Drawing::Point(1162, 390);
			this->current_graph_label->Name = L"current_graph_label";
			this->current_graph_label->Size = System::Drawing::Size(87, 16);
			this->current_graph_label->TabIndex = 28;
			this->current_graph_label->Text = L"Current graph";
			// 
			// top_sort_button
			// 
			this->top_sort_button->Location = System::Drawing::Point(977, 349);
			this->top_sort_button->Name = L"top_sort_button";
			this->top_sort_button->Size = System::Drawing::Size(135, 38);
			this->top_sort_button->TabIndex = 29;
			this->top_sort_button->Text = L"top. sort";
			this->top_sort_button->UseVisualStyleBackColor = true;
			this->top_sort_button->Visible = false;
			this->top_sort_button->Click += gcnew System::EventHandler(this, &TestForm::top_sort_button_Click);
			// 
			// top_sort_result
			// 
			this->top_sort_result->Location = System::Drawing::Point(1119, 349);
			this->top_sort_result->Name = L"top_sort_result";
			this->top_sort_result->Size = System::Drawing::Size(151, 22);
			this->top_sort_result->TabIndex = 30;
			// 
			// adjacency_matrix_box
			// 
			this->adjacency_matrix_box->Location = System::Drawing::Point(1296, 370);
			this->adjacency_matrix_box->Name = L"adjacency_matrix_box";
			this->adjacency_matrix_box->Size = System::Drawing::Size(186, 171);
			this->adjacency_matrix_box->TabIndex = 31;
			this->adjacency_matrix_box->Text = L"";
			// 
			// list_edges_box
			// 
			this->list_edges_box->Location = System::Drawing::Point(1497, 266);
			this->list_edges_box->Name = L"list_edges_box";
			this->list_edges_box->Size = System::Drawing::Size(173, 275);
			this->list_edges_box->TabIndex = 32;
			this->list_edges_box->Text = L"";
			// 
			// adjacency_matrix_label
			// 
			this->adjacency_matrix_label->AutoSize = true;
			this->adjacency_matrix_label->Location = System::Drawing::Point(1316, 349);
			this->adjacency_matrix_label->Name = L"adjacency_matrix_label";
			this->adjacency_matrix_label->Size = System::Drawing::Size(0, 16);
			this->adjacency_matrix_label->TabIndex = 33;
			// 
			// list_edges_label
			// 
			this->list_edges_label->AutoSize = true;
			this->list_edges_label->Location = System::Drawing::Point(1516, 247);
			this->list_edges_label->Name = L"list_edges_label";
			this->list_edges_label->Size = System::Drawing::Size(0, 16);
			this->list_edges_label->TabIndex = 34;
			// 
			// adjacency_matrix_button
			// 
			this->adjacency_matrix_button->Location = System::Drawing::Point(1309, 323);
			this->adjacency_matrix_button->Name = L"adjacency_matrix_button";
			this->adjacency_matrix_button->Size = System::Drawing::Size(153, 41);
			this->adjacency_matrix_button->TabIndex = 35;
			this->adjacency_matrix_button->Text = L"Input adjacency matrix";
			this->adjacency_matrix_button->UseVisualStyleBackColor = true;
			this->adjacency_matrix_button->Click += gcnew System::EventHandler(this, &TestForm::adjacency_matrix_button_Click);
			// 
			// list_edges_button
			// 
			this->list_edges_button->Location = System::Drawing::Point(1497, 224);
			this->list_edges_button->Name = L"list_edges_button";
			this->list_edges_button->Size = System::Drawing::Size(156, 36);
			this->list_edges_button->TabIndex = 36;
			this->list_edges_button->Text = L"Entering a list of edges";
			this->list_edges_button->UseVisualStyleBackColor = true;
			this->list_edges_button->Click += gcnew System::EventHandler(this, &TestForm::list_edges_button_Click);
			// 
			// min_span_tree_button
			// 
			this->min_span_tree_button->Location = System::Drawing::Point(1276, 147);
			this->min_span_tree_button->Name = L"min_span_tree_button";
			this->min_span_tree_button->Size = System::Drawing::Size(135, 40);
			this->min_span_tree_button->TabIndex = 37;
			this->min_span_tree_button->Text = L"min_span_tree";
			this->min_span_tree_button->UseVisualStyleBackColor = true;
			this->min_span_tree_button->Click += gcnew System::EventHandler(this, &TestForm::min_span_tree_button_Click);
			// 
			// comps
			// 
			this->comps->Location = System::Drawing::Point(1135, 147);
			this->comps->Name = L"comps";
			this->comps->Size = System::Drawing::Size(135, 38);
			this->comps->TabIndex = 38;
			this->comps->Text = L"comps";
			this->comps->UseVisualStyleBackColor = true;
			this->comps->Click += gcnew System::EventHandler(this, &TestForm::comps_Click);
			// 
			// min_path_button
			// 
			this->min_path_button->Location = System::Drawing::Point(1276, 103);
			this->min_path_button->Name = L"min_path_button";
			this->min_path_button->Size = System::Drawing::Size(135, 38);
			this->min_path_button->TabIndex = 39;
			this->min_path_button->Text = L"min_path";
			this->min_path_button->UseVisualStyleBackColor = true;
			this->min_path_button->Click += gcnew System::EventHandler(this, &TestForm::min_path_button_Click);
			// 
			// TestForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1682, 553);
			this->Controls->Add(this->min_path_button);
			this->Controls->Add(this->comps);
			this->Controls->Add(this->min_span_tree_button);
			this->Controls->Add(this->list_edges_button);
			this->Controls->Add(this->adjacency_matrix_button);
			this->Controls->Add(this->list_edges_label);
			this->Controls->Add(this->adjacency_matrix_label);
			this->Controls->Add(this->list_edges_box);
			this->Controls->Add(this->adjacency_matrix_box);
			this->Controls->Add(this->top_sort_result);
			this->Controls->Add(this->top_sort_button);
			this->Controls->Add(this->current_graph_label);
			this->Controls->Add(this->text_box_weight_of_edge);
			this->Controls->Add(this->is_weighted);
			this->Controls->Add(this->is_with_multiple_edges);
			this->Controls->Add(this->is_directed);
			this->Controls->Add(this->make_with_multiple_edges);
			this->Controls->Add(this->make_without_multiple_edges);
			this->Controls->Add(this->multiple_label);
			this->Controls->Add(this->make_weighted);
			this->Controls->Add(this->make_unweighted);
			this->Controls->Add(this->weighted_label);
			this->Controls->Add(this->directed_label);
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
			this->Name = L"TestForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
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
#pragma endregion
	private: System::Void add_vertex_Click(System::Object^ sender, System::EventArgs^ e) {
		auto& vertices = *get_current_vertices();
		string s = marshal_as<string>(this->box_vertex1->Text);
		if (vertices.find(s) != vertices.end()) {
			return;
		}
		auto graph = get_current_graph();
		vertices[s] = Graphs::Vertex<string>(s);
		graph->add_vertex(vertices[s]);
		update_picture_graph();
	}
	private: System::Void add_edge_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ text1 = this->box_vertex1->Text;
		String^ text2 = this->box_vertex2->Text;
		String^ text3 = this->text_box_weight_of_edge->Text;
		int weight_of_edge = 1;
		if (weighted) {
			if (!Int32::TryParse(text3, weight_of_edge)) {
				return;
			}
		}
		string s1 = marshal_as<string>(text1);
		string s2 = marshal_as<string>(text2);
		auto& vertices = *get_current_vertices();
		if (vertices.find(s1) == vertices.end() || vertices.find(s2) == vertices.end()) {
			return;
		}
		auto graph = get_current_graph();
		graph->add_edge({ vertices[s1], vertices[s2], weighted, weight_of_edge });
		update_picture_graph();
	}
	private: System::Void find_cycle_Click(System::Object^ sender, System::EventArgs^ e) {
		auto graph = get_current_graph();
		auto& vertices = *get_current_vertices();
		auto cycle = graph->get_the_cycle();
		std::unordered_map<Graphs::Edge<string>, std::string, Graphs::EdgeHash<string>> colors;
		for (auto e : cycle) {
			colors[e] = "red";
		}
		cycle.clear();
		std::string filename = "output_graph.dot";
		std::string output_image = "site\\output_image.png";

		Graphs::create_dot_file(*graph, filename, "black", &colors);
		Graphs::create_picture(filename, output_image);
		this->web_browser->Refresh();
	}
	private: System::Void remove_vertex_Click(System::Object^ sender, System::EventArgs^ e) {
		auto& vertices = *get_current_vertices();
		if (vertices.size() == 0) {
			return;
		}
		string s1 = marshal_as<string>(this->box_vertex1->Text);
		if (vertices.find(s1) == vertices.end()) {
			return;
		}
		auto graph = get_current_graph();
		graph->remove_vertex(vertices[s1]);
		vertices.erase(s1);
		update_picture_graph();
	}
	private: System::Void remove_edge_Click(System::Object^ sender, System::EventArgs^ e) {
		string s1 = marshal_as<string>(this->box_vertex1->Text);
		string s2 = marshal_as<string>(this->box_vertex2->Text);
		auto& vertices = *get_current_vertices();
		if (vertices.find(s1) == vertices.end() || vertices.find(s2) == vertices.end()) {
			return;
		}
		auto graph = get_current_graph();
		int n = graph->get_count_vertices();
		graph->remove_edges_from_to(vertices.at(s1), vertices.at(s2));
		update_picture_graph();
	}

	private: System::Void make_undirected_Click(System::Object^ sender, System::EventArgs^ e) {
		directed = false;
		this->is_directed->Text = "No";
		this->top_sort_button->Visible = false;
		this->min_span_tree_button->Visible = true;
		update_picture_graph();
	}
	private: System::Void make_directed_Click(System::Object^ sender, System::EventArgs^ e) {
		directed = true;
		this->is_directed->Text = "Yes";
		this->top_sort_button->Visible = true;
		this->min_span_tree_button->Visible = false;
		update_picture_graph();
	}
	private: System::Void make_unweighted_Click(System::Object^ sender, System::EventArgs^ e) {
		weighted = false;
		this->is_weighted->Text = "No";
		update_picture_graph();
	}
	private: System::Void make_weighted_Click(System::Object^ sender, System::EventArgs^ e) {
		weighted = true;
		this->is_weighted->Text = "Yes";
		update_picture_graph();
	}
	private: System::Void make_without_multiple_edges_Click(System::Object^ sender, System::EventArgs^ e) {
		with_multiple_edges = false;
		this->is_with_multiple_edges->Text = "No";
		update_picture_graph();
	}
	private: System::Void make_with_multiple_edges_Click(System::Object^ sender, System::EventArgs^ e) {
		with_multiple_edges = true;
		this->is_with_multiple_edges->Text = "Yes";
		update_picture_graph();
	}
	private: System::Void top_sort_button_Click(System::Object^ sender, System::EventArgs^ e) {
		auto graph = get_current_graph();
		auto dg = dynamic_cast<Graphs::DirectedGraph<string>*>(graph);
		auto ts = dg->topological_sorting();
		if (ts.size() == 0) {
			this->top_sort_result->Text = "Impossible";
			return;
		}
		std::stringstream ss;
		ss << "{rank=same; ";
		for (auto v : ts) {
			ss << v.get_object() << "; ";
		}
		ss << "}";
		std::string additional_command = ss.str();
		this->top_sort_result->Text = gcnew String(additional_command.c_str());
		std::string filename = "output_graph.dot";
		std::string output_image = "site\\output_image.png";

		Graphs::create_dot_file(*graph, filename, "black", static_cast<std::unordered_map<Graphs::Edge<string>, std::string, Graphs::EdgeHash<string>>*>(nullptr), additional_command);
		Graphs::create_picture(filename, output_image);
		this->web_browser->Refresh();
	}
	private: System::Void adjacency_matrix_button_Click(System::Object^ sender, System::EventArgs^ e) {
		if (weighted || with_multiple_edges) {
			return;
		}
		try {
			std::string inp_text = marshal_as<std::string>(this->adjacency_matrix_box->Text);
			std::istringstream cin(inp_text);
			Graphs::IGraph<string>* g;
			if (directed) {
				g = new Graphs::DirectedGraph<string>();
			}
			else {
				g = new Graphs::UndirectedGraph<string>();
			}
			int n;
			cin >> n;
			Graphs::DictOfVertices<string> v;
			for (int i = 1; i <= n; ++i) {
				string s = std::to_string(i);
				v[s] = Graphs::Vertex<string>(s);
			}
			Graphs::put_the_vertices_in_the_graph<string>(*g, v);
			int one;
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					cin >> one;
					string s1 = std::to_string(i);
					string s2 = std::to_string(j);
					if (one) {
						g->add_edge_(v[s1], v[s2]);
					}
				}
			}
			auto g_ = get_current_graph();
			auto& v_ = *get_current_vertices();
			if (directed) {
				auto casted_g = dynamic_cast<Graphs::DirectedGraph<string>*>(g);
				auto casted_g_ = dynamic_cast<Graphs::DirectedGraph<string>*>(g_);
				*casted_g_ = *casted_g;
			}
			else {
				auto casted_g = dynamic_cast<Graphs::UndirectedGraph<string>*>(g);
				auto casted_g_ = dynamic_cast<Graphs::UndirectedGraph<string>*>(g_);
				*casted_g_ = *casted_g;
			}
			v_ = v;
			update_picture_graph();
		}
		catch (...) {

		}
	}
	private: System::Void list_edges_button_Click(System::Object^ sender, System::EventArgs^ e) {
		if (with_multiple_edges) {
			return;
		}
		try {
			std::string inp_text = marshal_as<string>(this->list_edges_box->Text);
			std::istringstream cin(inp_text);
			Graphs::IGraph<string>* g;
			if (directed) {
				g = new Graphs::DirectedGraph<string>(false, weighted);
			}
			else {
				g = new Graphs::UndirectedGraph<string>(false, weighted);
			}
			int m, w = 0;
			cin >> m;
			Graphs::DictOfVertices<string> v;
			Graphs::VectorOfEdges<string> edges(m);
			string s1, s2;
			for (int i = 0; i < m; ++i) {
				cin >> s1 >> s2;
				if (weighted) {
					cin >> w;
				}
				if (v.find(s1) == v.end()) {
					v[s1] = s1;
				}
				if (v.find(s2) == v.end()) {
					v[s2] = s2;
				}
				edges[i] = Graphs::Edge<string>(v[s1], v[s2], true, w);
			}
			for (int i = 0; i < m; ++i) {
				g->add_edge(edges[i]);
			}
			auto g_ = get_current_graph();
			auto& v_ = *get_current_vertices();
			for (int i = 0; i < m; ++i) {
				v_[edges[i].vertex1.get_object()] = edges[i].vertex1;
				v_[edges[i].vertex2.get_object()] = edges[i].vertex2;
			}
			if (directed) {
				auto casted_g = dynamic_cast<Graphs::DirectedGraph<string>*>(g);
				auto casted_g_ = dynamic_cast<Graphs::DirectedGraph<string>*>(g_);
				*casted_g_ = *casted_g;
			}
			else {
				auto casted_g = dynamic_cast<Graphs::UndirectedGraph<string>*>(g);
				auto casted_g_ = dynamic_cast<Graphs::UndirectedGraph<string>*>(g_);
				*casted_g_ = *casted_g;
			}
			update_picture_graph();
		}
		catch (...) {

		}
	}
	private: System::Void min_span_tree_button_Click(System::Object^ sender, System::EventArgs^ e) {
		auto g = get_current_graph();
		auto& vertices = *get_current_vertices();
		auto graph = dynamic_cast<Graphs::UndirectedGraph<string>*>(g);
		auto span = graph->finding_minimum_spanning_tree();
		auto set_ = span.get_edges();
		auto colors = Graphs::EdgeColors<string>();
		for (auto& it : set_) {
			colors[it] = "green";
		}
		std::string filename = "output_graph.dot";
		std::string output_image = "site\\output_image.png";

		Graphs::create_dot_file(*graph, filename, "black", &colors);
		Graphs::create_picture(filename, output_image);
		this->web_browser->Refresh();
	}
	private: System::Void comps_Click(System::Object^ sender, System::EventArgs^ e) {
		auto g = get_current_graph();
		auto comps = g->get_connected_components();
		std::string filename = "output_graph.dot";
		std::string output_image = "site\\output_image.png";

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
		this->web_browser->Refresh();
	}
	private: System::Void min_path_button_Click(System::Object^ sender, System::EventArgs^ e) {
		string s1 = marshal_as<string>(this->box_vertex1->Text);
		string s2 = marshal_as<string>(this->box_vertex2->Text);
		auto graph = get_current_graph();
		auto vertices = get_current_vertices();
		if (vertices->find(s1) == vertices->end() || vertices->find(s2) == vertices->end()) {
			return;
		}
		auto path = graph->shortest_way(vertices->at(s1), vertices->at(s2));

		std::string filename = "output_graph.dot";
		std::string output_image = "site\\output_image.png";

		auto colors = Graphs::EdgeColors<string>();
		for (auto& it : path) {
			colors[it] = "yellow";
		}
		Graphs::create_dot_file(*graph, filename, "black", &colors);
		Graphs::create_picture(filename, output_image);
		this->web_browser->Refresh();
	}
};
}
