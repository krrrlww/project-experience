#pragma once
#include <wx/wx.h>
#include <wx/dcgraph.h>
#include <wx/dcbuffer.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/graphics.h>
#include "Component.h"

class DrawBoard2 : public wxPanel
{
public:
	wxGraphicsContext* gc;
	wxString componentName;

	void OnPaint(wxPaintEvent& event);



public:
	DrawBoard2(wxDialog* parent);
	~DrawBoard2();
};
