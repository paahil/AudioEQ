#include "EQGUI.hpp"

#include <wx/tglbtn.h>

#include <chrono>
#include <thread>

#include "EQcontrols.hpp"
#include "RtAudio.h"

namespace EQ {

EQFrame::EQFrame() : wxFrame(NULL, wxID_ANY, "AudioEQ") {
  this->SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER &
                       ~wxMAXIMIZE_BOX);
  CreateStatusBar();
  SetStatusText("AudioEQ is not active.");
  EQApp* main = &(wxGetApp());
  EQControls* controls = main->GetControls();
  wxPanel* panel = new wxPanel(this);
  wxGridSizer* framesizer = new wxGridSizer(1);
  framesizer->Add(panel);
  wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* devsizer = new wxBoxSizer(wxHORIZONTAL);
  wxChoice* inputdevs = new wxChoice(panel, ID_In);
  wxChoice* outputdevs = new wxChoice(panel, ID_Out);
  controls->inputnum = 0;
  controls->outputnum = 0;
  for (size_t i = 0; i < controls->adac.getDeviceCount(); i++) {
    if (controls->adac.getDeviceInfo(i).inputChannels > 0) {
      inputdevs->Append(controls->adac.getDeviceInfo(i).name);
      controls->inputnum++;
    }
    if (controls->adac.getDeviceInfo(i).outputChannels > 0) {
      outputdevs->Append(controls->adac.getDeviceInfo(i).name);
      controls->outputnum++;
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
  for (int j = 0; j < controls->filternum; j++) {
    wxSlider* slider = new wxSlider(
        panel, ID_Out + 1 + j, 0, -25, 25, wxDefaultPosition, wxSize(100, 300),
        wxSL_VERTICAL | wxSL_AUTOTICKS | wxSL_LABELS);
    cntrsizer->Add(slider);
    std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>
        prevs;
    prevs.push_back(std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0)));
    Controls.previousSamples.push_back(prevs);
    if (j == 0) {
      EQ::ChangeLowShelf(controls, j, 0, EQ::LowCoFreq);
    } else if (j == 1) {
      EQ::ChangeHighShelf(controls, j, 0, EQ::HighCoFreq);
    } else {
    }
    Bind(wxEVT_SLIDER, &EQFrame::OnChangeGain, this, ID_Out + 1 + j);
    std::vector<double> filtprevsamples(4, 0.0);
    controls->previousSamples.push_back(filtprevsamples);
  }
  topsizer->Add(cntrsizer, wxEXPAND);

  panel->SetSizer(topsizer);
  SetSizer(framesizer);
  framesizer->SetSizeHints(this);
}

IOThread::~IOThread() {
  wxCriticalSectionLocker enter(pHandler->pThreadCS);
  pHandler->pThread = NULL;
}

wxThread::ExitCode IOThread::Entry() {
  try {
    pControls->adac.openStream(&pControls->oParams, &pControls->iParams,
                               RTAUDIO_FLOAT64, 44100, &pControls->bufferFrames,
                               &RWSoundCard, (void*)pControls);
    pControls->bufferBytes = pControls->bufferFrames * 2 * 8;
    std::cout << pControls->bufferBytes << std::endl;
  } catch (RtAudioErrorType& e) {
    // e.printMessage();
    std::cout << "Error Open" << std::endl;
    return (wxThread::ExitCode)-1;
  }
  try {
    pControls->adac.startStream();
  } catch (RtAudioErrorType& e) {
    std::cout << "Error Start" << std::endl;
    // e.printMessage();
    return (wxThread::ExitCode)-1;
  }
  while (!TestDestroy()) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  try {
    pControls->adac.stopStream();
  } catch (RtAudioErrorType& e) {
    // e.printMessage();
    std::cout << "Error Stop" << std::endl;
    return (wxThread::ExitCode)-1;
  }
  return (wxThread::ExitCode)0;
}

void EQFrame::OnEnable(wxCommandEvent& event) {
  EQApp* main = &(wxGetApp());
  EQControls* controls = main->GetControls();
  if (event.IsChecked()) {
    SetStatusText("AudioEQ is active.");
    pThread = new IOThread(this, controls);
    if (pThread->Run() != wxTHREAD_NO_ERROR) {
      wxLogError("Can't create the thread!");
      delete pThread;
      pThread = NULL;
    }

  } else {
    SetStatusText("AudioEQ is not active.");
    {
      wxCriticalSectionLocker enter(pThreadCS);
      if (pThread)  // does the thread still exist?
      {
        wxMessageOutputDebug().Printf("MYFRAME: deleting thread");
        if (pThread->Delete() != wxTHREAD_NO_ERROR)
          wxLogError("Can't delete the thread!");
      }
    }  // exit from the critical section to give the thread
       // the possibility to enter its destructor
       // (which is guarded with m_pThreadCS critical section!)
    while (1) {
      {  // was the ~MyThread() function executed?
        wxCriticalSectionLocker enter(pThreadCS);
        if (!pThread) break;
      }
      // wait for thread completion
      wxThread::This()->Sleep(1);
    }
  }
}

void EQFrame::OnChangeOut(wxCommandEvent& event) {
  EQApp* main = &(wxGetApp());
  EQControls* controls = main->GetControls();
  if (event.GetSelection() == 2) {
    SetStatusText("jee");
  }
  EQ::ChangeOutputDevice(controls, event.GetSelection());
}

void EQFrame::OnChangeIn(wxCommandEvent& event) {
  EQApp* main = &(wxGetApp());
  EQControls* controls = main->GetControls();
  EQ::ChangeInputDevice(controls, event.GetSelection());
}

void EQFrame::OnChangeGain(wxCommandEvent& event) {
  EQApp* main = &(wxGetApp());
  EQControls* controls = main->GetControls();
  int id = event.GetId() - (ID_Out + 1);
  switch (id) {
    case 0:
      EQ::ChangeLowShelf(controls, id, event.GetInt(), EQ::LowCoFreq);
      break;

    case 1:
      EQ::ChangeHighShelf(controls, id, event.GetInt(), EQ::HighCoFreq);
      break;

    default:
      break;
  }
}
}  // namespace EQ
