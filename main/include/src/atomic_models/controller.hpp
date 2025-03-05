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
    CHECK_WINNER,
    IDLE
};

inline std::ostream& operator<<(std::ostream& out, const controllerActions& action){
    switch (action) {
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
    outcome result;
    double sigma;

    //Instantiate
    explicit controllerState(): state(controllerActions::IDLE), current_player(Players::CHALLENGER), challenger_score(0), dealer_score(0), result(outcome::CONTINUE) {
        sigma = std::numeric_limits<double>::infinity();
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const controllerState& state) {
    out << "State(controller): Player Score= " << state.challenger_score << ", Dealer Score= " << state.dealer_score << "\n Current player: " << state.current_player << "\n Outcome: " <<state.result << "\n";
    return out;
}
#endif

class controller : public Atomic<controllerState> {
    //Declare your ports here
    public:
    //in
    Port<int> startInPort;
    Port<decision> decisionInPort;
    Port<int> valueInPort;

    //out
    Port<deckCommand> commandOutPort;
    Port<outcome> outcomeOutPort;

    controller(const std::string id) : Atomic<controllerState>(id, controllerState()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize input ports
        startInPort = addInPort<int>("startInPort");
        decisionInPort = addInPort<decision>("decisionInPort");
        valueInPort = addInPort<int>("cardValueInPort");

        //Initialize output ports
        commandOutPort = addOutPort<deckCommand>("commandOutPort");
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
            if (state.current_player == Players::CHALLENGER){ // CHALLENGER STAND
                if (state.challenger_score > 21){ // Check if CHALLENGER bust
                    state.result = outcome::LOSE;
                    state.state = controllerActions::IDLE;
                    state.sigma = std::numeric_limits<double>::infinity();;
                }
                else { // next player (DEALER)
                    state.result = outcome::CONTINUE;
                    state.current_player = Players::DEALER;
                    state.state = controllerActions::HIT;
                }
            }
            else { // DEALER STAND
                if (state.dealer_score > 21) { // Check if DEALER bust -> CHALLENGER WIN
                    state.result = outcome::WIN;
                }
                else if (state.dealer_score < state.challenger_score) { // CHALLENGER win
                    state.result = outcome::WIN;
                }
                else if (state.dealer_score > state.challenger_score) { // CHALLENGER lose
                    state.result = outcome::LOSE;
                }
                else if (state.dealer_score == state.challenger_score) { // CHALLENGER tie
                    state.result = outcome::TIE;
                }
                state.state == controllerActions::IDLE;
                state.sigma = std::numeric_limits<double>::infinity();;
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
                    if (!valueInPort->empty()) {
                        if (state.current_player == Players::CHALLENGER) {
                            state.challenger_score = valueInPort->getBag().back();
                        }
                        else if (state.current_player == Players::DEALER) {
                            state.dealer_score = valueInPort->getBag().back();
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
            if (state.current_player == Players::CHALLENGER){
                commandOutPort->addMessage(deckCommand::DRAW_CHALLENGER);
            }
            else if (state.current_player == Players::DEALER){
                commandOutPort->addMessage(deckCommand::DRAW_DEALER);
            }
        }
        else if (state.state == controllerActions::STAND){
            if (state.dealer_score > 21) {
                outcomeOutPort->addMessage(outcome::WIN);
            }
            else if (state.challenger_score > 21) {
                outcomeOutPort->addMessage(outcome::LOSE);
            }
            else if (state.dealer_score != 0) {
                if (state.challenger_score > state.dealer_score) {
                    outcomeOutPort->addMessage(outcome::WIN);
                }
                else if (state.challenger_score < state.dealer_score) {
                    outcomeOutPort->addMessage(outcome::LOSE);
                }
                else {
                    outcomeOutPort->addMessage(outcome::TIE);
                }
            }
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const controllerState& state) const override {     
        return state.sigma;
    }
};

#endif
