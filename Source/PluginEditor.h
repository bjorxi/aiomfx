/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MidiGenAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MidiGenAudioProcessorEditor (MidiGenAudioProcessor&);
    ~MidiGenAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiGenAudioProcessor& audioProcessor;
    juce::ComboBox keyDropdow;
    juce::ComboBox scaleDropdow;
    juce::ToggleButton octDown;
    
    juce::Rectangle<int> keyC;
    juce::Rectangle<int> keyDb;
    juce::Rectangle<int> keyD;
    juce::Rectangle<int> keyEb;
    juce::Rectangle<int> keyE;
    juce::Rectangle<int> keyF;
    juce::Rectangle<int> keyGb;
    juce::Rectangle<int> keyG;
    juce::Rectangle<int> keyAb;
    juce::Rectangle<int> keyA;
    juce::Rectangle<int> keyBb;
    juce::Rectangle<int> keyB;
    
    std::map<std::string, juce::Rectangle<int>> keyStrToRect;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiGenAudioProcessorEditor)
};
