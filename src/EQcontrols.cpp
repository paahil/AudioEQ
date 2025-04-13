#include "EQcontrols.hpp"

#include "EQIO.hpp"
namespace EQ {

void ChangeInputDevice(int id) {
  if (eqstate.adac.getDeviceCount() < 1 || eqstate->inputnum < id) {
    return;
  }
  id = id + eqstate.outputnum;
  std::cout << eqstate.outputnum << std::endl;
  std::cout << id << ": Test: " << eqstate.adac.getDeviceInfo(id).name;
  eqstate.iParams.deviceId = id;
  eqstate.iParams.nChannels = nchannel;
}

void ChangeOutputDevice(int id) {
  if (eqstate.adac.getDeviceCount() < 1 || eqstate.outputnum < id) {
    return;
  }
  eqstate.oParams.deviceId = id;
  eqstate.oParams.nChannels = nchannel;
}

int ToggleEQ(ToggleEQenum a) {
  switch (a) {
    case On:
      if (eqstate->adac.openStream(&eqstate->oParams, &eqstate->iParams,
                                   RTAUDIO_FLOAT64, FS, nsamptotal,
                                   &RWSoundCard, (void*)eqstate)) {
        // e.printMessage();
        std::cout << "Error Open" << std::endl;
        return -1;
      }
      std::cout << bufferlen << std::endl;
      if (eqstate->adac.startStream()) {
        std::cout << "Error Start" << std::endl;
        // e.printMessage();
        return -1;
      }
      break;
    case Off:
      if (eqstate->adac.stopStream()) {
        // e.printMessage();
        std::cout << "Error Stop" << std::endl;
        return -1;
      }
      break;
    default:
      break;
  }
  return 0;
}
}  // namespace EQ
