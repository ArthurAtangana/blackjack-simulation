#ifndef mockDeck_HPP
#define mockDeck_HPP

using namespace cadmium;

#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/shared_data/cards.hpp"

struct mockDeckState {
    //State variables
    std::vector<Cards> mockOutput;
    double sigma;

    explicit mockDeckState(): sigma(1){

        mockOutput.push_back(Cards::ACE);
        mockOutput.push_back(Cards::TWO);
        mockOutput.push_back(Cards::THREE);
        mockOutput.push_back(Cards::FOUR);
        mockOutput.push_back(Cards::FIVE);
        mockOutput.push_back(Cards::SIX);
        mockOutput.push_back(Cards::SEVEN);
        mockOutput.push_back(Cards::EIGHT);
        mockOutput.push_back(Cards::NINE);
        mockOutput.push_back(Cards::TEN);
        mockOutput.push_back(Cards::JACK);
        mockOutput.push_back(Cards::QUEEN);
        mockOutput.push_back(Cards::KING);
        // Convert to FIFO
        std::reverse(mockOutput.begin(), mockOutput.end());
    }
};
#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const mockDeckState& state) {
    out << "{mockOutput(num): " << state.mockOutput.size() << ", mockOutput(next): " << state.mockOutput.back() << "}";
    return out;
}
#endif


class mockDeck : public Atomic<mockDeckState> {
    //Declare your ports here
    public: Port<Cards> mockOut;

    mockDeck(const std::string id) : Atomic<mockDeckState>(id, mockDeckState()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize output ports
        mockOut = addOutPort<Cards>("mockOut");
    }

    // inernal transition
    void internalTransition(mockDeckState& state) const override {
        //your internal transition function goes here
        state.mockOutput.pop_back();
        if (state.mockOutput.empty()){
            state.sigma = std::numeric_limits<double>::infinity();;
        }
    }

    // external transition
    void externalTransition(mockDeckState& state, double e) const override {
        // Should never trigger, no input ports.
        return;
    }
    
    
    // output function
    void output(const mockDeckState& state) const override {
        //your output function goes here
        mockOut->addMessage(state.mockOutput.back());
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const mockDeckState& state) const override {     
        // 11 seconds between all inputs, highest TA in system is 10. Simple way to avoid race conditions
        return state.sigma; // Should be based on a constant defined somewhere maybe.
    }
};


#endif
