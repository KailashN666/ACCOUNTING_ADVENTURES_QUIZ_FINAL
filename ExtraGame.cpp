//---------------------------------------------------------------------------

#include <fmx.h>

#include <random>
#include <Winapi.ShellAPI.hpp>

#pragma hdrstop

#include "ExtraGame.h"
#include "Selection.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TGameForm *GameForm;
//---------------------------------------------------------------------------

static int GenerateRandomNumber() {
	int MinRange = 0; // Minimum range value
	int MaxRange = 24; // Maximum range value

	// Generate a random number within the specified range
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(MinRange, MaxRange);
	int iRandomNumber = dist(mt);
	return iRandomNumber;
}

AnsiString BankOfTerms [25] = {"asset", "capital", "credit", "debit", "diversification", "expenses", "equity", "insolvency"
							   "ledger", "liability", "income", "profit", "loss", "bond", "account", "investment", "abatement"
							   "accrual", "actuary", "annuity", "audit", "dividend", "liquidation", "rebate", "revenue"};

int iRandom = GenerateRandomNumber();
AnsiString sSecretWord = BankOfTerms[iRandom];
AnsiString sGuessWord;

int iRemainingAttempts = 6;

__fastcall TGameForm::TGameForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::FormCreate(TObject *Sender)
{
  sGuessWord = StringOfChar('-', sSecretWord.Length());
  lblGuessed->Text = sGuessWord;
  lblAttempts->Text = "Remaining attempts: " + IntToStr(iRemainingAttempts);
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::btnSubmitClick(TObject *Sender)
{
    AnsiString cLetter = edtLetter->Text.LowerCase();

	if (cLetter.Length() != 1)
	{
		ShowMessage("Please enter a single letter.");
		edtLetter->Text = "";
		return;
	}

	// Check if the letter is in the secret word
	bool bFound = false;
	for (int i = 1; i <= sSecretWord.Length(); i++)
	{
		if (sSecretWord[i] == cLetter[1])
		{
			sGuessWord[i] = cLetter[1];
			bFound = true;
		}
	}

	if (!bFound)
	{
		iRemainingAttempts--;
		TBitmap *bitmap = new TBitmap();

		bitmap->LoadFromFile("Hang" + IntToStr(iRemainingAttempts) + ".png");
		image->Bitmap->Assign(bitmap);
	}

	lblGuessed->Text = sGuessWord;
	lblAttempts->Text = "Remaining attempts: " + IntToStr(iRemainingAttempts);
    Progress->Value = iRemainingAttempts;

	// Game is over?
	if (iRemainingAttempts == 0 || sGuessWord == sSecretWord)
	{
		btnSubmit->Enabled = false;
        edtLetter->Enabled = false;
		if (sGuessWord == sSecretWord)
		{
			ShowMessage("Congratulations! You guessed the word.");
			btnStillBored->Visible = true;
		}
		else
		{
			ShowMessage("Game over. Bro was hanged. The word was: " + sSecretWord);
            btnStillBored->Visible = true;
		}
	}

	edtLetter->Text = "";

}

std::wstring ConvertToWideString(const char* str)
{
    int length = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
    wchar_t* buffer = new wchar_t[length];
    MultiByteToWideChar(CP_ACP, 0, str, -1, buffer, length);
    std::wstring result(buffer);
	delete[] buffer;
	return result;
}

//---------------------------------------------------------------------------

void __fastcall TGameForm::btnStillBoredClick(TObject *Sender)
{
    const char* Link = "https://youtu.be/xvFZjo5PgG0";
	std::wstring YoutubeLink = ConvertToWideString(Link);

	//AnsiString YoutubeLink = "https://youtu.be/xvFZjo5PgG0";

	ShellExecuteW(0, L"open", YoutubeLink.c_str(), 0, 0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	iRandom = GenerateRandomNumber();
	sSecretWord = BankOfTerms[iRandom];
	sGuessWord;
	iRemainingAttempts = 6;

	TBitmap *bitmap = new TBitmap();

	//bitmap->LoadFromFile();
	image->Bitmap->Assign(bitmap);

    sGuessWord = StringOfChar('-', sSecretWord.Length());
	lblGuessed->Text = sGuessWord;
	lblAttempts->Text = "Remaining attempts: " + IntToStr(iRemainingAttempts);

    btnSubmit->Enabled = false;
	edtLetter->Enabled = false;

	btnStillBored->Visible = false;

	SelectionForm->Visible= true;
}
//---------------------------------------------------------------------------
