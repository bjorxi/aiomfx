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
        if (chordType == Note::chordTypeMajor) {
            return std::vector<int> {4,7};
        } else if (chordType == Note::chordTypeMajor5) {
            return std::vector<int> {4,8};
        } else if (chordType == Note::chordTypeMajorDim) {
            return std::vector<int> {3, 6};
        } else if (chordType == Note::chordTypeMajorNo3) {
            return std::vector<int> {7};
        } else if (chordType == Note::chordTypeMinor) {
            return std::vector<int> {3,7};
        } else if (chordType == Note::chordTypeMinor5) {
            return std::vector<int> {3, 8};
        }
        
        return {1,2,3};
    }
};


class Scale {
    std::string key;
    std::string name;
    
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
//    static const std::string scaleNameMajor;
//    static const std::string scaleNameMinor;
    
    static const std::vector<std::string> scalesNames;
    
    Scale() {};
    Scale(std::string key, std::string name);

    void paint(juce::Graphics& g);
    std::string toStr();
    
    std::vector<Note> getNotes() {
    return notes;
    }
    std::set<Note> getNotesInScale();
    std::set<Note> getNotesNotInScale();
    int adjustToScale(int noteNumber);
    std::vector<int> getChordIntervals(int noteNumber, int numOfNotes);
};
}
