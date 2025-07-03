#pragma once
#include <wx/wx.h>
#include "DrawBoard.h"
#include <fstream>
#include <iomanip>


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	//wxButton* m_btn1 = nullptr;
	//wxTextCtrl* m_txt1 = nullptr;
	//wxListBox* m_list1 = nullptr;
	wxButton* drawLineButton;
	DrawBoard* drawborad;
	wxButton* deleteButton;
	wxButton* TextButton;
	wxButton* SaveButton;
	wxButton* IntoButton;
	wxButton* ClearButton;
	wxButton* ComButton;
	wxButton* ChangeButton;
	wxButton* BigButton;
	wxButton* SmallButton;
	wxString componentName;

	//void OnButtoClicked(wxCommandEvent& evt);
	void OnDrawLineButtonClick(wxCommandEvent& event);
	void DeleteShape(wxCommandEvent& event);
	void AddText(wxCommandEvent& event);
	void FindCom(wxCommandEvent& event);
	void ClearMap(wxCommandEvent& event);
	void SaveMap(wxCommandEvent& event);
	void Big(wxCommandEvent& event);
	void Small(wxCommandEvent& event);
};

