#ifndef EQGUI_HPP
#define EQGUI_HPP
#include <wx/wx.h>
namespace EQ {
class EQFrame : public wxFrame {
 public:
  EQFrame();

 private:
  void OnEnable(wxCommandEvent& event);
};
enum { ID_Enable = 1, ID_In = 2, ID_Out = 3 };
class EQApp : public wxApp {
 public:
  virtual bool OnInit();
};
}  // namespace EQ
#endif