#include "EQcontrols.hpp"

#include "EQIO.hpp"
namespace EQ {
EQ::EQControls Controls;

void ChangeInputDevice(int id) {
  if (Controls.adac.getDeviceCount() < 1 || Controls.outputnum < id) exit(0);
  Controls.iParams.deviceId = id;
  Controls.iParams.nChannels = 2;
  // Stop the stream.
  Controls.adac.stopStream();
  if (!Controls.adac.isStreamOpen()) {
    Controls.adac.openStream(&Controls.oParams, &Controls.iParams,
                             RTAUDIO_FLOAT32, 44100, &Controls.bufferFrames,
                             &EQ::RWSoundCard, (void*)&Controls.bufferBytes);
    Controls.adac.startStream();
  }
}

void ChangeOutputDevice(int id) {
  if (Controls.adac.getDeviceCount() < 1 || Controls.outputnum < id) exit(0);
  Controls.oParams.deviceId = id;
  Controls.oParams.nChannels = 2;
  // Stop the stream.
  Controls.adac.stopStream();
  if (!Controls.adac.isStreamOpen()) {
    Controls.adac.openStream(&Controls.oParams, &Controls.iParams,
                             RTAUDIO_FLOAT32, 44100, &Controls.bufferFrames,
                             &EQ::RWSoundCard, (void*)&Controls.bufferBytes);
    Controls.adac.startStream();
  }
}
}  // namespace EQ
