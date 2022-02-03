#ifndef EQGUI_HPP
#define EQGUI_HPP
#include <wx/wx.h>
namespace EQ {
class EQFrame : public wxFrame {
 public:
  EQFrame();

 private:
  void OnHello(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
};
enum { ID_Hello = 1 };
class EQApp : public wxApp {
 public:
  virtual bool OnInit();
};
}  // namespace EQ
#endif