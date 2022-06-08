#include "aquila.h"
#include "wx/sizer.h"
#include "wx/wx.h"

class BasicDrawPane : public wxPanel {
 public:
  BasicDrawPane(wxFrame* parent);

  void paintEvent(wxPaintEvent& evt);
  void paintNow();

  void render(wxDC& dc);

  // some useful events
  /*
   void mouseMoved(wxMouseEvent& event);
   void mouseDown(wxMouseEvent& event);
   void mouseWheelMoved(wxMouseEvent& event);
   void mouseReleased(wxMouseEvent& event);
   void rightClick(wxMouseEvent& event);
   void mouseLeftWindow(wxMouseEvent& event);
   void keyPressed(wxKeyEvent& event);
   void keyReleased(wxKeyEvent& event);
   */

  DECLARE_EVENT_TABLE()
};

class MyApp : public wxApp {
  bool OnInit();

  wxFrame* frame;
  BasicDrawPane* drawPane;

 public:
};
static const std::size_t SIZEOWN = 512;
double mag[SIZEOWN];
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
  unsigned int FS = 44100;
  double gaindB = 20;
  double gain = std::pow(10, (gaindB / 20));
  const double pi = 3.14159265358979323846;
  double cofreq = (10000.0 / (FS)) * 2 * pi;
  const std::complex<double> i1(0, 1);
  std::cout << "i=" << i1 << std::endl;
  Aquila::SpectrumType filterSpectrum(SIZEOWN);
  // generate a low-pass filter spectrum
  for (std::size_t i = 0; i < SIZEOWN; ++i) {
    double f = (double)i / (2 * SIZEOWN);
    // std::cout << "f=" << f * FS << ", ";
    // std::cout << "wc=" << cofreq * FS / (2 * pi) << ", ";

    std::complex<double> b(((gain * std::tan(cofreq / 2) + std::sqrt(gain)) +
                            (gain * std::tan(cofreq / 2) - std::sqrt(gain)) *
                                std::cos(-2 * pi * f)),
                           (gain * std::tan(cofreq / 2) - std::sqrt(gain)) *
                               std::sin(-2 * pi * f));
    // std::cout << "b=" << b << ", ";

    std::complex<double> a(
        ((std::tan(cofreq / 2) + std::sqrt(gain)) +
         (std::tan(cofreq / 2) - std::sqrt(gain)) * std::cos(-2 * pi * f)),
        (std::tan(cofreq / 2) - std::sqrt(gain)) * std::sin(-2 * pi * f));
    // std::cout << "a=" << a << ", ";

    filterSpectrum[i] = std::abs(b / a);
    mag[i] = 20.0 * std::log(std::abs(b / a));
    // std::cout << std::abs(filterSpectrum[i]) << std::endl;
  }
  std::cout << std::endl;

  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new wxFrame((wxFrame*)NULL, -1, wxT("Hello wxDC"), wxPoint(50, 50),
                      wxSize(800, 600));

  drawPane = new BasicDrawPane((wxFrame*)frame);
  sizer->Add(drawPane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  frame->Show();
  return true;
}

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(BasicDrawPane::paintEvent)

END_EVENT_TABLE()

// some useful events
/*
 void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
 void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
 void BasicDrawPane::rightClick(wxMouseEvent& event) {}
 void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
 void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
 */

BasicDrawPane::BasicDrawPane(wxFrame* parent) : wxPanel(parent) {}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void BasicDrawPane::paintEvent(wxPaintEvent& evt) {
  wxPaintDC dc(this);
  render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void BasicDrawPane::paintNow() {
  wxClientDC dc(this);
  render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxDC& dc) {
  // draw a line
  dc.SetPen(wxPen(wxColor(0, 0, 0), 5));
  dc.DrawRectangle(0, 0, 800, 600);
  dc.SetPen(wxPen(wxColor(0, 0, 0), 1));  // black line, 3 pixels thick

  for (std::size_t i = 1; i < SIZEOWN; ++i) {
    dc.DrawLine(
        std::round(((i - 1) * 800.0) / SIZEOWN),
        300 - round((mag[i - 1] / 50.0) * 300),
        std::round(((i)*800.0) / SIZEOWN),
        300 - round((mag[i] / 50.0) * 300));  // draw line across the rectangle
  }
  // Look at the wxDC docs to learn how to draw other stuff
}

/*int main() {
  unsigned int FS = 44100;
  std::size_t SIZE = 512;
  double gain = 0.01;
  const double pi = 3.14159265358979323846;
  double cofreq = (12500.0 / (FS)) * 2 * pi;
  const std::complex<double> i1(0, 1);
  std::cout << "i=" << i1 << std::endl;

  // generate a low-pass filter spectrum
  Aquila::SpectrumType filterSpectrum(SIZE);
  for (std::size_t i = 0; i < SIZE; ++i) {
    double f = (double)i / (2 * SIZE);
    std::cout << "f=" << f * FS << ", ";
    std::cout << "wc=" << cofreq * FS / (2 * pi) << ", ";

    std::complex<double> b(((gain * std::tan(cofreq / 2) + std::sqrt(gain)) +
                            (gain * std::tan(cofreq / 2) - std::sqrt(gain)) *
                                std::cos(-2 * pi * f)),
                           (gain * std::tan(cofreq / 2) - std::sqrt(gain)) *
                               std::sin(-2 * pi * f));
    // std::cout << "b=" << b << ", ";

    std::complex<double> a(
        ((std::tan(cofreq / 2) + std::sqrt(gain)) +
         (std::tan(cofreq / 2) - std::sqrt(gain)) * std::cos(-2 * pi * f)),
        (std::tan(cofreq / 2) - std::sqrt(gain)) * std::sin(-2 * pi * f));
    // std::cout << "a=" << a << ", ";

    filterSpectrum[i] = std::abs(b / a);
    std::cout << std::abs(filterSpectrum[i]) << std::endl;
  }
  std::cout << std::endl;

  // the following line does the multiplication of two spectra
  // (which is complementary to convolution in time domain)

  return 0;
}*/