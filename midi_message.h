#pragma once

#include "stdafx.h"

#include <ostream>
#include <bitset>


/*
This class contains a midi message class that
functions as a wrapper for a 32 bit midi output
*/

static unsigned char byteMask = 0xFF;

class MidiMessage {
	friend class MidiMessageHandler;
protected:
	virtual MidiMessage* clone() const { return new MidiMessage(*this); }

	// _data = STATUS_BYTE, _data = second byte, _data = third byte
	DWORD _data;
	DWORD _timestamp;

public:
	MidiMessage() = delete;
	MidiMessage(DWORD message, DWORD timestamp);
	virtual ~MidiMessage() = default;

	// Polymorphic function used in place of operator<<
	virtual std::ostream& readIn(std::ostream& os);

	// Access types
	DWORD getMsg() const { return _data;  }
	DWORD getStatus() const { return _data & byteMask; }
	DWORD getByte2() const { return (_data >> 8) & byteMask; }
	DWORD getByte3() const { return (_data >> 16) & byteMask; }
	DWORD getTime() const { return _timestamp; }
	DWORD getChannel() const { return 1 + (_data & 0xF); }

	// get functionsbitsets for bytes of data inlined for convenience
	std::bitset<8> getBitsStatus() const { return std::bitset<8>(getStatus()); }
	std::bitset<8> getBitsByte2() const { return std::bitset<8>(getByte2()); }
	std::bitset<8> getBitsByte3() const { return std::bitset<8>(getByte3()); }
};

// subclass for midi messages that are notes
class MidiNoteOn: public MidiMessage {
protected:
	MidiNoteOn * clone() const { return new MidiNoteOn(*this); }
public:
	MidiNoteOn(DWORD message, DWORD timestamp) : MidiMessage(message, timestamp) {}
	~MidiNoteOn() = default;
	
	// MIDI note 60 = middle C
	DWORD getNoteNumber() const { return getByte2() & 0x7F; } // first 7 bits
	DWORD getVelocity() const { return getByte3() & 0x7F; } // first 7 bits

	std::ostream& readIn(std::ostream& os);
};


// subclass for midi messages signalling note release
class MidiNoteOff : public MidiMessage {
protected:
	MidiNoteOff * clone() const { return new MidiNoteOff(*this); }
public:
	MidiNoteOff(DWORD message, DWORD timestamp) : MidiMessage(message, timestamp) {}
	~MidiNoteOff() = default;

	// MIDI note 60 = middle C
	DWORD getNoteNumber() const { return getByte2() & 0x7F; } // first 7 bits

	std::ostream& readIn(std::ostream& os);
};



class MidiCtrl: public MidiMessage {
protected:
	MidiCtrl * clone() const { return new MidiCtrl(*this); }
public:
	MidiCtrl(DWORD message, DWORD timestamp) : MidiMessage(message, timestamp) {}
	~MidiCtrl() {}

	std::ostream& readIn(std::ostream& os);
};

std::ostream& operator<<(std::ostream& os, const MidiMessage& message);
std::ostream& operator<<(std::ostream& os, const MidiNoteOn& note);
std::ostream& operator<<(std::ostream& os, const MidiNoteOff& note);
std::ostream& operator<<(std::ostream& os, const MidiCtrl& ctrl);