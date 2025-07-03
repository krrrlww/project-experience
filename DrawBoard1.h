#pragma once
#include <wx/wx.h>
#include <wx/dcgraph.h>
#include <wx/dcbuffer.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/graphics.h>
#include "Shape.h"
#include "Dialog.h"

class DrawBoard1 : public wxPanel
{
public:
	wxGraphicsContext* gc;

	std::vector<std::unique_ptr<Shape>> shapes;

	wxPoint mousePos;
	wxPoint currentStart;
	wxPoint currentEnd;

	wxPoint circleCenter;
	wxPoint circlePoint;
	int clickCount;
	int rectangleCount;
	double startAngle;
	double endAngle;
	double radius;
	wxString text;
	double textAngle;
	double scale;

	bool isDrawingLine;//按下鼠标进入画线状态
	bool isDrawing;//点击按钮进入画线状态

	bool isDrawingArc;//点击按钮进入绘制曲线状态
	bool DrawingArc;//按下鼠标进入绘制曲线状态

	bool isAddText;//添加文本
	bool isTextShow;

	bool isAddRectangle;//添加矩形


	void OnPaint(wxPaintEvent& event);
	void drawDot(wxGraphicsContext* gc);
	void DrawCircle(wxGraphicsContext* gc, const wxPoint& center, double radius);
	void OnLeftDown(wxMouseEvent& event);
	void OnLeftUp(wxMouseEvent& event);
	void OnMotion(wxMouseEvent& event);

public:
	DrawBoard1(wxFrame* parent);
	~DrawBoard1();
};