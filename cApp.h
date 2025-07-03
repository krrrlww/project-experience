#pragma once
#include <wx/wx.h>
#include "menu1.h"

class cApp :public wxApp
{
public:
    cApp();
    ~cApp();

private:
    MyFrame2* m_fram1 = nullptr;

public:
    virtual bool OnInit();
};

