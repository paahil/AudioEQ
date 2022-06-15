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
  Controls.inputnum = 0;
  Controls.outputnum = 0;
  for (size_t i = 0; i < Controls.adac.getDeviceCount(); i++) {
    if (Controls.adac.getDeviceInfo(i).inputChannels > 0) {
      inputdevs->Append(Controls.adac.getDeviceInfo(i).name);
      Controls.inputnum++;
    }
    if (Controls.adac.getDeviceInfo(i).outputChannels > 0) {
      outputdevs->Append(Controls.adac.getDeviceInfo(i).name);
      Controls.outputnum++;
    }
  }
  Bind(wxEVT_CHOICE, &EQFrame::OnChangeIn, this, ID_In);
  Bind(wxEVT_CHOICE, &EQFrame::OnChangeOut, this, ID_Out);
  wxToggleButton* enable = new wxToggleButton(panel, ID_Enable, "Enable");
  Bind(wxEVT_TOGGLEBUTTON, &EQFrame::OnEnable, this, ID_Enable);
  devsizer->Add(enable);
  devsizer->Add(new wxStaticText(panel, wxID_ANY, " Input: "));
  devsizer->Add(inputdevs);
  devsizer->Add(new wxStaticText(panel, wxID_ANY, " Output: "));
  devsizer->Add(outputdevs);
  topsizer->Add(devsizer);
  
  wxBoxSizer* cntrsizer = new wxBoxSizer(wxHORIZONTAL);
  for (int j = 0; j < Controls.filternum; j++) {
    wxSlider* slider = new wxSlider(
        panel, ID_Out + 1 + j, 0, -25, 25, wxDefaultPosition, wxSize(100, 300),
        wxSL_VERTICAL | wxSL_AUTOTICKS | wxSL_LABELS);
    cntrsizer->Add(slider);
    std::vector<std::pair<std::pair<double,double>,std::pair<double,double>>> prevs;
    prevs.push_back(std::make_pair(std::make_pair(0,0),std::make_pair(0,0)));
    Controls.previousSamples.push_back(prevs);
    if (j == 0) {
      EQ::ChangeLowShelf(j,0,EQ::LowCoFreq);
    } else if (j == 1) {
      EQ::ChangeHighShelf(j,0,EQ::HighCoFreq);
    } else {
    }
    Bind(wxEVT_SLIDER, &EQFrame::OnChangeGain, this, ID_Out + 1 + j);
  }
  topsizer->Add(cntrsizer, wxEXPAND);

  panel->SetSizer(topsizer);
  SetSizer(framesizer);
  framesizer->SetSizeHints(this);
}

void EQFrame::OnEnable(wxCommandEvent& event) {
  if (event.IsChecked()) {
    SetStatusText("AudioEQ is active.");
    ToggleEQ(ToggleEQenum::On);

  } else {
    SetStatusText("AudioEQ is not active.");
    ToggleEQ(ToggleEQenum::Off);
  }
}

void EQFrame::OnChangeOut(wxCommandEvent& event) {
  if (event.GetSelection() == 2) {
    SetStatusText("jee");
  }
  EQ::ChangeOutputDevice(event.GetSelection());
}

void EQFrame::OnChangeIn(wxCommandEvent& event) {
  EQ::ChangeInputDevice(event.GetSelection());
}

void EQFrame::OnChangeGain(wxCommandEvent& event) {
  int id = event.GetId() - (ID_Out + 1);
  std::cout << "ID: " << id
            << " value: " << event.GetInt() << std::endl;
  switch(id){
    case 0:
      EQ::ChangeLowShelf(id, event.GetInt(), EQ::LowCoFreq);
      break;

    case 1:
      EQ::ChangeHighShelf(id, event.GetInt(), EQ::HighCoFreq);
      break;

    default:
      break;
  }
}
}  // namespace EQ
