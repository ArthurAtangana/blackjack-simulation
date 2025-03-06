#ifndef MOCK_GAME_HPP
#define MOCK_GAME_HPP

using namespace cadmium;

#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/shared_data/commands.hpp"

//mock the game for controller tests
struct mock_gameState {
    //State variables
    std::vector<decision> decisionsOutput;
    std::vector<int> cardValueOutput;
    int start;
    double sigma;

    explicit mock_gameState(): start(1), sigma(1){
        // TODO: Initialize decisionsOutput
        decisionsOutput.push_back(decision::STAND);
        decisionsOutput.push_back(decision::HIT);
        // decisionsOutput.push_back(decision::HIT);
        decisionsOutput.push_back(decision::HIT);
        decisionsOutput.push_back(decision::STAND);
        decisionsOutput.push_back(decision::HIT);
        decisionsOutput.push_back(decision::HIT);
        decisionsOutput.push_back(decision::HIT);

        // DEALER
        cardValueOutput.push_back(20); // + 3 -> STAND 20
        // cardValueOutput.push_back(21); //
        // cardValueOuput.push_back(22); // bust
        // cardValueOutput.push_back(17); // + 2
        // cardValueOutput.push_back(15); // + 10
        // cardValueOutput.push_back(5); // 5
        // CHALLENGER
        // cardValueOutput.push_back(21); // + 4 -> STAND 21 -> C_WIN
        cardValueOutput.push_back(19); // + 2 -> STAND 19 -> C_LOSE
        // cardValueOutput.push_back(20); // + 3 -> STAND 20 -> TIE
        // cardValueOutput.push_back(22); // bust
        // cardValueOutput.push_back(17); // + 7
        // cardValueOutput.push_back(10); // + 2
        // cardValueOutput.push_back(8); // 8
        
    }
};
#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const mock_gameState& state) {
    if (state.start == 1) {
        out << "STARTING GAME\n";
    }
    else {
        out << "Next Decision: " << state.decisionsOutput.back() << "\n";
        out << "Decisions: [";
        for (const auto& dec : state.decisionsOutput) {
            out << dec << ", ";  // Assumes `deckCommand` has an `operator<<`
        }
        out << "]\n";
        out << "Hand Value: " << state.cardValueOutput.back() << "\n";
        out << "Hand inputs: [";
        for (const auto& card : state.cardValueOutput) {
            out << card << ", ";  // Assumes `deckCommand` has an `operator<<`
        }
    out << "]";
    }
    return out;

}
#endif


class mock_game : public Atomic<mock_gameState> {
    //Declare your ports here
    public:
    // Out Ports
    Port<int> startPort;
    Port<decision> decisionOutPort;
    Port<int> handValueOutPort;

    mock_game(const std::string id) : Atomic<mock_gameState>(id, mock_gameState()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize output ports
        startPort = addOutPort<int>("startOutPort");
        decisionOutPort = addOutPort<decision>("decisionOutPort");
        handValueOutPort = addOutPort<int>("handValueOutPort");

    }

    // inernal transition
    void internalTransition(mock_gameState& state) const override {
        //your internal transition function goes here
        if (state.start == 1) {
            state.start = 0;
        }
        else {
            if (state.decisionsOutput.back() == decision::STAND){
                state.cardValueOutput.pop_back();
            }
            state.decisionsOutput.pop_back();
        }
        if (state.decisionsOutput.empty() && state.cardValueOutput.empty()){
            state.sigma = std::numeric_limits<double>::infinity();;
        }
    }

    // external transition
    void externalTransition(mock_gameState& state, double e) const override {
        // Should never trigger, no input ports.
        return;
    }
    
    
    // output function
    void output(const mock_gameState& state) const override {
        //your output function goes here
        if (state.start == 1) {
            startPort->addMessage(state.start);
        }
        else {
            decisionOutPort->addMessage(state.decisionsOutput.back());
            if (state.decisionsOutput.back() == decision::STAND){
                handValueOutPort->addMessage(state.cardValueOutput.back());
            }
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const mock_gameState& state) const override {     
        // 11 seconds between all inputs, highest TA in system is 10. Simple way to avoid race conditions
        return state.sigma; // Should be based on a constant defined somewhere maybe.
    }
};


#endif
