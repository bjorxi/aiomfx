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
    static const int minNoteNumber = 21;
    static const int maxNoteNumber = 108;
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

}
