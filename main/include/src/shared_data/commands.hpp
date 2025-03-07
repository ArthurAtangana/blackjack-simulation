#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include<iostream>

enum class deckCommand {
    SHUFFLE,
    DRAW
};
// Overloads out << operator for output
inline std::ostream& operator<<(std::ostream& out, const deckCommand& command) {
    switch (command) {
        case deckCommand::SHUFFLE: out << "SHUFFLE"; break;
        case deckCommand::DRAW: out << "DRAW"; break;
        default: out << "UNKNOWN"; break;
    }
    return out;
}
// Overload the >> operator for input
inline std::istream& operator>>(std::istream& in, deckCommand& command) {
    std::string value;
    in >> value;

    static const std::unordered_map<std::string, deckCommand> commandMap = {
        {"SHUFFLE", deckCommand::SHUFFLE},
        {"DRAW", deckCommand::DRAW}
    };

    auto it = commandMap.find(value);
    if (it != commandMap.end()) {
        command = it->second;
    } else {
        in.setstate(std::ios::failbit);  // Set fail state if invalid
    }

    return in;
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
