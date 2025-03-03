#ifndef DECK_HPP
#define DECK_HPP

using namespace cadmium;

#include <random>
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

enum class DeckState {
    IDLE,
    SHUFFLE,
    DRAW
};
struct cardOut{
    int player_id;
    int card;
};
std::ostream& operator<<(std::ostream& out, const cardOut& co) {
    out << "{ player_id: " << co.player_id << ", card: " << co.card << " }";
    return out;
}

struct deckState {
    DeckState state;
    std::vector<int> cards;
    int current_player;
    double sigma;
    //you can have as many state variables as you want/ need

    explicit deckState(): sigma(1), state(DeckState::IDLE), current_player(-1) {
        for (int i = 1; i <= 52; i++){
            cards.push_back(i);
        }
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const deckState& state) {
    out << "State: ";
    switch (state.state) {
        case DeckState::DRAW: out << "DRAW"; break;
        case DeckState::SHUFFLE: out << "SHUFFLE"; break;
        case DeckState::IDLE: out << "IDLE"; break;
    }
    out << ", cards remaining: " << state.cards.size() << "\n";
    if (state.state == DeckState::SHUFFLE) {
        out << "Current Order: ";
        for (int c: state.cards) {
            out << c << ",";
        }
        out << "]\n";
    }
    return out;
}
#endif

class deck_model : public Atomic<deckState> {
    //Declare your ports here
    public:
    Port<int> shuffleInPort;
    Port<int> drawInPort;
    Port<cardOut> cardOutPort;
    Port<int> hitOutPort;

    deck_model(const std::string id) : Atomic<deckState>(id, deckState()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize input ports
        shuffleInPort = addInPort<int>("shuffleInPort");
        drawInPort = addInPort<int>("drawInPort");

        //Initialize output ports
        cardOutPort = addOutPort<cardOut>("cardOutPort");
        hitOutPort = addOutPort<int>("hitOutPort");
    }

    // inernal transition
    void internalTransition(deckState& state) const override {
        //your internal transition function goes here
        if (state.state == DeckState::DRAW) {
            // deck - 1
            state.cards.pop_back();
            // go back to idle
            state.state = DeckState::IDLE;
        }
        else if (state.state == DeckState::SHUFFLE) {
            //shuffle the cards
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(state.cards.begin(), state.cards.end(), g);
            // go back to idle
            state.state = DeckState::IDLE;
        }
    }

    // external transition
    void externalTransition(deckState& state, double e) const override {
        //your external transition function hoes here
        std::vector<int> drawInPortMsg = drawInPort->getBag();
        std::vector<int> shuffleInPortMsg = shuffleInPort->getBag();
        if (!drawInPortMsg.empty()){
            if (!state.cards.empty()){
                state.state = DeckState::DRAW;
            }
        }
        //if shuffle, shuffle deck and go idle
        else if (!shuffleInPortMsg.empty()) {
            if (!state.cards.empty()){
                state.state = DeckState::SHUFFLE;
            }
        }
    }
    
    
    // output function
    void output(const deckState& state) const override {
        //your output function goes here
        if (state.state == DeckState::DRAW && !state.cards.empty()){
            int drawnCard = state.cards.back();
            cardOutPort->addMessage({state.current_player, drawnCard});
        }
        else if (state.state == DeckState::SHUFFLE) {
            hitOutPort->addMessage(1);
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const deckState& state) const override {     
        switch (state.state) {
            case DeckState::DRAW: return 1;
            case DeckState::SHUFFLE: return 10;
            case DeckState::IDLE: return std::numeric_limits<double>::infinity();
        }
        return 1;
    }
};


#endif
