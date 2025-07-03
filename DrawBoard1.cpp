#include "DrawBoard1.h"

DrawBoard1::DrawBoard1(wxFrame* parent) : wxPanel(parent) {
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &DrawBoard1::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &DrawBoard1::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &DrawBoard1::OnLeftUp, this);
    Bind(wxEVT_MOTION, &DrawBoard1::OnMotion, this);

    isDrawing = false;
    isDrawingLine = false;
    isDrawingArc = false;
    DrawingArc = false;
    isAddText = false;
    isTextShow = false;
    isAddRectangle = false;

    //��ʼ�������ߵĲ���
    clickCount = 0; // ��ʼ���������
    circleCenter = wxPoint(0, 0);
    circlePoint = wxPoint(0, 0);
    startAngle = 0;
    endAngle = 0;
    radius = 0;
    //��ʼ������ı��Ĳ���
    text = "";
    textAngle = 0;

    rectangleCount = 0;

    scale = 1.0;

    gc = nullptr;
}
DrawBoard1::~DrawBoard1() {
}

void DrawBoard1::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    wxBitmap bufferBitmap(GetClientSize());
    wxMemoryDC memDC;
    memDC.SelectObject(bufferBitmap);
    memDC.SetBackground(*wxWHITE_BRUSH);
    memDC.Clear();
    gc = wxGraphicsContext::Create(memDC);
    double centerX = GetSize().GetWidth()/2;
    double centerY = GetSize().GetHeight() / 2;

    // ƽ�Ƶ��������ĵ�
    gc->Translate(centerX, centerY);

    // ִ�����Ų���
    gc->Scale(scale, scale);  

    // ƽ�ƻ�ȥ
    gc->Translate(-centerX, -centerY);


    if (gc) {
        //���Ƶ���ͼ
        drawDot(gc);
        //����������
        wxSize size = GetSize(); // ����������Ĵ��ڻ򻭲��ĳߴ�
        int centerX = size.GetWidth() / 2;
        int centerY = size.GetHeight() / 2;
        wxPen pen(wxColour(32, 178, 170), 2);
        gc->SetPen(pen);
        // ���ƴ�ֱ������
        gc->StrokeLine(centerX, 0, centerX, size.GetHeight());
        // ����ˮƽ������
        gc->StrokeLine(0, centerY, size.GetWidth(), centerY);
         // ���ƶ�λֱ��
        gc->SetBrush(wxBrush(wxColour(0, 0, 0)));
        gc->SetPen(wxPen(wxColour(112, 128, 144), 1));
        gc->StrokeLine((mousePos.x+centerX*(scale-1))/scale, (mousePos.y - 30 + centerY * (scale - 1))/scale, (mousePos.x + centerX * (scale - 1)) / scale, (mousePos.y + 30 + centerY * (scale - 1)) / scale);
        gc->StrokeLine((mousePos.x - 30 + centerX * (scale - 1)) / scale, (mousePos.y + centerY * (scale - 1)) / scale, (mousePos.x + 30 + centerX * (scale - 1)) / scale, (mousePos.y + centerY * (scale - 1)) / scale);

        for (const std::unique_ptr<Shape>& shapePtr : shapes) {
            const Shape& shape = *shapePtr;
            gc->SetPen(wxPen(shape.GetColor(), shape.GetThickness()));
            gc->SetBrush(shape.GetBrushColor());
            shape.drawSelf(gc);
        }

        if (isDrawingLine) {
            gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
            gc->StrokeLine(currentStart.x, currentStart.y, currentEnd.x, currentEnd.y);
        }
        if (isAddText) {
            TextEntryDialog dialog(this, "Add Text");
            if (dialog.ShowModal() == wxID_OK) {
                text = dialog.textCtrl->GetValue();
                wxString angle = dialog.textCtrl1->GetValue();
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
        if (isAddRectangle) {
            if (rectangleCount == 1) {
                gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
                gc->StrokeLine(currentStart.x, currentStart.y, mousePos.x, currentStart.y);
                gc->StrokeLine(currentStart.x, mousePos.y, mousePos.x, mousePos.y);
                gc->StrokeLine(currentStart.x, currentStart.y, currentStart.x, mousePos.y);
                gc->StrokeLine(mousePos.x, currentStart.y, mousePos.x, mousePos.y);
            }
        }
        if (isDrawingArc) {
            if (clickCount == 1) {
                // ����Բ��
                gc->SetPen(wxPen(wxColour(255, 0, 0), 2)); // ��ɫ������Բ��
                DrawCircle(gc, circleCenter, 1); // ����Բ�ĵ�
            }
            else if (clickCount == 2) {
                // ����Բ�ĺͰ뾶
                gc->SetPen(wxPen(wxColour(255, 0, 0), 2)); // ��ɫ������Բ��
                DrawCircle(gc, circleCenter, 1); // ����Բ�ĵ�
                gc->SetPen(wxPen(wxColour(0, 255, 0), 2)); // ��ɫ�����ڰ뾶
                gc->StrokeLine(circleCenter.x, circleCenter.y, circlePoint.x, circlePoint.y);
                gc->SetPen(wxPen(wxColour(255, 0, 255), 2)); // ��ɫ�����ڻ��ߵ��յ�
                wxGraphicsPath path = gc->CreatePath();
                path.MoveToPoint(currentStart.x, currentStart.y);
                startAngle = atan2(currentStart.y - circleCenter.y, currentStart.x - circleCenter.x);
                endAngle = atan2(currentEnd.y - circleCenter.y, currentEnd.x - circleCenter.x);
                radius = sqrt(pow(circlePoint.x - circleCenter.x, 2) + pow(circlePoint.y - circleCenter.y, 2));
                path.AddArc(circleCenter.x, circleCenter.y, radius, startAngle, endAngle, true);
                gc->StrokePath(path);
            }
            else if (clickCount == 3) {
                clickCount = 0;
                isDrawingArc = false;
            }
        }

        delete gc;
    }
    dc.Blit(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight(), &memDC, 0, 0);
}

void DrawBoard1::drawDot(wxGraphicsContext* gc) {

    wxSize size = GetSize();
    int spacing = 30;
    wxPen pen(wxColour(119, 136, 153), 2);
    gc->SetPen(pen);
    for (int x = 10; x < size.x; x += spacing) {
        for (int y = 10; y < size.y; y += spacing) {
            //gc->StrokeLine(x,y,x+1,y+1);
            wxPoint center;
            center.x = x;
            center.y = y;
            DrawCircle(gc, center, 1);
        }
    }
}

void DrawBoard1::DrawCircle(wxGraphicsContext* gc, const wxPoint& center, double radius) {
    wxGraphicsPath path = gc->CreatePath();
    path.AddCircle(center.x, center.y, radius);
    gc->StrokePath(path);
}

void DrawBoard1::OnLeftDown(wxMouseEvent& event) {
    if (isDrawing) {
        currentStart = event.GetPosition();
        isDrawingLine = true;
    }
}

void DrawBoard1::OnLeftUp(wxMouseEvent& event) {

    if (isDrawingLine) {
        currentEnd = event.GetPosition(); // ��¼������
        int num = 0;
        std::unique_ptr<Shape> linePtr = std::make_unique<Line>(currentStart, currentEnd,num);
        shapes.push_back(std::move(linePtr));
        isDrawingLine = false; // ֹͣ����
        isDrawing = false;
        Refresh(); // ˢ�½�������ʾ��������
    }
    if (isDrawingArc) {
        switch (clickCount) {
        case 0:
            circleCenter = event.GetPosition();
            break;
        case 1:
            circlePoint = event.GetPosition();
            currentStart = event.GetPosition();
            currentEnd = event.GetPosition();
            DrawingArc = true;
            break;
        case 2:
            currentEnd = event.GetPosition();
            std::unique_ptr<Shape> ArcPtr = std::make_unique< MyArc >(startAngle, endAngle, radius, circleCenter, currentStart);
            shapes.push_back(std::move(ArcPtr));
            DrawingArc = false;
            break;
        }
        clickCount++; // ���ӵ������
        Refresh(); // ˢ�½���
    }
    if (isAddRectangle) {
        if (rectangleCount == 0) {
            currentStart= event.GetPosition();
            rectangleCount = 1;
        }
        else {
            currentEnd= event.GetPosition();
            std::unique_ptr<Shape> recPtr = std::make_unique< Rectangle1 >(currentStart, currentEnd);
            shapes.push_back(std::move(recPtr));
            rectangleCount = 0;
            isAddRectangle = false;
        }
    }
    if (isTextShow) {
        currentStart = event.GetPosition();
        std::unique_ptr<Shape> TextPtr = std::make_unique<TextShape>(currentStart, text, textAngle);
        shapes.push_back(std::move(TextPtr));
        isTextShow = false;
        Refresh();
    }
}

void DrawBoard1::OnMotion(wxMouseEvent& event) {
    mousePos = event.GetPosition();
    Refresh();
    if (isDrawingLine) {
        currentEnd = event.GetPosition(); // ���½�����
        Refresh(); // ˢ�½�������ʾ�м�����
    }
    if (DrawingArc) {
        // ������ڻ��ƻ��ߣ����»��ߵ��յ㣬��ˢ�½�������ʾ���ߵ�Ԥ��
        currentEnd = event.GetPosition();
        Refresh();
    }

}