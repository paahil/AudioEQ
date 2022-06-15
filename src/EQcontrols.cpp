#include "EQcontrols.hpp"

#include "EQIO.hpp"
namespace EQ {
EQ::EQControls Controls;

void ChangeInputDevice(int id) {
  if (Controls.adac.getDeviceCount() < 1 || Controls.inputnum < id) {
    return;
  }
  id = id + Controls.outputnum;
  Controls.iParams.deviceId = id;
  Controls.iParams.nChannels = 2;
}

void ChangeOutputDevice(int id) {
  if (Controls.adac.getDeviceCount() < 1 || Controls.outputnum < id) {
    return;
  }
  Controls.oParams.deviceId = id;
  Controls.oParams.nChannels = 2;
}
}  // namespace EQ
