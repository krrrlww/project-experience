#include "Dialog.h"

TextEntryDialog::TextEntryDialog(wxWindow* parent, const wxString& title)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize) {
    textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    okButton = new wxButton(this, wxID_OK);
    cancelButton = new wxButton(this, wxID_CANCEL);
    m_staticText = new wxStaticText(this, wxID_ANY, wxT("Text:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Angle:"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("Color:"), wxDefaultPosition, wxDefaultSize, 0);


    wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
    wxRadioButton* blueRadio = new wxRadioButton(this, wxID_ANY, "À¶É«", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    wxRadioButton* redRadio = new wxRadioButton(this, wxID_ANY, "ºìÉ«");
    wxRadioButton* orangeRadio = new wxRadioButton(this, wxID_ANY, "³ÈÉ«");
    sizer1->Add(blueRadio, 0, wxALL, 5);
    sizer1->Add(redRadio, 0, wxALL, 5);
    sizer1->Add(orangeRadio, 0, wxALL, 5);

    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    sizer2->Add(okButton, 0, wxALL, 5);
    sizer2->Add(cancelButton, 0, wxALL, 5);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_staticText, 0, wxALL, 5);
    sizer->Add(textCtrl, wxSizerFlags().Expand().Border());
    sizer->Add(m_staticText1, 0, wxALL, 5); 
    sizer->Add(textCtrl1, wxSizerFlags().Expand().Border());
    sizer->Add(m_staticText2, 0, wxALL, 5);
    sizer->Add(sizer1, wxSizerFlags().Expand().Border());
    sizer->Add(sizer2, wxSizerFlags().Expand().Border());

    SetSizer(sizer);
    sizer->Fit(this);
}

void TextEntryDialog::OnOk(wxCommandEvent& event) {
    EndModal(wxID_OK);
}

void TextEntryDialog::OnCancel(wxCommandEvent& event) {
    EndModal(wxID_CANCEL);
}
