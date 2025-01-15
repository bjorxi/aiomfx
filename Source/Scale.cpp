#include "Scale.h"


namespace midiGen {

std::map<int, int> CMajorMap = std::map<int, int> {
    {25, 24},
    {27, 26},
    {30, 29},
    {32, 31},
    {34, 33},
    {37, 36},
    {39, 38},
    {42, 41},
    {44, 43},
    {46, 45},
    {49, 48},
    {51, 50},
    {54, 53},
    {56, 55},
    {58, 57},
    {61, 60},
    {63, 62},
    {66, 65},
    {68, 67},
    {70, 69},
    {73, 72},
    {75, 74},
    {78, 77},
    {80, 79},
    {82, 80},
    {85, 84},
    {87, 86},
    {90, 89},
    {92, 91},
    {94, 93},
    {97, 96},
    {99, 98},
    {102, 101},
    {104, 103},
    {106, 105}
};


const std::string Scale::scaleNameMajor = "Major";
const std::string Scale::scaleNameMinor = "Minor";



Scale::Scale(std::string key, std::string name) : key(key), name(name) {
    if (name == "Major")
        buildMajorScale();
    else if (name == "Minor")
        buildMinorScale();
}


void Scale::paint(juce::Graphics &g) {
    
}


void Scale::buildScale(std::vector<int> &intervals, std::vector<int> &chordTypes) {
    int noteId = keyToNoteNum[key];
    notes[noteId].setInScale(true);
    notes[noteId].setChordType(chordTypes[0]);
    std::cout << "\n==Scale root: " << notes[noteId].getName() << std::endl;
    for (int i = 0; i < intervals.size(); i++) {
        noteId += intervals[i];
        std::cout << "\nInterval intervals[i] " << intervals[i] << std::endl;
        std::cout << "- Key: " << noteId << "; ChordType: " << chordTypes[i] << std::endl;
        if (noteId > 11) {
            noteId = noteId - 12;
        }
        
        notes[noteId].setInScale(true);
        notes[noteId].setChordType(chordTypes[i+1]);
        std::cout << "+Key: " << notes[noteId].getName() << "; ChordType: " << chordTypes[i+1] << std::endl;
    }
    
    buildScaleMap();
    
}

// WWHWWWH
void Scale::buildMajorScale() {
    std::vector<int> intervals {2,2,1,2,2,2};
    std::vector<int> chordTypes {
        Note::chordTypeMajor, Note::chordTypeMinor, Note::chordTypeMinor,
        Note::chordTypeMajor, Note::chordTypeMajor, Note::chordTypeMinor, Note::chordTypeMinor5};
    buildScale(intervals, chordTypes);
}

// W‑H‑W‑W‑H‑W‑W
void Scale::buildMinorScale() {
    std::vector<int> intervals {2,1,2,2,1,2};
    std::vector<int> chordTypes {
        Note::chordTypeMinor, Note::chordTypeMinor5, Note::chordTypeMajor,
        Note::chordTypeMinor, Note::chordTypeMinor, Note::chordTypeMajor, Note::chordTypeMajor};
    buildScale(intervals, chordTypes);
}

std::string Scale::toStr() {
    std::stringstream s;
    
    for (auto note : notes)
        s << note.getId() << " ";
    
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

int Scale::adjustToScale(int noteNumber) {
    if (scaleMapping.count(noteNumber) > 0)
        return scaleMapping[noteNumber];
    
    return noteNumber;
}

std::vector<int> Scale::getChordIntervals(int noteNumber, int numOfNotes=3) {
    noteNumber = noteNumber % 12;
    return notes[noteNumber].getChordIntervals(numOfNotes);
}

void Scale::buildScaleMap() {
    int minNoteNumber = 21;
    int maxNoteNumber = 108;
    std::set<int> notesNumsInScale;
    
    for (auto note : getNotesInScale()) {
        // note ids start with 1
        notesNumsInScale.insert(note.getId()-1);
        std::cout << "ScaleMapping::__noteNum is in scale " << note.getId() << std::endl;
    }
//    std::map<std::string, int> keyToFirstNoteNumInScale {
//        {"A", 21}, {"Bb", 22}, {"B", 23}, {"C", 24}, {"Cb", 25},
//        {"D", 26}, {"Db", 27}, {"E", 28}, {"F", 29}, {"Fb", 30},
//        {"G", 31}, {"Gb", 32}, {"A", 33}, {"Ab", 34}
//    };
    
    if (name == Scale::scaleNameMajor) {
        std::vector<int> intervals {2,2,1,2,2,2,1};
        
        for (int noteNum = minNoteNumber; noteNum <= maxNoteNumber; noteNum++) {
            
            if (notesNumsInScale.count(noteNum % 12) == 0) {
                scaleMapping[noteNum] = noteNum - 1;
                std::cout << "ScaleMapping:: noteNum is not in scale " << noteNum << std::endl;
            }
            std::cout << "ScaleMapping:: noteNum is in scale " << noteNum << std::endl;
        }
    }
    
    for (auto elem : scaleMapping) {
        std::cout << "ScaleMapping::Map " << elem.first << " => " << elem.second << std::endl;
    }
}

}; // namespace midiGen
