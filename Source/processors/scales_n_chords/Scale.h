#pragma once

#include <JuceHeader.h>

#include "Note.h"

namespace aiomfx {

class Scale {
    std::string key;
    std::string name;
    bool isActvie = true;
    
    bool octDown = false;
    bool chordsAreOn = true;
    int numOfNotesInChords = 3;
    
    std::vector<Note> notes {
        Note(1, "C", true), Note(2, "Db", false), Note(3, "D", true),
        Note(4, "Eb", false), Note(5, "E", true), Note(6, "F", true),
        Note(7, "Gb", false), Note(8, "G", true), Note(9, "Ab", false),
        Note(10, "A",  true), Note(11, "Bb",  false), Note(12, "B", true)
    };
    
    std::map<std::string, int> keyToNoteNum {
        {"C", 0},{"Db", 1},{"D", 2},{"Eb", 3},{"E", 4},{"F", 5},
        {"Gb", 6},{"G", 7},{"Ab", 8},{"A", 9},{"Bb", 10},{"B", 11}
    };
    
    std::map<int, int> scaleMapping;
    
    void buildMajorScale();
    void buildMinorScale();
    void buildLydianScale();
    void buildMyxolydianScale();
    void buildSpanishScale();
    void buildDorianScale();
    void buildPhrygianScale();
    void buildHarmonicMinorScale();
    void buildMelodicMinorScale();
    void buildMajorPentatonicScale();
    void buildMinorPentatonicScale();
    
    void buildScale(std::vector<int> &intervals, std::vector<int> &chordTypes);
    void buildScaleMap();
    
    
    
public:
    static const std::vector<std::string> scalesNames;
    
    Scale() {};
    Scale(std::string key, std::string name);
    
    /**
     * Returns a string representation of the scale. Used for debugging
     */
    std::string toStr();
    
    std::vector<Note> getNotes();
    
    /**
     * Returns notes that belong to the scale
     */
    std::set<Note> getNotesInScale();
    
    /**
     * Return notes that don't belog to the scale
     */
    std::set<Note> getNotesNotInScale();
    
    /**
     * Adjust a note to the scale if it doesn't belong to the current scale
     *
     * @param noteNumber - MIDI note number
     */
    int adjustToScale(int noteNumber);
    std::vector<int> getChordIntervals(int noteNumber, int numOfNotes);
    bool getIsActive();
    void setIsActive(bool val);
    void process(const juce::MidiMessageMetadata & metadata, juce::MidiBuffer& buffer);
    
    void setOctDown(bool val);
    bool getOctDown();
    
    void setChordsAreOn(bool val);
    bool getChordsAreOn();
    
    void setNumOfNotesInChords(int val);
    int getNumOfNotesInChords();
};
}
