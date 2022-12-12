#include "EQGUI.hpp"
#include "EQcontrols.hpp"

namespace EQ {
wxIMPLEMENT_APP(EQApp);
bool EQApp::OnInit() {
  cntrls = new EQControls();
  cntrls->filternum = 3;
  EQFrame* frame = new EQFrame();
  frame->Show(true);
  return true;
}

}  // namespace EQ
