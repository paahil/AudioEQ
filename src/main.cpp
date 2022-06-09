#include "EQGUI.hpp"
#include "EQcontrols.hpp"

namespace EQ {
wxIMPLEMENT_APP(EQApp);
bool EQApp::OnInit() {
  Controls.filternum = 1;
  EQFrame* frame = new EQFrame();
  frame->Show(true);
  return true;
}
}  // namespace EQ
