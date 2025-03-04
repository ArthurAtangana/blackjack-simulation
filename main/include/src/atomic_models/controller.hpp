#ifndef CONTROLLER_MODEL_HPP
#define CONTROLLER_MODEL_HPP

#include <cstring>
using namespace cadmium;

#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/shared_data/commands.hpp"
#include "src/shared_data/players.hpp"


// name of the states, as actions to be performed
enum controllerActions {
    START,
    HIT,
    STAND,
    CHECK_WINNER,
    IDLE
};

inline std::ostream& operator<<(std::ostream& out, const controllerActions& action){
    switch (o) {
        case controllerActions::START: out << "START"; break;
        case controllerActions::HIT: out << "HIT"; break;
        case controllerActions::STAND: out << "STAND"; break;
        case controllerActions::CHECK_WINNER: out << "CHECK_WINNER"; break;
        case controllerActions::IDLE: out << "IDLE"; break;
        defautl: out << "UNKNOWN STATE"; break;
    }
    return out;
}

struct controllerState {
    //State variables
    controllerActions state;
    Players current_player;
    int challenger_score;
    int dealer_score;

    //Instantiate
    explicit controllerState(): state(controllerActions::IDLE), current_player(Players::CHALLENGER), challenger_score(0), dealer_score(0) {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const controllerState& state) {
    out << "State: ";
    out << "Player Score: " << state.challenger_score << ", Dealer Score: " << state.dealer_score << "\n"; break;
    out << "Current player: " << state.current_player << "\n"; break;
    return out;
}
#endif

class controller : public Atomic<controllerState> {
    //Declare your ports here
    public:
    //in
    port<int> startPort;
    Port<decision> inPort;

    //out
    Port<deckCommand> commandOutPort;
    Port<outcome> outcomeOutPort;

    controller(const std::string id) : Atomic<controllerState>(id, controllerState()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize input ports
        startPort = addInPort<int>("startPort");
        inPort = addInPort<decision>("inPort");

        //Initialize output ports
        commandOutPort = addOutPort<deckCommand>("commandOutPort");
        outcomeOutPort = addOutPort<outcome>("outcomeOutPort");
    }

    // internal transition
    void internalTransition(controllerState& state) const override {
        // Start: starts the game with challenger playing first
        if (state.state == controllerActions::START) {
            state.current_player = Players::CHALLENGER;
            state.dealer_score = 0;
            state.challenger_score = 0;
            state.state = controllerActions::IDLE;
        }
        // HIT: go back to idle 
        else if (state.state == controllerActions::HIT){
            state.state = controllerActions::IDLE;
        }
        // STAND
        else if (state.state == controllerActions::STAND){
            if (state.current_player == Players::CHALLENGER){
                //check for bust
                if (state.challenger_score > 21){
                    state.state == controllerActions::CHECK_WINNER;
                }
                // next player (dealer)
                else {
                    state.current_player = Players::DEALER;
                }
            }
            else {
                state.state == controllerActions::CHECK_WINNER;
            }
        }
        // CHECK_WINNER
        else if (state.state == controllerActions::CHECK_WINNER) {
            state.state = controllerActions::IDLE;
        }
        //

    }


    // external transition
    void externalTransition(controllerState& state, double e) const override {
        //your external transition function goes here
        
    }

    // output function
    void output(const controllerState& state) const override {
        //your output function goes here
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const controllerState& state) const override {     

    }
}


}

#endif
