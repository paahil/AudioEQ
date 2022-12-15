#include <csignal>

#include "EQGUI.hpp"
#include "EQcontrols.hpp"
namespace EQ {
wxIMPLEMENT_APP(EQApp);
bool EQApp::OnInit() {
  cntrls = new EQControls();
  cntrls->filternum = 8;
  std::vector<double> noise(cntrls->bufferFrames / 2, -100.0);
  cntrls->magspec = noise;
  frame = new EQFrame();
  frame->Show(true);
  return true;
}

}  // namespace EQ
