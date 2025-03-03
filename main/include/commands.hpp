#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include<iostream>

enum class Commands {
    SHUFFLE,
    DRAW_CHALLENGER,
    DRAW_DEALER,
    HIT
};

inline std::ostream& operator<<(std::ostream& out, const Commands& command) {
    switch (command) {
        case Commands::HIT: out << "HIT"; break;
        case Commands::SHUFFLE: out << "SHUFFLE"; break;
        case Commands::DRAW_CHALLENGER: out << "DRAW_CHALLENGER"; break;
        case Commands::DRAW_DEALER: out << "DRAW_DEALER"; break;
        default: out << "UNKNOWN"; break;
    }
    return out;
}

#endif

