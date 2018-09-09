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

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RichTextBox^  cmdBox;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  Col1;
	private: System::Windows::Forms::ColumnHeader^  Col2;
	private: System::Windows::Forms::ColumnHeader^  Col3;
	private: System::Windows::Forms::OpenFileDialog^  OFD;
	private: System::Windows::Forms::Label^  debugLabel;
	private: System::Windows::Forms::ColumnHeader^  Col2i;

	private: System::Windows::Forms::ToolStripMenuItem^  saveResultsToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^  SFD;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::ToolStripMenuItem^  loadEqualToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::ComboBox^  OptWaySelect;
	private: System::Windows::Forms::TextBox^  initPointBox;
	private: System::Windows::Forms::TextBox^  nowEquationBox;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::RichTextBox^  optRichBox;

	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::ListBox^  EqtListBox;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  intervalBBox;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  intervalABox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::RadioButton^  DeriRadioButton;
	private: System::Windows::Forms::RadioButton^  NumRadioButton;
	private: System::Windows::Forms::CheckBox^  newtonstep;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::PictureBox^  transPicBox;
	private: System::Windows::Forms::PictureBox^  oriPicBox;
	private: System::Windows::Forms::Button^  transBtn;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::GroupBox^  groupBox7;












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
			this->saveResultsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadEqualToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->Col1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->Col2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->Col2i = (gcnew System::Windows::Forms::ColumnHeader());
			this->Col3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->cmdBox = (gcnew System::Windows::Forms::RichTextBox());
			this->OFD = (gcnew System::Windows::Forms::OpenFileDialog());
			this->debugLabel = (gcnew System::Windows::Forms::Label());
			this->SFD = (gcnew System::Windows::Forms::SaveFileDialog());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->optRichBox = (gcnew System::Windows::Forms::RichTextBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->EqtListBox = (gcnew System::Windows::Forms::ListBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->newtonstep = (gcnew System::Windows::Forms::CheckBox());
			this->DeriRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->NumRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->intervalBBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->intervalABox = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->OptWaySelect = (gcnew System::Windows::Forms::ComboBox());
			this->initPointBox = (gcnew System::Windows::Forms::TextBox());
			this->nowEquationBox = (gcnew System::Windows::Forms::TextBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->oriPicBox = (gcnew System::Windows::Forms::PictureBox());
			this->transPicBox = (gcnew System::Windows::Forms::PictureBox());
			this->transBtn = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->toolStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->oriPicBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->transPicBox))->BeginInit();
			this->groupBox7->SuspendLayout();
			this->SuspendLayout();
			// 
			// toolStrip1
			// 
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripDropDownButton1 });
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->toolStrip1->Size = System::Drawing::Size(961, 31);
			this->toolStrip1->TabIndex = 0;
			this->toolStrip1->Text = L"toolStrip1";
			this->toolStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &WinForm::toolStrip1_ItemClicked);
			// 
			// toolStripDropDownButton1
			// 
			this->toolStripDropDownButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripDropDownButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->載入檔案ToolStripMenuItem,
					this->saveResultsToolStripMenuItem, this->loadEqualToolStripMenuItem
			});
			this->toolStripDropDownButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripDropDownButton1.Image")));
			this->toolStripDropDownButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripDropDownButton1->Name = L"toolStripDropDownButton1";
			this->toolStripDropDownButton1->Size = System::Drawing::Size(37, 28);
			this->toolStripDropDownButton1->Text = L"toolStripDropDownButton1";
			this->toolStripDropDownButton1->Click += gcnew System::EventHandler(this, &WinForm::toolStripDropDownButton1_Click);
			// 
			// 載入檔案ToolStripMenuItem
			// 
			this->載入檔案ToolStripMenuItem->Name = L"載入檔案ToolStripMenuItem";
			this->載入檔案ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->載入檔案ToolStripMenuItem->Text = L"Load Variables";
			this->載入檔案ToolStripMenuItem->Click += gcnew System::EventHandler(this, &WinForm::載入檔案ToolStripMenuItem_Click);
			// 
			// saveResultsToolStripMenuItem
			// 
			this->saveResultsToolStripMenuItem->Name = L"saveResultsToolStripMenuItem";
			this->saveResultsToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->saveResultsToolStripMenuItem->Text = L"Save Results";
			this->saveResultsToolStripMenuItem->Click += gcnew System::EventHandler(this, &WinForm::saveResultsToolStripMenuItem_Click);
			// 
			// loadEqualToolStripMenuItem
			// 
			this->loadEqualToolStripMenuItem->Name = L"loadEqualToolStripMenuItem";
			this->loadEqualToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->loadEqualToolStripMenuItem->Text = L"Load  Equation";
			this->loadEqualToolStripMenuItem->Click += gcnew System::EventHandler(this, &WinForm::loadEqualToolStripMenuItem_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->listView1);
			this->groupBox1->Controls->Add(this->cmdBox);
			this->groupBox1->Location = System::Drawing::Point(0, 6);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(920, 445);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Main Panel";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(788, 375);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Clear Table";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &WinForm::button1_Click);
			// 
			// listView1
			// 
			this->listView1->AutoArrange = false;
			this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->Col1, this->Col2,
					this->Col2i, this->Col3
			});
			this->listView1->Location = System::Drawing::Point(416, 21);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(485, 399);
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
			// Col2i
			// 
			this->Col2i->Text = L"Size";
			// 
			// Col3
			// 
			this->Col3->Text = L"Value";
			this->Col3->Width = 500;
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
			this->cmdBox->Size = System::Drawing::Size(392, 399);
			this->cmdBox->TabIndex = 0;
			this->cmdBox->Text = L"";
			this->cmdBox->TextChanged += gcnew System::EventHandler(this, &WinForm::cmdBox_TextChanged);
			this->cmdBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &WinForm::cmdBox_KeyPress);
			// 
			// OFD
			// 
			this->OFD->FileName = L"openFileDialog1";
			// 
			// debugLabel
			// 
			this->debugLabel->AutoSize = true;
			this->debugLabel->Location = System::Drawing::Point(823, 555);
			this->debugLabel->Name = L"debugLabel";
			this->debugLabel->Size = System::Drawing::Size(0, 12);
			this->debugLabel->TabIndex = 3;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Location = System::Drawing::Point(8, 34);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(948, 501);
			this->tabControl1->TabIndex = 4;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(940, 475);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Base Function";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->groupBox4);
			this->tabPage2->Controls->Add(this->groupBox3);
			this->tabPage2->Controls->Add(this->groupBox2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(940, 475);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Optimization";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->button4);
			this->groupBox4->Controls->Add(this->optRichBox);
			this->groupBox4->Location = System::Drawing::Point(15, 103);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(605, 366);
			this->groupBox4->TabIndex = 2;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Results";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(455, 308);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(96, 29);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Clear Result";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &WinForm::button4_Click);
			// 
			// optRichBox
			// 
			this->optRichBox->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->optRichBox->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->optRichBox->ForeColor = System::Drawing::Color::Cyan;
			this->optRichBox->Location = System::Drawing::Point(14, 26);
			this->optRichBox->Name = L"optRichBox";
			this->optRichBox->ReadOnly = true;
			this->optRichBox->Size = System::Drawing::Size(571, 327);
			this->optRichBox->TabIndex = 0;
			this->optRichBox->Text = L"";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->button3);
			this->groupBox3->Controls->Add(this->EqtListBox);
			this->groupBox3->Location = System::Drawing::Point(626, 6);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(308, 463);
			this->groupBox3->TabIndex = 1;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Equation List";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(184, 405);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(96, 29);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Clear Equations";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &WinForm::button3_Click);
			// 
			// EqtListBox
			// 
			this->EqtListBox->FormattingEnabled = true;
			this->EqtListBox->ItemHeight = 12;
			this->EqtListBox->Location = System::Drawing::Point(16, 21);
			this->EqtListBox->Name = L"EqtListBox";
			this->EqtListBox->Size = System::Drawing::Size(277, 424);
			this->EqtListBox->TabIndex = 0;
			this->EqtListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &WinForm::EqtListBox_SelectedIndexChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->newtonstep);
			this->groupBox2->Controls->Add(this->DeriRadioButton);
			this->groupBox2->Controls->Add(this->NumRadioButton);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->intervalBBox);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->intervalABox);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Controls->Add(this->OptWaySelect);
			this->groupBox2->Controls->Add(this->initPointBox);
			this->groupBox2->Controls->Add(this->nowEquationBox);
			this->groupBox2->Location = System::Drawing::Point(15, 6);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(605, 91);
			this->groupBox2->TabIndex = 0;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Optimizer";
			// 
			// newtonstep
			// 
			this->newtonstep->AutoSize = true;
			this->newtonstep->Checked = true;
			this->newtonstep->CheckState = System::Windows::Forms::CheckState::Checked;
			this->newtonstep->Enabled = false;
			this->newtonstep->Location = System::Drawing::Point(446, 55);
			this->newtonstep->Name = L"newtonstep";
			this->newtonstep->Size = System::Drawing::Size(126, 16);
			this->newtonstep->TabIndex = 10;
			this->newtonstep->Text = L"牛頓法使用Step Size";
			this->newtonstep->UseVisualStyleBackColor = true;
			this->newtonstep->CheckedChanged += gcnew System::EventHandler(this, &WinForm::newtonstep_CheckedChanged);
			// 
			// DeriRadioButton
			// 
			this->DeriRadioButton->AutoSize = true;
			this->DeriRadioButton->Checked = true;
			this->DeriRadioButton->Location = System::Drawing::Point(211, 55);
			this->DeriRadioButton->Name = L"DeriRadioButton";
			this->DeriRadioButton->Size = System::Drawing::Size(107, 16);
			this->DeriRadioButton->TabIndex = 9;
			this->DeriRadioButton->TabStop = true;
			this->DeriRadioButton->Text = L"用導函數算微分";
			this->DeriRadioButton->UseVisualStyleBackColor = true;
			this->DeriRadioButton->CheckedChanged += gcnew System::EventHandler(this, &WinForm::DeriRadioButton_CheckedChanged);
			// 
			// NumRadioButton
			// 
			this->NumRadioButton->AutoSize = true;
			this->NumRadioButton->Location = System::Drawing::Point(332, 55);
			this->NumRadioButton->Name = L"NumRadioButton";
			this->NumRadioButton->Size = System::Drawing::Size(107, 16);
			this->NumRadioButton->TabIndex = 8;
			this->NumRadioButton->Text = L"用數值計算微分";
			this->NumRadioButton->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(6, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(19, 16);
			this->label2->TabIndex = 7;
			this->label2->Text = L"X";
			// 
			// intervalBBox
			// 
			this->intervalBBox->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->intervalBBox->Location = System::Drawing::Point(123, 49);
			this->intervalBBox->Name = L"intervalBBox";
			this->intervalBBox->Size = System::Drawing::Size(65, 22);
			this->intervalBBox->TabIndex = 6;
			this->intervalBBox->Text = L"-100,100";
			this->intervalBBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(101, 49);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(19, 16);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Y";
			// 
			// intervalABox
			// 
			this->intervalABox->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->intervalABox->Location = System::Drawing::Point(30, 49);
			this->intervalABox->Name = L"intervalABox";
			this->intervalABox->Size = System::Drawing::Size(65, 22);
			this->intervalABox->TabIndex = 4;
			this->intervalABox->Text = L"-100,100";
			this->intervalABox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(524, 16);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 29);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Run";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &WinForm::button2_Click);
			// 
			// OptWaySelect
			// 
			this->OptWaySelect->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->OptWaySelect->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->OptWaySelect->FormattingEnabled = true;
			this->OptWaySelect->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Powell Method", L"Steep Decent", L"Newton Method",
					L"Conjugate Gradient", L"Quasi Newton"
			});
			this->OptWaySelect->Location = System::Drawing::Point(388, 21);
			this->OptWaySelect->Name = L"OptWaySelect";
			this->OptWaySelect->Size = System::Drawing::Size(121, 21);
			this->OptWaySelect->TabIndex = 2;
			this->OptWaySelect->SelectedIndexChanged += gcnew System::EventHandler(this, &WinForm::OptWaySelect_SelectedIndexChanged);
			// 
			// initPointBox
			// 
			this->initPointBox->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->initPointBox->Location = System::Drawing::Point(211, 21);
			this->initPointBox->Name = L"initPointBox";
			this->initPointBox->Size = System::Drawing::Size(171, 22);
			this->initPointBox->TabIndex = 1;
			this->initPointBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// nowEquationBox
			// 
			this->nowEquationBox->Location = System::Drawing::Point(6, 21);
			this->nowEquationBox->Name = L"nowEquationBox";
			this->nowEquationBox->Size = System::Drawing::Size(199, 22);
			this->nowEquationBox->TabIndex = 0;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->groupBox7);
			this->tabPage3->Controls->Add(this->groupBox6);
			this->tabPage3->Controls->Add(this->groupBox5);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(940, 475);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Transform";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->oriPicBox);
			this->groupBox5->Location = System::Drawing::Point(15, 16);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(363, 428);
			this->groupBox5->TabIndex = 0;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Original";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->transPicBox);
			this->groupBox6->Location = System::Drawing::Point(384, 16);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(380, 428);
			this->groupBox6->TabIndex = 1;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Transform";
			// 
			// oriPicBox
			// 
			this->oriPicBox->Location = System::Drawing::Point(7, 22);
			this->oriPicBox->Name = L"oriPicBox";
			this->oriPicBox->Size = System::Drawing::Size(345, 390);
			this->oriPicBox->TabIndex = 0;
			this->oriPicBox->TabStop = false;
			// 
			// transPicBox
			// 
			this->transPicBox->Location = System::Drawing::Point(7, 22);
			this->transPicBox->Name = L"transPicBox";
			this->transPicBox->Size = System::Drawing::Size(365, 390);
			this->transPicBox->TabIndex = 1;
			this->transPicBox->TabStop = false;
			// 
			// transBtn
			// 
			this->transBtn->Location = System::Drawing::Point(18, 47);
			this->transBtn->Name = L"transBtn";
			this->transBtn->Size = System::Drawing::Size(118, 23);
			this->transBtn->TabIndex = 2;
			this->transBtn->Text = L"Transform";
			this->transBtn->UseVisualStyleBackColor = true;
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(18, 21);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(117, 20);
			this->comboBox1->TabIndex = 3;
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->transBtn);
			this->groupBox7->Controls->Add(this->comboBox1);
			this->groupBox7->Location = System::Drawing::Point(770, 16);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(155, 82);
			this->groupBox7->TabIndex = 4;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"groupBox7";
			// 
			// WinForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(961, 545);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->debugLabel);
			this->Controls->Add(this->toolStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(2);
			this->MaximizeBox = false;
			this->Name = L"WinForm";
			this->Text = L"EM Homework";
			this->Load += gcnew System::EventHandler(this, &WinForm::WinForm_Load);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->oriPicBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->transPicBox))->EndInit();
			this->groupBox7->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void toolStripDropDownButton1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void WinForm_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void 載入檔案ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void toolStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
	}
	private: System::Void cmdBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {


	}
	private: System::Void cmdBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ ex);

	private: System::Void saveResultsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void InfoBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void loadEqualToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void EqtListBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void DeriRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void OptWaySelect_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void newtonstep_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e);
};
}