//---------------------------------------------------------------------------

#ifndef QuizThreeH
#define QuizThreeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TQuizThreeForm : public TForm
{
__published:	// IDE-managed Components
	TBrushObject *Brush1;
	TButton *ConfirmButton;
	TEdit *edtAnswer;
	TImage *image;
	TImage *Image1;
	TLabel *Label1;
	TLabel *lblInstructions;
	TLabel *lblQuestionNumber;
	TLabel *lblScore;
	TProgressBar *Progress;
	TStyleBook *StyleBook1;
	void __fastcall ConfirmButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TQuizThreeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQuizThreeForm *QuizThreeForm;
//---------------------------------------------------------------------------
#endif
