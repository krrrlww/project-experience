#include "DrawBoard.h"
#include <wx/string.h>

DrawBoard::DrawBoard(wxFrame* parent) : wxPanel(parent) {

    SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &DrawBoard::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &DrawBoard::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &DrawBoard::OnLeftUp, this);
    Bind(wxEVT_MOTION, &DrawBoard::OnMotion, this);
    Bind(wxEVT_MOUSEWHEEL, &DrawBoard::OnMouseWheel, this);
    Bind(wxEVT_RIGHT_DOWN, &DrawBoard::OnRightDown, this);

    st1 = new wxStaticText(this, -1, wxT(""), wxPoint(10, 10));
    st2 = new wxStaticText(this, -1, wxT(""), wxPoint(10, 30));
 

    isDrawing = false;
    isDrawingLine = false;
    isDrawingComponent = false;
    isAddText = false;
    isTextShow = false;
    componentMove = false;
    isChooseComponent = false;
    isComponentShow = false;
    isChooseLine = false;
    lineMove = false;

    //��ʼ�������ߵĲ���
    clickCount = 0; // ��ʼ���������
    circleCenter = wxPoint(0, 0);
    circlePoint = wxPoint(0, 0);

    startAngle=0;
    endAngle=0;
    radius=0;

    gc = nullptr;
    text = "";
    textAngle = 0;

    moveCount=0;
    currentIndex = -1;

    num = 0;
    lineNum = 0;

    newScale = 1.0;
    //���ߵĳ�ʼ����Ϊy����
    direction = 1;

    scale = 1;
}

DrawBoard::~DrawBoard(){
}


