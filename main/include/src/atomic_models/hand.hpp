#ifndef HAND_MODEL_HPP
#define HAND_MODEL_HPP

using namespace cadmium;

#include <limits> //Required for infinity
#include "cadmium/modeling/devs/atomic.hpp"
#include "include/src/shared_data/cards.hpp"

struct handState{
    int value;
    Cards card;
    double sigma;
    // Defaults
explicit handState():
    value(0), 
    card(Cards::NO_CARD),
    sigma(std::numeric_limits<double>::infinity()) {}
};
#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const handState& state) {
    out << "{value: " << state.value << ", card: " << state.card << "}";
    return out;
}
#endif


int cardConverter(Cards c){
    return c > 10 ? 10 : c;
}

int nextValue(const handState& state){
    return state.value + cardConverter(state.card);
}

class hand: public Atomic<handState> {
    // Port declaration
    public: 
        Port<Cards> cardIn;
        Port<int> handValueOut;

    
        hand(const std::string id) : Atomic<handState>(id, handState()) {
        //Constructor of your atomic model. Initialize ports here.
        cardIn = addInPort<Cards>("cardIn");
        handValueOut = addOutPort<int>("handValueOut");
    }

    void externalTransition(handState& state, double e) const override {
        if(!cardIn->empty()){
            const auto lastInput = (cardIn -> getBag()).back();
            state.card = lastInput;
        }
        state.sigma = 0.1; // Not sure how to add variation yet.
    }

    void output(const handState& state) const override {
    // Send next hand value to output
        handValueOut->addMessage(nextValue(state));
    }

    void internalTransition(handState& state) const override {
        //your code block goes here
        state.value = nextValue(state);
        state.card = Cards::NO_CARD;
        state.sigma = std::numeric_limits<double>::infinity();
    }

    [[nodiscard]] double timeAdvance(const handState& state) const override {
        return state.sigma;
    }
};

#endif