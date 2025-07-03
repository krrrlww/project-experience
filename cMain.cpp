#include "cMain.h"
#include "DrawBoard.h"
#include <wx/menu.h>

cMain::cMain() : wxFrame(nullptr,wxID_ANY,"原理图编辑器",wxPoint(400,200),wxSize(1000,700))
{
	SetBackgroundColour(wxColour(240, 255, 255));

	wxInitAllImageHandlers();
	wxBitmap bitmapForDrawLine;
	bool ifok = bitmapForDrawLine.LoadFile("resource/image/drawLine.png", wxBITMAP_TYPE_PNG);
	wxImage imageForDrawLine = bitmapForDrawLine.ConvertToImage();
	imageForDrawLine = imageForDrawLine.Scale(40, 40, wxIMAGE_QUALITY_HIGH);
	bitmapForDrawLine = wxBitmap(imageForDrawLine);

	drawLineButton = new wxBitmapButton(this, wxID_ANY, bitmapForDrawLine, wxDefaultPosition, wxDefaultSize);
	drawLineButton->Bind(wxEVT_BUTTON, &cMain::OnDrawLineButtonClick, this);
	drawLineButton->SetBackgroundColour(wxColour(255, 255, 255));
	drawLineButton->SetToolTip("Draw line");

	//创建撤回按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForDelete;
	bool ifok1 = bitmapForDelete.LoadFile("resource/image/back.png", wxBITMAP_TYPE_PNG);
	wxImage imageForDelete = bitmapForDelete.ConvertToImage();
	imageForDelete = imageForDelete.Scale(40, 40, wxIMAGE_QUALITY_HIGH);
	bitmapForDelete = wxBitmap(imageForDelete);

	deleteButton = new wxBitmapButton(this, wxID_ANY, bitmapForDelete, wxDefaultPosition, wxDefaultSize);
	deleteButton->Bind(wxEVT_BUTTON, &cMain::DeleteShape, this);
	deleteButton->SetBackgroundColour(wxColour(255, 255, 255));
	deleteButton->SetToolTip("delete");

	//创建添加文本按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForText;
	bool ifok4 = bitmapForText.LoadFile("resource/image/text.png", wxBITMAP_TYPE_PNG);
	wxImage imageForText = bitmapForText.ConvertToImage();
	imageForText = imageForText.Scale(40, 40, wxIMAGE_QUALITY_HIGH);
	bitmapForText = wxBitmap(imageForText);

	TextButton = new wxBitmapButton(this, wxID_ANY, bitmapForText, wxDefaultPosition, wxDefaultSize);
	TextButton->Bind(wxEVT_BUTTON, &cMain::AddText, this);
	TextButton->SetBackgroundColour(wxColour(255, 255, 255));
	TextButton->SetToolTip("add text");


	//创建元件库按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForCom;
	bool ifok9 = bitmapForCom.LoadFile("resource/image/cangku.png", wxBITMAP_TYPE_PNG);
	wxImage imageForCom = bitmapForCom.ConvertToImage();
	imageForCom = imageForCom.Scale(40, 40, wxIMAGE_QUALITY_HIGH);
	bitmapForCom = wxBitmap(imageForCom);

	ComButton = new wxBitmapButton(this, wxID_ANY, bitmapForCom, wxPoint(10, 262), wxDefaultSize);
	ComButton->Bind(wxEVT_BUTTON, &cMain::FindCom, this);
	ComButton->SetBackgroundColour(wxColour(255, 255, 255));
	ComButton->SetToolTip("Find Components");

	wxBoxSizer* controlboard = new wxBoxSizer(wxVERTICAL);
	controlboard->Add(drawLineButton, 0, wxALL | wxEXPAND, 3);
	controlboard->Add(deleteButton, 0, wxALL | wxEXPAND, 3);
	controlboard->Add(TextButton, 0, wxALL | wxEXPAND, 3);
	controlboard->Add(ComButton, 0, wxALL | wxEXPAND, 3);

	//创建保存按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForSave;
	bool ifok6 = bitmapForSave.LoadFile("resource/image/save1.png", wxBITMAP_TYPE_PNG);
	wxImage imageForSave = bitmapForSave.ConvertToImage();
	imageForSave = imageForSave.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
	bitmapForSave = wxBitmap(imageForSave);

	SaveButton = new wxBitmapButton(this, wxID_ANY, bitmapForSave, wxDefaultPosition, wxSize(30,10));
	SaveButton->SetBackgroundColour(wxColour(255, 255, 255));
    SaveButton->Bind(wxEVT_BUTTON, &cMain::SaveMap, this);
	SaveButton->SetToolTip("保存原理图");

	//创建导入按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForInto;
	bool ifok7 = bitmapForInto.LoadFile("resource/image/daoru.png", wxBITMAP_TYPE_PNG);
	wxImage imageForInto = bitmapForInto.ConvertToImage();
	imageForInto = imageForInto.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
	bitmapForInto = wxBitmap(imageForInto);

	IntoButton = new wxBitmapButton(this, wxID_ANY, bitmapForInto, wxDefaultPosition, wxSize(30, 10));
	IntoButton->SetBackgroundColour(wxColour(255, 255, 255));
	IntoButton->SetToolTip("导入原理图");
	
	//创建清除按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForClear;
	bool ifok8 = bitmapForClear.LoadFile("resource/image/clear.png", wxBITMAP_TYPE_PNG);
	wxImage imageForClear = bitmapForClear.ConvertToImage();
	imageForClear = imageForClear.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
	bitmapForClear = wxBitmap(imageForClear);

	ClearButton = new wxBitmapButton(this, wxID_ANY, bitmapForClear, wxDefaultPosition, wxSize(30, 10));
	ClearButton->SetBackgroundColour(wxColour(255, 255, 255));
	ClearButton->Bind(wxEVT_BUTTON, &cMain::ClearMap, this);
	ClearButton->SetToolTip("删除原理图");

	//创建切换按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForChange;
	bool ifok10 = bitmapForChange.LoadFile("resource/image/电子元器件.png", wxBITMAP_TYPE_PNG);
	wxImage imageForChange = bitmapForChange.ConvertToImage();
	imageForChange = imageForChange.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
	bitmapForChange = wxBitmap(imageForChange);

	ChangeButton = new wxBitmapButton(this, wxID_ANY, bitmapForChange, wxDefaultPosition, wxSize(30, 10));
	ChangeButton->SetBackgroundColour(wxColour(255, 255, 255));
	ChangeButton->Bind(wxEVT_BUTTON, &cMain::ClearMap, this);
	ChangeButton->SetToolTip("切换到元件编辑器");

	//创建放大按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForBig;
	bool ifok11 = bitmapForBig.LoadFile("resource/image/zoom-out.png", wxBITMAP_TYPE_PNG);
	wxImage imageForBig = bitmapForBig.ConvertToImage();
	imageForBig = imageForBig.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
	bitmapForBig = wxBitmap(imageForBig);

	BigButton = new wxBitmapButton(this, wxID_ANY, bitmapForBig, wxDefaultPosition, wxSize(30, 10));
	BigButton->SetBackgroundColour(wxColour(255, 255, 255));
	BigButton->Bind(wxEVT_BUTTON, &cMain::Big, this);
	BigButton->SetToolTip("放大");

	//创建缩小按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForSmall;
	bool ifok12 = bitmapForSmall.LoadFile("resource/image/zoom-in.png", wxBITMAP_TYPE_PNG);
	wxImage imageForSmall = bitmapForSmall.ConvertToImage();
	imageForSmall = imageForSmall.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
	bitmapForSmall = wxBitmap(imageForSmall);

	SmallButton = new wxBitmapButton(this, wxID_ANY, bitmapForSmall, wxDefaultPosition, wxSize(30, 10));
	SmallButton->SetBackgroundColour(wxColour(255, 255, 255));
	SmallButton->Bind(wxEVT_BUTTON, &cMain::Small, this);
	SmallButton->SetToolTip("缩小");

	wxBoxSizer* menuboard = new wxBoxSizer(wxHORIZONTAL);
	menuboard->Add(SaveButton, 0, wxALL | wxEXPAND, 0);
	menuboard->Add(IntoButton, 0, wxALL | wxEXPAND, 0);
	menuboard->Add(ClearButton, 0, wxALL | wxEXPAND, 0);
	menuboard->Add(BigButton, 0, wxALL | wxEXPAND, 0);
	menuboard->Add(SmallButton, 0, wxALL | wxEXPAND, 0);
	menuboard->Add(ChangeButton, 0, wxALL | wxEXPAND, 0);

	drawborad = new DrawBoard(this);

	wxBoxSizer* main= new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(controlboard, 0, wxALL | wxEXPAND, 0);
	mainSizer->Add(drawborad, 1, wxALL | wxEXPAND, 5);

	main->Add(menuboard, 1, wxALL | wxEXPAND, 0);
	main->Add(mainSizer, 18, wxALL | wxEXPAND, 5);

	SetSizer(main);
}

