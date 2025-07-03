#pragma once
#include <wx/wx.h>
#include <wx/dcgraph.h>
#include <wx/dcbuffer.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/graphics.h>
#include "Shape.h"
#include "Dialog.h"
#include "Component.h"
#include <cmath>
#include < wx/cursor.h >
#include "noname.h"

class DrawBoard : public wxPanel
{
public:
	std::vector<std::unique_ptr<Component>> Components;
	std::vector<std::unique_ptr<Line>> lines;
	std::vector<std::unique_ptr<Shape>> shapes;

	wxPoint mousePos;
	wxPoint currentStart;
	wxPoint currentEnd;
	wxPoint oldStart;
	wxPoint oldEnd;
	wxStaticText* st1;
	wxStaticText* st2;
	wxPoint circleCenter;
	wxPoint circlePoint;
	int clickCount;
	double startAngle;
	double endAngle;
	double textAngle;
	double radius;
	wxGraphicsContext* gc;
	wxString text;
	int moveCount;//用于获取被选中元器件的状态
	size_t currentIndex;//用于获取容器中元素的下标
	int num;//用于创建元器件时给定下标
	int lineNum;//用于储存连线时给定下标
	double newScale;//当前图形缩放比例
	wxString componentName;//用于保存从元件库中获取的元件名称
	int direction;//1为y方向，0为x方向

	bool isDrawingLine;//按下鼠标进入画线状态
	bool isDrawing;//点击按钮进入画线状态
	bool isDrawingComponent;//点击按钮添加电源
	bool isAddText;//添加文本
	bool isTextShow;
	bool componentMove;//元器件移动
	bool isChooseComponent;//元器件选中
	bool isChooseLine;//线条选中
	bool isFindCom;//按下按钮进入元件库bool isFindCom;
	bool isComponentShow;//是否显示元器件
	bool lineMove;//控制连线移动

	double scale;

	void OnPaint(wxPaintEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void drawGrid(wxGraphicsContext* gc);
	void OnLeftUp(wxMouseEvent& event);
	void OnMotion(wxMouseEvent& event);
	void DrawCircle(wxGraphicsContext* gc, const wxPoint& center, double radius);
	void OnMouseWheel(wxMouseEvent& event);
	void OnRightDown(wxMouseEvent& event);


public:
	DrawBoard(wxFrame* parent);
	~DrawBoard();


};
