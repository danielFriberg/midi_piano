// Implements midi device wrapper functions

#include "stdafx.h"

#include "midi_device.h"

std::ostream& operator<<(std::ostream& os, const MIDIINCAPS& midi_d) {
	os << midi_d.wMid << ", " << midi_d.wPid << ", " << midi_d.vDriverVersion
		<< ", " << midi_d.szPname;
	return os;
}

// Wrapper that fills the MIDIINCAPS struct with data from driver with port_id, and returns error code
UINT fillMidiDriverInfo(UINT port_id, MIDIINCAPS * fillStruct) {
	// err_val is the error code, currently unused
	return midiInGetDevCaps(port_id, fillStruct, sizeof(*fillStruct));
}


// Wrapper that fills HMIDIIN struct with data, binds the callback function, then returns an error code
UINT fillMidiDriverHandle(UINT port_id, DWORD callbackFunction, HMIDIIN * fillStruct) {
	return midiInOpen(fillStruct, port_id, callbackFunction, 0, CALLBACK_FUNCTION);
}

// Lists available MIDI devices and their driver info
void listDevices(std::ostream& os) {
	UINT device_count = midiInGetNumDevs();
	MIDIINCAPS midi_data;
	os << device_count << (device_count == 1 ? " device" : " devices") << " connected." << std::endl;
	for (unsigned int pidx = 0; pidx < device_count; pidx++) {
		if (fillMidiDriverInfo(pidx, &midi_data) == MMSYSERR_NOERROR) {
			os << "PORT[" << pidx << "]: " << midi_data << std::endl;
		}
	}
}

// Prompts user for a valid midi port number
UINT promptValidPort(std::ostream& os, std::istream& is) {
	UINT device_count = midiInGetNumDevs();
	std::string buf;
	do {
		os << "Enter a valid port digit id to connect to: " << std::endl; // only digits for now
		is.clear();
		is >> buf;
	} while (is.fail() || !is_positive_int(buf) || stoul(buf) >= device_count);
	return stoul(buf);
}

