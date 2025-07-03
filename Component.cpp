#include "Component.h"

void Power_10v::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    gc->StrokeLine(GetStart().x - 10*GetScale(), GetStart().y + 5 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y + 5 * GetScale());
    gc->StrokeLine(GetStart().x - 5 * GetScale(), GetStart().y - 5 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y - 5 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y + 5 * GetScale(), GetStart().x, GetStart().y + 15 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y - 5 * GetScale(), GetStart().x, GetStart().y - 15 * GetScale());
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxColour color(0, 0, 255);
    gc->SetFont(font, color);
    gc->DrawText("E 10v", GetStart().x + 12 * GetScale(), GetStart().y - 6 * GetScale());
    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - (GetWidth()/2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
    }

}

void Power_5v::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    gc->StrokeLine(GetStart().x - 10 * GetScale(), GetStart().y + 5 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y + 5 * GetScale());
    gc->StrokeLine(GetStart().x - 5 * GetScale(), GetStart().y - 5 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y - 5 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y + 5 * GetScale(), GetStart().x, GetStart().y + 15 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y - 5 * GetScale(), GetStart().x, GetStart().y - 15 * GetScale());
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxColour color(0, 0, 255);
    gc->SetFont(font, color);
    gc->DrawText("E 5v", GetStart().x + 12 * GetScale(), GetStart().y - 6 * GetScale());
    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
    }

}

void R::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    gc->StrokeLine(GetStart().x - 5*GetScale(), GetStart().y + 10 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y + 10 * GetScale());
    gc->StrokeLine(GetStart().x - 5 * GetScale(), GetStart().y - 10 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y - 10 * GetScale());
    gc->StrokeLine(GetStart().x - 5 * GetScale(), GetStart().y + 10 * GetScale(), GetStart().x - 5 * GetScale(), GetStart().y - 10 * GetScale());
    gc->StrokeLine(GetStart().x + 5 * GetScale(), GetStart().y + 10 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y - 10 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y + 10 * GetScale(), GetStart().x, GetStart().y + 15 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y - 10 * GetScale(), GetStart().x, GetStart().y - 15 * GetScale());
    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - 10 * GetScale(), GetStart().y + 20 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y + 20 * GetScale());
        gc->StrokeLine(GetStart().x - 10 * GetScale(), GetStart().y - 20 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y - 20 * GetScale());
        gc->StrokeLine(GetStart().x - 10 * GetScale(), GetStart().y + 20 * GetScale(), GetStart().x - 10 * GetScale(), GetStart().y - 20 * GetScale());
        gc->StrokeLine(GetStart().x + 10 * GetScale(), GetStart().y + 20 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y - 20 * GetScale());
    }
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxColour color(0, 0, 255);
    gc->SetFont(font, color);
    gc->DrawText("R 10¦¸", GetStart().x + 11* GetScale(), GetStart().y-4*GetScale());
}

void R_Variable::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    gc->StrokeLine(GetStart().x - 5 * GetScale(), GetStart().y + 10 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y + 10 * GetScale());
    gc->StrokeLine(GetStart().x - 5 * GetScale(), GetStart().y - 10 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y - 10 * GetScale());
    gc->StrokeLine(GetStart().x - 5 * GetScale(), GetStart().y + 10 * GetScale(), GetStart().x - 5 * GetScale(), GetStart().y - 10 * GetScale());
    gc->StrokeLine(GetStart().x + 5 * GetScale(), GetStart().y + 10 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y - 10 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y + 10 * GetScale(), GetStart().x, GetStart().y + 15 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y - 10 * GetScale(), GetStart().x, GetStart().y - 15 * GetScale());

    gc->StrokeLine(GetStart().x - 8 * GetScale(), GetStart().y + 8 * GetScale(), GetStart().x + 8 * GetScale(), GetStart().y - 8 * GetScale());
    gc->StrokeLine(GetStart().x + 8 * GetScale(), GetStart().y - 8 * GetScale(), GetStart().x + 6 * GetScale(), GetStart().y - 8 * GetScale());
    gc->StrokeLine(GetStart().x + 8 * GetScale(), GetStart().y - 8 * GetScale(), GetStart().x + 8 * GetScale(), GetStart().y - 6 * GetScale());

    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - 10 * GetScale(), GetStart().y + 20 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y + 20 * GetScale());
        gc->StrokeLine(GetStart().x - 10 * GetScale(), GetStart().y - 20 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y - 20 * GetScale());
        gc->StrokeLine(GetStart().x - 10 * GetScale(), GetStart().y + 20 * GetScale(), GetStart().x - 10 * GetScale(), GetStart().y - 20 * GetScale());
        gc->StrokeLine(GetStart().x + 10 * GetScale(), GetStart().y + 20 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y - 20 * GetScale());
    }
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxColour color(0, 0, 255);
    gc->SetFont(font, color);
    gc->DrawText("R_Variable", GetStart().x + 11 * GetScale(), GetStart().y - 4 * GetScale());
}

