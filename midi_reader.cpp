/* 
midi_reader.cpp : Defines the entry point for the console application.

This file contains the main loop as well as the critical midiCallback function
that determines how to handle the data recieved from an MIDI event
*/

#include "stdafx.h"

#include "my_logger.h"
#include "midi_message_handler.h"
#include "utils.h"
#include "midi_device.h"

#include <iostream>
#include <string>
#include <bitset>

// Not used yet
static MidiLog logger;

// This function called when MIDI driver receives a response from a device
// Data is inserted into a handle class MidiInfo
void CALLBACK midiCallback(HMIDIIN handle, UINT msg, DWORD dwInstance, DWORD midi_msg, DWORD time)
{	
	// dwInstance is unused;
	// msg is the type of message given by midi driver

	MidiMessageHandler midi_info(midi_msg, time);
	std::cout << midi_info << std::endl;
	std::cout << "-------------------" << std::endl;
}

int main() {
	MIDIINCAPS midi_driver_info;
	HMIDIIN midi_driver_handle;
	UINT err_val;
	UINT port_id;

	listDevices(std::cout);

	port_id = promptValidPort(std::cout, std::cin);

	// fill MIDIINCAPS structure
	std::cout << "\nPort " << port_id << " selected:" << std::endl;
	err_val = fillMidiDriverInfo(port_id, &midi_driver_info);
	if (err_val) {
		std::cout << "Error retrieving driver info." << std::endl;
		return err_val;
	}
	std::cout << midi_driver_info << std::endl;

	// fill HMIDIIN midi input handle
	std::cout << "\nOpening port " << port_id << std::endl;
	// Bind function midiCallback to handle and open the port
	err_val = fillMidiDriverHandle(port_id, (DWORD)midiCallback, &midi_driver_handle);
	if (err_val) {
		std::cout << "Cannot open MIDI device." << std::endl;
		return err_val;
	}

	midiInStart(midi_driver_handle);
	std::cout << "Starting midi input." << std::endl;

	// Loop to keep program alive to recieve MIDI events
	char c;
	while (true) {
		if (std::cin >> c) {
			if (c == 'q') {
				std::cout << "Quitting" << std::endl;
				break;
			}
			std::cin.clear();
		}
	}

	midiInClose(midi_driver_handle);
	return 0;
}
