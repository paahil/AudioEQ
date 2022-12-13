#include "EQGUI.hpp"

#include <wx/tglbtn.h>

#include <chrono>
#include <csignal>
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
    if (j == 0) {
      EQ::ChangeLowShelf(controls, j, 0, EQ::LowCoFreq);
    } else if (j == controls->filternum - 1) {
      EQ::ChangeHighShelf(controls, j, 0, EQ::HighCoFreq);
    } else {
      EQ::ChangePNFilter(controls, j, 0, EQ::GetPNFreq(controls, j));
    }
    Bind(wxEVT_SLIDER, &EQFrame::OnChangeGain, this, ID_Out + 1 + j);
    std::vector<double> wlvl(2, 0.0);
    std::vector<std::vector<double>> chnlvl(2, wlvl);
    controls->previousSamples.push_back(chnlvl);
  }
  wxBoxSizer* screensizer = new wxBoxSizer(wxHORIZONTAL);
  specplot = new SpecDrawPane(panel);
  specplot->SetMinSize(wxSize(800, 200));
  screensizer->Add(specplot);
  topsizer->Add(screensizer);
  topsizer->Add(cntrsizer);
  panel->SetSizer(topsizer);
  SetSizer(framesizer);
  framesizer->SetSizeHints(this);
}

EQFrame::RefreshScreen() { specplot->paintNow(); }

RefreshThread::~RefreshThread() {
  wxCriticalSectionLocker enter(pHandler->pThreadCS);
  pHandler->pThread = NULL;
}

wxThread::ExitCode RefreshThread::Entry() {
  EQApp* main = &(wxGetApp());
  EQFrame* frame = main->GetEQFrame();
  EQControls* cntrls = main->GetControls();
  int sleeptime = 1000 / cntrls->FPS;  // in milliseconds;
  while (!TestDestroy()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
    frame->RefreshScreen();
  }
  return (wxThread::ExitCode)0;
}

void EQFrame::OnEnable(wxCommandEvent& event) {
  EQApp* main = &(wxGetApp());
  EQControls* controls = main->GetControls();
  if (event.IsChecked()) {
    SetStatusText("AudioEQ is active.");
    try {
      controls->adac.openStream(&controls->oParams, &controls->iParams,
                                RTAUDIO_FLOAT64, 44100, &controls->bufferFrames,
                                &RWSoundCard, (void*)controls);
      controls->bufferBytes = controls->bufferFrames * 2 * 8;
    } catch (RtAudioErrorType& e) {
      // e.printMessage();
      std::cout << "Error Open" << std::endl;
    }
    try {
      controls->adac.startStream();
    } catch (RtAudioErrorType& e) {
      std::cout << "Error Start" << std::endl;
      // e.printMessage();
    }
    pThread = new RefreshThread(this);
    if (pThread->Run() != wxTHREAD_NO_ERROR) {
      wxLogError("Can't create the thread!");
      delete pThread;
      pThread = NULL;
    }
  } else {
    SetStatusText("AudioEQ is not active.");
    try {
      controls->adac.stopStream();
    } catch (RtAudioErrorType& e) {
      // e.printMessage();
      std::cout << "Error Stop" << std::endl;
    }
    wxCriticalSectionLocker enter(pThreadCS);
    if (pThread)  // does the thread still exist?
    {
      wxMessageOutputDebug().Printf("MYFRAME: deleting thread");
      if (pThread->Delete() != wxTHREAD_NO_ERROR)
        wxLogError("Can't delete the thread!");
    }
    // exit from the critical section to give the thread
    // the possibility to enter its destructor
    // (which is guarded with m_pThreadCS critical section!)
    while (1) {  // was the ~MyThread() function executed?
      wxCriticalSectionLocker enter(pThreadCS);
      if (!pThread) break;
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
  int maxind = controls->filternum - 1;
  int id = event.GetId() - (ID_Out + 1);
  if (id == 0) {
    EQ::ChangeLowShelf(controls, id, event.GetInt(), EQ::LowCoFreq);
  } else if (id == maxind) {
    EQ::ChangeHighShelf(controls, id, event.GetInt(), EQ::HighCoFreq);
  } else {
    EQ::ChangePNFilter(controls, id, event.GetInt(),
                       EQ::GetPNFreq(controls, id));
  }
}
BEGIN_EVENT_TABLE(SpecDrawPane, wxPanel)
EVT_PAINT(SpecDrawPane::paintEvent)
END_EVENT_TABLE()

SpecDrawPane::SpecDrawPane(wxPanel* parent) : wxPanel(parent) {}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void SpecDrawPane::paintEvent(wxPaintEvent& evt) {
  wxPaintDC dc(this);
  render(dc);
}

void SpecDrawPane::paintNow() {
  wxClientDC dc(this);
  render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void SpecDrawPane::render(wxDC& dc) {
  // draw a line
  wxSize size = this->GetSize();
  EQApp* main = &(wxGetApp());
  int w = size.GetX();
  int h = size.GetY();
  EQControls* cntrls = main->GetControls();
  unsigned int N = cntrls->bufferFrames / 2;
  dc.SetPen(wxPen(wxColor(0, 0, 0), 4));
  dc.DrawRectangle(0, 0, w, h);
  dc.SetPen(wxPen(wxColor(0, 0, 0), 1));  // black line, 3 pixels thick

  int wd = w - 4;
  int hd = h - 4;
  int x0 = 2;
  int y0 = 2;
  double gmin = 10;
  double xscale = ((double)wd / (double)N);
  double yscale = ((double)hd / (2 * 40));
  for (std::size_t i = 1; i < N; ++i) {
    dc.DrawLine(x0 + std::round((i - 1) * xscale),
                y0 + hd / 2 - std::round(cntrls->magspec[i - 1] * yscale),
                x0 + std::round(i * xscale),
                y0 + hd / 2 -
                    std::round(cntrls->magspec[i] *
                               yscale));  // draw line across the rectangle
  }
  // Look at the wxDC docs to learn how to draw other stuff
}
}  // namespace EQ
