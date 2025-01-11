/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiGenAudioProcessorEditor::MidiGenAudioProcessorEditor (MidiGenAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), scale("C", "Major")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    addAndMakeVisible(keyDropdown);
    addAndMakeVisible(scaleDropdown);
    addAndMakeVisible(octDown);
    
    std::vector<std::string> notes = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};
    setUpDropdown(keyDropdown, notes, 1, true);

    
    
    std::vector<std::string> scalesNames = {"Major", "Minor",
        "Lydian", "Mixolydian", "Spanish", "Dorian", "Phrygian",
        "Harmonic Minor", "Melodic Minor", "Major Pentatonic", "Minor Pentatonic"};
    
    setUpDropdown(scaleDropdown, scalesNames, 1, true);

    octDown.setTitle("Oct Down");
    octDown.setButtonText("Oct Down");

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

    itor[1] = keyC;
    itor[2] = keyDb;
    itor[3] = keyD;
    itor[4] = keyEb;
    itor[5] = keyE;
    itor[6] = keyF;
    itor[7] = keyGb;
    itor[8] = keyG;
    itor[9] = keyAb;
    itor[10] = keyA;
    itor[11] = keyBb;
    itor[12] = keyB;
}

MidiGenAudioProcessorEditor::~MidiGenAudioProcessorEditor()
{
}

//==============================================================================
void MidiGenAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    
    for (auto note : scale.getNotes()) {
        if (note.getIsNatural()) {
            if (note.getInScale()) {
                g.setColour(notesColours["naturalActive"]);
                g.fillRect(itor[note.getKid()]);
            } else {
                g.setColour(notesColours["naturalNotActive"]);
                g.fillRect(itor[note.getKid()]);
            }
        }
    }
    
    for (auto note : scale.getNotes()) {
        if (!note.getIsNatural()) {
            if (note.getInScale()) {
                g.setColour(notesColours["sharpActive"]);
                g.fillRect(itor[note.getKid()]);
            } else {
                g.setColour(notesColours["sharpNotActive"]);
                g.fillRect(itor[note.getKid()]);
            }
        }
    }
}

void MidiGenAudioProcessorEditor::resized()
{
    keyDropdown.setBounds(10, 10, 60, 30);
    scaleDropdown.setBounds(90, 10, 100, 30);
    octDown.setBounds(10, 50, 50, 30);
}

void MidiGenAudioProcessorEditor::comboBoxChanged(juce::ComboBox *box) {
    std::cout << keyDropdown.getText() << " | " << scaleDropdown.getText() << std::endl;
    if (box == &keyDropdown || box == &scaleDropdown) {
        midiGen::Scale newScale(keyDropdown.getText().toStdString(),
                       scaleDropdown.getText().toStdString());
        scale = newScale;
        repaint();
    }
}

void MidiGenAudioProcessorEditor::setUpDropdown(juce::ComboBox &dropdown, std::vector<std::string> &options, int selectedOption, bool addListener) {
    
    for (int i = 0; i < options.size(); i++) {
        dropdown.addItem(options[i], i+1);
    }
    
    dropdown.setEditableText(false);
    dropdown.setSelectedId(selectedOption);
    
    if (addListener)
        dropdown.addListener(this);
}
