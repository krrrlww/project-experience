#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp() {

}

cApp::~cApp() {


}

bool cApp::OnInit() {
    m_fram1 = new MyFrame2(
        nullptr,          // �޸�����
        wxID_ANY,         // ��ϵͳ���䴰��ID
        wxString("�˵�"),  // ���ڱ���
        wxDefaultPosition,  // ��ϵͳѡ��Ĭ��λ��
        wxSize(800, 600),   // ���ô��ڴ�СΪ 800x600
        wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL  // ʹ��Ĭ����ʽ�����ñ�ǩ����
    );
    m_fram1->Show();
    return true;
}