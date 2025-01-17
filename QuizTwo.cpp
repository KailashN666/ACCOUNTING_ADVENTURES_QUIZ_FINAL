//---------------------------------------------------------------------------

#include <fmx.h>
#include<vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <Windows.h>
#include <mmsystem.h>

#pragma hdrstop

#include "QuizTwo.h"
#include "GlobalVariables.h"
#include "Selection.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TQuizTwoForm *QuizTwoForm;
//---------------------------------------------------------------------------
userInfo currentUserInfo; //make sure to add to all

class QuestionMultipleChoice{
  public:
	std::string FocusQuestion;
	std::string OptionA;
	std::string OptionB;
	std::string OptionC;
	std::string OptionD;
	std::string CorrectAnswer;

	QuestionMultipleChoice(){
	}

	QuestionMultipleChoice(std::string cQuest, std::string OptA, std::string OptB, std::string OptC, std::string OptD, std::string cAnswer){
		FocusQuestion=cQuest;
		OptionA=OptA;
		OptionB=OptB;
		OptionC=OptC;
		OptionD=OptD;
		CorrectAnswer=cAnswer;
	}

};

static std::vector<QuestionMultipleChoice> LoadQuestions(){

	std::ifstream inputFile("Level 2 Bank.txt");

	 if (!inputFile){
		ShowMessage("Failed to open the file!");
	 }


	std::string sa1;
	std::string sa2;
	std::string sa3;
	std::string sa4;
	std::string sa5;
	std::string sa6;

	static std::vector<QuestionMultipleChoice> questions;

	for (int i = 1; i < 76; i++) {
			std::getline(inputFile, sa1);
			std::getline(inputFile, sa2);
			std::getline(inputFile, sa3);
			std::getline(inputFile, sa4);
			std::getline(inputFile, sa5);
			std::getline(inputFile, sa6);
			QuestionMultipleChoice q = QuestionMultipleChoice(sa1,sa2,sa3,sa4,sa5,sa6);
			questions.push_back(q);
	}

	inputFile.close();

	return questions;
}

static int GenerateRandomNumber() {
	int MinRange = 0; // Minimum range value
	int MaxRange = 74; // Maximum range value

	// Generate a random number within the specified range
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(MinRange, MaxRange);
	int iRandomNumber = dist(mt);
	return iRandomNumber;
}

static std::vector<QuestionMultipleChoice>VectorQuestions;
static int IndexArray [10];
//scores object
Score Points = Score(0);
static int QuestionCounter = 0;
static QuestionMultipleChoice CurrentQuestion;

