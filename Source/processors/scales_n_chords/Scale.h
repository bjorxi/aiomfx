#pragma once

#include <JuceHeader.h>

#include "Note.h"
#include "Chord.h"

namespace aiomfx {

class Scale {
    std::string key;
    std::string name;
    bool isActvie = true;
    bool addOctDown = false;
    bool addOctUp = false;
    bool chordsAreOn = true;
    int numOfNotesInChords = 3;
    int inversion = 1;
    
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
     * @param numOfotes - number of the notes in the chord. 3 for a triad, 4 for a 7th chord, 5 for a 9th chord
     */
    int adjustToScale(int noteNumber);
    std::vector<int> getChordIntervals(int noteNumber, int numOfNotes);
    bool getIsActive();
    void setIsActive(bool val);
    void process(const juce::MidiMessageMetadata & metadata, juce::MidiBuffer& buffer);
    
    void setAddOctDown(bool val);
    bool getAddOctDown();
    
    void setAddOctUp(bool val);
    bool getAddOctUp();
    
    void setChordsAreOn(bool val);
    bool getChordsAreOn();
    
    void setNumOfNotesInChords(int val);
    int getNumOfNotesInChords();
    
    void setInversion(int val);
    int getInversion();
    
    void invertChord(std::deque<int> &notes, int inversion);
    
    /**
     * Sets a new value for the key and therefore rebuilds the scale
     *
     * @param newKey - new key name
     */
    void setKey(std::string newKey);
    
    /**
     * Sets a new value for the scale name and therefore rebuilds the scale
     *
     * @param newName - new scale name
     */
    void setName(std::string newName);
    
    /**
     * Sets new values for the key and scale and therefore rebuilds the scale
     *
     * @param newKey - new key name
     * @param newName - new scale name
     */
    void setKeyAndName(std::string newKey, std::string newName);
};
}
