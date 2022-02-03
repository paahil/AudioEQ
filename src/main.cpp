// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include "EQGUI.hpp"
namespace EQ {
wxIMPLEMENT_APP(EQApp);
bool EQApp::OnInit() {
  EQFrame* frame = new EQFrame();
  frame->Show(true);
  return true;
}
}  // namespace EQ
