#pragma once
#include <wx/wx.h>
#include "DrawBoard1.h"
#include <fstream>
#include <iomanip>
#include "json.h"

class cMain1 : public wxFrame
{
public:
	cMain1();
	~cMain1();

public:
	wxButton* drawLineButton;
	wxButton* deleteButton;
	wxButton* TextButton;
	wxButton* ArcButton;
	wxButton* SaveButton;
	wxButton* BigButton;
	wxButton* SmallButton;
	wxButton* RecButton;
	wxButton* changeButton;
	DrawBoard1* drawborad;

	void OnDrawLineButtonClick(wxCommandEvent& event);
	void DeleteShape(wxCommandEvent& event);
	void DrawArc(wxCommandEvent& event);
	void AddText(wxCommandEvent& event);
	void Big(wxCommandEvent& event);
	void Small(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void AddRectangle(wxCommandEvent& event);
	void Change(wxCommandEvent& event);
};