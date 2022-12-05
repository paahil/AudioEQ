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
  std::cout << "jee" << std::endl;
  cntrls->oParams.deviceId = id;
  cntrls->oParams.nChannels = 2;
  // Controls.iParams.deviceId = 0;
  //  Stop the stream.
  /*Controls.adac.stopStream();
  if (!((unsigned int)Controls.inputnum < Controls.iParams.deviceId)) {
    if (!Controls.adac.isStreamOpen()) {
      Controls.adac.openStream(&Controls.oParams, &Controls.iParams,
                               RTAUDIO_FLOAT32, 44100, &Controls.bufferFrames,
                               &RWSoundCard,
                               (void*)&Controls.bufferBytes);
      Controls.adac.startStream();
    }
  }*/
}
}  // namespace EQ
