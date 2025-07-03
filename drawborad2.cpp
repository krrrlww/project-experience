#include "DrawBoard2.h"

DrawBoard2::DrawBoard2(wxDialog* parent) : wxPanel(parent) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &DrawBoard2::OnPaint, this);

    gc = nullptr;
    componentName = "";
}
DrawBoard2::~DrawBoard2() {
}

void DrawBoard2::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    wxBitmap bufferBitmap(GetClientSize());
    wxMemoryDC memDC;
    memDC.SelectObject(bufferBitmap);
    memDC.SetBackground(*wxWHITE_BRUSH);
    memDC.Clear();
    gc = wxGraphicsContext::Create(memDC);

    if (gc) {
        //绘制边框线
        wxPen pen(wxColour(32, 178, 170), 1);
        gc->SetPen(pen);
        gc->StrokeLine(20, 20, GetSize().x - 20, 20);
        gc->StrokeLine(20, GetSize().y - 20, GetSize().x - 20, GetSize().y - 20);
        gc->StrokeLine(20, 20, 20, GetSize().y - 20);
        gc->StrokeLine(GetSize().x - 20, 20, GetSize().x - 20, GetSize().y - 20);

        gc->StrokeLine(17, 17, GetSize().x - 17, 17);
        gc->StrokeLine(17, GetSize().y - 17, GetSize().x - 17, GetSize().y - 17);
        gc->StrokeLine(17, 17, 17, GetSize().y - 17);
        gc->StrokeLine(GetSize().x - 17, 17, GetSize().x - 17, GetSize().y - 17);

        if (componentName == "R") {
            wxPoint start(120, 120);
            int index = 1;
            R r(start,index);
            r.SetScale(2);
            r.drawSelf(gc);
        }
        if (componentName == "R_Variable") {
            wxPoint start(120, 120);
            int index = 1;
            R_Variable r(start, index);
            r.SetScale(2);
            r.drawSelf(gc);
        }
        if (componentName == "R_Trim") {
            wxPoint start(120, 120);
            int index = 1;
            R_Trim r(start, index);
            r.SetScale(2);
            r.drawSelf(gc);
        }
        if (componentName == "与门") {
            wxPoint start(120, 120);
            int index = 2;
            AndGate gate(start, index);
            gate.drawSelf(gc);
        }
        if (componentName == "与非门") {
            wxPoint start(120, 120);
            int index = 2;
            AndNotGate gate(start, index);
            gate.SetScale(0.5);
            gate.drawSelf(gc);
        }
        if (componentName == "或门") {
            wxPoint start(120, 120);
            int index = 2;
            OrGate gate(start, index);
            gate.drawSelf(gc);
        }
        if (componentName == "或非门") {
            wxPoint start(120, 120);
            int index = 2;
            OrNotGate gate(start, index);
            gate.drawSelf(gc);
        }
        if (componentName == "非门") {
            wxPoint start(120, 120);
            int index = 2;
            NotGate gate(start, index);
            gate.drawSelf(gc);
        }
        if (componentName == "异或门") {
            wxPoint start(120, 120);
            int index = 2;
            XorGate gate(start, index);
            gate.drawSelf(gc);
        }
        if (componentName == "+10v") {
            wxPoint start(120, 120);
            int index = 2;
            Power_10v power(start, index);
            power.drawSelf(gc);
        }
        if (componentName == "+5v") {
            wxPoint start(120, 120);
            int index = 2;
            Power_5v power(start, index);
            power.drawSelf(gc);
        }
        delete gc;
    }
    dc.Blit(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight(), &memDC, 0, 0);
}