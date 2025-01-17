//---------------------------------------------------------------------------

#ifndef SelectionH
#define SelectionH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Edit.hpp>
//---------------------------------------------------------------------------
class TSelectionForm : public TForm
{
__published:	// IDE-managed Components
	TRectangle *Rectangle1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLine *Line1;
	TEdit *edtname;
	TLine *Line2;
	TEdit *edtsurname;
	TLabel *Label7;
	TLine *Line4;
	TEdit *edtscore1;
	TLabel *Label5;
	TLine *Line5;
	TEdit *edtscore2;
	TLine *Line6;
	TEdit *edtscore3;
	TLabel *Label8;
	TLabel *Label6;
	TRoundRect *btnquiz1;
	TLabel *Label18;
	TRoundRect *btnquiz2;
	TLabel *Label9;
	TImage *backgroundImage;
	TRectangle *Rectangle3;
	TRoundRect *RoundRect1;
	TLabel *lblusername;
	TRoundRect *btnquiz3;
	TLabel *Label10;
	TRoundRect *btnLeaderBoard;
	TLabel *Label11;
	TRoundRect *btnextrgame;
	TLabel *Label12;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnLeaderBoardClick(TObject *Sender);
	void __fastcall btnquiz1Click(TObject *Sender);
	void __fastcall btnquiz2Click(TObject *Sender);
	void __fastcall btnquiz3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnextrgameClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSelectionForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectionForm *SelectionForm;
//---------------------------------------------------------------------------
#endif
