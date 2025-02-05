#pragma once


#include <JuceHeader.h>

#include "Note.h"

namespace aiomfx {

class Chord {
public:
    // Available chord types
    enum Type {
        MAJOR,
        MAJOR_5,
        MAJOR_6,
        MAJOR_7,
        MAJOR_7TH,
        MAJOR_9TH,
        MAJOR_DIM,
        MAJOR_NO3,
        MAJOR_SUS4,
        MAJOR_7_SUS4,
        MAJOR_7TH_FLAT_5,
        MAJOR_ADD_9,
        MAJOR_9TH_SHARP_11,

        MAJOR_AUG,
        MAJOR_AUG_7TH,
        
        MINOR,
        MINOR_5,
        MINOR_7TH,
        MINOR_DIM,
        MINOR_NO3,
        MINOR_6,
        MINOR_7TH_FLAT_5,
        MINOR_ADD_9,

        MINOR_MAJOR_7TH,
        DIM,
        FULLY_DIM_7TH,
        HALF_DIM_7TH,
        SEVEN_SHARP_5,
        SEVEN_FLAT_9,
        SEVEN_SHARP_9,
        SEVEN_SHARP_11,
        NINE,
        THIRTEEN,
    };
    
    enum Inversion {
        FIRST,
        SECOND,
        THIRD,
        FOURTH,
    };
private:
    std::string name;
    int rootNoteId;
    std::vector<int> intervals;
    Type type;
public:
    Chord(int rootNoteId, Type type);
    Chord(Type type);
    std::string getName();
    std::vector<int> getIntervals();
    std::vector<int> invert(Inversion inversion);
    std::vector<int> makeOpen();    
};

}
