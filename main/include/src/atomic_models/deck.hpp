#ifndef DECK_HPP
#define DECK_HPP

using namespace cadmium;

#include <random>
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"
#include "include/src/shared_data/commands.hpp"

enum class DeckActions {
    IDLE,
    SHUFFLE,
    DRAW_DEALER,
    DRAW_CHALLENGER
};
std::ostream& operator<<(std::ostream& out, const DeckActions& action) {
    switch (action) {
        case DeckActions::IDLE: out << "IDLE"; break;
        case DeckActions::SHUFFLE: out << "SHUFFLE"; break;
        case DeckActions::DRAW_DEALER: out << "DRAW_DEALER"; break;
        case DeckActions::DRAW_CHALLENGER: out << "DRAW_CHALLENGER"; break;
        default: out << "UNKNOWN"; break;
    }
    return out;
}

struct cardOut{
    DeckActions command;
    int card;
};
std::ostream& operator<<(std::ostream& out, const cardOut& co) {
    out << "{ command: " << co.command << ", card: " << co.card << " }";
    return out;
}

struct deckState {
    //State variables
    DeckActions state;
    std::vector<int> cards;

    explicit deckState(): state(DeckActions::IDLE) {
        for (int i = 1; i <= 52; i++){
            cards.push_back(i);
        }
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const deckState& state) {
    out << "State: ";
    switch (state.state) {
        case DeckActions::DRAW_CHALLENGER: out << "DRAW_CHALLENGER"; break;
        case DeckActions::DRAW_DEALER: out << "DRAW_DEALER"; break;
        case DeckActions::SHUFFLE: out << "SHUFFLE"; break;
        case DeckActions::IDLE: out << "IDLE"; break;
    }
    out << ", cards remaining: " << state.cards.size() << "\n";
    out << "Current Order: [";
    for (int c: state.cards) {
        out << c << ",";
    }
    out << "]\n";
    return out;
}
#endif

class deck : public Atomic<deckState> {
    //Declare your ports here
    public:
    Port<Commands> inPort;
    Port<cardOut> cardOutPort;
    Port<Commands> hitOutPort;

    deck(const std::string id) : Atomic<deckState>(id, deckState()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize input ports
        inPort = addInPort<Commands>("inPort");

        //Initialize output ports
        cardOutPort = addOutPort<cardOut>("cardOutPort");
        hitOutPort = addOutPort<Commands>("hitOutPort");
    }

    // inernal transition
    void internalTransition(deckState& state) const override {
        //your internal transition function goes here
        if (state.state == DeckActions::DRAW_CHALLENGER || state.state == DeckActions::DRAW_DEALER) {
            // deck - 1
            state.cards.pop_back();
            // go back to idle
            state.state = DeckActions::IDLE;
        }
        else if (state.state == DeckActions::SHUFFLE) {
            //shuffle the cards
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(state.cards.begin(), state.cards.end(), g);
            // go back to idle
            state.state = DeckActions::IDLE;
        }
    }

    // external transition
    void externalTransition(deckState& state, double e) const override {
        //your external transition function hoes here
        std::vector<Commands> inPortMsg = inPort->getBag();
        if (!inPortMsg.empty()){
            switch (inPortMsg.back()) {
                case Commands::DRAW_CHALLENGER: state.state = DeckActions::DRAW_CHALLENGER; break;
                case Commands::DRAW_DEALER: state.state = DeckActions::DRAW_DEALER; break;
                case Commands::SHUFFLE: state.state = DeckActions::SHUFFLE; break;
            }
        }
    }
    
    
    // output function
    void output(const deckState& state) const override {
        //your output function goes here
        if (state.state == DeckActions::DRAW_DEALER && !state.cards.empty()){
            int drawnCard = state.cards.back();
            cardOutPort->addMessage({DeckActions::DRAW_DEALER, drawnCard});
        }
        else if (state.state == DeckActions::DRAW_CHALLENGER && !state.cards.empty()){
            int drawnCard = state.cards.back();
            cardOutPort->addMessage({DeckActions::DRAW_CHALLENGER, drawnCard});
        }
        else if (state.state == DeckActions::SHUFFLE) {
            hitOutPort->addMessage(Commands::HIT);
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const deckState& state) const override {     
        switch (state.state) {
            case DeckActions::DRAW_CHALLENGER: return 1; break;
            case DeckActions::DRAW_DEALER: return 1; break;
            case DeckActions::SHUFFLE: return 10; break;
            case DeckActions::IDLE: return std::numeric_limits<double>::infinity(); break;
        }
        return 1;
    }
};


#endif
