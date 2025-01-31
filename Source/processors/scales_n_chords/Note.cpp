#include "Note.h"

namespace aiomfx {

std::vector<std::string> Note::notes = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};


std::string Note::getNameFromNoteNumber(int nodeNum) {
    return "C";
}

}