void DrawBoard::OnPaint(wxPaintEvent& event) {
        wxAutoBufferedPaintDC dc(this);
        dc.SetBackground(*wxWHITE_BRUSH);
        dc.Clear();

        wxBitmap bufferBitmap(GetClientSize());
        wxMemoryDC memDC;
        memDC.SelectObject(bufferBitmap);
        memDC.SetBackground(*wxWHITE_BRUSH);
        memDC.Clear();
        gc = wxGraphicsContext::Create(memDC);
        double centerX = GetSize().GetWidth() / 2;
        double centerY = GetSize().GetHeight() / 2;

        // ƽ�Ƶ��������ĵ�
        gc->Translate(centerX, centerY);

        // ִ�����Ų���
        gc->Scale(scale, scale);

        // ƽ�ƻ�ȥ
        gc->Translate(-centerX, -centerY);
        if (gc) {
            //gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);
            //gc->SetInterpolationQuality(wxINTERPOLATION_DEFAULT);

           
            //��������
            drawGrid(gc);
            //���Ʊ߿���
            wxPen pen(wxColour(32, 178, 170), 1);
            gc->SetPen(pen);
            //��
            gc->StrokeLine(20, 20, GetSize().x - 15, 20);
            //��
            gc->StrokeLine(20, GetSize().y - 20, GetSize().x - 15, GetSize().y - 20);
            //��
            gc->StrokeLine(20, 20, 20, GetSize().y - 20);
            //��
            gc->StrokeLine(GetSize().x - 15, 20, GetSize().x - 15, GetSize().y - 20);

            gc->StrokeLine(17, 17, GetSize().x - 12, 17);
            gc->StrokeLine(17, GetSize().y - 17, GetSize().x - 12, GetSize().y - 17);
            gc->StrokeLine(17, 17, 17, GetSize().y - 17);
            gc->StrokeLine(GetSize().x - 12, 17, GetSize().x - 12, GetSize().y - 17);
            //����������Ϣ
            gc->StrokeLine(GetSize().x - 250, GetSize().y - 120, GetSize().x - 15, GetSize().y - 120);
            gc->StrokeLine(GetSize().x - 250, GetSize().y - 60, GetSize().x - 15, GetSize().y - 60);
            gc->StrokeLine(GetSize().x - 250, GetSize().y - 40, GetSize().x - 15, GetSize().y - 40);
            gc->StrokeLine(GetSize().x - 250, GetSize().y - 120, GetSize().x - 250, GetSize().y - 20);
            gc->StrokeLine(GetSize().x - 100, GetSize().y - 40, GetSize().x - 100, GetSize().y - 20);
    
            wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
            wxColour color(32, 178, 170);
            gc->SetFont(font, color);
            gc->DrawText("Title:", GetSize().x - 242, GetSize().y - 57);
            wxFont font1(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM);
            gc->SetFont(font1, color);
            gc->DrawText("Date: 2025.1.12", GetSize().x - 242, GetSize().y - 37);
            gc->DrawText("Size: A4", GetSize().x -92, GetSize().y - 37);

            // ���ƶ�λֱ��
            gc->SetBrush(wxBrush(wxColour(0, 0, 0)));
            gc->SetPen(wxPen(wxColour(112, 128, 144), 1));
            gc->StrokeLine((mousePos.x + centerX * (scale - 1)) / scale, (mousePos.y - 30 + centerY * (scale - 1)) / scale, (mousePos.x + centerX * (scale - 1)) / scale, (mousePos.y + 30 + centerY * (scale - 1)) / scale);
            gc->StrokeLine((mousePos.x - 30 + centerX * (scale - 1)) / scale, (mousePos.y + centerY * (scale - 1)) / scale, (mousePos.x + 30 + centerX * (scale - 1)) / scale, (mousePos.y + centerY * (scale - 1)) / scale);

            for (const std::unique_ptr<Line>& linePtr : lines) {
                const Line& line = *linePtr;
                line.drawSelf(gc);
            }
            for (const std::unique_ptr<Component>& componentPtr : Components) {
                const Component& component = *componentPtr;
                component.drawSelf(gc);
            }

            for (const std::unique_ptr<Shape>& componentPtr : shapes) {
                const Shape& shape = *componentPtr;
                shape.drawSelf(gc);
            }

            if (isAddText) {
                TextEntryDialog dialog(this, "Add Text");
                if (dialog.ShowModal() == wxID_OK) {
                    text = dialog.textCtrl->GetValue();
                    wxString angle= dialog.textCtrl1->GetValue();
                    angle.ToDouble(&textAngle);
                }
                dialog.Destroy();
                isTextShow = true;
                isAddText = false;
            }

            if (isTextShow) {           
                wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
                wxColour color(0, 0, 255);
                gc->SetFont(font, color);
                // ������ת����ı�wλ��
                double textX = cos(wxDegToRad(textAngle)) * mousePos.x + sin(wxDegToRad(textAngle)) * mousePos.y;
                double textY = -sin(wxDegToRad(textAngle)) * mousePos.x + cos(wxDegToRad(textAngle)) * mousePos.y;
                gc->PushState();  // ���浱ǰ״̬
                // ��ת����ϵ
                gc->Rotate(wxDegToRad(textAngle));
                // ���ƴ�ֱ�ı�
                gc->DrawText(text, textX, textY);
                gc->PopState();  // �ָ���֮ǰ��״̬
            }

            if (isFindCom) {
                // �ڴ˴�������������ʾ
                MyFrame1 frame(this, "Ԫ����");
                if (frame.ShowModal() == wxID_OK) {
                    componentName = frame.itemText;
                    isComponentShow = true;
                }
                frame.Destroy();
                isFindCom = 0; // �� isFindCom ����Ϊ 0����ֹ�ٴ���ʾ����
            }

            if (isComponentShow) {
                isDrawingComponent = true;
                if (componentName == "R") {
                    int index = 1;
                    R r(mousePos, index);
                    r.drawSelf(gc);
                }
                else if (componentName == "R_Variable") {
                    int index = 1;
                    R_Variable r(mousePos, index);
                    r.drawSelf(gc);
                }

                else if (componentName == "����") {
                    int index = 1;
                    AndGate gate(mousePos, index);
                    gate.drawSelf(gc);
                }
                else if (componentName == "�����") {
                    int index = 1;
                    AndNotGate gate(mousePos, index);
                    gate.drawSelf(gc);
                }
                else if (componentName == "����") {
                    int index = 1;
                    OrGate gate(mousePos, index);
                    gate.drawSelf(gc);
                }
                else if (componentName == "�����") {
                    int index = 1;
                    OrNotGate gate(mousePos, index);
                    gate.drawSelf(gc);
                }
                else if (componentName == "����") {
                    int index = 1;
                    NotGate gate(mousePos, index);
                    gate.drawSelf(gc);
                }
                else if (componentName == "�����") {
                    int index = 1;
                    XorGate gate(mousePos, index);
                    gate.drawSelf(gc);
                }
                else if (componentName == "+10v") {
                    int index = 1;
                    Power_10v power(mousePos, index);
                    power.drawSelf(gc);
                }
            }

            if (componentMove) {
                Component& component = *Components[currentIndex];
                component.SetPos(mousePos);
                Refresh();
            }
            if (lineMove) {
                Line& line = *lines[currentIndex];
                wxPoint newStart;
                newStart.x = oldStart.x+ mousePos.x-currentStart.x;
                newStart.y = oldStart.y + mousePos.y- currentStart.y;
                wxPoint newEnd;
                newEnd.x = oldEnd.x + mousePos.x - currentStart.x;
                newEnd.y = oldEnd.y + mousePos.y - currentStart.y;
                line.setStart(newStart);
                line.setEnd(newEnd);
            }

            if (isChooseComponent) {
                Component& component = *Components[currentIndex];
                wxCursor cursor;
                if (mousePos.x > component.GetStart().x - component.GetWidth() * component.GetScale() / 2 && mousePos.x < component.GetStart().x + component.GetWidth() * component.GetScale() / 2 && mousePos.y>component.GetStart().y - component.GetHeight() * component.GetScale() / 2 && mousePos.y < component.GetStart().y + component.GetHeight() * component.GetScale() / 2) {
                    cursor = wxCursor(wxCURSOR_HAND);
                    SetCursor(cursor);
                    Refresh();
                }
                else {
                    cursor = wxCursor(wxCURSOR_ARROW);
                    SetCursor(cursor);
                    Refresh();
                }
            }
            if (isChooseLine) {
                Line& line = *lines[currentIndex];
                wxCursor cursor;
                if ((mousePos.x == line.GetStart().x && mousePos.y >= line.GetStart().y && mousePos.y <= line.GetEnd().y) || (mousePos.x == line.GetStart().x && mousePos.y <= line.GetStart().y && mousePos.y >= line.GetEnd().y) || (mousePos.y == line.GetStart().y && mousePos.x >= line.GetStart().x && mousePos.x <= line.GetEnd().x) || (mousePos.y == line.GetStart().y && mousePos.x <= line.GetStart().x && mousePos.x >= line.GetEnd().x)) {
                    cursor = wxCursor(wxCURSOR_HAND);
                    SetCursor(cursor);
                    Refresh();
                }
                else {
                    cursor = wxCursor(wxCURSOR_ARROW);
                    SetCursor(cursor);
                    Refresh();
                }
            }

            if (isDrawingLine) {
                gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
                if (direction == 1) {
                    gc->StrokeLine(currentStart.x, currentStart.y, currentStart.x, mousePos.y);
                }
                else {
                    gc->StrokeLine(currentStart.x, currentStart.y, mousePos.x, currentStart.y);
                }
                Refresh();
            }
       

            delete gc;
        }

        dc.Blit(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight(), &memDC, 0, 0);

}


