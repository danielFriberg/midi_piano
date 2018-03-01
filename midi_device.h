#pragma once

/*
These functions are wrappers to communicate with the device driver

Will mostly be expanded into a singleton class in the future
*/

#include "stdafx.h"

#include "utils.h"

#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& os, const MIDIINCAPS& midi_d);
// Wrapper that fills the MIDIINCAPS struct with data from driver with port_id, and returns error code
UINT fillMidiDriverInfo(UINT port_id, MIDIINCAPS * fillStruct);

// Wrapper that fills HMIDIIN struct with data, binds the callback function, then returns an error code
UINT fillMidiDriverHandle(UINT port_id, DWORD callbackFunction, HMIDIIN * fillStruct);

// Lists available MIDI devices and their driver info
void listDevices(std::ostream& os);

// Prompts user for a valid midi port number
UINT promptValidPort(std::ostream& os, std::istream& is);

