#ifndef CONTROLLER_MODEL_HPP
#define CONTROLLER_MODEL_HPP

#include <cmath>
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
    IDLE
};

inline std::ostream& operator<<(std::ostream& out, const controllerActions& action){
    switch (action) {
        case controllerActions::START: out << "START"; break;
        case controllerActions::HIT: out << "HIT"; break;
        case controllerActions::STAND: out << "STAND"; break;
        case controllerActions::IDLE: out << "IDLE"; break;
        defautl: out << "UNKNOWN STATE"; break;
    }
    return out;
}

struct controllerState {
    //State variables
    Players current_player; // s1
    int challenger_score; // s2
    int dealer_score; // s3
    controllerActions state; // s4
    double sigma;

    //Instantiate
    explicit controllerState():
    current_player(Players::CHALLENGER),
    challenger_score(0),
    dealer_score(0),
    state(controllerActions::IDLE) {
        sigma = std::numeric_limits<double>::infinity();
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const controllerState& state) {
    out << "State(controller): Player Score= " << state.challenger_score << ", Dealer Score= " << state.dealer_score << "\n Current player: " << state.current_player << "\n";
    return out;
}
#endif

// check winner funtion
outcome check_winner(const controllerState& state) {
    if (state.dealer_score > 21) {
        return outcome::WIN;
    }
    else if (state.challenger_score > 21) {
        return outcome::LOSE;
        }
    else if (state.dealer_score != 0) {
        if (state.challenger_score > state.dealer_score) {
            return outcome::WIN;
        }
        else if (state.challenger_score < state.dealer_score) {
            return outcome::LOSE;
        }
        else {
            return outcome::TIE;
        }
    }
    return outcome::CONTINUE;
}

class controller : public Atomic<controllerState> {
    //Declare your ports here
    public:
    //in
    Port<int> startInPort;
    Port<decision> decisionInPort;
    Port<int> handValueInPort;

    //out
    Port<deckCommand> commandOutPort;
    Port<Players> playerOutPort;
    Port<outcome> outcomeOutPort;

    controller(const std::string id) : Atomic<controllerState>(id, controllerState()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize input ports
        startInPort = addInPort<int>("startInPort");
        decisionInPort = addInPort<decision>("decisionInPort");
        handValueInPort = addInPort<int>("handValueInPort");

        //Initialize output ports
        commandOutPort = addOutPort<deckCommand>("commandOutPort");
        playerOutPort = addOutPort<Players>("playerOutPort");
        outcomeOutPort = addOutPort<outcome>("outcomeOutPort");
    }

    // internal transition
    void internalTransition(controllerState& state) const override {
        // START: starts the game with challenger playing first
        if (state.state == controllerActions::START) {
            state.current_player = Players::CHALLENGER;
            state.dealer_score = 0;
            state.challenger_score = 0;
            state.state = controllerActions::IDLE;
            state.sigma = std::numeric_limits<double>::infinity();;
        }
        // HIT: go back to idle 
        else if (state.state == controllerActions::HIT){
            state.state = controllerActions::IDLE;
            state.sigma = std::numeric_limits<double>::infinity();;
        }
        // STAND:
        else if (state.state == controllerActions::STAND){
            if (check_winner(state) != outcome::CONTINUE){
                state.state == controllerActions::IDLE;
                state.sigma = std::numeric_limits<double>::infinity();;

            }
            else { // next player (DEALER)
                state.current_player = Players::DEALER;
                state.state = controllerActions::HIT;
            }
        }
    }


    // external transition
    void externalTransition(controllerState& state, double e) const override {
        // startInPort
        if (!startInPort->empty()) {
            state.state = controllerActions::START;
            state.sigma = 1;
        }
        // decision port
        else if (!decisionInPort->empty()) {
            const auto lastInput = (decisionInPort->getBag()).back();
            switch (lastInput) {
                case decision::HIT:
                    state.state = controllerActions::HIT; 
                    state.sigma = 1;
                    break;
                case decision::STAND:
                    if (!handValueInPort->empty()) {
                        if (state.current_player == Players::CHALLENGER) {
                            state.challenger_score = handValueInPort->getBag().back();
                        }
                        else if (state.current_player == Players::DEALER) {
                            state.dealer_score = handValueInPort->getBag().back();
                        }
                        state.state = controllerActions::STAND;
                        state.sigma = 1;
                    }

                    break;
            }
        }
    }

    // output function
    void output(const controllerState& state) const override {
        //your output function goes here
        if (state.state == controllerActions::START) {
                commandOutPort->addMessage(deckCommand::SHUFFLE);
        }
        else if (state.state == controllerActions::HIT) {
            commandOutPort->addMessage(deckCommand::DRAW);
            playerOutPort->addMessage(state.current_player);
        }
        else if (state.state == controllerActions::STAND){
            outcomeOutPort->addMessage(check_winner(state));
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const controllerState& state) const override {     
        return state.sigma;
    }
};

#endif
