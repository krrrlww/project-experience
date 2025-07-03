#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include "json.h"
#include <cmath> 

using json = Json::Value;
using namespace std;

class Shape {
protected:
    wxPen pen;
    wxPoint startPos;
    wxPoint endPos;
    int Thickness;
    wxColour Color;
    wxColour brushColor;
    wxString shapeType;
    wxString Text;
    double startAngle=0;//画弧线的开始角度
    double endAngle=0;//画弧线的结束角度
    double radius=0;//画弧线时的半径
    wxPoint circleCenter;//画弧线时的圆心坐标
    double angle=0;//文本旋转角度
    int index;//在容器中的序号
public:
    Shape()
        : Thickness(1) {}
    virtual ~Shape() {}

    wxPen GetPen() const { return pen; }
    wxPoint GetStart() const { return startPos; }
    wxPoint GetEnd() const { return endPos; }
    int GetThickness() const { return Thickness; }
    wxColour GetColor() const { return Color; }
    wxColour GetBrushColor() const { return brushColor; }
    wxString GetType() const { return shapeType; }
    wxString GetText() const { return Text; }
    double GetStartAngle() const { return startAngle; }
    double GetEndAngle() const { return endAngle; }
    double GetRadius() const { return  radius; }
    wxPoint GetCircleCenter() const { return circleCenter; }
    double GetAngle() const { return angle; }
    int GetIndex() const { return index; }

 
    void setType(wxString shape) { this->shapeType = shape; }
    void setThickness(int thick) { this->Thickness = thick; }
    void setPen(wxPen newPen) { this->pen = newPen; }
    void setBrushColor(wxColor color) { this->brushColor = color; }
    void setStart(wxPoint start) { this->startPos = start;}
    void setEnd(wxPoint end) { this->endPos = end; }
    void setCircleCenter(wxPoint CircleCenter) { this->circleCenter = CircleCenter; }
    void setStartAngle(double angle) { this->startAngle = angle; }
    void setEndAngle(double angle) { this->startAngle = angle; }
    void setRadius(double radius) { this->radius = radius; }
    void setText(wxString text) { this->Text = text; }
    void SetIndex(int n) { index = n; }

    virtual json toJson() const=0;
    
    
    virtual void drawSelf(wxGraphicsContext* gc) const = 0;
};

class Line : public Shape {

public:
    Line(const wxPoint& start, const wxPoint& end, const int index)
        : Shape() {
        this->startPos = start; this->endPos = end;
        wxPen newPen(wxColour(0, 0, 0), 2);
        this->pen = newPen;
        shapeType = "Line";
        this->index = index;
    }
    Line()
        :Shape() {
        shapeType = "Line";
    }

   
    virtual json toJson() const override;
    
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class TextShape : public Shape {

public:
    TextShape(const wxPoint& start, const wxString& text,const double textAngle)
        : Shape() {
        this->startPos = start;
        this->Text = text;
        this->angle = textAngle;
        shapeType = "Text";
    }
    TextShape()
        :Shape() {
        shapeType = "Text";
    }
    virtual json toJson() const override;
    
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class MyArc : public Shape {

public:
    MyArc(const double startAngle, const double endAngle, const double radius,const wxPoint& circleCenter, const wxPoint& start)
        : Shape(){
        this->startAngle = startAngle;
        this->endAngle = endAngle;
        this->radius = radius;
        this->circleCenter = circleCenter;
        this->startPos = start;
        shapeType = "Arc";
    }
    MyArc()
        :Shape() {
        shapeType = "Arc";
    }
    virtual json toJson() const override;
    
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class Rectangle1 : public Shape {

public:
    Rectangle1(const wxPoint& start, const wxPoint& end)
        : Shape() {
        this->startPos = start; this->endPos = end;
        wxPen newPen(wxColour(0, 0, 0), 2);
        this->pen = newPen;
        shapeType = "矩形";
    }
    Rectangle1()
        :Shape() {
        shapeType = "矩形";
    }


    virtual json toJson() const override;

    virtual void drawSelf(wxGraphicsContext* gc) const override;
};