void R_Trim::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    gc->StrokeLine(GetStart().x - 5 * GetScale(), GetStart().y + 10 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y + 10 * GetScale());
    gc->StrokeLine(GetStart().x - 5 * GetScale(), GetStart().y - 10 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y - 10 * GetScale());
    gc->StrokeLine(GetStart().x - 5 * GetScale(), GetStart().y + 10 * GetScale(), GetStart().x - 5 * GetScale(), GetStart().y - 10 * GetScale());
    gc->StrokeLine(GetStart().x + 5 * GetScale(), GetStart().y + 10 * GetScale(), GetStart().x + 5 * GetScale(), GetStart().y - 10 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y + 10 * GetScale(), GetStart().x, GetStart().y + 15 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y - 10 * GetScale(), GetStart().x, GetStart().y - 15 * GetScale());

    gc->StrokeLine(GetStart().x - 8 * GetScale(), GetStart().y + 8 * GetScale(), GetStart().x + 8 * GetScale(), GetStart().y - 8 * GetScale());
    gc->StrokeLine(GetStart().x + 5 * GetScale(), GetStart().y - 11 * GetScale(), GetStart().x + 11 * GetScale(), GetStart().y - 5 * GetScale());
   

    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - 10 * GetScale(), GetStart().y + 20 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y + 20 * GetScale());
        gc->StrokeLine(GetStart().x - 10 * GetScale(), GetStart().y - 20 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y - 20 * GetScale());
        gc->StrokeLine(GetStart().x - 10 * GetScale(), GetStart().y + 20 * GetScale(), GetStart().x - 10 * GetScale(), GetStart().y - 20 * GetScale());
        gc->StrokeLine(GetStart().x + 10 * GetScale(), GetStart().y + 20 * GetScale(), GetStart().x + 10 * GetScale(), GetStart().y - 20 * GetScale());
    }
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxColour color(0, 0, 255);
    gc->SetFont(font, color);
    gc->DrawText("R_Trim", GetStart().x + 11 * GetScale(), GetStart().y - 4 * GetScale());
}

void AndGate::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    wxGraphicsPath path = gc->CreatePath();
    double radius = 40;
    double startAngle = 0;
    double endAngle = 3.14;
    path.AddArc(GetStart().x, GetStart().y, radius * GetScale(), startAngle, endAngle, true);
    gc->StrokePath(path);
    gc->StrokeLine(GetStart().x + radius * GetScale(), GetStart().y, GetStart().x + radius * GetScale(), GetStart().y-25 * GetScale());
    gc->StrokeLine(GetStart().x - radius * GetScale(), GetStart().y, GetStart().x - radius * GetScale(), GetStart().y - 25 * GetScale());
    gc->StrokeLine(GetStart().x - radius * GetScale(), GetStart().y - 25 * GetScale(), GetStart().x + radius * GetScale(), GetStart().y - 25 * GetScale());
    gc->StrokeLine(GetStart().x + radius/2 * GetScale(), GetStart().y - 25 * GetScale(), GetStart().x + radius/2 * GetScale(), GetStart().y - 45 * GetScale());
    gc->StrokeLine(GetStart().x - radius / 2 * GetScale(), GetStart().y - 25 * GetScale(), GetStart().x - radius / 2 * GetScale(), GetStart().y - 45 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y + radius * GetScale(), GetStart().x , GetStart().y +60 * GetScale());
    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
    }

}

