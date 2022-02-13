#include "EQGUI.hpp"

#include <wx/tglbtn.h>

#include "EQcontrols.hpp"
#include "RtAudio.h"
namespace EQ {
EQFrame::EQFrame() : wxFrame(NULL, wxID_ANY, "AudioEQ") {
  this->SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER &
                       ~wxMAXIMIZE_BOX);
  CreateStatusBar();
  SetStatusText("AudioEQ is not active.");

  wxPanel* panel = new wxPanel(this);
  wxGridSizer* framesizer = new wxGridSizer(1);
  framesizer->Add(panel);
  wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* devsizer = new wxBoxSizer(wxHORIZONTAL);
  wxChoice* inputdevs = new wxChoice(panel, ID_In);
  wxChoice* outputdevs = new wxChoice(panel, ID_Out);
  for (size_t i = 0; i < Controls.adac.getDeviceCount(); i++) {
    if (Controls.adac.getDeviceInfo(i).inputChannels == 2) {
      inputdevs->Append(Controls.adac.getDeviceInfo(i).name);
    }
    if (Controls.adac.getDeviceInfo(i).outputChannels == 2) {
      outputdevs->Append(Controls.adac.getDeviceInfo(i).name);
    }
  }
  wxToggleButton* enable = new wxToggleButton(panel, ID_Enable, "Enable");
  Bind(wxEVT_TOGGLEBUTTON, &EQFrame::OnEnable, this, ID_Enable);
  devsizer->Add(enable);
  devsizer->Add(new wxStaticText(panel, wxID_ANY, " Input: "));
  devsizer->Add(inputdevs);
  devsizer->Add(new wxStaticText(panel, wxID_ANY, " Output: "));
  devsizer->Add(outputdevs);
  topsizer->Add(devsizer);

  wxBoxSizer* cntrsizer = new wxBoxSizer(wxHORIZONTAL);

  panel->SetSizer(topsizer);
  SetSizer(framesizer);
  framesizer->SetSizeHints(this);
}

void EQFrame::OnEnable(wxCommandEvent& event) {
  if (event.IsChecked()) {
    SetStatusText("AudioEQ is active.");
  } else {
    SetStatusText("AudioEQ is not active.");
  }
}
}  // namespace EQ
