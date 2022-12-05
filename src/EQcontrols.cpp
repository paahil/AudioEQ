#include "EQcontrols.hpp"

#include "EQIO.hpp"
namespace EQ {

void ChangeInputDevice(EQControls* cntrls, int id) {
  if (cntrls->adac.getDeviceCount() < 1 || cntrls->inputnum < id) {
    return;
  }
  id = id + cntrls->outputnum;
  std::cout << cntrls->outputnum << std::endl;
  std::cout << id << ": Test: " << cntrls->adac.getDeviceInfo(id).name;
  cntrls->iParams.deviceId = id;
  cntrls->iParams.nChannels = 2;
}

void ChangeOutputDevice(EQControls* cntrls, int id) {
  if (cntrls->adac.getDeviceCount() < 1 || cntrls->outputnum < id) {
    return;
  }
  cntrls->oParams.deviceId = id;
  cntrls->oParams.nChannels = 2;
}
}  // namespace EQ
