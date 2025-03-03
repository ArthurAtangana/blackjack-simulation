#ifndef MOCK_CONTROLLER_HPP
#define MOCK_CONTROLLER_HPP

using namespace cadmium;

#include <random>
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/shared_data/commands.hpp"

struct mockControllerState {
    //State variables
    std::vector<deckCommand> mockOutput;
    double sigma;

    explicit mockControllerState(): sigma(11) {
        // TODO: Initialize mockOutput
        mockOutput.push_back(deckCommand::DRAW_DEALER);
        mockOutput.push_back(deckCommand::DRAW_CHALLENGER);
        mockOutput.push_back(deckCommand::SHUFFLE);
    }
};

std::ostream& operator<<(std::ostream& out, const mockControllerState& state) {
    out << "mockOutput: [";
    for (const auto& cmd : state.mockOutput) {
        out << cmd << ", ";  // Assumes `deckCommand` has an `operator<<`
    }
    out << "]";
    return out;
}


class mockController : public Atomic<mockControllerState> {
    //Declare your ports here
    public:
    Port<deckCommand> mockOut;

    mockController(const std::string id) : Atomic<mockControllerState>(id, mockControllerState()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize output ports
        mockOut = addOutPort<deckCommand>("mockOut");
    }

    // inernal transition
    void internalTransition(mockControllerState& state) const override {
        //your internal transition function goes here
        if (!state.mockOutput.empty()){
            state.mockOutput.pop_back();
        }
        if (state.mockOutput.empty()){
            state.sigma = std::numeric_limits<double>::infinity();
        }
    }

    // external transition
    void externalTransition(mockControllerState& state, double e) const override {
        // Should never trigger, no input ports.
        return;
    }
    
    
    // output function
    void output(const mockControllerState& state) const override {
        //your output function goes here
        mockOut->addMessage(state.mockOutput.back());
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const mockControllerState& state) const override {     
        return state.sigma; // Should be based on a constant defined somewhere maybe.
    }
};


#endif