cMain::~cMain() {
	
}
/*
void cMain::OnButtoClicked(wxCommandEvent& evt) {
	if (!drawborad->shapes.empty()) {
	drawborad->shapes.pop_back();
	}
	drawborad->Refresh();
}
*/
void cMain::OnDrawLineButtonClick(wxCommandEvent& event) {
	drawborad->isDrawing = true;
}

void cMain::DeleteShape(wxCommandEvent& event) {
	
	if (drawborad->isChooseComponent == true) {
		drawborad->isChooseComponent = false;
		drawborad->componentMove = false;
		drawborad->moveCount = 0;
		if (drawborad->currentIndex == (drawborad->num - 1)) {
			if (!drawborad->Components.empty()) {
				drawborad->Components.pop_back();
				drawborad->num--;
			}
		}
		else {
			drawborad->Components.erase(drawborad->Components.begin() + drawborad->currentIndex);
			drawborad->num--; 
			for (int i = drawborad->currentIndex; i < drawborad->num; ++i) {
				Component& component = *drawborad->Components[i];
				component.SetIndex(component.GetIndex() - 1);
			}
		}
		}
	if (drawborad->isChooseLine == true) {
		drawborad->isChooseLine = false;
		drawborad->lineMove = false;
		drawborad->moveCount = 0;
		if (drawborad->currentIndex == (drawborad->lineNum - 1)) {
			if (!drawborad->lines.empty()) {
				drawborad->lines.pop_back();
				drawborad->lineNum--;
			}
		}
		else {
			drawborad->lines.erase(drawborad->lines.begin() + drawborad->currentIndex);
			drawborad->lineNum--;
			for (int i = drawborad->currentIndex; i < drawborad->lineNum; ++i) {
				Line& line = *drawborad->lines[i];
				line.SetIndex(line.GetIndex() - 1);
			}
		}
	}
	
	drawborad->Refresh();
}


