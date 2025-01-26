/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AiomFXAudioProcessorEditor::AiomFXAudioProcessorEditor (AiomFXAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), scale("C", "Major")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    audioProcessor.setScale(scale);
    setSize (minWidth, minHeight);
    setResizable(true, true);
    setResizeLimits (minWidth, minHeight, maxWidth, maxHeight);

    addAndMakeVisible(keyDropdown);
    addAndMakeVisible(scaleDropdown);
    addAndMakeVisible(scaleSectionLabel);
    addAndMakeVisible(scaleSectionKeyLabel);
    addAndMakeVisible(scaleSectionScaleLabel);
    addAndMakeVisible(scaleSectionBypassBtn);
    addAndMakeVisible(scaleSectionOctDownBtn);
    addAndMakeVisible(scaleSectionChordsAreOnBtn);
    addAndMakeVisible(scaleSectionNumOfNotesSlider);

    scaleSectionLabel.setFont (juce::Font (18.0f, juce::Font::bold));
    scaleSectionLabel.setText("Scales & Chords", juce::dontSendNotification);
    scaleSectionLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    scaleSectionKeyLabel.setText("Key", juce::dontSendNotification);
    scaleSectionKeyLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    scaleSectionScaleLabel.setText("Scale", juce::dontSendNotification);
    scaleSectionScaleLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    setUpDropdown(keyDropdown, aiomfx::Note::notes, 1, true);
    setUpDropdown(scaleDropdown, aiomfx::Scale::scalesNames, 1, true);

    scaleSectionBypassBtn.setTitle("Bypass");
    scaleSectionBypassBtn.setButtonText("Bypass");
    scaleSectionBypassBtn.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    scaleSectionBypassBtn.addListener(this);
    scaleSectionBypassBtn.setToggleable(true);

    if (audioProcessor.scale.getIsActive()) {
        scaleSectionBypassBtn.setState(juce::Button::ButtonState::buttonDown);
    }

    scaleSectionOctDownBtn.setTitle("Oct Down");
    scaleSectionOctDownBtn.setButtonText("Oct Down");
    scaleSectionOctDownBtn.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    scaleSectionOctDownBtn.addListener(this);
    scaleSectionOctDownBtn.setToggleable(true);

    scaleSectionChordsAreOnBtn.setTitle("Chords");
    scaleSectionChordsAreOnBtn.setButtonText("Chords");
    scaleSectionChordsAreOnBtn.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    scaleSectionChordsAreOnBtn.addListener(this);
    scaleSectionChordsAreOnBtn.setToggleable(true);
    scaleSectionChordsAreOnBtn.setToggleState(true, juce::dontSendNotification);

    // scaleSectionNumOfNotesSlider.setRange(2.0, 5.0, 1.0);
    juce::NormalisableRange<double> range (2.0, 5.0, 1.0, true); // Snap to integers
    scaleSectionNumOfNotesSlider.setNormalisableRange (range);
    scaleSectionNumOfNotesSlider.setValue(3.0);
    scaleSectionNumOfNotesSlider.setDoubleClickReturnValue(true, 0.0);
    scaleSectionNumOfNotesSlider.setTextBoxIsEditable(false);
    scaleSectionNumOfNotesSlider.setTextBoxStyle(
            juce::Slider::TextEntryBoxPosition::TextBoxBelow,
            true,
            20,
            20
    );
    scaleSectionNumOfNotesSlider.addListener(this);

    drawScaleSectionPiano(10, 90);

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

    juce::Timer::startTimer(1);
}

AiomFXAudioProcessorEditor::~AiomFXAudioProcessorEditor()
{
    juce::Timer::stopTimer();
}

//==============================================================================
void AiomFXAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(backgroundColour);

    g.setColour(scaleSectionPianoBorderColour);
    g.fillRect(scaleSectionPianoTopBorder);
    g.fillRect(scaleSectionPianoBottomBorder);
    g.fillRect(scaleSectionPianoLeftBorder);
    g.fillRect(scaleSectionPianoRightBorder);

    for (auto note : scale.getNotes()) {
        if (note.getIsNatural()) {
            if (note.getIsInScale()) {
                g.setColour(notesColours["naturalActive"]);
                g.fillRect(itor[note.getId()]);
            } else {
                g.setColour(notesColours["naturalNotActive"]);
                g.fillRect(itor[note.getId()]);
            }

            if (note.getId() == currentNoteNumber) {
                g.setColour(juce::Colours::orange);
                g.fillRect(itor[note.getId()]);
            }
        }
    }

    // sharps and flats have to be painted after the naturals because order of painting
    // matters in juce. this way shaprs/flat are drawn correctly on top of naturals
    for (auto note : scale.getNotes()) {
        if (!note.getIsNatural()) {
            if (note.getIsInScale()) {
                g.setColour(notesColours["sharpActive"]);
                g.fillRect(itor[note.getId()]);
            } else {
                g.setColour(notesColours["sharpNotActive"]);
                g.fillRect(itor[note.getId()]);
            }

            if (note.getId() == currentNoteNumber) {
                g.setColour(juce::Colours::orange);
                g.fillRect(itor[note.getId()]);
            }
        }
    }
}