void DrawBoard::drawGrid(wxGraphicsContext* gc) {

    wxSize size = GetSize();
    int gridSize = 35;

    gc->SetPen(wxPen(wxColour(180, 180, 180), 1, wxPENSTYLE_DOT_DASH));
    for (int x = 0; x < size.x; x += gridSize) {
        gc->StrokeLine(x, 0, x, size.y);
    }

    for (int y = 0; y < size.y; y += gridSize) {
        gc->StrokeLine(0, y, size.x, y);
    }
}


void DrawBoard::OnLeftDown(wxMouseEvent& event) {
    if (isDrawing) {
        if (isDrawingLine == false) {
            currentStart = event.GetPosition();
        }
        else {
            if (direction == 1) {
                currentEnd.x= currentStart.x;
                currentEnd.y = mousePos.y;
                std::unique_ptr<Line> linePtr = std::make_unique<Line>(currentStart, currentEnd,lineNum);
                lines.push_back(std::move(linePtr));
                direction = 0;
            }
            else {
                currentEnd.x = mousePos.x;
                currentEnd.y = currentStart.y;
                std::unique_ptr<Line> linePtr = std::make_unique<Line>(currentStart, currentEnd, lineNum);
                lines.push_back(std::move(linePtr));
                direction = 1;
            }
            lineNum = lineNum + 1;
            currentStart = currentEnd;
        }
        isDrawingLine = true;
         }
    else if (isDrawingComponent) {
        currentStart = event.GetPosition();
        if (componentName == "R") {
            std::unique_ptr<Component> R_Ptr = std::make_unique< R >(currentStart, num);
            Components.push_back(std::move(R_Ptr));
        }
        if (componentName == "R_Variable") {
            std::unique_ptr<Component> R_Ptr = std::make_unique< R_Variable >(currentStart, num);
            Components.push_back(std::move(R_Ptr));
        }
        if (componentName == "����") {
            std::unique_ptr<Component> Gate_Ptr = std::make_unique< AndGate >(currentStart, num);
            Components.push_back(std::move(Gate_Ptr));
        }
        if (componentName == "�����") {
            std::unique_ptr<Component> Gate_Ptr = std::make_unique< AndNotGate >(currentStart, num);
            Components.push_back(std::move(Gate_Ptr));
        }
        if (componentName == "����") {
            std::unique_ptr<Component> Gate_Ptr = std::make_unique< OrGate >(currentStart, num);
            Components.push_back(std::move(Gate_Ptr));
        }
        if (componentName == "�����") {
            std::unique_ptr<Component> Gate_Ptr = std::make_unique< OrNotGate >(currentStart, num);
            Components.push_back(std::move(Gate_Ptr));
        }
        if (componentName == "����") {
            std::unique_ptr<Component> Gate_Ptr = std::make_unique< NotGate >(currentStart, num);
            Components.push_back(std::move(Gate_Ptr));
        }
        if (componentName == "�����") {
            std::unique_ptr<Component> Gate_Ptr = std::make_unique< XorGate >(currentStart, num);
            Components.push_back(std::move(Gate_Ptr));
        }
        if (componentName == "+10v") {
            std::unique_ptr<Component> Gate_Ptr = std::make_unique< Power_10v >(currentStart, num);
            Components.push_back(std::move(Gate_Ptr));
        }

        num=num+1;
        isDrawingComponent = false;
        isComponentShow = false;
        Refresh();
    }
    
    else if (isTextShow) {
        currentStart = event.GetPosition();
        std::unique_ptr<Shape> TextPtr = std::make_unique<TextShape>(currentStart, text, textAngle);
        shapes.push_back(std::move(TextPtr));
        isTextShow = false;
        Refresh();
    }
    
    else {
        currentStart = event.GetPosition();
        isChooseComponent = false;
        isChooseLine = false;
        for (const std::unique_ptr<Component>&componentPtr : Components) {
             Component& component = *componentPtr;
        
             if (currentStart.x >= component.GetStart().x - component.GetWidth() * component.GetScale() / 2 && currentStart.x <= component.GetStart().x + component.GetWidth() * component.GetScale() / 2 && currentStart.y>=component.GetStart().y - component.GetHeight() * component.GetScale() / 2 && currentStart.y <= component.GetStart().y + component.GetHeight() * component.GetScale() / 2) {
                 switch (moveCount) {
                 case 0:
                     component.SetShowFrame(true);
                     moveCount = 1;
                     currentIndex= component.GetIndex();
                     Refresh();
                     break;
                 case 1:
                     if (currentIndex == component.GetIndex()) {
                             componentMove = true;
                     }
                     else {
                         currentIndex = component.GetIndex();
                         for (const std::unique_ptr<Component>& componentPtr : Components) {
                             Component& component = *componentPtr;
                             component.SetShowFrame(false);
                         }
                         component.SetShowFrame(true);
                     }
                     Refresh();
                     break;
                 }
                 isChooseComponent = true;
             }
        }
        for (const std::unique_ptr<Line>& linePtr : lines) {
            wxPen pen(wxColour(0, 255, 0), 3);
            Line& line = *linePtr;
            if ((currentStart.x == line.GetStart().x&&currentStart.y>= line.GetStart().y&& currentStart.y<= line.GetEnd().y)||(currentStart.x == line.GetStart().x && currentStart.y <= line.GetStart().y && currentStart.y >= line.GetEnd().y)|| (currentStart.y == line.GetStart().y && currentStart.x >= line.GetStart().x && currentStart.x <= line.GetEnd().x) || (currentStart.y == line.GetStart().y && currentStart.x <= line.GetStart().x && currentStart.x >= line.GetEnd().x)) {
                switch (moveCount) {
                case 0:
                    line.setPen(pen);
                    moveCount = 1;
                    currentIndex = line.GetIndex();
                    Refresh();
                    break;
                case 1:
                    if (currentIndex == line.GetIndex()) {
                        lineMove = true;
                        oldStart = line.GetStart();
                        oldEnd = line.GetEnd();
                    }
                    else {
                        currentIndex = line.GetIndex();
                        for (const std::unique_ptr<Line>& linePtr : lines) {
                            Line& line1 = *linePtr;
                            wxPen pen1(wxColour(0, 0, 0), 2);
                            line1.setPen(pen1);
                        }
                        line.setPen(pen);
                    }
                    Refresh();
                    break;
                }
                isChooseLine = true;
                Refresh();
            }
        }
        if (!isChooseComponent) {
            for (const std::unique_ptr<Component>& componentPtr : Components) {
                Component& component = *componentPtr;
                component.SetShowFrame(false);
            }
            wxCursor cursor;
            cursor = wxCursor(wxCURSOR_ARROW);
            SetCursor(cursor);
        }
        if (!isChooseLine) {
            for (const std::unique_ptr<Line>& linePtr : lines) {
                Line& line = *linePtr;
                wxPen pen(wxColour(0, 0, 0), 2);
                line.setPen(pen);
            }
        }
        if (!isChooseComponent && !isChooseLine) {
            moveCount = 0;
        }
    }
}