void cMain::AddText(wxCommandEvent& event) {
	drawborad->isAddText = true;
	drawborad->Refresh();
}

void cMain::FindCom(wxCommandEvent& event) {
	drawborad->isFindCom = true;
	drawborad->Refresh();
}

void cMain::ClearMap(wxCommandEvent& event) {
	drawborad->lines.clear();
	drawborad->shapes.clear();
	drawborad->Components.clear();
	drawborad->Refresh();
}

void cMain::SaveMap(wxCommandEvent& event) {
	wxString filename = wxFileSelector("Save File", wxEmptyString, wxEmptyString, "json", "JSON files (*.json)|*.json", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (!filename.empty()) {
		json jsonData;

		for (const unique_ptr<Component>& componentPtr : drawborad->Components) {
			Component& component = *componentPtr;
			jsonData["components"].append(component.toJson());
		}
		for (const unique_ptr<Line>& componentPtr : drawborad->lines) {
			Line& line = *componentPtr;
			jsonData["lines"].append(line.toJson());
		}
		for (const unique_ptr<Shape>& componentPtr : drawborad->shapes) {
			Shape& text = *componentPtr;
			jsonData["texts"].append(text.toJson());
		}
		ofstream ofs(filename.ToStdString());
		ofs << setw(4) << jsonData;
	}
	drawborad->Refresh();
}

void cMain::Big(wxCommandEvent& event) {
	if (drawborad->scale < 2) {
		drawborad->scale = drawborad->scale + 0.2;
	}
	drawborad->Refresh();
}

void cMain::Small(wxCommandEvent& event) {
	if (drawborad->scale > 1) {
		drawborad->scale = drawborad->scale - 0.2;
	}
	drawborad->Refresh();
}