void AndNotGate::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    wxGraphicsPath path = gc->CreatePath();
    double radius = 40;
    double startAngle = 0;
    double endAngle = 3.14;
    path.AddArc(GetStart().x, GetStart().y, radius * GetScale(), startAngle, endAngle, true);
    gc->StrokePath(path);
    gc->StrokeLine(GetStart().x + radius * GetScale(), GetStart().y, GetStart().x + radius * GetScale(), GetStart().y - 25 * GetScale());
    gc->StrokeLine(GetStart().x - radius * GetScale(), GetStart().y, GetStart().x - radius * GetScale(), GetStart().y - 25 * GetScale());
    gc->StrokeLine(GetStart().x - radius * GetScale(), GetStart().y - 25 * GetScale(), GetStart().x + radius * GetScale(), GetStart().y - 25 * GetScale());
    gc->StrokeLine(GetStart().x + radius / 2 * GetScale(), GetStart().y - 25 * GetScale(), GetStart().x + radius / 2 * GetScale(), GetStart().y - 45 * GetScale());
    gc->StrokeLine(GetStart().x - radius / 2 * GetScale(), GetStart().y - 25 * GetScale(), GetStart().x - radius / 2 * GetScale(), GetStart().y - 45 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y + 48 * GetScale(), GetStart().x, GetStart().y + 67 * GetScale());
    path.AddCircle(GetStart().x, GetStart().y + 44 * GetScale(), 4*GetScale());
    gc->StrokePath(path);
    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
    }

}

void OrGate::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    wxGraphicsPath path = gc->CreatePath();
    
    double radius = 42.426;
    double startAngle = 1.25*PI;
    double endAngle = 1.75*PI;
    path.AddArc(GetStart().x, GetStart().y+60*GetScale(), radius * GetScale(), startAngle, endAngle, true);
    gc->StrokePath(path);
    
    wxGraphicsPath path1 = gc->CreatePath();
    double radius1 = 90;
    double startAngle1 = PI;
    double endAngle1 = PI+0.841;
    path1.AddArc(GetStart().x+60*GetScale(), GetStart().y + 30 * GetScale(), radius1 * GetScale(), startAngle1, endAngle1, true);
    
    gc->StrokePath(path1);

    wxGraphicsPath path2 = gc->CreatePath();
    double radius2 = 90;
    double startAngle2 = 2*PI- 0.841;
    double endAngle2 = 2*PI;
    path2.AddArc(GetStart().x - 60 * GetScale(), GetStart().y + 30 * GetScale(), radius2 * GetScale(), startAngle2, endAngle2, true);

    gc->StrokePath(path2);

    gc->StrokeLine(GetStart().x, GetStart().y - 37.1 * GetScale(), GetStart().x, GetStart().y - 50 * GetScale());
    gc->StrokeLine(GetStart().x+15 * GetScale(), GetStart().y + 20.5 * GetScale(), GetStart().x + 15 * GetScale(), GetStart().y + 39 * GetScale());
    gc->StrokeLine(GetStart().x - 15 * GetScale(), GetStart().y + 20.5 * GetScale(), GetStart().x - 15 * GetScale(), GetStart().y + 39 * GetScale());

    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
    }
}

void OrNotGate::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    wxGraphicsPath path = gc->CreatePath();

    double radius = 42.426;
    double startAngle = 1.25 * PI;
    double endAngle = 1.75 * PI;
    path.AddArc(GetStart().x, GetStart().y + 60 * GetScale(), radius * GetScale(), startAngle, endAngle, true);
    gc->StrokePath(path);

    wxGraphicsPath path1 = gc->CreatePath();
    double radius1 = 90;
    double startAngle1 = PI;
    double endAngle1 = PI + 0.841;
    path1.AddArc(GetStart().x + 60 * GetScale(), GetStart().y + 30 * GetScale(), radius1 * GetScale(), startAngle1, endAngle1, true);

    gc->StrokePath(path1);

    wxGraphicsPath path2 = gc->CreatePath();
    double radius2 = 90;
    double startAngle2 = 2 * PI - 0.841;
    double endAngle2 = 2 * PI;
    path2.AddArc(GetStart().x - 60 * GetScale(), GetStart().y + 30 * GetScale(), radius2 * GetScale(), startAngle2, endAngle2, true);

    gc->StrokePath(path2);

    gc->StrokeLine(GetStart().x, GetStart().y - 45.1 * GetScale(), GetStart().x, GetStart().y - 55 * GetScale());
    gc->StrokeLine(GetStart().x + 15 * GetScale(), GetStart().y + 20.5 * GetScale(), GetStart().x + 15 * GetScale(), GetStart().y + 39 * GetScale());
    gc->StrokeLine(GetStart().x - 15 * GetScale(), GetStart().y + 20.5 * GetScale(), GetStart().x - 15 * GetScale(), GetStart().y + 39 * GetScale());

    path.AddCircle(GetStart().x, GetStart().y - 41.1 * GetScale(), 4 * GetScale());
    gc->StrokePath(path);

    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
    }
}

