#include "WinForm.h"
#include "Interpreter.h"
#include <msclr/marshal_cppstd.h>
System::Void EM::WinForm::���J�ɮ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	 string path = msclr::interop::marshal_as< std::string >(this->OFD->FileName);

}