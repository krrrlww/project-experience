#pragma once

#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/radiobut.h>


class TextEntryDialog : public wxDialog {
public:
    TextEntryDialog(wxWindow* parent, const wxString& title);
    wxTextCtrl* textCtrl;
    wxTextCtrl* textCtrl1;
    wxStaticText* m_staticText;
    wxStaticText* m_staticText1;
    wxStaticText* m_staticText2;

private:
    wxButton* okButton;
    wxButton* cancelButton;


    void OnOk(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
};