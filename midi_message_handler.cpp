#include "stdafx.h"

#include "midi_message_handler.h"


std::string MidiMessageHandler::getType() const { return toString(midi_data->getMsg()); }

// copy ctors
MidiMessageHandler::MidiMessageHandler(const MidiMessageHandler& other) : midi_data(nullptr) {
	if (other.midi_data) midi_data = other.midi_data->clone();
}

MidiMessageHandler& MidiMessageHandler::operator=(const MidiMessageHandler& other) {
	if (&other != this) {
		delete midi_data;
		if (other.midi_data) midi_data = other.midi_data->clone();
		else midi_data = nullptr;
	}
	return *this;
}

// Bits 3-7 of msg determine MIDI message type
midi_type enumerate(DWORD msg) {
	UINT bits = (msg >> 4) & 0xF;
	midi_type type;
	switch (bits) {
	case 0x8:
		type = NOTE_OFF;
		break;
	case 0x9:
		type = NOTE_ON;
		break;
	case 0xA:
		type = POLY;
		break;
	case 0xB:
		type = CTRL_CHANGE;
		break;
	case 0xC:
		type = PRGRM_CHANGE;
		break;
	case 0xD:
		type = CHANNEL_PRESSURE;
		break;
	case 0xE:
		type = PITCH_BEND;
		break;
	default:
		type = OTHER;
		break;
	}

	// In case piano sends NOTE_ON with velocity 0 instead of NOTE_OFF
	//std::cout << ((msg >> 16) & 0xFF == 0) << std::endl;

	if (type == NOTE_ON && (msg >> 16) == 0) {
		//std::cout << "OFFING" << std::endl;
		//std::cout << msg << " | " << (msg >> 8) << std::endl;
		type = NOTE_OFF;
	}

	return type;
}

void MidiMessageHandler::assign(DWORD msg, DWORD timestamp) {
	midi_type type = enumerate(msg);
	if (type == NOTE_ON) {
		midi_data = new MidiNoteOn(msg, timestamp);
	}
	else if (type == NOTE_OFF) {
		midi_data = new MidiNoteOff(msg, timestamp);
	}
	else if (type == CTRL_CHANGE) {
		midi_data = new MidiCtrl(msg, timestamp);
	}
	else {
		// Other or not yet implemented types
		midi_data = new MidiMessage(msg, timestamp);
	}
}

// Get string representation of enum type
std::string toString(midi_type t) { return enum_strings[t]; }

std::string toString(DWORD msg) { return enum_strings[enumerate(msg)]; }


std::ostream& operator<<(std::ostream& os, const MidiMessageHandler& midi) {
	// Dereferencing and using operator<< casted midi to 
	// base class so virtual function is used instead
	os << midi.getType() << ": ";
	return midi.midi_data->readIn(os);
}