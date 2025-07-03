#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include "json.h"
using json = Json::Value;
using namespace std;

#define PI 3.14159265358979323846

class Component {
protected:
	int Thickness;
	wxColour Color;
	wxPoint startPos;
	wxString componentType;
	double scale;
	double height;
	double width;
	bool isShowFrame;
	int index;
public:
	Component()
		:Thickness(1), Color(*wxBLACK) {}
	virtual ~Component(){}


	wxPoint GetStart() const { return startPos; }
	double GetScale() const { return scale; }
	double GetHeight() const { return height; }
	double GetWidth() const { return width; }
	void  SetShowFrame(bool isShow)  { isShowFrame = isShow; }
	bool GetisShowFrame() const { return isShowFrame; }
	void SetPos(wxPoint Pos) { startPos.x = Pos.x; startPos.y = Pos.y; }
	void SetScale(double newscale) { scale = newscale; }
	void SetIndex(int n) { index = n; }
	int GetIndex() const { return index; }

	virtual void drawSelf(wxGraphicsContext* gc) const = 0;

	virtual json toJson() const;
};

class Power_10v : public Component {

public:
	Power_10v(const wxPoint& start,const int index)
		: Component() {
		this->startPos = start;
		this->scale = 1.0;
		this->isShowFrame = false;
		this->width = 30;
		this->height = 40;
		this->index = index;
		this->componentType = "Power_10v";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};


class Power_5v : public Component {

public:
	Power_5v(const wxPoint& start, const int index)
		: Component() {
		this->startPos = start;
		this->scale = 1.0;
		this->isShowFrame = false;
		this->width = 30;
		this->height = 40;
		this->index = index;
		this->componentType = "Power_5v";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};


class R : public Component {

public:
	R(const wxPoint& start,const int index)
		: Component() {
		this->startPos = start;
		this->scale = 1.0;
		this->isShowFrame = false;
		this->width = 20;
		this->height = 40;
		this->index = index;
		this->componentType = "R";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};

class AndGate : public Component {

public:
	AndGate(const wxPoint& start, const int index)
		: Component() {
		this->startPos = start;
		this->scale = 0.5;
		this->isShowFrame = false;
		this->width = 100;
		this->height = 130;
		this->index = index;
		this->componentType = "AndGate";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};

class AndNotGate : public Component {

public:
	AndNotGate(const wxPoint& start, const int index)
		: Component() {
		this->startPos = start;
		this->scale = 0.8;
		this->isShowFrame = false;
		this->width = 100;
		this->height = 140;
		this->index = index;
		this->componentType = "AndNotGate";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};

class OrGate : public Component {

public:
	OrGate(const wxPoint& start, const int index)
		: Component() {
		this->startPos = start;
		this->scale = 0.6;
		this->isShowFrame = false;
		this->width = 80;
		this->height = 120;
		this->index = index;
		this->componentType = "OrGate";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};

class OrNotGate : public Component {

public:
	OrNotGate(const wxPoint& start, const int index)
		: Component() {
		this->startPos = start;
		this->scale = 0.6;
		this->isShowFrame = false;
		this->width = 80;
		this->height = 120;
		this->index = index;
		this->componentType = "OrNotGate";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};

class NotGate : public Component {

public:
	NotGate(const wxPoint& start, const int index)
		: Component() {
		this->startPos = start;
		this->scale = 0.5;
		this->isShowFrame = false;
		this->width = 100;
		this->height = 160;
		this->index = index;
		this->componentType = "NotGate";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};

class XorGate : public Component {

public:
	XorGate(const wxPoint& start, const int index)
		: Component() {
		this->startPos = start;
		this->scale = 0.6;
		this->isShowFrame = false;
		this->width = 80;
		this->height = 120;
		this->index = index;
		this->componentType = "XorGate";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};

class R_Variable : public Component {

public:
	R_Variable(const wxPoint& start, const int index)
		: Component() {
		this->startPos = start;
		this->scale = 1.0;
		this->isShowFrame = false;
		this->width = 20;
		this->height = 40;
		this->index = index;
		this->componentType = "R_Variable";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};

class R_Trim : public Component {

public:
	R_Trim(const wxPoint& start, const int index)
		: Component() {
		this->startPos = start;
		this->scale = 1.0;
		this->isShowFrame = false;
		this->width = 20;
		this->height = 40;
		this->index = index;
		this->componentType = "R_Trim";
	}
	virtual void drawSelf(wxGraphicsContext* gc) const override;

	virtual json toJson() const override;
};
