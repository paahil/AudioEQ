#include <csignal>

#include "EQGUI.hpp"
#include "EQcontrols.hpp"
namespace EQ {
wxIMPLEMENT_APP(EQApp);
bool EQApp::OnInit() {
  cntrls = new EQControls();
  cntrls->filternum = 8;
  std::vector<double> zero(cntrls->bufferFrames / 2, 0.0);
  cntrls->magspec = zero;
  frame = new EQFrame();
  frame->Show(true);
  return true;
}

}  // namespace EQ