void DrawBoard::OnLeftUp(wxMouseEvent& event) {
    /*
    if (isDrawingLine) {
        currentEnd = event.GetPosition(); // ��¼������
        std::unique_ptr<Shape> linePtr = std::make_unique<Line>(currentStart, currentEnd);
        shapes.push_back(std::move(linePtr));
        isDrawingLine = false; // ֹͣ����
        isDrawing = false;
        Refresh(); // ˢ�½�������ʾ��������
    }
    */
    if (componentMove) {
        componentMove = false;//�ر�Ԫ��λ��������ƶ�
    }
    if (lineMove) {
        lineMove = false;
    }
}

void DrawBoard::OnMotion(wxMouseEvent& event) {
    mousePos = event.GetPosition();
    st1->SetLabel(wxString::Format(wxT("x: %d"), event.GetX()));
    st2->SetLabel(wxString::Format(wxT("y: %d"), event.GetY()));
    Refresh();
}

void DrawBoard::DrawCircle(wxGraphicsContext* gc, const wxPoint& center, double radius) {
    wxGraphicsPath path = gc->CreatePath();
    path.AddCircle(center.x, center.y, radius);
    gc->StrokePath(path);
}

void DrawBoard::OnMouseWheel(wxMouseEvent& event) {
    if (isChooseComponent) {
        Component& component = *Components[currentIndex];
        double scale = component.GetScale();
        // ������������
        float zoomInFactor = 1.1f; // �Ŵ�����
        float zoomOutFactor = 1.0f / zoomInFactor; // ��С����

        if (event.GetWheelRotation() > 0) {
            // �������Ϲ������Ŵ�ͼ��
            scale = scale * zoomInFactor;
        }
        else {
            // �������¹�������Сͼ��
            scale *= zoomOutFactor;
        }
        component.SetScale(scale);
        // ���»���ͼ��
        Refresh();
    }
}

void DrawBoard::OnRightDown(wxMouseEvent& event) {
    isDrawingLine = false; // ֹͣ����
    isDrawing = false;
    direction = 1;
    Refresh(); // ˢ�½�������ʾ��������
}

