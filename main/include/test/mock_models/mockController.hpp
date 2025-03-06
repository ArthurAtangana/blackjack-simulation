#ifndef MOCK_CONTROLLER_HPP
#define MOCK_CONTROLLER_HPP

using namespace cadmium;

#include <random>
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/shared_data/commands.hpp"
#include "src/shared_data/players.hpp"

struct mockControllerState {
    //State variables
    std::vector<deckCommand> mockCommands; // mockCommands to be sent to the deck
    std::vector<Players> players; // players that are being sent out the card
    double sigma;

    explicit mockControllerState(): sigma(11) {
        mockCommands.push_back(deckCommand::DRAW);
        mockCommands.push_back(deckCommand::DRAW);
        mockCommands.push_back(deckCommand::SHUFFLE);

        players.push_back(Players::DEALER);
        players.push_back(Players::CHALLENGER);
    }
};

std::ostream& operator<<(std::ostream& out, const mockControllerState& state) {
    out << "mockCommands: [";
    for (const auto& cmd : state.mockCommands) {
        out << cmd << ", ";  // Assumes `deckCommand` has an `operator<<`
    }
    out << "]";
    out << "mockPlayerCommands: [";
    for (const auto& p : state.players) {
        out << p << ", ";  // Assumes `deckCommand` has an `operator<<`
    }
    out << "]";
    return out;
}


class mockController : public Atomic<mockControllerState> {
    //Declare your ports here
    public:
    Port<deckCommand> commandOutPort;
    Port<Players> playerOutPort;

    mockController(const std::string id) : Atomic<mockControllerState>(id, mockControllerState()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize output ports
        commandOutPort = addOutPort<deckCommand>("commandOutPort");
        playerOutPort = addOutPort<Players>("playerOutPort");
    }

    // inernal transition
    void internalTransition(mockControllerState& state) const override {
        //your internal transition function goes here
        if (!state.mockCommands.empty()){
            if (state.mockCommands.back() == deckCommand::DRAW) {
                state.mockCommands.pop_back();
                state.players.pop_back();
            }
            else {
                state.mockCommands.pop_back();
            }
        }
        if (state.mockCommands.empty() && state.players.empty()){
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
        commandOutPort->addMessage(state.mockCommands.back());
        if (state.mockCommands.back() == deckCommand::DRAW) {
            playerOutPort->addMessage(state.players.back());
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const mockControllerState& state) const override {     
        return state.sigma; // Should be based on a constant defined somewhere maybe.
    }
};


#endif