__fastcall TQuizTwoForm::TQuizTwoForm(TComponent* Owner)
	: TForm(Owner)
{

	VectorQuestions=LoadQuestions();

	int RandomNumber = GenerateRandomNumber();

	IndexArray[QuestionCounter] = RandomNumber;
	QuestionCounter += 1;
	CurrentQuestion = VectorQuestions[RandomNumber];

	UnicodeString uniQuestion = UnicodeString(CurrentQuestion.FocusQuestion.c_str());
	UnicodeString uniA = UnicodeString(CurrentQuestion.OptionA.c_str());
	UnicodeString uniB = UnicodeString(CurrentQuestion.OptionB.c_str());
	UnicodeString uniC = UnicodeString(CurrentQuestion.OptionC.c_str());
	UnicodeString uniD = UnicodeString(CurrentQuestion.OptionD.c_str());
	lblQuestion->Text = uniQuestion;
	rgpA->Text = "A. " + uniA;
	rgpB->Text = "B. " + uniB;
	rgpC->Text = "C. " + uniC;
	rgpD->Text = "D. " + uniD;
	lblQuestionNumber->Text = "Question " +IntToStr(QuestionCounter) + " of 10";
	lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
	Progress->Value = QuestionCounter;

}
//---------------------------------------------------------------------------
void __fastcall TQuizTwoForm::ConfirmButtonClick(TObject *Sender)
{
   static int RandomNumber;
   static bool Found;
   static int I;
   static UnicodeString uniQuestion;
   static UnicodeString uniA;
   static UnicodeString uniB;
   static UnicodeString uniC;
   static UnicodeString uniD;

   if (rgpA->IsChecked) {
	  if (CurrentQuestion.CorrectAnswer == "A") {
		  ++Points;
		  PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME);

		  if (QuestionCounter < 10) {
			 RandomNumber = GenerateRandomNumber();

			 Found = false;
			 for (I = 0; I < 10; I++) {
				 if (IndexArray[I] == RandomNumber) {
					 Found = true;
				 }
			 }

			 if (Found == true) {
				 do{
				   RandomNumber = GenerateRandomNumber();

					Found = false;
					for (I = 0; I < 10; I++) {
						if (IndexArray[I] == RandomNumber) {
							Found = true;
						}
					}
				 } while (Found == true);
			 }

			 IndexArray[QuestionCounter] = RandomNumber;
			 QuestionCounter += 1;
			 CurrentQuestion = VectorQuestions[RandomNumber];

			 uniQuestion = UnicodeString(CurrentQuestion.FocusQuestion.c_str());
			 uniA = UnicodeString(CurrentQuestion.OptionA.c_str());
			 uniB = UnicodeString(CurrentQuestion.OptionB.c_str());
			 uniC = UnicodeString(CurrentQuestion.OptionC.c_str());
			 uniD = UnicodeString(CurrentQuestion.OptionD.c_str());
			 lblQuestion->Text = uniQuestion;
			 rgpA->Text = "A. " + uniA;
			 rgpB->Text = "B. " + uniB;
			 rgpC->Text = "C. " + uniC;
			 rgpD->Text = "D. " + uniD;
			 lblQuestionNumber->Text = "Question " +IntToStr(QuestionCounter) + " of 10";
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 Progress->Value = QuestionCounter;

		  }else{
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 rgpA->Enabled = false;
			 rgpB->Enabled = false;
			 rgpC->Enabled = false;
			 rgpD->Enabled = false;
			 ConfirmButton->Enabled= false;

			 ShowMessage("Congratulations. You have completed phase of the quiz with a score of " + IntToStr(Points.getPoints()) + " out of 100.");


			 currentUserInfo.score2 = Points.getPoints();      /////////////////////get new points
			 changeScore(currentUserInfo);     				   ////////////////////chnage score
		  }

	  }else{
		  if (QuestionCounter < 10) {
			 RandomNumber = GenerateRandomNumber();

			 Found = false;
			 for (I = 0; I < 10; I++) {
				 if (IndexArray[I] == RandomNumber) {
					 Found = true;
				 }
			 }

			 if (Found == true) {
				 do{
				   RandomNumber = GenerateRandomNumber();

					Found = false;
					for (I = 0; I < 10; I++) {
						if (IndexArray[I] == RandomNumber) {
							Found = true;
						}
					}
				 } while (Found == true);
			 }

			 IndexArray[QuestionCounter] = RandomNumber;
			 QuestionCounter += 1;
			 CurrentQuestion = VectorQuestions[RandomNumber];

			 uniQuestion = UnicodeString(CurrentQuestion.FocusQuestion.c_str());
			 uniA = UnicodeString(CurrentQuestion.OptionA.c_str());
			 uniB = UnicodeString(CurrentQuestion.OptionB.c_str());
			 uniC = UnicodeString(CurrentQuestion.OptionC.c_str());
			 uniD = UnicodeString(CurrentQuestion.OptionD.c_str());
			 lblQuestion->Text = uniQuestion;
			 rgpA->Text = "A. " + uniA;
			 rgpB->Text = "B. " + uniB;
			 rgpC->Text = "C. " + uniC;
			 rgpD->Text = "D. " + uniD;
			 lblQuestionNumber->Text = "Question " +IntToStr(QuestionCounter) + " of 10";
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 Progress->Value = QuestionCounter;
		  }else{
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/10";
			 rgpA->Enabled = false;
			 rgpB->Enabled = false;
			 rgpC->Enabled = false;
			 rgpD->Enabled = false;
			 ConfirmButton->Enabled= false;

			 ShowMessage("Congratulations. You have completed phase of the quiz with a score of " + IntToStr(Points.getPoints()) + " out of 10.");


             currentUserInfo.score2 = Points.getPoints();      /////////////////////get new points
			 changeScore(currentUserInfo);     				   ////////////////////chnage score
		  }
	  }
	 rgpA->IsChecked = false;
   }else if (rgpB->IsChecked) {
	  if (CurrentQuestion.CorrectAnswer == "B") {
		  ++Points;
		  PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME);

		  if (QuestionCounter < 10) {
			 RandomNumber = GenerateRandomNumber();

			 Found = false;
			 for (I = 0; I < 10; I++) {
				 if (IndexArray[I] == RandomNumber) {
					 Found = true;
				 }
			 }

			 if (Found == true) {
				 do{
				   RandomNumber = GenerateRandomNumber();

					Found = false;
					for (I = 0; I < 10; I++) {
						if (IndexArray[I] == RandomNumber) {
							Found = true;
						}
					}
				 } while (Found == true);
			 }

			 IndexArray[QuestionCounter] = RandomNumber;
			 QuestionCounter += 1;
			 CurrentQuestion = VectorQuestions[RandomNumber];

			 uniQuestion = UnicodeString(CurrentQuestion.FocusQuestion.c_str());
			 uniA = UnicodeString(CurrentQuestion.OptionA.c_str());
			 uniB = UnicodeString(CurrentQuestion.OptionB.c_str());
			 uniC = UnicodeString(CurrentQuestion.OptionC.c_str());
			 uniD = UnicodeString(CurrentQuestion.OptionD.c_str());
			 lblQuestion->Text = uniQuestion;
			 rgpA->Text = "A. " + uniA;
			 rgpB->Text = "B. " + uniB;
			 rgpC->Text = "C. " + uniC;
			 rgpD->Text = "D. " + uniD;
			 lblQuestionNumber->Text = "Question " +IntToStr(QuestionCounter) + " of 10";
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 Progress->Value = QuestionCounter;

		  }else{
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 rgpA->Enabled = false;
			 rgpB->Enabled = false;
			 rgpC->Enabled = false;
			 rgpD->Enabled = false;
			 ConfirmButton->Enabled= false;

			 ShowMessage("Congratulations. You have completed phase of the quiz with a score of " + IntToStr(Points.getPoints()) + " out of 100.");


             currentUserInfo.score2 = Points.getPoints();      /////////////////////get new points
			 changeScore(currentUserInfo);     				   ////////////////////chnage score
		  }

	  }else{
		  if (QuestionCounter < 10) {
			 RandomNumber = GenerateRandomNumber();

			 Found = false;
			 for (I = 0; I < 10; I++) {
				 if (IndexArray[I] == RandomNumber) {
					 Found = true;
				 }
			 }

			 if (Found == true) {
				 do{
				   RandomNumber = GenerateRandomNumber();

					Found = false;
					for (I = 0; I < 10; I++) {
						if (IndexArray[I] == RandomNumber) {
							Found = true;
						}
					}
				 } while (Found == true);
			 }

			 IndexArray[QuestionCounter] = RandomNumber;
			 QuestionCounter += 1;
			 CurrentQuestion = VectorQuestions[RandomNumber];

			 uniQuestion = UnicodeString(CurrentQuestion.FocusQuestion.c_str());
			 uniA = UnicodeString(CurrentQuestion.OptionA.c_str());
			 uniB = UnicodeString(CurrentQuestion.OptionB.c_str());
			 uniC = UnicodeString(CurrentQuestion.OptionC.c_str());
			 uniD = UnicodeString(CurrentQuestion.OptionD.c_str());
			 lblQuestion->Text = uniQuestion;
			 rgpA->Text = "A. " + uniA;
			 rgpB->Text = "B. " + uniB;
			 rgpC->Text = "C. " + uniC;
			 rgpD->Text = "D. " + uniD;
			 lblQuestionNumber->Text = "Question " +IntToStr(QuestionCounter) + " of 10";
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 Progress->Value = QuestionCounter;
		  }else{
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 rgpA->Enabled = false;
			 rgpB->Enabled = false;
			 rgpC->Enabled = false;
			 rgpD->Enabled = false;
			 ConfirmButton->Enabled= false;

			 ShowMessage("Congratulations. You have completed phase of the quiz with a score of " + IntToStr(Points.getPoints()) + " out of 100.");


             currentUserInfo.score2 = Points.getPoints();      /////////////////////get new points
			 changeScore(currentUserInfo);     				   ////////////////////chnage score
		  }
	  }
	 rgpB->IsChecked = false;
   }else if (rgpC->IsChecked) {
	  if (CurrentQuestion.CorrectAnswer == "C") {
		  ++Points;
		  PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME);

		  if (QuestionCounter < 10) {
			 RandomNumber = GenerateRandomNumber();

			 Found = false;
			 for (I = 0; I < 10; I++) {
				 if (IndexArray[I] == RandomNumber) {
					 Found = true;
				 }
			 }

			 if (Found == true) {
				 do{
				   RandomNumber = GenerateRandomNumber();

					Found = false;
					for (I = 0; I < 10; I++) {
						if (IndexArray[I] == RandomNumber) {
							Found = true;
						}
					}
				 } while (Found == true);
			 }

			 IndexArray[QuestionCounter] = RandomNumber;
			 QuestionCounter += 1;
			 CurrentQuestion = VectorQuestions[RandomNumber];

			 uniQuestion = UnicodeString(CurrentQuestion.FocusQuestion.c_str());
			 uniA = UnicodeString(CurrentQuestion.OptionA.c_str());
			 uniB = UnicodeString(CurrentQuestion.OptionB.c_str());
			 uniC = UnicodeString(CurrentQuestion.OptionC.c_str());
			 uniD = UnicodeString(CurrentQuestion.OptionD.c_str());
			 lblQuestion->Text = uniQuestion;
			 rgpA->Text = "A. " + uniA;
			 rgpB->Text = "B. " + uniB;
			 rgpC->Text = "C. " + uniC;
			 rgpD->Text = "D. " + uniD;
			 lblQuestionNumber->Text = "Question " +IntToStr(QuestionCounter) + " of 10";
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 Progress->Value = QuestionCounter;

		  }else{
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 rgpA->Enabled = false;
			 rgpB->Enabled = false;
			 rgpC->Enabled = false;
			 rgpD->Enabled = false;
			 ConfirmButton->Enabled= false;

			 ShowMessage("Congratulations. You have completed phase of the quiz with a score of " + IntToStr(Points.getPoints()) + " out of 100.");


			 currentUserInfo.score2 = Points.getPoints();      /////////////////////get new points
			 changeScore(currentUserInfo);     				   ////////////////////chnage score
		  }

	  }else{
		  if (QuestionCounter < 10) {
			 RandomNumber = GenerateRandomNumber();

			 Found = false;
			 for (I = 0; I < 10; I++) {
				 if (IndexArray[I] == RandomNumber) {
					 Found = true;
				 }
			 }

			 if (Found == true) {
				 do{
				   RandomNumber = GenerateRandomNumber();

					Found = false;
					for (I = 0; I < 10; I++) {
						if (IndexArray[I] == RandomNumber) {
							Found = true;
						}
					}
				 } while (Found == true);
			 }

			 IndexArray[QuestionCounter] = RandomNumber;
			 QuestionCounter += 1;
			 CurrentQuestion = VectorQuestions[RandomNumber];

			 uniQuestion = UnicodeString(CurrentQuestion.FocusQuestion.c_str());
			 uniA = UnicodeString(CurrentQuestion.OptionA.c_str());
			 uniB = UnicodeString(CurrentQuestion.OptionB.c_str());
			 uniC = UnicodeString(CurrentQuestion.OptionC.c_str());
			 uniD = UnicodeString(CurrentQuestion.OptionD.c_str());
			 lblQuestion->Text = uniQuestion;
			 rgpA->Text = "A. " + uniA;
			 rgpB->Text = "B. " + uniB;
			 rgpC->Text = "C. " + uniC;
			 rgpD->Text = "D. " + uniD;
			 lblQuestionNumber->Text = "Question " +IntToStr(QuestionCounter) + " of 10";
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 Progress->Value = QuestionCounter;
		  }else{
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 rgpA->Enabled = false;
			 rgpB->Enabled = false;
			 rgpC->Enabled = false;
			 rgpD->Enabled = false;
			 ConfirmButton->Enabled= false;

			 ShowMessage("Congratulations. You have completed phase of the quiz with a score of " + IntToStr(Points.getPoints()) + " out of 100.");


			 currentUserInfo.score2 = Points.getPoints();      /////////////////////get new points
			 changeScore(currentUserInfo);     				   ////////////////////chnage score
		  }
	  }
	 rgpC->IsChecked = false;
   }else if (rgpD->IsChecked) {
      if (CurrentQuestion.CorrectAnswer == "D") {
		  ++Points;
		  PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME);

		  if (QuestionCounter < 10) {
			 RandomNumber = GenerateRandomNumber();

			 Found = false;
			 for (I = 0; I < 10; I++) {
				 if (IndexArray[I] == RandomNumber) {
					 Found = true;
				 }
			 }

			 if (Found == true) {
				 do{
				   RandomNumber = GenerateRandomNumber();

					Found = false;
					for (I = 0; I < 10; I++) {
						if (IndexArray[I] == RandomNumber) {
							Found = true;
						}
					}
				 } while (Found == true);
			 }

			 IndexArray[QuestionCounter] = RandomNumber;
			 QuestionCounter += 1;
			 CurrentQuestion = VectorQuestions[RandomNumber];

			 uniQuestion = UnicodeString(CurrentQuestion.FocusQuestion.c_str());
			 uniA = UnicodeString(CurrentQuestion.OptionA.c_str());
			 uniB = UnicodeString(CurrentQuestion.OptionB.c_str());
			 uniC = UnicodeString(CurrentQuestion.OptionC.c_str());
			 uniD = UnicodeString(CurrentQuestion.OptionD.c_str());
			 lblQuestion->Text = uniQuestion;
			 rgpA->Text = "A. " + uniA;
			 rgpB->Text = "B. " + uniB;
			 rgpC->Text = "C. " + uniC;
			 rgpD->Text = "D. " + uniD;
			 lblQuestionNumber->Text = "Question " +IntToStr(QuestionCounter) + " of 10";
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 Progress->Value = QuestionCounter;

		  }else{
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 rgpA->Enabled = false;
			 rgpB->Enabled = false;
			 rgpC->Enabled = false;
			 rgpD->Enabled = false;
			 ConfirmButton->Enabled= false;

			 ShowMessage("Congratulations. You have completed phase of the quiz with a score of " + IntToStr(Points.getPoints()) + " out of 100.");


			 currentUserInfo.score2 = Points.getPoints();      /////////////////////get new points
			 changeScore(currentUserInfo);     				   ////////////////////chnage score
		  }

	  }else{
		  if (QuestionCounter < 10) {
			 RandomNumber = GenerateRandomNumber();

			 Found = false;
			 for (I = 0; I < 10; I++) {
				 if (IndexArray[I] == RandomNumber) {
					 Found = true;
				 }
			 }

			 if (Found == true) {
				 do{
				   RandomNumber = GenerateRandomNumber();

					Found = false;
					for (I = 0; I < 10; I++) {
						if (IndexArray[I] == RandomNumber) {
							Found = true;
						}
					}
				 } while (Found == true);
			 }

			 IndexArray[QuestionCounter] = RandomNumber;
			 QuestionCounter += 1;
			 CurrentQuestion = VectorQuestions[RandomNumber];

			 uniQuestion = UnicodeString(CurrentQuestion.FocusQuestion.c_str());
			 uniA = UnicodeString(CurrentQuestion.OptionA.c_str());
			 uniB = UnicodeString(CurrentQuestion.OptionB.c_str());
			 uniC = UnicodeString(CurrentQuestion.OptionC.c_str());
			 uniD = UnicodeString(CurrentQuestion.OptionD.c_str());
			 lblQuestion->Text = uniQuestion;
			 rgpA->Text = "A. " + uniA;
			 rgpB->Text = "B. " + uniB;
			 rgpC->Text = "C. " + uniC;
			 rgpD->Text = "D. " + uniD;
			 lblQuestionNumber->Text = "Question " +IntToStr(QuestionCounter) + " of 10";
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 Progress->Value = QuestionCounter;
		  }else{
			 lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
			 rgpA->Enabled = false;
			 rgpB->Enabled = false;
			 rgpC->Enabled = false;
			 rgpD->Enabled = false;
			 ConfirmButton->Enabled= false;

			 ShowMessage("Congratulations. You have completed phase of the quiz with a score of " + IntToStr(Points.getPoints()) + " out of 100.");


			 currentUserInfo.score2 = Points.getPoints();      /////////////////////get new points
			 changeScore(currentUserInfo);     				   ////////////////////chnage score
		  }
	  }
	 rgpD->IsChecked = false;
   }else {
	 ShowMessage("You have not selected an option.");
   }
}
//---------------------------------------------------------------------------
void __fastcall TQuizTwoForm::rgpAClick(TObject *Sender)
{
  rgpB->IsChecked = false;
  rgpC->IsChecked = false;
  rgpD->IsChecked = false;
}
//---------------------------------------------------------------------------
void __fastcall TQuizTwoForm::rgpBClick(TObject *Sender)
{
  rgpA->IsChecked = false;
  rgpC->IsChecked = false;
  rgpD->IsChecked = false;
}
//---------------------------------------------------------------------------
void __fastcall TQuizTwoForm::rgpCClick(TObject *Sender)
{
  rgpA->IsChecked = false;
  rgpB->IsChecked = false;
  rgpD->IsChecked = false;
}
//---------------------------------------------------------------------------
void __fastcall TQuizTwoForm::rgpDClick(TObject *Sender)
{
  rgpA->IsChecked = false;
  rgpB->IsChecked = false;
  rgpC->IsChecked = false;
}
//---------------------------------------------------------------------------
void __fastcall TQuizTwoForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	std::vector<QuestionMultipleChoice>VectorQuestions;
	IndexArray [10];
	//scores object
	Points = Score(0);
	QuestionCounter = 0;
	CurrentQuestion;

    VectorQuestions=LoadQuestions();

	int RandomNumber = GenerateRandomNumber();

	IndexArray[QuestionCounter] = RandomNumber;
	QuestionCounter += 1;
	CurrentQuestion = VectorQuestions[RandomNumber];

	UnicodeString uniQuestion = UnicodeString(CurrentQuestion.FocusQuestion.c_str());
	UnicodeString uniA = UnicodeString(CurrentQuestion.OptionA.c_str());
	UnicodeString uniB = UnicodeString(CurrentQuestion.OptionB.c_str());
	UnicodeString uniC = UnicodeString(CurrentQuestion.OptionC.c_str());
	UnicodeString uniD = UnicodeString(CurrentQuestion.OptionD.c_str());
	lblQuestion->Text = uniQuestion;
	rgpA->Text = "A. " + uniA;
	rgpB->Text = "B. " + uniB;
	rgpC->Text = "C. " + uniC;
	rgpD->Text = "D. " + uniD;
	lblQuestionNumber->Text = "Question " +IntToStr(QuestionCounter) + " of 10";
	lblScore->Text = "Your score is " +IntToStr(Points.getPoints()) + "/100";
	Progress->Value = QuestionCounter;

	rgpA->Enabled = true;
	rgpB->Enabled = true;
	rgpC->Enabled = true;
	rgpD->Enabled = true;
	ConfirmButton->Enabled= true;

	SelectionForm->Visible= true;
}
//---------------------------------------------------------------------------
void __fastcall TQuizTwoForm::FormCreate(TObject *Sender)
{
	Image1->Bitmap->LoadFromFile("LevelPic.jpg");
}
//---------------------------------------------------------------------------
void __fastcall TQuizTwoForm::FormActivate(TObject *Sender)
{
	loadUserData(currentUserInfo);       ////////////////////////////////load user
}
//---------------------------------------------------------------------------
