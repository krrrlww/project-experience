// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////


#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/treectrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <fstream>
#include <iomanip>
#include <wx/button.h>
#include "DrawBoard2.h"
#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/button.h>


///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxDialog
{
public:

	wxTreeCtrl* m_treeCtrl2;
	wxButton* okButton;
	wxButton* cancelButton;
	DrawBoard2* drawborad;

	MyFrame1(wxWindow* parent, const wxString& title);

	~MyFrame1();

	wxString itemText;

	void OnItemActivated(wxTreeEvent& event);
	void OnOk(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event); 

};


