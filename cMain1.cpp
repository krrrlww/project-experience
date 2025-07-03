#include "cMain1.h"
#include "cMain.h"

cMain1::cMain1() : wxFrame(nullptr, wxID_ANY, "符号编辑器", wxPoint(400, 200), wxSize(1000, 700))
{
	SetBackgroundColour(wxColour(240, 255, 255));
	//创建绘线按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForDrawLine;
	bool ifok = bitmapForDrawLine.LoadFile("resource/image/直线1.png", wxBITMAP_TYPE_PNG);
	wxImage imageForDrawLine = bitmapForDrawLine.ConvertToImage();
	imageForDrawLine = imageForDrawLine.Scale(30, 30, wxIMAGE_QUALITY_HIGH);
	bitmapForDrawLine = wxBitmap(imageForDrawLine);

	drawLineButton = new wxBitmapButton(this, wxID_ANY, bitmapForDrawLine, wxDefaultPosition, wxDefaultSize);
	drawLineButton->Bind(wxEVT_BUTTON, &cMain1::OnDrawLineButtonClick, this);
	drawLineButton->SetBackgroundColour(wxColour(255, 255, 255));
	drawLineButton->SetToolTip("Draw line");

	//创建撤回按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForDelete;
	bool ifok1 = bitmapForDelete.LoadFile("resource/image/撤销.png", wxBITMAP_TYPE_PNG);
	wxImage imageForDelete = bitmapForDelete.ConvertToImage();
	imageForDelete = imageForDelete.Scale(30, 30, wxIMAGE_QUALITY_HIGH);
	bitmapForDelete = wxBitmap(imageForDelete);

	deleteButton = new wxBitmapButton(this, wxID_ANY, bitmapForDelete, wxDefaultPosition, wxDefaultSize);
	deleteButton->Bind(wxEVT_BUTTON, &cMain1::DeleteShape, this);
	deleteButton->SetBackgroundColour(wxColour(255, 255, 255));
	deleteButton->SetToolTip("delete");

	//创建添加文本按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForText;
	bool ifok4 = bitmapForText.LoadFile("resource/image/文本编辑.png", wxBITMAP_TYPE_PNG);
	wxImage imageForText = bitmapForText.ConvertToImage();
	imageForText = imageForText.Scale(30, 30, wxIMAGE_QUALITY_HIGH);
	bitmapForText = wxBitmap(imageForText);

	TextButton = new wxBitmapButton(this, wxID_ANY, bitmapForText, wxDefaultPosition, wxDefaultSize);
	TextButton->Bind(wxEVT_BUTTON, &cMain1::AddText, this);
	TextButton->SetBackgroundColour(wxColour(255, 255, 255));
	TextButton->SetToolTip("add text");

	//创建绘制曲线按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForArc;
	bool ifok5 = bitmapForArc.LoadFile("resource/image/弧线图.png", wxBITMAP_TYPE_PNG);
	wxImage imageForArc = bitmapForArc.ConvertToImage();
	imageForArc = imageForArc.Scale(30, 30, wxIMAGE_QUALITY_HIGH);
	bitmapForArc = wxBitmap(imageForArc);

	ArcButton = new wxBitmapButton(this, wxID_ANY, bitmapForArc, wxDefaultPosition, wxDefaultSize);
	ArcButton->Bind(wxEVT_BUTTON, &cMain1::DrawArc, this);
	ArcButton->SetBackgroundColour(wxColour(255, 255, 255));
	ArcButton->SetToolTip("Draw Arc");

	//创建保存按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForSave;
	bool ifok6 = bitmapForSave.LoadFile("resource/image/保存1.png", wxBITMAP_TYPE_PNG);
	wxImage imageForSave = bitmapForSave.ConvertToImage();
	imageForSave = imageForSave.Scale(30, 30, wxIMAGE_QUALITY_HIGH);
	bitmapForSave = wxBitmap(imageForSave);

	SaveButton = new wxBitmapButton(this, wxID_ANY, bitmapForSave, wxDefaultPosition, wxDefaultSize);
	SaveButton->Bind(wxEVT_BUTTON, &cMain1::OnSave, this);
	SaveButton->SetBackgroundColour(wxColour(255, 255, 255));
	SaveButton->SetToolTip("Save");

	//创建矩形按钮
	wxInitAllImageHandlers();
	wxBitmap bitmap1;
	bool ifok7 = bitmap1.LoadFile("resource/image/矩形.png", wxBITMAP_TYPE_PNG);
	wxImage image1 = bitmap1.ConvertToImage();
	image1 = image1.Scale(30, 30, wxIMAGE_QUALITY_HIGH);
	bitmap1 = wxBitmap(image1);

	RecButton = new wxBitmapButton(this, wxID_ANY, bitmap1, wxDefaultPosition, wxDefaultSize);
	RecButton->Bind(wxEVT_BUTTON, &cMain1::AddRectangle, this);
	RecButton->SetBackgroundColour(wxColour(255, 255, 255));
	RecButton->SetToolTip("绘制矩形");

	//创建放大按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForBig;
	bool ifok11 = bitmapForBig.LoadFile("resource/image/zoom-out.png", wxBITMAP_TYPE_PNG);
	wxImage imageForBig = bitmapForBig.ConvertToImage();
	imageForBig = imageForBig.Scale(30, 30, wxIMAGE_QUALITY_HIGH);
	bitmapForBig = wxBitmap(imageForBig);

	BigButton = new wxBitmapButton(this, wxID_ANY, bitmapForBig, wxDefaultPosition, wxDefaultSize);
	BigButton->SetBackgroundColour(wxColour(255, 255, 255));
	BigButton->Bind(wxEVT_BUTTON, &cMain1::Big, this);
	BigButton->SetToolTip("放大");

	//创建缩小按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForSmall;
	bool ifok12 = bitmapForSmall.LoadFile("resource/image/zoom-in.png", wxBITMAP_TYPE_PNG);
	wxImage imageForSmall = bitmapForSmall.ConvertToImage();
	imageForSmall = imageForSmall.Scale(30, 30, wxIMAGE_QUALITY_HIGH);
	bitmapForSmall = wxBitmap(imageForSmall);

	SmallButton = new wxBitmapButton(this, wxID_ANY, bitmapForSmall, wxDefaultPosition, wxDefaultSize);
	SmallButton->SetBackgroundColour(wxColour(255, 255, 255));
	SmallButton->Bind(wxEVT_BUTTON, &cMain1::Small, this);
	SmallButton->SetToolTip("缩小");

	//创建切换按钮
	wxInitAllImageHandlers();
	wxBitmap bitmapForChange;
	bool ifok13 = bitmapForChange.LoadFile("resource/image/button1.png", wxBITMAP_TYPE_PNG);
	wxImage imageForChange = bitmapForChange.ConvertToImage();
	imageForChange = imageForChange.Scale(30, 30, wxIMAGE_QUALITY_HIGH);
	bitmapForChange = wxBitmap(imageForChange);

	changeButton = new wxBitmapButton(this, wxID_ANY, bitmapForChange, wxDefaultPosition, wxDefaultSize);
	changeButton->SetBackgroundColour(wxColour(255, 255, 255));
	changeButton->Bind(wxEVT_BUTTON, &cMain1::Change, this);
	changeButton->SetToolTip("切换到原理图编辑器");

	wxBoxSizer* controlboard = new wxBoxSizer(wxVERTICAL);
	controlboard->Add(drawLineButton, 0, wxALL | wxEXPAND, 5);
	controlboard->Add(deleteButton, 0, wxALL | wxEXPAND, 5);
	controlboard->Add(TextButton, 0, wxALL | wxEXPAND, 5);
	controlboard->Add(ArcButton, 0, wxALL | wxEXPAND, 5);
	controlboard->Add(RecButton, 0, wxALL | wxEXPAND, 5);
	controlboard->Add(SaveButton, 0, wxALL | wxEXPAND, 5);
	controlboard->Add(BigButton, 0, wxALL | wxEXPAND, 5);
	controlboard->Add(SmallButton, 0, wxALL | wxEXPAND, 5);
	controlboard->Add(changeButton, 0, wxALL | wxEXPAND, 5);

	drawborad = new DrawBoard1(this);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(drawborad, 1, wxALL | wxEXPAND, 10);
	mainSizer->Add(controlboard, 0, wxALL | wxEXPAND, 5);

	SetSizer(mainSizer);

}

