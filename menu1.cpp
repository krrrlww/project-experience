///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "menu1.h"
#include "cMain.h"
#include "cMain1.h"

///////////////////////////////////////////////////////////////////////////

MyFrame2::MyFrame2(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, wxPoint(400, 200), wxSize(1000, 700), style)
{
    this->SetTitle("Start-My Kicad");
    this->SetSizeHints(wxSize(-1, -1), wxDefaultSize);
    SetBackgroundColour(wxColour(240, 255, 255));

    // 加载背景图片
    wxBitmap bmpBackground(wxT("resource/image/icon.bmp"), wxBITMAP_TYPE_ANY);

    wxStaticBitmap* staticBmp = new wxStaticBitmap(this, wxID_ANY, bmpBackground, wxPoint(0, 0), wxDefaultSize, wxSIMPLE_BORDER);

    
   

    m_bpButton2 = new wxBitmapButton(staticBmp, wxID_ANY, wxBitmap(wxT("resource/image/button2.bmp"), wxBITMAP_TYPE_ANY), wxPoint(50,100), wxSize(100, 100), wxBU_AUTODRAW);
   
    m_textCtrl5 = new wxTextCtrl(staticBmp, wxID_ANY, wxT("Allows the user to create custom component symbols as needed."), wxPoint(200, 100), wxSize(200, 100), wxTE_MULTILINE);
   
    m_bpButton3 = new wxBitmapButton(staticBmp, wxID_ANY, wxBitmap(wxT("resource/image/button1.bmp"), wxBITMAP_TYPE_ANY), wxPoint(50, 250), wxSize(100, 100), wxBU_AUTODRAW);
   

    m_textCtrl6 = new wxTextCtrl(staticBmp, wxID_ANY, wxT("It has an extensive symbol library to help designers quickly design circuits."), wxPoint(200, 250), wxSize(200, 100), wxTE_MULTILINE);
   

    
   

    // Connect Events
    m_bpButton2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame2::jump1), NULL, this);
    m_bpButton3->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame2::jump), NULL, this);
}

MyFrame2::~MyFrame2()
{
    // Disconnect Events
    m_bpButton2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame2::jump1), NULL, this);
    m_bpButton3->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame2::jump), NULL, this);

}

void MyFrame2::jump(wxCommandEvent& event) {
    // 创建 cMain 窗口的实例
    cMain* mainFrame = new cMain();

    // 显示窗口
    mainFrame->Show();
}

void MyFrame2::jump1(wxCommandEvent& event) {
    // 创建 cMain1 窗口的实例
    cMain1* mainFrame = new cMain1();

    // 显示窗口
    mainFrame->Show();
}


