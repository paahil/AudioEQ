#include "EQcontrols.hpp"

#include "EQIO.hpp"
namespace EQ {
EQ::EQControls Controls;

void ChangeInputDevice(int id) {
  if (Controls.adac.getDeviceCount() < 1 || Controls.inputnum < id) {
    return;
  }
  id = id + Controls.outputnum;
  std::cout << Controls.outputnum << std::endl;
  std::cout << id << ": Test: " << Controls.adac.getDeviceInfo(id).name;
  Controls.iParams.deviceId = id;
  Controls.iParams.nChannels = 2;
}

void ChangeOutputDevice(int id) {
  if (Controls.adac.getDeviceCount() < 1 || Controls.outputnum < id) {
    return;
  }
  std::cout << "jee" << std::endl;
  Controls.oParams.deviceId = id;
  Controls.oParams.nChannels = 2;
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
