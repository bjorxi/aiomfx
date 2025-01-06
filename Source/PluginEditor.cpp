/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiGenAudioProcessorEditor::MidiGenAudioProcessorEditor (MidiGenAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    addAndMakeVisible(keyDropdow);
    addAndMakeVisible(scaleDropdow);
    addAndMakeVisible(octDown);
    
    keyDropdow.setEditableText(false);
    keyDropdow.addItem("C", 1);
    keyDropdow.addItem("Db", 2);
    keyDropdow.addItem("D", 3);
    keyDropdow.addItem("Eb", 4);
    keyDropdow.addItem("E", 5);
    keyDropdow.addItem("F", 6);
    keyDropdow.addItem("Gb", 7);
    keyDropdow.addItem("G", 8);
    keyDropdow.addItem("Ab", 9);
    keyDropdow.addItem("A", 10);
    keyDropdow.addItem("Bb", 11);
    keyDropdow.addItem("B", 12);
    keyDropdow.setSelectedId(1);
    
    scaleDropdow.setEditableText(false);
    scaleDropdow.addItem("Major", 1);
    scaleDropdow.addItem("Minor", 2);
    scaleDropdow.addItem("Lydian", 3);
    scaleDropdow.addItem("Mixolydian", 4);
    scaleDropdow.addItem("Spanish", 5);
    scaleDropdow.addItem("Dorian", 6);
    scaleDropdow.addItem("Phrygian", 7);
    scaleDropdow.addItem("Harmonic Minor", 8);
    scaleDropdow.addItem("Melodic Minor", 9);
    scaleDropdow.addItem("Major Pentatonic", 10);
    scaleDropdow.addItem("Minor Pentatonic", 11);
    scaleDropdow.setSelectedId(1);
    
    octDown.setTitle("Oct Down");
    octDown.setButtonText("Oct Down");
        
    keyStrToRect["C"] = keyC;
    keyStrToRect["Db"] = keyDb;
    keyStrToRect["D"] = keyD;
    keyStrToRect["Eb"] = keyEb;
    keyStrToRect["E"] = keyE;
    keyStrToRect["F"] = keyF;
    keyStrToRect["Gb"] = keyGb;
    keyStrToRect["G"] = keyG;
    keyStrToRect["Ab"] = keyAb;
    keyStrToRect["A"] = keyA;
    keyStrToRect["Bb"] = keyBb;
    keyStrToRect["B"] = keyB;
    
    keyC = juce::Rectangle<int>(10, 90, 20, 50);
    keyDb = juce::Rectangle<int>(20, 90, 20, 25);
    keyD = juce::Rectangle<int>(31, 90, 20, 50);
    keyEb = juce::Rectangle<int>(41, 90, 20, 25);
    keyE = juce::Rectangle<int>(52, 90, 20, 50);
    keyF = juce::Rectangle<int>(73, 90, 20, 50);
    keyGb = juce::Rectangle<int>(83, 90, 20, 25);
    keyG = juce::Rectangle<int>(94, 90, 20, 50);
    keyAb = juce::Rectangle<int>(104, 90, 20, 25);
    keyA = juce::Rectangle<int>(115, 90, 20, 50);
    keyBb = juce::Rectangle<int>(125, 90, 20, 25);
    keyB = juce::Rectangle<int>(136, 90, 20, 50);
    
}

MidiGenAudioProcessorEditor::~MidiGenAudioProcessorEditor()
{
}

//==============================================================================
void MidiGenAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setColour (juce::Colours::white);
    g.fillRect(keyC);
    g.fillRect(keyD);
    g.fillRect(keyE);
    g.fillRect(keyF);
    g.fillRect(keyG);
    g.fillRect(keyA);
    g.fillRect(keyB);
    
    g.setColour (juce::Colours::black);
    g.fillRect(keyDb);
    g.fillRect(keyEb);
    g.fillRect(keyGb);
    g.fillRect(keyAb);
    g.fillRect(keyBb);

}

void MidiGenAudioProcessorEditor::resized()
{
    
    keyDropdow.setBounds(10, 10, 50, 30);
    scaleDropdow.setBounds(70, 10, 100, 30);
    octDown.setBounds(10, 50, 50, 30);
}
