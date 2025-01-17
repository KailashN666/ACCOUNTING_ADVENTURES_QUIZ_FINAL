//---------------------------------------------------------------------------

#ifndef QuizTwoH
#define QuizTwoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TQuizTwoForm : public TForm
{
__published:	// IDE-managed Components
	TBrushObject *Brush1;
	TBrushObject *Brush2;
	TBrushObject *Brush3;
	TBrushObject *Brush4;
	TBrushObject *Brush5;
	TBrushObject *Brush6;
	TButton *ConfirmButton;
	TImage *Image1;
	TLabel *Label1;
	TLabel *lblQuestionNumber;
	TLabel *lblScore;
	TProgressBar *Progress;
	TRectangle *Rectangle1;
	TLabel *lblQuestion;
	TRectangle *Rectangle2;
	TRadioButton *rgpA;
	TRadioButton *rgpB;
	TRadioButton *rgpC;
	TRadioButton *rgpD;
	TBrushObject *BrushObject1;
	TRectAnimation *RectAnimation1;
	TStyleBook *StyleBook1;
	void __fastcall ConfirmButtonClick(TObject *Sender);
	void __fastcall rgpAClick(TObject *Sender);
	void __fastcall rgpBClick(TObject *Sender);
	void __fastcall rgpCClick(TObject *Sender);
	void __fastcall rgpDClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TQuizTwoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQuizTwoForm *QuizTwoForm;
//---------------------------------------------------------------------------
#endif
