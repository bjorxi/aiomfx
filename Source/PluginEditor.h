/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "processors/scales_n_chords/Scale.h"
#include "LookAndFeel.h"


//==============================================================================
/**
*/
class AiomFXAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer,
private juce::ComboBox::Listener, private juce::ToggleButton::Listener, private juce::Slider::Listener
{
public:
    AiomFXAudioProcessorEditor (AiomFXAudioProcessor&);
    ~AiomFXAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox *box) override;
    void buttonClicked(juce::Button *button) override;
    void timerCallback() override;
    void sliderValueChanged(juce::Slider *slider) override;
    
    /**
     * @param x starting offset by X for drawing piano
     * @param y starting offset by Y for drawing piano
     */
    void drawScaleSectionPiano(int x, int y);

private:
    AiomFXAudioProcessor& audioProcessor;
    aiomfx::AiomFXLookAndFeel aiomFXLAF;
    
    // Min width and heigt of the plugin
    int minWidth = 600;
    int minHeight = 200;
    int maxWidth = 800;
    int maxHeight = 700;
    
    juce::ComboBox keyDropdown;
    juce::ComboBox scaleDropdown;
    juce::ToggleButton scaleSectionOctDownBtn;
    juce::ToggleButton scaleSectionOctUpBtn;
    juce::ToggleButton scaleSectionBypassBtn;
    juce::Label scaleSectionLabel;
    juce::Label scaleSectionKeyLabel;
    juce::Label scaleSectionScaleLabel;
    juce::ToggleButton scaleSectionChordsAreOnBtn;
    juce::Slider scaleSectionNumOfNotesSlider = juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                                             juce::Slider::TextEntryBoxPosition::TextBoxBelow);
    juce::Label scaleSectionNumOfNotesSliderLabel;
    juce::Label scaleSectionNumOfNotesSliderVal2;
    juce::Label scaleSectionNumOfNotesSliderVal3;
    juce::Label scaleSectionNumOfNotesSliderVal4;
    juce::Label scaleSectionNumOfNotesSliderVal5;
    
    juce::Rectangle<int> scaleSectionHeaderBorder;
    juce::Rectangle<int> scaleSectionPianoTopBorder;
    juce::Rectangle<int> scaleSectionPianoLeftBorder;
    juce::Rectangle<int> scaleSectionPianoRightBorder;
    juce::Rectangle<int> scaleSectionPianoBottomBorder;
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

    aiomfx::Scale scale;
    std::map<int, juce::Rectangle<int>> itor;
    void setUpDropdown(juce::ComboBox &dropdown, const std::vector<std::string> &options, int selectedOption, bool addListener);
    
    int currentNoteNumber;
    
    // Colors
    std::map<std::string, juce::Colour> notesColours{
        {"naturalNotActive", juce::Colour(199, 214, 201)},
        {"naturalActive", juce::Colour(146, 176, 149)},
        {"sharpNotActive", juce::Colour (134, 146, 136)},
        {"sharpActive", juce::Colour(88, 141, 97)},
    };
    
    juce::Colour scaleSectionPianoBorderColour = juce::Colour(100, 90, 85);
    
    juce::Colour backgroundColour = juce::Colour(255, 249, 245);
//    juce::Colour backgroundColour = juce::Colour(86, 100, 139);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AiomFXAudioProcessorEditor)
};
