#ifndef EQGUI_HPP
#define EQGUI_HPP
#include <wx/wx.h>
#
#include "EQIO.hpp"
#include "EQcontrols.hpp"
#include "EQfilters.hpp"
namespace EQ {
class RefreshThread;
class SpecDrawPane : public wxPanel {
 public:
  SpecDrawPane(wxPanel* parent);
  void paintEvent(wxPaintEvent& evt);
  void paintNow();
  void render(wxDC& dc);
  DECLARE_EVENT_TABLE()
};

class EQFrame : public wxFrame {
 public:
  EQFrame();
  RefreshThread* pThread;
  wxCriticalSection pThreadCS;
  RefreshScreen();

 private:
  void OnEnable(wxCommandEvent& event);
  void OnChangeOut(wxCommandEvent& event);
  void OnChangeIn(wxCommandEvent& event);
  void OnChangeGain(wxCommandEvent& event);
  SpecDrawPane* specplot;
};

class RefreshThread : public wxThread {
 public:
  RefreshThread(EQFrame* handler) : wxThread() { pHandler = handler; }
  ~RefreshThread();

 private:
  virtual ExitCode Entry();
  EQFrame* pHandler;
};

enum { ID_Enable = 1, ID_In = 2, ID_Out = 3 };

class EQApp : public wxApp {
 public:
  virtual bool OnInit();
  EQControls* GetControls() { return cntrls; }
  EQFrame* GetEQFrame() { return frame; }

 private:
  EQControls* cntrls;
  EQFrame* frame;
};

wxDECLARE_APP(EQApp);
}  // namespace EQ
#endif