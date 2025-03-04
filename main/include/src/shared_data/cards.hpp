#ifndef CARDS_HPP
#define CARDS_HPP

#include<iostream>

enum Cards {
    NO_CARD,
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

inline std::ostream& operator<<(std::ostream& out, const Cards& command) {
    switch (command) {
        case Cards::NO_CARD: out << "NO CARD"; break;
        case Cards::TWO: out << "2"; break;
        case Cards::THREE: out << "3"; break;
        case Cards::FOUR: out << "4"; break;
        case Cards::FIVE: out << "5"; break;
        case Cards::SIX: out << "6"; break;
        case Cards::SEVEN: out << "7"; break;
        case Cards::EIGHT: out << "8"; break;
        case Cards::NINE: out << "9"; break;
        case Cards::TEN: out << "10"; break;
        case Cards::JACK: out << "J"; break;
        case Cards::QUEEN: out << "Q"; break;
        case Cards::KING: out << "K"; break;
        case Cards::ACE: out << "A"; break;
        default: out << "UNKNOWN"; break;
    }
    return out;
}

#endif
