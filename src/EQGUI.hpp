#ifndef EQGUI_HPP
#define EQGUI_HPP
#include <wx/wx.h>
#
#include "EQIO.hpp"
#include "EQcontrols.hpp"
#include "EQfilters.hpp"
namespace EQ {
class IOThread;

class EQFrame : public wxFrame {
 public:
  EQFrame();
  IOThread* pThread;
  wxCriticalSection pThreadCS;

 private:
  void OnEnable(wxCommandEvent& event);
  void OnChangeOut(wxCommandEvent& event);
  void OnChangeIn(wxCommandEvent& event);
  void OnChangeGain(wxCommandEvent& event);
};

class IOThread : public wxThread {
 public:
  IOThread(EQFrame* handler, EQControls* controls) : wxThread() {
    pHandler = handler;
    pControls = controls;
  }
  ~IOThread();

 private:
  virtual ExitCode Entry();
  EQControls* pControls;
  EQFrame* pHandler;
};

enum { ID_Enable = 1, ID_In = 2, ID_Out = 3 };

class EQApp : public wxApp {
 public:
  virtual bool OnInit();
  EQControls* GetControls() { return cntrls; }

 private:
  EQControls* cntrls;
};

wxDECLARE_APP(EQApp);
}  // namespace EQ
#endif