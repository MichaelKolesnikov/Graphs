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
	Graphs::VectorOfVertices<int> vertices;
	Graphs::UndirectedGraph<int> undirected_graph;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form {
	public:
		MyForm() {
			std::string filename = "output_graph.dot";
			std::string output_image = "site\\output_image.png";

			Graphs::create_dot_file(undirected_graph, filename);
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
		void InitializeComponent(void)
		{
			this->add_vertex = (gcnew System::Windows::Forms::Button());
			this->add_edge = (gcnew System::Windows::Forms::Button());
			this->box_vertex1 = (gcnew System::Windows::Forms::TextBox());
			this->box_vertex2 = (gcnew System::Windows::Forms::TextBox());
			this->web_browser = (gcnew System::Windows::Forms::WebBrowser());
			this->find_cycle = (gcnew System::Windows::Forms::Button());
			this->remove_vertex = (gcnew System::Windows::Forms::Button());
			this->remove_edge = (gcnew System::Windows::Forms::Button());
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
			this->web_browser->DocumentCompleted += gcnew System::Windows::Forms::WebBrowserDocumentCompletedEventHandler(this, &MyForm::web_browser_DocumentCompleted);
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1282, 553);
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

		void update_picture_graph(void) {
			std::string filename = "output_graph.dot";
			std::string output_image = "site\\output_image.png";

			Graphs::create_dot_file(undirected_graph, filename);
			Graphs::create_picture(filename, output_image);
			this->web_browser->Refresh();
		}
#pragma endregion

		private: System::Void add_vertex_Click(System::Object^ sender, System::EventArgs^ e) {
			int n = undirected_graph.get_count_vertices();
			vertices.push_back(Graphs::Vertex<int>(n));
			undirected_graph.add_vertex(vertices.back());
			update_picture_graph();
		}
		private: System::Void add_edge_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ text1 = this->box_vertex1->Text;
			String^ text2 = this->box_vertex2->Text;
			int v1, v2, n = undirected_graph.get_count_vertices();
			if (Int32::TryParse(text1, v1) && Int32::TryParse(text2, v2) && v1 < n && v2 < n) {
				undirected_graph.add_edge({ vertices[v1], vertices[v2] });
				update_picture_graph();
			}
		}
		private: System::Void web_browser_DocumentCompleted(System::Object^ sender, System::Windows::Forms::WebBrowserDocumentCompletedEventArgs^ e) {}
		private: System::Void find_cycle_Click(System::Object^ sender, System::EventArgs^ e) {
			auto cycle = undirected_graph.get_the_cycle();
			auto set_cycle = Graphs::Edges<int>(begin(cycle), end(cycle));
			cycle.clear();
			std::string filename = "output_graph.dot";
			std::string output_image = "site\\output_image.png";

			Graphs::create_dot_file(undirected_graph, filename, &set_cycle);
			Graphs::create_picture(filename, output_image);
			this->web_browser->Refresh();
		}
		private: System::Void remove_vertex_Click(System::Object^ sender, System::EventArgs^ e) {
			undirected_graph.remove_vertex(vertices.back());
			vertices.pop_back();
			update_picture_graph();
		}
		private: System::Void remove_edge_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ text1 = this->box_vertex1->Text;
			String^ text2 = this->box_vertex2->Text;
			int v1, v2, n = undirected_graph.get_count_vertices();
			if (Int32::TryParse(text1, v1) && Int32::TryParse(text2, v2) && v1 < n && v2 < n) {
				undirected_graph.remove_edges_from_to(vertices[v1], vertices[v2]);
				update_picture_graph();
			}
		}
};
}