void AiomFXAudioProcessorEditor::resized() {
    scaleSectionLabel.setBounds(10, 10, 200, 15);
    scaleSectionBypassBtn.setBounds(10, 200, 100, 50);
    scaleSectionOctDownBtn.setBounds(120, 200, 100, 50);
    scaleSectionChordsAreOnBtn.setBounds(230, 200, 100, 50);
    scaleSectionKeyLabel.setBounds(10, 30, 40, 15);
    scaleSectionNumOfNotesSlider.setBounds(200, 10, 80, 80);

    keyDropdown.setBounds(10, 50, 60, 30);
    scaleSectionScaleLabel.setBounds(90, 30, 100, 15);
    scaleDropdown.setBounds(90, 50, 100, 30);
}

void AiomFXAudioProcessorEditor::comboBoxChanged(juce::ComboBox *box) {
//    std::cout << keyDropdown.getText() << " | " << scaleDropdown.getText() << std::endl;
    if (box == &keyDropdown || box == &scaleDropdown) {
        aiomfx::Scale newScale(keyDropdown.getText().toStdString(),
                       scaleDropdown.getText().toStdString());
        scale = newScale;
        audioProcessor.setScale(newScale);
        repaint();
    }
}

void AiomFXAudioProcessorEditor::buttonClicked(juce::Button *btn) {
    bool isToggled = btn->getToggleState();

    if (btn == &scaleSectionOctDownBtn) {
        audioProcessor.scale.setOctDown(isToggled);
    } else if (btn == &scaleSectionBypassBtn) {
        audioProcessor.scale.setIsActive(!isToggled);
    } else if (btn == &scaleSectionChordsAreOnBtn) {
        audioProcessor.scale.setChordsAreOn(isToggled);
    }
}

void AiomFXAudioProcessorEditor::setUpDropdown(juce::ComboBox &dropdown, const std::vector<std::string> &options, int selectedOption, bool addListener) {

    for (int i = 0; i < options.size(); i++) {
        dropdown.addItem(options[i], i+1);
    }

    dropdown.setEditableText(false);
    dropdown.setSelectedId(selectedOption);

    if (addListener)
        dropdown.addListener(this);
}

void AiomFXAudioProcessorEditor::timerCallback() {
    currentNoteNumber = audioProcessor.getCurrentNoteNumber();
    if (currentNoteNumber > 0) {
        currentNoteNumber = currentNoteNumber % 12 + 1;
        repaint();
    }
}

void AiomFXAudioProcessorEditor::drawScaleSectionPiano(int x, int y) {
    int numOfNaturalNotes = 7;
    int naturalNotePadding = 1; // space between natural notes
    int allNaturalNotesPadding = (numOfNaturalNotes-1) * naturalNotePadding;
    int borderSize = 3;
    int scalePianoY = y+borderSize;
    int scalePianoX = x+borderSize;
    int scalePianoNaturalsHeight = 55;
    int scalePianoFlatsHeight = 25;
    int scalePianoNaturalsWidth = 25;
    int scalePianoFlatsWidth = 18;

    int bottomBorderY = scalePianoY + scalePianoNaturalsHeight;
    int leftRightBorderHeight = scalePianoNaturalsHeight + 2 * borderSize;
    int rightBorderX = x + borderSize + numOfNaturalNotes * scalePianoNaturalsWidth + allNaturalNotesPadding;
    int topBottomBorderWidth = 2 * borderSize + numOfNaturalNotes * scalePianoNaturalsWidth + allNaturalNotesPadding;

    scaleSectionPianoTopBorder = juce::Rectangle<int>(x, y, topBottomBorderWidth, borderSize);
    scaleSectionPianoBottomBorder = juce::Rectangle<int>(x, bottomBorderY, topBottomBorderWidth, borderSize);
    scaleSectionPianoLeftBorder = juce::Rectangle<int>(x, y, borderSize, leftRightBorderHeight);
    scaleSectionPianoRightBorder = juce::Rectangle<int>(rightBorderX, y, borderSize, leftRightBorderHeight);
    // Scale piano roll

    keyC = juce::Rectangle<int>(scalePianoX, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyDb = juce::Rectangle<int>(keyC.getX()+keyC.getWidth() - scalePianoFlatsWidth / 2, scalePianoY, scalePianoFlatsWidth, scalePianoFlatsHeight);
    keyD = juce::Rectangle<int>(scalePianoX+keyC.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyEb = juce::Rectangle<int>(keyD.getX()+keyD.getWidth() - scalePianoFlatsWidth / 2, scalePianoY, scalePianoFlatsWidth, scalePianoFlatsHeight);
    keyE = juce::Rectangle<int>(keyD.getX()+keyD.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyF = juce::Rectangle<int>(keyE.getX()+keyE.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyGb = juce::Rectangle<int>(keyF.getX()+keyF.getWidth() - scalePianoFlatsWidth / 2, scalePianoY, scalePianoFlatsWidth, scalePianoFlatsHeight);
    keyG = juce::Rectangle<int>(keyF.getX()+keyF.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyAb = juce::Rectangle<int>(keyG.getX()+keyG.getWidth() - scalePianoFlatsWidth / 2, scalePianoY, scalePianoFlatsWidth, scalePianoFlatsHeight);
    keyA = juce::Rectangle<int>(keyG.getX()+keyG.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyBb = juce::Rectangle<int>(keyA.getX()+keyA.getWidth() - scalePianoFlatsWidth / 2, scalePianoY, scalePianoFlatsWidth, scalePianoFlatsHeight);
    keyB = juce::Rectangle<int>(keyA.getX()+keyA.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
}

void AiomFXAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    std::cout << "Slider has been changed:" << slider->getValue() << std::endl;
    if (slider == &scaleSectionNumOfNotesSlider) {
        audioProcessor.scale.setNumOfNotesInChords((int)slider->getValue());
    }
}
