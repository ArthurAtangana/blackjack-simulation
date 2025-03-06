#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include<iostream>

enum Players {
    CHALLENGER,
    DEALER
};

inline std::ostream& operator<<(std::ostream& out, const Players& p) {
    switch (p) {
        case Players::CHALLENGER: out << "CHALLENGER"; break;
        case Players::DEALER: out << "DEALER"; break;
        default: out << "UNKNOWN PLAYER"; break;
    }
    return out;
}
#endif
