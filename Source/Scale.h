#pragma once

#include <JuceHeader.h>

namespace aiomfx {

class Note {
    int id;
    std::string name;
    int octave;
    bool isNatural;
    bool inScale = false;
    int chordType;
    
public:
    static const int chordTypeMajor = 1;
    static const int chordTypeMajor5 = 2;
    static const int chordTypeMajorDim = 3;
    static const int chordTypeMajorNo3 = 4;
    static const int chordTypeMinor = 6;
    static const int chordTypeMinor5 = 7;
    static std::vector<std::string> notes;
    
    bool operator <(const Note& b) const
    {
        return id < b.getId();
    }
    
    Note(int kid, std::string name, bool isNatural) : id(kid), name(name), isNatural(isNatural) {};
    int getId() const {
        return id;
    }
    
    void setInScale(bool val) {
        inScale = val;
    }
    
    std::string getName() {
        return name;
    }
    
    bool getIsNatural() {
        return isNatural;
    }
    
    bool getIsInScale() {
        return inScale;
    }
    
    void setChordType(int val) {
        chordType = val;
    }
    
    int getChordType() {
        return chordType;
    }
    
    std::vector<int> getChordIntervals(int notes=3) {
        // Major chords
        
        if (notes == 2 && chordType == Note::chordTypeMajor)
            return {4};
        
        if (notes == 3 && chordType == Note::chordTypeMajor)
            return {4,7};
        
        if (notes == 4 && chordType == Note::chordTypeMajor)
            return {4,7,11};
        
        if (notes == 5 && chordType == Note::chordTypeMajor)
            return {4,7,11,14};
        
        // Major 5 chords
        
        if (notes == 2 && chordType == Note::chordTypeMajor5)
            return {4};
        
        if (notes == 3 && chordType == Note::chordTypeMajor5)
            return {4,8};
        
        if (notes == 4 && chordType == Note::chordTypeMajor5)
            return {4,8,9};
        
        if (notes == 5 && chordType == Note::chordTypeMajor5)
            return {4,8,9,13};
        
        // Major Dim chords
        
        if (notes == 2 && chordType == Note::chordTypeMajorDim)
            return {3};
        
        if (notes == 3 && chordType == Note::chordTypeMajorDim)
            return {3,6};
        
        if (notes == 4 && chordType == Note::chordTypeMajorDim)
            return {3,6,10};
        
        if (notes == 5 && chordType == Note::chordTypeMajorDim)
            return {3,6,10,13};
        
        // Major No3
        
        if (notes == 2 && chordType == Note::chordTypeMajorNo3)
            return {};
        
        if (notes == 3 && chordType == Note::chordTypeMajorNo3)
            return {7};
        
        if (notes == 4 && chordType == Note::chordTypeMajorNo3)
            return {7,10};
        
        if (notes == 5 && chordType == Note::chordTypeMajorNo3)
            return {7,14};
        
        // Minor chords
        
        if (notes == 2 && chordType == Note::chordTypeMinor)
            return {3};
        
        if (notes == 3 && chordType == Note::chordTypeMinor)
            return {3,7};
        
        if (notes == 4 && chordType == Note::chordTypeMinor)
            return {3,7,10};
        
        if (notes == 5 && chordType == Note::chordTypeMinor)
            return {3,7,10,14};
        
        if (notes == 3 && chordType == Note::chordTypeMinor5)
            return {3,8};
        
        if (notes == 4 && chordType == Note::chordTypeMinor5)
            return {3,8,10};
        
        if (notes == 5 && chordType == Note::chordTypeMinor5)
            return {3,8,10,13};
        
        return {1,2,3};
    }
};


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
