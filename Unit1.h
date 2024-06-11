//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Menus.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.DateTimeCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTabControl *TabControl1;
	TTabItem *TabItem1;
	TTabItem *TabItem2;
	TButton *AddButton;
	TEdit *AddEdit;
	TLabel *AddLabel;
	TButton *DeleteButton;
	TEdit *DeleteEdit;
	TLabel *DeleteLabel;
	TStringGrid *InventGrid;
	TStringColumn *NameStringColumn;
	TIntegerColumn *IDIntegerColumn;
	TStringColumn *StatusStringColumn;
	TDateColumn *DateColumn;
	TStringGrid *TransGrid;
	TStringColumn *NameStringColumn_tr;
	TIntegerColumn *IDIntegerColumn_tr;
	TStringColumn *StatusStringColumn_tr;
	TDateColumn *DateColumn_tr;
	TTabItem *TabItem3;
	TStringGrid *SearchStringGrid;
	TStringColumn *NameStringColumn_sr;
	TIntegerColumn *IDIntegerColumn_sr;
	TStringColumn *StatusStringColumn_sr;
	TDateColumn *DateColumn_sr;
	TButton *SearchButton;
	TEdit *SearchEdit;
	TLabel *SearchLabel;
	TLabel *MatchesLabel;
	TTabItem *TabItem4;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TComboBox *ComboBox;
	TEdit *IDEdit;
	TLabel *IDLabel;
	TButton *ConfirmButton;
	TListBoxItem *CheckListBoxItem;
	TListBoxItem *ReturnListBoxItem;
	TLabel *StatusLabel;
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall DeleteButtonClick(TObject *Sender);
	void __fastcall SearchButtonClick(TObject *Sender);
	void __fastcall AddEditKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall DeleteEditKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall SearchEditKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ConfirmButtonClick(TObject *Sender);



private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
