#include "Chord.h"


namespace aiomfx {


Chord::Chord(int rootNoteId, Type type) : rootNoteId(rootNoteId), type(type) {
    if (type == Type::MAJOR) {
        intervals = std::vector<int>{0,4,7};
        name = Note::getNameFromNoteNumber(rootNoteId);
    } else if (type == Type::MINOR) {
        intervals = std::vector<int>{0,3,7};
        name = Note::getNameFromNoteNumber(rootNoteId)+"m";
    } else if (type == Type::DIM) {
        intervals = std::vector<int>{0,3,6};
        name = Note::getNameFromNoteNumber(rootNoteId)+"dim";
    } else if (type == Type::MAJOR_AUG) {
        intervals = std::vector<int>{0,4,8};
        name = Note::getNameFromNoteNumber(rootNoteId)+"aug";
    } else if (type == Type::MAJOR_SUS4) {
        intervals = std::vector<int>{0,5,7};
        name = Note::getNameFromNoteNumber(rootNoteId)+"sus4";
    } else if (type == Type::MAJOR_5) {
        intervals = std::vector<int>{0,7};
        name = Note::getNameFromNoteNumber(rootNoteId)+"5";
    } else if (type == Type::MAJOR_6) {
        intervals = std::vector<int>{0,4,7,9};
        name = Note::getNameFromNoteNumber(rootNoteId)+"6";
    } else if (type == Type::MINOR_6) {
        intervals = std::vector<int>{0,3,7,9};
        name = Note::getNameFromNoteNumber(rootNoteId)+"m6";
    } else if (type == Type::MAJOR_7TH) {
        intervals = std::vector<int>{0,4,7,11};
        name = Note::getNameFromNoteNumber(rootNoteId)+"maj7";
    } else if (type == Type::MAJOR_7) {
        intervals = std::vector<int>{0,4,7,10};
        name = Note::getNameFromNoteNumber(rootNoteId)+"7";
    } else if (type == Type::MAJOR_7_SUS4) {
        intervals = std::vector<int>{0,5,7,10};
        name = Note::getNameFromNoteNumber(rootNoteId)+"7sus4";
    } else if (type == Type::MINOR_7TH) {
        intervals = std::vector<int>{0,3,7,10};
        name = Note::getNameFromNoteNumber(rootNoteId)+"m7";
    } else if (type == Type::MAJOR_AUG_7TH) {
        intervals = std::vector<int>{0,4,8,10};
        name = Note::getNameFromNoteNumber(rootNoteId)+"aug7";
    } else if (type == Type::MINOR_MAJOR_7TH) {
        intervals = std::vector<int>{0,3,7,11};
        name = Note::getNameFromNoteNumber(rootNoteId)+"m(maj7)";
    } else if (type == Type::FULLY_DIM_7TH) {
        intervals = std::vector<int>{0,3,6,9};
        name = Note::getNameFromNoteNumber(rootNoteId)+"fdim7";
    } else if (type == Type::HALF_DIM_7TH) {
        intervals = std::vector<int>{0,3,6,10};
        name = Note::getNameFromNoteNumber(rootNoteId)+"hdim7";
    } else if (type == Type::MINOR_7TH_FLAT_5) {
        intervals = std::vector<int>{0,3,6,10};
        name = Note::getNameFromNoteNumber(rootNoteId)+"m7b5";
    } else if (type == Type::MAJOR_7TH_FLAT_5) {
        intervals = std::vector<int>{0,4,6,10};
        name = Note::getNameFromNoteNumber(rootNoteId)+"7b5";
    } else if (type == Type::SEVEN_SHARP_5) {
        intervals = std::vector<int>{0,4,8,10};
        name = Note::getNameFromNoteNumber(rootNoteId)+"7#5";
    } else if (type == Type::SEVEN_FLAT_9) {
        intervals = std::vector<int>{0,4,7,10,13};
        name = Note::getNameFromNoteNumber(rootNoteId)+"7b9";
    } else if (type == Type::SEVEN_SHARP_9) {
        intervals = std::vector<int>{0,4,7,10,15};
        name = Note::getNameFromNoteNumber(rootNoteId)+"7#9";
    } else if (type == Type::NINE) {
        intervals = std::vector<int>{0,4,7,10,14};
        name = Note::getNameFromNoteNumber(rootNoteId)+"9";
    } else if (type == Type::MAJOR_9TH) {
        intervals = std::vector<int>{0,4,7,11,14};
        name = Note::getNameFromNoteNumber(rootNoteId)+"maj9";
    } else if (type == Type::MAJOR_ADD_9) {
        intervals = std::vector<int>{0,4,7,14};
        name = Note::getNameFromNoteNumber(rootNoteId)+"(add9)";
    } else if (type == Type::MINOR_ADD_9) {
        intervals = std::vector<int>{0,3,7,13};
        name = Note::getNameFromNoteNumber(rootNoteId)+"(add 9)";
    } else if (type == Type::MAJOR_9TH_SHARP_11) {
        intervals = std::vector<int>{0,4,7,11,15,19};
        name = Note::getNameFromNoteNumber(rootNoteId)+"maj9#11";
    } else if (type == Type::SEVEN_SHARP_11) {
        intervals = std::vector<int>{0,4,7,10,14,18};
        name = Note::getNameFromNoteNumber(rootNoteId)+"7#11";
    } else if (type == Type::THIRTEEN) {
        intervals = std::vector<int>{0,4,7,10,14,17,21};
        name = Note::getNameFromNoteNumber(rootNoteId)+"13";
    }
}

} // namespace aiomfx
