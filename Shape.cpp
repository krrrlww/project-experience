#include "Shape.h"



void Line::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(GetPen());
    gc->StrokeLine(GetStart().x, GetStart().y, GetEnd().x, GetEnd().y);
}

void Rectangle1::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(GetPen());
    gc->StrokeLine(GetStart().x, GetStart().y, GetEnd().x, GetStart().y);
    gc->StrokeLine(GetStart().x, GetEnd().y, GetEnd().x, GetEnd().y);
    gc->StrokeLine(GetStart().x, GetStart().y, GetStart().x, GetEnd().y);
    gc->StrokeLine(GetEnd().x, GetStart().y, GetEnd().x, GetEnd().y);
}


void TextShape::drawSelf(wxGraphicsContext* gc) const  {
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxColour color(0, 0, 255); 
    gc->SetFont(font, color);
    // 计算旋转后的文本w位置
    double textX = cos(wxDegToRad(GetAngle())) * GetStart().x + sin(wxDegToRad(GetAngle())) * GetStart().y;
    double textY = -sin(wxDegToRad(GetAngle())) * GetStart().x + cos(wxDegToRad(GetAngle())) * GetStart().y;
    gc->PushState();  // 保存当前状态
    // 旋转坐标系
    gc->Rotate(wxDegToRad(GetAngle()));
    // 绘制垂直文本
    gc->DrawText(GetText(), textX, textY);
    gc->PopState();  // 恢复到之前的状态
}

void MyArc::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    wxGraphicsPath path = gc->CreatePath();
    path.MoveToPoint(GetStart().x, GetStart().y);
    path.AddArc(GetCircleCenter().x, GetCircleCenter().y, GetRadius(), GetStartAngle(), GetEndAngle(), true);
    gc->StrokePath(path);
}

json Line::toJson() const {
    json jsonShape;

    jsonShape["Type"] = shapeType.ToStdString();

    json startPosArray;
    startPosArray.append(startPos.x);
    startPosArray.append(startPos.y);
    jsonShape["startPos"] = startPosArray;

    json endPosArray;
    endPosArray.append(endPos.x);
    endPosArray.append(endPos.y);
    jsonShape["endPos"] = endPosArray;

    jsonShape["thickness"] = 2;


    return jsonShape;
}

json Rectangle1::toJson() const {
    json jsonShape;

    jsonShape["Type"] = shapeType.ToStdString();

    json startPosArray;
    startPosArray.append(startPos.x);
    startPosArray.append(startPos.y);
    jsonShape["startPos"] = startPosArray;

    json endPosArray;
    endPosArray.append(endPos.x);
    endPosArray.append(endPos.y);
    jsonShape["endPos"] = endPosArray;

    jsonShape["thickness"] = 2;


    return jsonShape;
}

json MyArc::toJson() const {
    json jsonShape;

    jsonShape["Type"] = shapeType.ToStdString();

    json startPosArray;
    startPosArray.append(startPos.x);
    startPosArray.append(startPos.y);
    jsonShape["startPos"] = startPosArray;

    jsonShape["startAngle"] = startAngle;
    jsonShape["endAngle"] = endAngle;
    jsonShape["radius"] = radius;

    json circleCenterArray;
    circleCenterArray.append(circleCenter.x);
    circleCenterArray.append(circleCenter.y);
    jsonShape["circleCenter"] = circleCenterArray;

    jsonShape["thickness"] = 2;


    return jsonShape;
}

json TextShape::toJson() const {
    json jsonShape;

    jsonShape["Type"] = shapeType.ToStdString();

    json startPosArray;
    startPosArray.append(startPos.x);
    startPosArray.append(startPos.y);
    jsonShape["startPos"] = startPosArray;

    jsonShape["Text"]=Text.ToStdString();
    jsonShape["TextAngle"] = angle;

    return jsonShape;
}