#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp() {

}

cApp::~cApp() {


}

bool cApp::OnInit() {
    m_fram1 = new MyFrame2(
        nullptr,          // 无父窗口
        wxID_ANY,         // 让系统分配窗口ID
        wxString("菜单"),  // 窗口标题
        wxDefaultPosition,  // 让系统选择默认位置
        wxSize(800, 600),   // 设置窗口大小为 800x600
        wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL  // 使用默认样式并启用标签遍历
    );
    m_fram1->Show();
    return true;
}