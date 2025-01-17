//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
//---------------------------------------------------------------------------
USEFORM("Registration.cpp", RegistrationForm);
USEFORM("Selection.cpp", SelectionForm);
USEFORM("LeaderBoard.cpp", LeaderBoardForm);
USEFORM("Login.cpp", LoginForm);
USEFORM("Main.cpp", MainForm);
USEFORM("QuizOne.cpp", QuizOneForm);
USEFORM("QuizTwo.cpp", QuizTwoForm);
USEFORM("QuizThree.cpp", QuizThreeForm);
USEFORM("ExtraGame.cpp", GameForm);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TLoginForm), &LoginForm);
		Application->CreateForm(__classid(TRegistrationForm), &RegistrationForm);
		Application->CreateForm(__classid(TSelectionForm), &SelectionForm);
		Application->CreateForm(__classid(TLeaderBoardForm), &LeaderBoardForm);
		Application->CreateForm(__classid(TQuizOneForm), &QuizOneForm);
		Application->CreateForm(__classid(TQuizTwoForm), &QuizTwoForm);
		Application->CreateForm(__classid(TQuizThreeForm), &QuizThreeForm);
		Application->CreateForm(__classid(TGameForm), &GameForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
