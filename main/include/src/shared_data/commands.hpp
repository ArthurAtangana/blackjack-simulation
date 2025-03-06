#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include<iostream>

enum class deckCommand {
    SHUFFLE,
    DRAW
};

inline std::ostream& operator<<(std::ostream& out, const deckCommand& command) {
    switch (command) {
        case deckCommand::SHUFFLE: out << "SHUFFLE"; break;
        case deckCommand::DRAW_CHALLENGER: out << "DRAW_CHALLENGER"; break;
        case deckCommand::DRAW_DEALER: out << "DRAW_DEALER"; break;
        default: out << "UNKNOWN"; break;
    }
    return out;
}

enum class decision{
    HIT,
    STAND
};

inline std::ostream& operator<<(std::ostream& out, const decision& command) {
    switch (command) {
        case decision::HIT: out << "HIT"; break;
        case decision::STAND: out << "STAND"; break;
        default: out << "UNKNOWN"; break;
    }
    return out;
}

enum class outcome{
    CONTINUE,
    WIN,
    LOSE,
    TIE
};

inline std::ostream& operator<<(std::ostream& out, const outcome& o){
    switch (o) {
        case outcome::CONTINUE: out << "CONTINUE"; break;
        case outcome::WIN: out << "WIN"; break;
        case outcome::LOSE: out << "LOSE"; break;
        case outcome::TIE: out << "TIE"; break;
        defautl: out << "UNKNOWN OUTCOME"; break;
    }
    return out;
}

#endif
