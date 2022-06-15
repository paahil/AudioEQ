#include "EQGUI.hpp"
#include "EQcontrols.hpp"

namespace EQ {
wxIMPLEMENT_APP(EQApp);
bool EQApp::OnInit() {
  Controls.filternum = 2;
  EQFrame* frame = new EQFrame();
  frame->Show(true);
  return true;
}
}  // namespace EQ
