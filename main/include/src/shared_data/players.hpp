#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include<iostream>

enum Players {
    CHALLENGER,
    DEALER
};
// Overloads out << operator for output
inline std::ostream& operator<<(std::ostream& out, const Players& p) {
    switch (p) {
        case Players::CHALLENGER: out << "CHALLENGER"; break;
        case Players::DEALER: out << "DEALER"; break;
        default: out << "UNKNOWN PLAYER"; break;
    }
    return out;
}
// Overloads in >> operator for input
inline std::istream& operator>>(std::istream& in, Players& player) {
    std::string value;
    in >> value;

    static const std::unordered_map<std::string, Players> playerMap = {
        {"CHALLENGER", Players::CHALLENGER},
        {"DEALER", Players::DEALER}
    };

    auto it = playerMap.find(value);
    if (it != playerMap.end()) {
        player = it->second;
    } else {
        in.setstate(std::ios::failbit);  // Invalid input
    }

    return in;
}

#endif