void NotGate::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    gc->StrokeLine(GetStart().x, GetStart().y - 60 * GetScale(), GetStart().x, GetStart().y - 45 * GetScale());
    gc->StrokeLine(GetStart().x - 40 * GetScale(), GetStart().y -35 * GetScale(), GetStart().x + 40* GetScale(), GetStart().y - 35 * GetScale());
    gc->StrokeLine(GetStart().x - 40 * GetScale(), GetStart().y - 35 * GetScale(), GetStart().x , GetStart().y + 55 * GetScale());
    gc->StrokeLine(GetStart().x + 40 * GetScale(), GetStart().y - 35 * GetScale(), GetStart().x, GetStart().y + 55 * GetScale());
    gc->StrokeLine(GetStart().x, GetStart().y + 55 * GetScale(), GetStart().x, GetStart().y + 75 * GetScale());
    wxGraphicsPath path = gc->CreatePath();
    path.AddCircle(GetStart().x, GetStart().y - 40 * GetScale(), 5 * GetScale());
    gc->StrokePath(path);
    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
    }

}

void XorGate::drawSelf(wxGraphicsContext* gc) const {
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    wxGraphicsPath path = gc->CreatePath();
    wxGraphicsPath path3 = gc->CreatePath();

    double radius = 42.426;
    double startAngle = 1.25 * PI;
    double endAngle = 1.75 * PI;
    path.AddArc(GetStart().x, GetStart().y + 60 * GetScale(), radius * GetScale(), startAngle, endAngle, true);
    path3.AddArc(GetStart().x, GetStart().y + 70 * GetScale(), radius * GetScale(), startAngle, endAngle, true);
    gc->StrokePath(path);
    gc->StrokePath(path3);

    wxGraphicsPath path1 = gc->CreatePath();
    double radius1 = 90;
    double startAngle1 = PI;
    double endAngle1 = PI + 0.841;
    path1.AddArc(GetStart().x + 60 * GetScale(), GetStart().y + 30 * GetScale(), radius1 * GetScale(), startAngle1, endAngle1, true);

    gc->StrokePath(path1);

    wxGraphicsPath path2 = gc->CreatePath();
    double radius2 = 90;
    double startAngle2 = 2 * PI - 0.841;
    double endAngle2 = 2 * PI;
    path2.AddArc(GetStart().x - 60 * GetScale(), GetStart().y + 30 * GetScale(), radius2 * GetScale(), startAngle2, endAngle2, true);

    gc->StrokePath(path2);

    gc->StrokeLine(GetStart().x, GetStart().y - 37.1 * GetScale(), GetStart().x, GetStart().y - 50 * GetScale());
    gc->StrokeLine(GetStart().x + 15 * GetScale(), GetStart().y + 20.5 * GetScale(), GetStart().x + 15 * GetScale(), GetStart().y + 45 * GetScale());
    gc->StrokeLine(GetStart().x - 15 * GetScale(), GetStart().y + 20.5 * GetScale(), GetStart().x - 15 * GetScale(), GetStart().y + 45 * GetScale());

    if (GetisShowFrame()) {
        gc->SetPen(wxPen(wxColour(160, 160, 160), 2, wxPENSTYLE_DOT));
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x - (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
        gc->StrokeLine(GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y + (GetHeight() / 2) * GetScale(), GetStart().x + (GetWidth() / 2) * GetScale(), GetStart().y - (GetHeight() / 2) * GetScale());
    }
}

json Component::toJson() const {
    json jsonShape;

    jsonShape["Type"] = componentType.ToStdString();

    json startPosArray;
    startPosArray.append(startPos.x);
    startPosArray.append(startPos.y);
    jsonShape["startPos"] = startPosArray;

    jsonShape["scale"] = scale;

    jsonShape["index"] = index;

    return jsonShape;
}

json Power_10v::toJson() const {
    return Component::toJson();
}

json Power_5v::toJson() const {
    return Component::toJson();
}

json R::toJson() const {
    return Component::toJson();
}

json AndGate::toJson() const {
    return Component::toJson();
}

json AndNotGate::toJson() const {
    return Component::toJson();
}

json OrNotGate::toJson() const {
    return Component::toJson();
}

json NotGate::toJson() const {
    return Component::toJson();
}

json XorGate::toJson() const {
    return Component::toJson();
}

json OrGate::toJson() const {
    return Component::toJson();
}

json R_Variable::toJson() const {
    return Component::toJson();
}

json R_Trim::toJson() const {
    return Component::toJson();
}