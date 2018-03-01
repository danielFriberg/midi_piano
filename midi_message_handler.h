#pragma once

#include "stdafx.h"

#include "midi_message.h"

#include <string>
#include <ostream>

enum midi_type { NOTE_OFF, NOTE_ON, POLY, CTRL_CHANGE, PRGRM_CHANGE, CHANNEL_PRESSURE, PITCH_BEND , OTHER};
static const char * enum_strings[] = { 
	"NOTE_OFF", "NOTE_ON", "POLY", "CTRL_CHANGE", "PRGRM_CHANGE", 
	"CHANNEL_PRESSURE", "PITCH_BEND" , "OTHER" };

// Midi_message Handler class
class MidiMessageHandler {
private:
	MidiMessage * midi_data;

public:
	MidiMessageHandler() : midi_data(nullptr) {}
	MidiMessageHandler(DWORD msg, DWORD timestamp) : midi_data(nullptr) { assign(msg, timestamp); }
	~MidiMessageHandler() { delete midi_data; }
	MidiMessageHandler(const MidiMessageHandler&);
	MidiMessageHandler& operator=(const MidiMessageHandler&);
	
	// assigns correct type to midi_data depending on status byte
	void assign(DWORD msg, DWORD timestamp); // 

	friend std::ostream& operator<< (std::ostream&, const MidiMessageHandler&);

	// Access
	std::string getType() const;
	DWORD getTime() { return midi_data->getTime(); }

};

// Bits 3-7 of msg determine MIDI message type
midi_type enumerate(DWORD msg);

// Get string representation of enum type
std::string toString(midi_type t);

std::string toString(DWORD msg);
