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
	int moveCount;//���ڻ�ȡ��ѡ��Ԫ������״̬
	size_t currentIndex;//���ڻ�ȡ������Ԫ�ص��±�
	int num;//���ڴ���Ԫ����ʱ�����±�
	int lineNum;//���ڴ�������ʱ�����±�
	double newScale;//��ǰͼ�����ű���
	wxString componentName;//���ڱ����Ԫ�����л�ȡ��Ԫ������
	int direction;//1Ϊy����0Ϊx����

	bool isDrawingLine;//���������뻭��״̬
	bool isDrawing;//�����ť���뻭��״̬
	bool isDrawingComponent;//�����ť��ӵ�Դ
	bool isAddText;//����ı�
	bool isTextShow;
	bool componentMove;//Ԫ�����ƶ�
	bool isChooseComponent;//Ԫ����ѡ��
	bool isChooseLine;//����ѡ��
	bool isFindCom;//���°�ť����Ԫ����bool isFindCom;
	bool isComponentShow;//�Ƿ���ʾԪ����
	bool lineMove;//���������ƶ�

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
