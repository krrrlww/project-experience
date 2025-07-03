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

    //初始化画弧线的操作
    clickCount = 0; // 初始化点击次数
    circleCenter = wxPoint(0, 0);
    circlePoint = wxPoint(0, 0);
    startAngle = 0;
    endAngle = 0;
    radius = 0;
    //初始化添加文本的操作
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

    // 平移到缩放中心点
    gc->Translate(centerX, centerY);

    // 执行缩放操作
    gc->Scale(scale, scale);  

    // 平移回去
    gc->Translate(-centerX, -centerY);


    if (gc) {
        //绘制点阵图
        drawDot(gc);
        //绘制中轴线
        wxSize size = GetSize(); // 假设这是你的窗口或画布的尺寸
        int centerX = size.GetWidth() / 2;
        int centerY = size.GetHeight() / 2;
        wxPen pen(wxColour(32, 178, 170), 2);
        gc->SetPen(pen);
        // 绘制垂直中轴线
        gc->StrokeLine(centerX, 0, centerX, size.GetHeight());
        // 绘制水平中轴线
        gc->StrokeLine(0, centerY, size.GetWidth(), centerY);
         // 绘制定位直线
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
            // 计算旋转后的文本w位置
            double textX = cos(wxDegToRad(textAngle)) * mousePos.x + sin(wxDegToRad(textAngle)) * mousePos.y;
            double textY = -sin(wxDegToRad(textAngle)) * mousePos.x + cos(wxDegToRad(textAngle)) * mousePos.y;
            gc->PushState();  // 保存当前状态
            // 旋转坐标系
            gc->Rotate(wxDegToRad(textAngle));
            // 绘制垂直文本
            gc->DrawText(text, textX, textY);
            gc->PopState();  // 恢复到之前的状态
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
                // 绘制圆心
                gc->SetPen(wxPen(wxColour(255, 0, 0), 2)); // 红色笔用于圆心
                DrawCircle(gc, circleCenter, 1); // 绘制圆心点
            }
            else if (clickCount == 2) {
                // 绘制圆心和半径
                gc->SetPen(wxPen(wxColour(255, 0, 0), 2)); // 红色笔用于圆心
                DrawCircle(gc, circleCenter, 1); // 绘制圆心点
                gc->SetPen(wxPen(wxColour(0, 255, 0), 2)); // 绿色笔用于半径
                gc->StrokeLine(circleCenter.x, circleCenter.y, circlePoint.x, circlePoint.y);
                gc->SetPen(wxPen(wxColour(255, 0, 255), 2)); // 紫色笔用于弧线的终点
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
        currentEnd = event.GetPosition(); // 记录结束点
        int num = 0;
        std::unique_ptr<Shape> linePtr = std::make_unique<Line>(currentStart, currentEnd,num);
        shapes.push_back(std::move(linePtr));
        isDrawingLine = false; // 停止绘制
        isDrawing = false;
        Refresh(); // 刷新界面以显示最终线条
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
        clickCount++; // 增加点击次数
        Refresh(); // 刷新界面
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
        currentEnd = event.GetPosition(); // 更新结束点
        Refresh(); // 刷新界面以显示中间线条
    }
    if (DrawingArc) {
        // 如果正在绘制弧线，更新弧线的终点，并刷新界面以显示弧线的预览
        currentEnd = event.GetPosition();
        Refresh();
    }

}