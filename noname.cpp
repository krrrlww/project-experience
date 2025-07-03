///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, const wxString& title) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
	SetBackgroundColour(wxColour(240, 255, 255));
	this->SetTitle("元件库");
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetSize(100, 100, 470, 300);

	itemText = "";

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_treeCtrl2 = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(170, 200), wxTR_DEFAULT_STYLE);
	bSizer1->Add(m_treeCtrl2, 0, wxALL, 5);

	okButton = new wxButton(this, wxID_OK);
	cancelButton = new wxButton(this, wxID_CANCEL);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(okButton, 0, wxALL, 7);
	sizer->Add(cancelButton, 0, wxALL, 7);

	drawborad = new DrawBoard2(this);

	bSizer1->Add(sizer, 0, wxALL, 5);

	mainSizer->Add(bSizer1, 0, wxALL | wxEXPAND, 5);
	mainSizer->Add(drawborad, 1, wxALL | wxEXPAND, 5);

	this->SetSizer(mainSizer);
	this->Layout();

	this->Centre(wxBOTH);

	// 添加根节点
	wxTreeItemId root = m_treeCtrl2->AddRoot("选择元件");

	// 添加子节点
	wxTreeItemId child1 = m_treeCtrl2->AppendItem(root, "gate");
	wxTreeItemId child2 = m_treeCtrl2->AppendItem(root, "power");
	wxTreeItemId child3 = m_treeCtrl2->AppendItem(root, "resistance");
	wxTreeItemId child4 = m_treeCtrl2->AppendItem(root, "user-defined");

	// 为子节点添加孙子节点
	wxTreeItemId subChild1 = m_treeCtrl2->AppendItem(child1, "与门");
	wxTreeItemId subChild2 = m_treeCtrl2->AppendItem(child1, "或门");
	wxTreeItemId subChild3 = m_treeCtrl2->AppendItem(child1, "非门");
	wxTreeItemId subChild4 = m_treeCtrl2->AppendItem(child1, "与非门");
	wxTreeItemId subChild5 = m_treeCtrl2->AppendItem(child1, "或非门");
	wxTreeItemId subChild6 = m_treeCtrl2->AppendItem(child1, "异或门");
	wxTreeItemId subChild7 = m_treeCtrl2->AppendItem(child2, "+10v");
	wxTreeItemId subChild8 = m_treeCtrl2->AppendItem(child2, "+5v");
	wxTreeItemId subChild10 = m_treeCtrl2->AppendItem(child3, "R");
	wxTreeItemId subChild11 = m_treeCtrl2->AppendItem(child3, "R_Variable");
	wxTreeItemId subChild12 = m_treeCtrl2->AppendItem(child4, "R_Trim");
	//绑定分支激活事件
	m_treeCtrl2->Bind(wxEVT_TREE_ITEM_ACTIVATED, &MyFrame1::OnItemActivated, this);
	
}

MyFrame1::~MyFrame1()
{
}

void MyFrame1::OnItemActivated(wxTreeEvent& event) {
	wxTreeItemId itemId = event.GetItem();
	itemText=m_treeCtrl2->GetItemText(itemId);
	drawborad->componentName=itemText;
	drawborad->Refresh();
}

void MyFrame1::OnOk(wxCommandEvent& event) {

	EndModal(wxID_OK);
}

void MyFrame1::OnCancel(wxCommandEvent& event) {
	EndModal(wxID_CANCEL);
}