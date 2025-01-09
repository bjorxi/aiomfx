#include "Scale.h"


namespace midiGen {

Scale::Scale(std::string key, std::string name) : key(key), name(name) {
    if (name == "Major")
        buildMajorScale();
    else if (name == "Minor")
        buildMinorScale();
}


void Scale::paint(juce::Graphics &g) {
    
}

// WWHWWWH
void Scale::buildMajorScale() {
    std::vector<int> intervals {2,2,1,2,2,2,1};
    int keyId = ktoi[key];
    
    for (auto interval : intervals) {
        keyId += interval;
        
        if (keyId <= 12) {
            notesInScale.insert(keyId);
        } else {
            notesInScale.insert(keyId % 12);
        }
    }
}

// W‑H‑W‑W‑H‑W‑W
void Scale::buildMinorScale() {
    std::vector<int> intervals {2,1,2,2,1,2,2};
    int keyId = ktoi[key];
    
    for (auto interval : intervals) {
        keyId += interval;
        
        if (keyId <= 12) {
            notesInScale.insert(keyId);
        } else {
            notesInScale.insert(keyId % 12);
        }
    }
}

std::string Scale::toStr() {
    std::stringstream s;
    
    for (auto note : notesInScale)
        s << note << " ";
    
    return s.str();
}

}; // namespace midiGen
