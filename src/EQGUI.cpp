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

void EQFrame::RefreshScreen() { specplot->paintNow(); }

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
  wxSize size = this->GetSize();
  EQApp* main = &(wxGetApp());
  EQControls* cntrls = main->GetControls();
  unsigned int N = cntrls->bufferFrames / 2;
  // Figure option variables
  int bw = 3;      // Figure border width (must be odd)
  int xtickn = 4;  // Number of ticks on the x-axis per decade.
  int ytickn = 4;  // Number of ticks on the y-axis

  // Figure position variables
  int w = size.GetX();  // Total width of the panel
  int h = size.GetY();  // Total height of the panel
  int indentl = 40;     // Figure indent from left (outer border)
  int indentr = 20;     // Figure indent from right (outer border)
  int indentu = 10;     // Figure indent from above (outer border)
  int indentd = 40;     // Figure indent from below (outer border)

  // Plot limits
  double mmin = -100;   // Lower limit of the magnitude (dB)
  double mmax = -20;    // Upper limit of the magnitude (dB)
  double fmin = 20;     // Lower limit of the frequency (Hz) (Must be >0)
  double fmax = 20000;  // Upper limit of the frequency (Hz)

  // Figure border rectangle calculation
  int fx0 = indentl;                          // Upper left corner (x)
  int fy0 = (bw - 1) / 2 + indentu;           // Upper left corner (y)
  int fw = w - fx0 - (bw - 1) / 2 - indentr;  // Width
  int fh = h - fy0 - (bw - 1) / 2 - indentd;  // Heigth

  // Plotting area calculation (inside the figure borders)
  int x0 = fx0 + (bw - 1) / 2 + 1;       // Upper left corner (x)
  int y0 = fy0 + (bw - 1) / 2 + 1;       // Upper left corner (y)
  int wp = fw - 2 * (1 + (bw - 1) / 2);  // Width
  int hp = fh - 2 * (1 + (bw - 1) / 2);  // Heigth

  // Plotting coefficient calculation
  double logfmin = std::log10(fmin);      // Lower frequency limit in log10
  double logfmax = std::log10(fmax);      // Upper frequency limit in log10
  double fsc = (0.5 * FS) / N;            // From FFT index to frequency
  double xsc = wp / (logfmax - logfmin);  // From frequency to pixels
  double ysc = hp / (mmax - mmin);        // From magnitude to pixels

  // Tick constant definitons
  int ticke = 5;   // Number of pixels the tick lines extend outside the figure
  int tickg = 3;   // Gap between the line and value label
  int tickw = 20;  // Tick value label bounding rectangle width
  int tickh = 11;  // Tick value label bounding rectangle height

  // Tick line plotting coeficcients
  int ticky0 = fy0 + fh + ticke + (bw - 1) / 2;  // Constant y value for x lines
  int tickx0 = fx0 - ticke - (bw - 1) / 2;       // Constant x value for y lines
  double tickxsc = (double)wp / (logfmax - logfmin);  // From index to pixel
  double xlinsc = 10.0 / xtickn;
  double tickysc = hp / ytickn;  // From index to pixel
  double lblysc = (mmax - mmin) / ytickn;
  // Draw the figure bounding rectangle
  dc.SetPen(wxPen(wxColor(128, 128, 128), bw));
  dc.DrawRectangle(fx0, fy0, fw, fh);

  // Draw the tick lines and labels
  wxString ticklbl;
  dc.SetPen(wxPen(wxColor(128, 128, 128), 1, wxPENSTYLE_LONG_DASH));
  if (indentl >= tickw + ticke + tickg) {
    for (int i = 0; i <= ytickn; i++) {
      dc.DrawLine(tickx0, y0 + i * tickysc, x0 + wp, y0 + i * tickysc);
      double yval = mmax - std::round(i * lblysc);
      int tx0 = tickx0 - tickg - tickw;
      int ty0 = y0 + i * tickysc - tickh / 2;
      ticklbl << yval;
      dc.DrawLabel(ticklbl, wxRect(tx0, ty0, tickw, tickh));
      ticklbl.Clear();
    }
  }
  if (indentd >= tickh + ticke + tickg) {
    for (int j = 0; j <= logfmax - logfmin; j++) {
      for (int i = 0; i < xtickn; i++) {
        double xval = std::round(std::pow(10, (logfmin + j)) * i * xlinsc);
        if (i == 0) {
          xval = std::round(std::pow(10, (logfmin + j)));
        }
        int xpos = x0 + (std::log10(xval) - logfmin) * tickxsc;
        if (xpos <= fx0 + fw && xpos >= fx0) {
          dc.DrawLine(xpos, ticky0, xpos, y0);
          int tx0 = xpos - tickw / 2;
          int ty0 = ticky0 + tickg;
          ticklbl << xval;
          dc.DrawLabel(ticklbl, wxRect(tx0, ty0, tickw, tickh), wxALIGN_CENTER);
          ticklbl.Clear();
        }
      }
    }
  }

  // Draw the spectrum
  dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
  int x1, x2, y1, y2;
  for (unsigned int i = 1; i < N; ++i) {
    y2 = y0 - std::round((cntrls->magspec[i] - mmax) * ysc);
    y1 = y0 - std::round((cntrls->magspec[i - 1] - mmax) * ysc);
    x2 = x0 + std::round((std::log10(i * fsc) - logfmin) * xsc);
    if (i == 1) {
      y1 = y1 + std::round(x0 * ((double)(y2 - y1) / (double)(x2)));
      x1 = x0;
    } else {
      x1 = x0 + std::round((std::log10((i - 1) * fsc) - logfmin) * xsc);
    }
    if (x2 > x0 + wp) {
      y2 = y0 + hp;
      x2 = x0 + wp;
    }
    if (y1 > y0 + hp) {
      y1 = y0 + hp;
    }
    if (y2 > y0 + hp) {
      y2 = y0 + hp;
    }
    if (!(x1 > x0 + wp)) {
      dc.DrawLine(x1, y1, x2, y2);
    }
  }
}
}  // namespace EQ
