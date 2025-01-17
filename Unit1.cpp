//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------

int id, col_count =  4, NameCol_index = 0, IdCol_index = 1, StatCol_index = 2, DateCol_index = 3;
void __fastcall TForm1::AddButtonClick(TObject *Sender)
{
	if (AddEdit->Text.Trim() == "") {
		ShowMessage("'Book Name' should not be empty.");
		AddEdit->Text = "";
		return;
	}

	for (int row = 0; row < (InventGrid->RowCount); row++) {
		if (LowerCase(InventGrid->Cells[NameCol_index][row]) == LowerCase(AddEdit->Text.Trim())) {
			ShowMessage("A book with this name already exists.\nPlease enter a unique book name.");
			AddEdit->Text = "";
			return;
		}
	}

	int add_row = 0;
	if (!((InventGrid->RowCount == 1) && (InventGrid->Cells[0][0] == ""))) {
		add_row = (InventGrid->RowCount)++;
	}

	InventGrid->Cells[NameCol_index][add_row] = AddEdit->Text.Trim();
	InventGrid->Cells[IdCol_index][add_row] = id++;
	AddEdit->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteButtonClick(TObject *Sender)
{
	if (DeleteEdit->Text.Trim() == "") {
		ShowMessage("'Book ID' should not be empty.");
		DeleteEdit->Text = "";
		return;
	}

	int del_row = -1;
	for (int row = 0; row < (InventGrid->RowCount); row++) {
		if (InventGrid->Cells[IdCol_index][row] == DeleteEdit->Text.Trim()) {
			del_row = row;
			break;
		}
	}

	if (del_row == -1) {
		ShowMessage("No book found with the entered ID.\nPlease double-check the ID and try again.");
	} else if ((del_row == 0) && (InventGrid->RowCount == 1)) { //special case
		for (int col = 0; col < col_count; col++) {
			InventGrid->Cells[col][del_row] = "";
		}
	} else {
		if (del_row < (InventGrid->RowCount)-1) {
			for (int row = del_row; row < (InventGrid->RowCount)-1; row++) {
				for (int col = 0; col < col_count; col++) {
					InventGrid->Cells[col][row] = InventGrid->Cells[col][row+1];
				}
			}
		}
		InventGrid->RowCount--;
	}

	DeleteEdit->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConfirmButtonClick(TObject *Sender)
{
	if ((IDEdit->Text.Trim() == "") || (ComboBox->ItemIndex == -1)) {
		ShowMessage("'Book ID' and 'Book Status' should not be empty.");
		IDEdit->Text = "";
		return;
	}

	int invent_row = -1;
	for (int row = 0; row < (InventGrid->RowCount); row++) {
		if (InventGrid->Cells[IdCol_index][row] == IDEdit->Text.Trim()) {
			invent_row = row;
			if (ComboBox->Text == "Returned" && InventGrid->Cells[StatCol_index][invent_row] != "Checked out") {
				ShowMessage("Cannot update the status to 'Returned' as the book has not been checked out.");
			} else if (ComboBox->Text == InventGrid->Cells[StatCol_index][invent_row]) {
				String message = "This book has already been " + ComboBox->Text + ".";
				ShowMessage(message);
			} else {
				int trans_row = 0;
				if (!((TransGrid->RowCount == 1) && (TransGrid->Cells[0][0] == ""))) {
					trans_row = (TransGrid->RowCount)++;
				}
				TransGrid->Cells[NameCol_index][trans_row] = InventGrid->Cells[NameCol_index][invent_row];
				TransGrid->Cells[IdCol_index][trans_row] = InventGrid->Cells[IdCol_index][invent_row];
				TransGrid->Cells[StatCol_index][trans_row] = ComboBox->Text;
				TDateTime now = TDateTime::CurrentDateTime();
				String dateString = FormatDateTime("dd/mm/yyyy", now);
				TransGrid->Cells[DateCol_index][trans_row] = dateString;

				InventGrid->Cells[StatCol_index][invent_row] = ComboBox->Text;
				InventGrid->Cells[DateCol_index][invent_row] = dateString;
				break;
			}
		}
	}

	if (invent_row == -1) {
		ShowMessage("No book found with the entered ID.\nPlease double-check the ID and try again.");
	}

	IDEdit->Text = "";
	ComboBox->ItemIndex = -1;
	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SearchButtonClick(TObject *Sender)
{
	int match = 0;
	SearchStringGrid->RowCount = 1;
	for (int col = 0; col < col_count; col++) {
		SearchStringGrid->Cells[col][0] = "";
	}

	if (SearchEdit->Text.Trim() == "") {
		ShowMessage("'Book Name' should not be empty.");
		return;
	}

	int len = (SearchEdit->Text).Length();
	for (int row = 0; row < (InventGrid->RowCount); row++) {
		if (LowerCase(InventGrid->Cells[NameCol_index][row].SubString(0, len)) == LowerCase(SearchEdit->Text.Trim())) {
			if (match >= 1) {
				SearchStringGrid->RowCount++;
			}
			for (int col = 0; col < col_count; col++) {
				SearchStringGrid->Cells[col][match] = InventGrid->Cells[col][row];
			}
			match++;
		}
	}
	MatchesLabel->Text = match;
	if (match == 0) {
		ShowMessage("No book found with the entered name.\nPlease double-check the name and try again.");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AddEditKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
	if (Key == VK_RETURN) {
		AddButtonClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteEditKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
	if (Key == VK_RETURN) {
		DeleteButtonClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SearchEditKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
	if (Key == VK_RETURN) {
		SearchButtonClick(Sender);
	}
}
//---------------------------------------------------------------------------

void SaveGridToFile(TStringGrid *Grid, const String &FileName)
{
	ofstream file(FileName.c_str()); // Open file for writing
	for (int row = 0; row < (Grid->RowCount); row++) {
		for (int col = 0; col < col_count; col++) {
			if (col > 0)  {
				file << ",";
			}
			AnsiString ansiString = Grid->Cells[col][row];
			file << ansiString;
		}
		file << endl;
	}
	file.close();
}
//---------------------------------------------------------------------------

void LoadGridFromFile(TStringGrid *Grid, const String &FileName)
{
	ifstream file(FileName.c_str());
	string line;
	int row = 0;
	while (getline(file, line)) {
		int col = 0;
		if (row>= 1) {
			Grid->RowCount++;
		}

		size_t pos = 0;
		string cell;
		while ((pos = line.find(',')) != string::npos) {
			cell = line.substr(0, pos);
			Grid->Cells[col][row] = cell.c_str();
			line.erase(0, pos + 1);
			col++;
		}
		// Last column
		Grid->Cells[col][row] = line.c_str();

		row++;
	}
	file.close();
}
//---------------------------------------------------------------------------

void SaveIdToFile(const String &FileName, int id) {
	ofstream file(FileName.c_str());
	if (file.is_open()) {
		file << id;
		file.close();
	}
}
//---------------------------------------------------------------------------

void LoadIdFromFile(const String &FileName, int &id) {
	ifstream file(FileName.c_str());
    if (file.is_open()) {
		file >> id;
		file.close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	SaveGridToFile(InventGrid, "C:\\Users\\w.i\\Desktop\\Projects\\Project\\data.txt.txt");
	SaveGridToFile(TransGrid, "C:\\Users\\w.i\\Desktop\\Projects\\Project\\data2.txt.txt");
	SaveIdToFile("C:\\Users\\w.i\\Desktop\\Projects\\Project\\id.txt.txt", id);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	LoadGridFromFile(InventGrid, "C:\\Users\\w.i\\Desktop\\Projects\\Project\\data.txt.txt");
	LoadGridFromFile(TransGrid, "C:\\Users\\w.i\\Desktop\\Projects\\Project\\data2.txt.txt");
	LoadIdFromFile("C:\\Users\\w.i\\Desktop\\Projects\\Project\\id.txt.txt", id);
}
//---------------------------------------------------------------------------

