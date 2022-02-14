// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include "EQGUI.hpp"
#include "EQcontrols.hpp"
namespace EQ {
wxIMPLEMENT_APP(EQApp);
bool EQApp::OnInit() {
  Controls.filternum = 3;
  EQFrame* frame = new EQFrame();
  frame->Show(true);
  return true;
}
}  // namespace EQ
