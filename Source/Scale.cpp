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
    int noteId = ktoi[key];
    
    notes[noteId].setInScale(true);
    
    for (auto interval : intervals) {
        noteId += interval;
        
        if (noteId > 12) {
            noteId = noteId % 12;
        }
        
        notes[noteId-1].setInScale(true);
    }
}

// W‑H‑W‑W‑H‑W‑W
void Scale::buildMinorScale() {
    std::vector<int> intervals {2,1,2,2,1,2,2};
    
    int noteId = ktoi[key];
    
    notes[noteId].setInScale(true);
    
    for (auto interval : intervals) {
        noteId += interval;
        
        if (noteId > 12) {
            noteId = noteId % 12;
        }
        
        notes[noteId-1].setInScale(true);
    }
}

std::string Scale::toStr() {
    std::stringstream s;
    
    for (auto note : notes)
        s << note.getKid() << " ";
    
    return s.str();
}

std::set<Note> Scale::getNotesInScale() {
    std::set<Note> out;
    
    for (auto note : notes) {
        if (note.getInScale())
            out.insert(note);
    }
    return out;
}

std::set<Note> Scale::getNotesNotInScale() {
    std::set<Note> out;
    
    for (auto note : notes) {
        if (!note.getInScale())
            out.insert(note);
    }
    return out;
}

}; // namespace midiGen
