#pragma once

namespace EM {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// WinForm 的摘要
	/// </summary>
	public ref class WinForm : public System::Windows::Forms::Form
	{
	public:
		WinForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~WinForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	protected:
	private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton1;
	private: System::Windows::Forms::ToolStripMenuItem^  載入檔案ToolStripMenuItem;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RichTextBox^  cmdBox;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  Col1;
	private: System::Windows::Forms::ColumnHeader^  Col2;
	private: System::Windows::Forms::ColumnHeader^  Col3;
	private: System::Windows::Forms::OpenFileDialog^  OFD;





	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WinForm::typeid));
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripDropDownButton1 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->載入檔案ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->Col1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->Col2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->Col3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->cmdBox = (gcnew System::Windows::Forms::RichTextBox());
			this->OFD = (gcnew System::Windows::Forms::OpenFileDialog());
			this->toolStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripDropDownButton1 });
			this->toolStrip1->Location = System::Drawing::Point(0, 24);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(1239, 25);
			this->toolStrip1->TabIndex = 0;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripDropDownButton1
			// 
			this->toolStripDropDownButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripDropDownButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->載入檔案ToolStripMenuItem });
			this->toolStripDropDownButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripDropDownButton1.Image")));
			this->toolStripDropDownButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripDropDownButton1->Name = L"toolStripDropDownButton1";
			this->toolStripDropDownButton1->Size = System::Drawing::Size(29, 22);
			this->toolStripDropDownButton1->Text = L"toolStripDropDownButton1";
			this->toolStripDropDownButton1->Click += gcnew System::EventHandler(this, &WinForm::toolStripDropDownButton1_Click);
			// 
			// 載入檔案ToolStripMenuItem
			// 
			this->載入檔案ToolStripMenuItem->Name = L"載入檔案ToolStripMenuItem";
			this->載入檔案ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->載入檔案ToolStripMenuItem->Text = L"Load";
			this->載入檔案ToolStripMenuItem->Click += gcnew System::EventHandler(this, &WinForm::載入檔案ToolStripMenuItem_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1239, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->listView1);
			this->groupBox1->Controls->Add(this->cmdBox);
			this->groupBox1->Location = System::Drawing::Point(12, 276);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(602, 310);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			// 
			// listView1
			// 
			this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->Col1, this->Col2,
					this->Col3
			});
			this->listView1->Location = System::Drawing::Point(310, 21);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(286, 270);
			this->listView1->TabIndex = 1;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// Col1
			// 
			this->Col1->Text = L"Name";
			// 
			// Col2
			// 
			this->Col2->Text = L"Type";
			// 
			// Col3
			// 
			this->Col3->Text = L"Value";
			// 
			// cmdBox
			// 
			this->cmdBox->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->cmdBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->cmdBox->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->cmdBox->ForeColor = System::Drawing::Color::Lime;
			this->cmdBox->ImeMode = System::Windows::Forms::ImeMode::Alpha;
			this->cmdBox->Location = System::Drawing::Point(18, 21);
			this->cmdBox->Name = L"cmdBox";
			this->cmdBox->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->cmdBox->Size = System::Drawing::Size(286, 270);
			this->cmdBox->TabIndex = 0;
			this->cmdBox->Text = L"";
			// 
			// OFD
			// 
			this->OFD->FileName = L"openFileDialog1";
			// 
			// WinForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1239, 598);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"WinForm";
			this->Text = L"Mat";
			this->Load += gcnew System::EventHandler(this, &WinForm::WinForm_Load);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void toolStripDropDownButton1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void WinForm_Load(System::Object^  sender, System::EventArgs^  e) {
		ListViewItem ^lvi = gcnew ListViewItem();
		lvi->SubItems->Add("1");
		lvi->SubItems->Add("2");
		lvi->SubItems->Add("3");

		this->listView1->Items->Add(lvi);
	}
private: System::Void 載入檔案ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
};
}
