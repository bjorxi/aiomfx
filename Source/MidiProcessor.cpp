/*
  ==============================================================================

    MidiProcessor.cpp
    Created: 5 Jan 2025 9:12:59pm
    Author:  Nodari L

  ==============================================================================
*/

#include "MidiProcessor.h"

void MidiProcessor::processBlock(juce::MidiBuffer &midiMessages) {
    juce::MidiBuffer newBuffer;
    int sampleNumber = 0;
    for (const juce::MidiMessageMetadata metadata : midiMessages) {
        DBG(metadata.getMessage().getDescription());
        juce::MidiMessage msg = juce::MidiMessage::noteOn(1, 60, (juce::uint8) 80);
        newBuffer.addEvent(msg, sampleNumber);
    }
    midiMessages.swapWith(newBuffer);
}