cMain1::~cMain1() {

}

void cMain1::OnDrawLineButtonClick(wxCommandEvent& event) {
	drawborad->isDrawing = true;
}

void cMain1::DeleteShape(wxCommandEvent& event) {
	if (!drawborad->shapes.empty()) {
		drawborad->shapes.pop_back();
	}
	drawborad->Refresh();
}

void cMain1::DrawArc(wxCommandEvent& event) {
	drawborad->isDrawingArc = true;
}


void cMain1::OnSave(wxCommandEvent& event) {
	wxString filename = wxFileSelector("Save File", wxEmptyString, wxEmptyString, "json", "JSON files (*.json)|*.json", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (!filename.empty()) {
		json jsonData;

		for (const unique_ptr<Shape>& shapePtr : drawborad->shapes) {
			Shape& shape = *shapePtr;
			jsonData["shapes"].append(shape.toJson());
		}
		ofstream ofs(filename.ToStdString());
		ofs << setw(4) << jsonData; 
	}
	if (!filename.empty()) {
		drawborad->shapes.clear();
	}
	drawborad->Refresh();
}

void cMain1::AddText(wxCommandEvent& event) {
	drawborad->isAddText = true;
	drawborad->Refresh();
}

void cMain1::Big(wxCommandEvent& event) {
	if (drawborad->scale < 2) {
		drawborad->scale = drawborad->scale + 0.2;
	}
	drawborad->Refresh();
}

void cMain1::Small(wxCommandEvent& event) {
	if (drawborad->scale > 1) {
		drawborad->scale = drawborad->scale - 0.2;
	}
	drawborad->Refresh();
}

void cMain1::AddRectangle(wxCommandEvent& event) {
	drawborad->isAddRectangle = true;
	drawborad->Refresh();
}

void cMain1::Change(wxCommandEvent& event) {
	// 创建 cMain 窗口的实例
	cMain* mainFrame = new cMain();

	// 显示窗口
	mainFrame->Show();
}
