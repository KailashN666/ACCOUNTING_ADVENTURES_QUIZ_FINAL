//---------------------------------------------------------------------------

#ifndef LoginH
#define LoginH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TLoginForm : public TForm
{
__published:	// IDE-managed Components
	TImage *backgroundImage;
	TRectangle *Rectangle1;
	TCircle *Circle;
	TImage *iconImage;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLine *Line1;
	TEdit *edtusername;
	TLine *Line2;
	TEdit *edtpassword;
	TRoundRect *RoundRect1;
	TLabel *Label4;
	TRectangle *Rectangle2;
	void __fastcall RoundRect1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TLoginForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLoginForm *LoginForm;

//---------------------------------------------------------------------------
#endif
