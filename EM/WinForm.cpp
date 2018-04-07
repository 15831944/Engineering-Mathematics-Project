#include "WinForm.h"
#include "Interpreter.h"
#include <msclr/marshal_cppstd.h>
System::Void EM::WinForm::¸ü¤JÀÉ®×ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->OFD->ShowDialog();
	string path = msclr::interop::marshal_as< std::string >(this->OFD->FileName);
	
	loadVars(path);
	for (auto it = vars.begin(); it != vars.end(); it++) {
		ListViewItem^ lvi = gcnew ListViewItem();
		lvi->Text = gcnew String(it->first.c_str());
		lvi->SubItems->Add(gcnew String(it->second.type.c_str()));
		if (it->second.type == "Vector")
			lvi->SubItems->Add(gcnew String(((Vector*)(it->second.data))->ToString().c_str()));
		else if (it->second.type == "Matrix")
			lvi->SubItems->Add(gcnew String(((Matrix*)(it->second.data))->ToString().c_str()));
		this->listView1->Items->Add(lvi);
	}
}

System::Void EM::WinForm::WinForm_Load(System::Object^  sender, System::EventArgs^  e) {
	this->debugLabel->Text = gcnew String(dealFormula("Dot(1,2)").c_str());
}