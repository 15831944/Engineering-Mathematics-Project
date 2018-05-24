#include "WinForm.h"
#include "Interpreter.h"
#include "Equation.h"
#include "Optimization.h"
#include <msclr/marshal_cppstd.h>


string resultRecord = "";

System::Void EM::WinForm::¸ü¤JÀÉ®×ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->OFD->ShowDialog();
	string path = msclr::interop::marshal_as< std::string >(this->OFD->FileName);
	
	loadVars(path);
	this->listView1->Items->Clear();
	for (auto it = vars.begin(); it != vars.end(); it++) {
		ListViewItem^ lvi = gcnew ListViewItem();
		lvi->Text = gcnew String(it->first.c_str());
		lvi->SubItems->Add(gcnew String(it->second.type.c_str()));
		if (it->second.type == "Vector") {
			lvi->SubItems->Add(gcnew String(((Vector*)(it->second.data))->getSizeInfo().c_str()));
			lvi->SubItems->Add(gcnew String(((Vector*)(it->second.data))->ToString().c_str()));
		}
		else if (it->second.type == "Matrix") {
			lvi->SubItems->Add(gcnew String(((Matrix*)(it->second.data))->getSizeInfo().c_str()));
			lvi->SubItems->Add(gcnew String(((Matrix*)(it->second.data))->ToString().c_str()));
		}
		this->listView1->Items->Add(lvi);
	}
}

System::Void EM::WinForm::DeriRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	
}

System::Void EM::WinForm::WinForm_Load(System::Object^  sender, System::EventArgs^  e) {
	this->OptWaySelect->SelectedIndex = 0;
	


	// debug area
	/*
	Equation eqt("7+x^2-3xy+3.25y^2-4y");
	string info;
	Matrix h1, h2;
	h1 = getHessian(eqt, Vector({ 50.0,30.0 }));
	h2 = numericalGetHessian(eqt, Vector({ 50.0,30.0 }));
	optimize(eqt, Vector({50.0,30.0}), Vector({ -50,70 }), Vector({ -70,70 }), "Conjugate Gradient", info);
	
	cout << "guo";
	*/
	//
}

System::Void EM::WinForm::cmdBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ ex) {

	if (ex->KeyChar == '\r') {
		String^ f = this->cmdBox->Lines[cmdBox->Lines->Length - 2];
		String^ result = getResultStr(f);
		this->cmdBox->SelectionColor = Color::AntiqueWhite;
		resultRecord += msclr::interop::marshal_as< std::string >(result);
		this->cmdBox->AppendText(result);
		this->cmdBox->SelectionColor = this->cmdBox->ForeColor;
	}
}
System::Void EM::WinForm::saveResultsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->SFD->ShowDialog();
	string path = msclr::interop::marshal_as< std::string >(this->SFD->FileName);
	std::ofstream fout(path);
	fout << resultRecord;
	fout.close();
}

System::Void EM::WinForm::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	clearMap();
	vCounter = 0;
	mCounter = 0;
	this->listView1->Items->Clear();
}

System::Void EM::WinForm::loadEqualToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->OFD->ShowDialog();
	string path = msclr::interop::marshal_as< std::string >(this->OFD->FileName);
	vector<string> display = loadEquations(path);
	this->EqtListBox->Items->Clear();
	for (int i = 0; i < display.size(); ++i) {
		this->EqtListBox->Items->Add(gcnew String(display[i].c_str()));
	}
}

System::Void EM::WinForm::EqtListBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	this->nowEquationBox->Text = this->EqtListBox->SelectedItem->ToString();

}

Vector strToVec(string str) {
	size_t nowPosi = 0, cammaPosi = str.find(',', nowPosi);
	vector<size_t> cammaPosis;
	while (cammaPosi != string::npos) {
		cammaPosis.push_back(cammaPosi);
		nowPosi = cammaPosi + 1;
		cammaPosi = str.find(',', nowPosi);
	}

	Vector point(cammaPosis.size() + 1);

	nowPosi = 0;
	for (int i = 0; i < cammaPosis.size(); ++i) {
		point.data_[i] = std::stof(str.substr(nowPosi, cammaPosis[i] - nowPosi));
		nowPosi = cammaPosis[i] + 1;
	}
	point.data_[point.dim_ - 1] = std::stof(str.substr(nowPosi, str.size() - nowPosi));
	return point;
}



bool checkBound(Vector p, const Vector& limX, const Vector& limY) {
	bool result;
	if (p.dim_ == 1) {
		result = p.data_[0] > limX.data_[0] && p.data_[0] < limX.data_[1];
	}
	else {
		result = p.data_[0] > limX.data_[0] && p.data_[0] < limX.data_[1] && p.data_[1] > limY.data_[0] && p.data_[1] < limY.data_[1];
	}
	return result;
}

System::Void EM::WinForm::button2_Click(System::Object^  sender, System::EventArgs^  e) {
	// optimization

	// get info
	string eqtStr = msclr::interop::marshal_as< std::string >(this->nowEquationBox->Text);
	string initPStr = msclr::interop::marshal_as< std::string >(this->initPointBox->Text);
	string optMethod = msclr::interop::marshal_as< std::string >(this->OptWaySelect->Items[this->OptWaySelect->SelectedIndex]->ToString());
	string intervalX = msclr::interop::marshal_as< std::string >(this->intervalABox->Text);
	string intervalY = msclr::interop::marshal_as< std::string >(this->intervalBBox->Text);

	// convert
	Equation eqt(eqtStr);
	Vector initP = strToVec(initPStr);
	Vector limX = strToVec(intervalX);
	Vector limY = strToVec(intervalY);
	
	// call optimize
	
	string info = "";
	int iter_times = 0;
	NumType gradient = getGradient(eqt, initP,this->NumRadioButton->Checked).Norm();
	Vector lastP = getGradient(eqt, initP, this->NumRadioButton->Checked).Scalar(100) + initP;
	
	// print initial information

	// set color
	
	info = "\nf = " + eqt.ToString() + "\n";
	info += "initail Point = " + initP.ToString() + "\n";
	info += "Optimization Method : " + optMethod + "\n";
	info += "---------------------------------------------";
	this->optRichBox->SelectionColor = Color::AntiqueWhite;;
	this->optRichBox->AppendText(gcnew String(info.c_str()));
	this->optRichBox->SelectionColor = this->optRichBox->ForeColor;
	//
	while ((++iter_times < MAX_ITER) && (gradient > OptDlt) && initP.Dist(lastP)>OptDlt) {
		info = "\n" + std::to_string(iter_times)+ " times iteration\n";
		lastP = initP;
		optimize(eqt, initP,limX,limY, optMethod, info, this->NumRadioButton->Checked,iter_times);
		info += "\n------------------------------------------------";
		this->optRichBox->AppendText(gcnew String(info.c_str()));
		gradient = getGradient(eqt, initP, this->NumRadioButton->Checked).Norm();
		Application::DoEvents();
		if (!checkBound(initP, limX, limY)) {
			info = "\nout of domain, Try another initial point !!";
			this->optRichBox->AppendText(gcnew String(info.c_str()));
		}
	}
	info = "\n X = " + initP.ToString();
	info += "\n min = " + std::to_string(Equation::calcEquation(eqt,initP));
	this->optRichBox->AppendText(gcnew String(info.c_str()));

}
