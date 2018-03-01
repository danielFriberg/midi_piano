# midi_reader

By Daniel M. Friberg, 2018

Currently, this program only supports Windows systems. Open the Visual C++ project file in the main directory and build to use.
Be sure to link the Windows Multimedia Library (winmm.lib), as that is not linked by default by Visual Studio

## Overview

NOTE TO RECRUITERS - While this project is in its infancy, I hope it can at least provide proof of ability to code in C++,
the ability to write legible code with a consistent style, ability to interface with hardware, and knowledge of object 
oriented principles. In particular, midi_message and midi_message_handler might be useful to look at.


midi_reader is a console program that is capable of low level communications with MIDI devices. Currently, it only
capable of handling input data. Classes are made to handle the data and output it in a human readible format. By 
default, it simply streams the human readible data back out to standard output.

This project is being developed out of a desire to create midi software and visualizer and my inability to compile
or understand existing midi APIs. Thus, I set out to create an API that reads in midi data from my keyboard for use
in future projects.


## Files
- midi_reader
		Main loop of the program. Contains the midiCallback function that handles events from the midi driver.
		Data is read into a handler class for midi messages that assigns appropriate classes for the data.
		Currently, midiCallback only prints out the data in a human readible format, but users are free to
		use the handler class for anything else.

- midi_device
		Contains functions that directly communicate with the midi drivers. 

- midi_message
		Contains the base class for midi messages and any defined inherited classes for specific message types
		Currently, there are unique inherited classes for NOTE_ON, NOTE_OFF, and CONTROL_CHANGE midi messages

- midi_message_handler
		Handle class for midi_message data. Allows for simple reading in of any type of midi data, and acts
		as an interface between the midi_message (and inherited classes) and midi_reader (the user).

- my_logger
		A not very useful logger. Exanding it will be sidetracked until I find it necessary to log

