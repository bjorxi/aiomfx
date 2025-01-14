#pragma once

#include <JuceHeader.h>

namespace midiGen {

#define MIN_NOTE_NUMBER 21;
#define MAX_NOTE_NUMBER 108;



extern std::map<int, int> CMajorMap;

class Note {
    int id;
    std::string name;
    int octave;
    bool isNatural;
    bool inScale = false;
    
public:
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
    
    bool getInScale() {
        return inScale;
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
    
    std::map<std::string, int> ktoi {
        {"C", 1},{"Db", 2},{"D", 3},{"Eb", 4},{"E", 5},{"F", 6},
        {"Gb", 7},{"G", 8},{"Ab", 9},{"A", 10},{"Bb", 11},{"B", 12}
    };
    void buildMajorScale();
    void buildMinorScale();
    
public:
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
};
}
