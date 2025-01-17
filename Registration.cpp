//---------------------------------------------------------------------------

#include <fmx.h>

#include <string>
#include <fstream>

#include <algorithm>
#include <random>
#include <ctime>

#include <FMX.Dialogs.hpp>

#pragma hdrstop

#include "Main.h"
#include "Registration.h"
#include "GlobalVariables.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TRegistrationForm *RegistrationForm;
//---------------------------------------------------------------------------
__fastcall TRegistrationForm::TRegistrationForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::btnCloseClick(TObject *Sender)
{
	edtname->Text = "";
	edtsurname->Text = "";
	edtnumber->Text = "";
	edtidnumber->Text = "";
	edtcode->Text = "";
	lblusername->Text = "generate_username";
	lblpassword->Text = "generate_password";
	memlogind->Lines->Clear();
	memlogind->Lines->Add("Login Details:");
	Close();

}
//---------------------------------------------------------------------------

 bool isIDNumberValid(const AnsiString idNumber) {
	return idNumber.Length() == 13;
}

bool isCellNumberValid(const AnsiString cellNumber) {
	return cellNumber.Length() == 10;
}

																											// Function that generate a password
std::string generatePassword(const std::string& name, const std::string& surname, const std::string& idNumber, const std::string& contactNumber) {
																		// combines all input strings
    std::string combined = name + surname + idNumber + contactNumber;

																														// shuffles the combined string
    std::shuffle(combined.begin(), combined.end(), std::default_random_engine(static_cast<unsigned>(std::time(nullptr))));

													// create a string with a special characters
    std::string specialCharacters = "!@#$%^&*()";

							// generates a random index for the special character
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, specialCharacters.size() - 1);
    int specialCharIndex = dis(gen);

																// generates a random index for the capital letter
    std::uniform_int_distribution<> dis2(0, combined.size() - 1);
    int capitalLetterIndex = dis2(gen);

														// ensures the capital letter index is different from the special character index
    while (capitalLetterIndex == specialCharIndex) {
        capitalLetterIndex = dis2(gen);
    }

													// creates the password with a length of 8
    std::string password = combined.substr(0, 8);

																// insert the special character and capital letter into the password
    password[specialCharIndex] = specialCharacters[dis(gen)];
    password[capitalLetterIndex] = std::toupper(password[capitalLetterIndex]);

	return password;
}

//--------------------------------------------------------------------------------------
void __fastcall TRegistrationForm::btnClearTextClick(TObject *Sender)
{
    edtname->Text = "";
	edtsurname->Text = "";
	edtnumber->Text = "";
	edtidnumber->Text = "";
	edtcode->Text = "";
	lblusername->Text = "generate_username";
	lblpassword->Text = "generate_password";
	memlogind->Lines->Clear();
	memlogind->Lines->Add("Login Details:");
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::btnregisteruserClick(TObject *Sender)
{
	memlogind->Lines->Clear();
	memlogind->Lines->Add("Login Details:");

	bool isValidId = false;
	bool isValidCellNum = false;

	  fstream file;
	  file.open("Registration_info.txt",ios::app);
	  if(file.is_open()){
		AnsiString name = edtname->Text;
		AnsiString surname = edtsurname->Text;
		AnsiString cell_num = edtnumber->Text;
		AnsiString id_num = edtidnumber->Text;
		AnsiString username = name + "_" + countLinesInFile("Registration_info.txt");   //ensures no 2 users have the same username
		std::string spassword = generatePassword(AnsiString(name).c_str(),AnsiString(surname).c_str(),AnsiString(id_num).c_str(),AnsiString(cell_num).c_str());
		AnsiString password = spassword.c_str();
		AnsiString code = "NO CODE";
		if(edtcode->Text != "") {
			code = edtcode->Text;
		}

		isValidCellNum = isCellNumberValid(cell_num);
		if (isValidCellNum == false) {
			//int cell_chk = Application->MessageBox(L"PLEASE ENTER A 10 DIGIT CELL NUMBER",L"INVALID ID",MB_RETRYCANCEL|MB_ICONEXCLAMATION);
			int cell_chk = MessageDlg("PLEASE ENTER A 10 DIGIT CELL NUMBER", TMsgDlgType::mtError, TMsgDlgButtons() << TMsgDlgBtn::mbRetry << TMsgDlgBtn::mbCancel, 0);
			if (cell_chk == mrRetry) {
			   edtnumber->Text = "";
			}
		}

		isValidId = isIDNumberValid(id_num);
		if (isValidId == false) {
			//int id_chk = Application->MessageBox(L"PLEASE ENTER A 13 DIGIT ID NUMBER",L"INVALID ID",MB_RETRYCANCEL|MB_ICONEXCLAMATION);
			int id_chk = MessageDlg("PLEASE ENTER A 13 DIGIT ID NUMBER", TMsgDlgType::mtError, TMsgDlgButtons() << TMsgDlgBtn::mbRetry << TMsgDlgBtn::mbCancel, 0);
			if (id_chk == mrRetry) {
			   edtidnumber->Text = "";
			}
		}

		if(isValidId && isValidCellNum){
		//file<<name<<":"<<surname<<":"<<cell_num<<":"<<id_num<<":"<<username<<":"<<password<<":"<<code<<"\n";
		file<<username<<":"<<password<<":"<<code<<":"<<name<<":"<<surname<<":"<<cell_num<<":"<<id_num<<":"<<"0"<<":"<<"0"<<":"<<"0"<<"\n";

		 //formate of text fille
		//username:password:code:name:surname:cell_number:id_number:score_Quiz1:score_Quiz2:score_Quiz3

		lblusername->Text = username;
		lblpassword->Text = password;

		memlogind->Lines->Add("Username:"+username);
		memlogind->Lines->Add("Password:"+password);
		memlogind->Lines->Add("Backup-Code:"+code);

		btnsave->Enabled = true;

        edtname->Text = "";
		edtsurname->Text = "";
		edtnumber->Text = "";
		edtidnumber->Text = "";
		edtcode->Text = "";

		int confirmation_m = MessageDlg("USER SUCCESSFULLY REGISTERED", TMsgDlgType::mtConfirmation, TMsgDlgButtons() << TMsgDlgBtn::mbOK, 0);

		}


		file.close();

	  }
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::btnsaveClick(TObject *Sender)
{
    if(SaveDialog1->Execute() == true){
		memlogind->Lines->SaveToFile(SaveDialog1->FileName);
		btnsave->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::FormCreate(TObject *Sender)
{
//Load TImage component and set it as the background of the form
backgroundImage->Parent = RegistrationForm;
backgroundImage->Align = TAlignLayout::Client;
backgroundImage->Bitmap->LoadFromFile("Registration.jpg");
backgroundImage->SendToBack();
}
//---------------------------------------------------------------------------



void __fastcall TRegistrationForm::FormClose(TObject *Sender, TCloseAction &Action)

{
	MainForm->Visible = true;
	Close();
}
//---------------------------------------------------------------------------

