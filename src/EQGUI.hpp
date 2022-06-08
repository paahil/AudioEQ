#ifndef EQGUI_HPP
#define EQGUI_HPP
#include <wx/wx.h>

#include "EQIO.hpp"
namespace EQ {
class EQFrame : public wxFrame {
 public:
  EQFrame();

 private:
  void OnEnable(wxCommandEvent& event);
  void OnChangeOut(wxCommandEvent& event);
  void OnChangeIn(wxCommandEvent& event);
  void OnChangeGain(wxCommandEvent& event);
};
enum { ID_Enable = 1, ID_In = 2, ID_Out = 3 };
class EQApp : public wxApp {
 public:
  virtual bool OnInit();
};
}  // namespace EQ
#endif