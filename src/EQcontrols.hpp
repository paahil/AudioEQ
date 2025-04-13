#ifndef EQCONTROLSHPP
#define EQCONTROLSHPP
#include <iostream>
#include <vector>

#include "../libs/rtaudio/RtAudio.h"
#include "EQstate.hpp"
namespace EQ {
enum ToggleEQenum { On, Off };
void ChangeInputDevice(int id);
void ChangeOutputDevice(int id);
int ToggleEQ(ToggleEQenum a);
}  // namespace EQ

#endif