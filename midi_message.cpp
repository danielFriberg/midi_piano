#include "stdafx.h"

#include "midi_message.h"

// Redundant readIn; implement a template member function in the future?
/*
template<class T>
std::ostream& T::readIn(std::ostream& os) {
	return os << *this;
}
*/

MidiMessage::MidiMessage(DWORD message, DWORD timestamp): _data(message), _timestamp(timestamp) {
}


std::ostream& MidiMessage::readIn(std::ostream& os) { return os << *this; }

std::ostream& operator<<(std::ostream& os, const MidiMessage& midi_msg) {
	os << "STATUS: " << midi_msg.getBitsStatus();
	os << " || BYTE2:  " << midi_msg.getBitsByte2();
	os << " || BYTE3:  " << midi_msg.getBitsByte3();
	return os;
}


std::ostream& MidiNoteOn::readIn(std::ostream& os) { return os << *this; }

std::ostream& operator<<(std::ostream& os, const MidiNoteOn& note) {
	os << " CHANNEL: " << note.getChannel();
	os << " || NOTE: " << note.getNoteNumber();
	os << " || VELOCITY: " << note.getVelocity();
	return os;
}

std::ostream& MidiNoteOff::readIn(std::ostream& os) { return os << *this; }

std::ostream& operator<<(std::ostream& os, const MidiNoteOff& note) {
	os << "CHANNEL: " << note.getChannel();
	os << " || NOTE: " << note.getNoteNumber();
	//os << " || VELOCITY: " << note.getVelocity();
	return os;
}

std::ostream& MidiCtrl::readIn(std::ostream& os) { return os << *this; }

std::ostream& operator<<(std::ostream& os, const MidiCtrl& ctrl) {
	os << "STATUS: " << ctrl.getBitsStatus();
	os << " || CTRL#:  " << ctrl.getByte2();
	os << " || VALUE:  " << ctrl.getByte3();
	return os;
}