/*
  ==============================================================================

    MidiProcessor.h
    Created: 5 Jan 2025 9:12:59pm
    Author:  Nodari L

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MidiProcessor {
public:
    void processBlock(juce::MidiBuffer &midiMessages);
};
