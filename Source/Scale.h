#pragma once

#include <JuceHeader.h>

namespace midiGen {

class Scale {
    std::string key;
    std::string name;
    std::set<int> notesInScale;
    
    std::map<std::string, int> ktoi {
        {"C", 1},
        {"Db", 2},
        {"D", 3},
        {"Eb", 4},
        {"E", 5},
        {"F", 6},
        {"Gb", 7},
        {"G", 8},
        {"Ab", 9},
        {"A", 10},
        {"Bb", 11},
        {"B", 12}
    };
    void buildMajorScale();
    void buildMinorScale();
    
    
public:
    Scale();
    Scale(std::string key, std::string name);

    void paint(juce::Graphics& g);
    std::string toStr();
    std::set<int> getNotesInScale() {
        return notesInScale;
    };
};
}
