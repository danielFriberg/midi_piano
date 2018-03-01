#pragma once

#include "stdafx.h"
#include<ostream>
#include<string>
#include<sstream>
#include<ctime>
#include<chrono>
#include <iostream>

enum MIDILogLevel { OPEN, CLOSE, DATA, LONGDATA, MIDIERROR, MIDILONGERROR };
static const char * EnumStrings[] = { "OPEN", "CLOSE", "DATA", "LONGDATA", "MIDIERROR", "MIDILONGERROR" };
class MidiLog {
public:
	MidiLog() {};
	virtual ~MidiLog();
	std::ostream& Get(UINT);
protected:
	//std::ostream os = std::cout;
private:
	MidiLog(const MidiLog&);
	//Log& operator =(const Log&);
private:
	//MIDILogLevel enumerate(UINT umsg); // enumerates the midi msg which has an offset of 961
	MIDILogLevel messageLevel;
};

// enumerates the midi msg which has an offset of 961 (MIM_OPEN)
MIDILogLevel enumerate(UINT umsg) {
	return MIDILogLevel(umsg-MIM_OPEN);
}

std::string ToString(MIDILogLevel level) {
	return EnumStrings[level];//vector<string> a = { "OPEN", CLOSE, DATA, LONGDATA, MIDIERROR, MIDILONGERROR }
}

// windows.h midi message to MIDILogLevel string
std::string ToString(UINT uMSG) {
	return ToString(enumerate(uMSG));
}

std::ostream& log_midi_umsg(UINT uMsg,
	unsigned int width, char filler) {

	std::string message = ToString(uMsg);
	std::cout << std::string((width - message.size()) / 2, filler);
	std::cout << " " << message << " ";
	std::cout << std::string((width - message.size()) / 2, filler);
	return std::cout;
}

void ptest() {
	std::cout << ToString(OPEN) << std::endl;
}

std::ostream& MidiLog::Get(UINT uMSG) {
	MIDILogLevel level = enumerate(uMSG);
	std::cout << "- " << "TIME";
	std::cout << " " << ToString(level) << ": ";
	std::cout << '\t';
	messageLevel = level;
	return std::cout;
}

MidiLog::~MidiLog()
{
	if (true)
	{
		std::cout << std::endl;
		//fprintf(stderr, "%s", os.str().c_str());
		//fflush(stderr);
	}
}