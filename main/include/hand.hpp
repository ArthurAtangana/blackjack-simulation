#ifndef HAND_MODEL_HPP
#define HAND_MODEL_HPP

using namespace cadmium;

#include <limits> //Required for infinity
#include "cadmium/modeling/devs/atomic.hpp"

struct handState{
    int value;
    String card;
    double sigma;
    // Defaults
explicit handState():
    value(0), 
    card(""),
    sigma(infinity()) {}
};

class hand: public Atomic<handState> {
    // Port declaration
    public Port</datatype/> /portName/;

    
    atomic_model(const std::string id) : Atomic<deck_modelState>(id, deck_modelState()) {
        //Constructor of your atomic model. Initialize ports here.
        /name of the port variable/ = addInPort</datatype/>("/portname/");
        /name of the port variable/ = addOutPort</datatype/>("/portname/");
    }

    void externalTransition(handState& state, double e) const override {
        // we can read input messages from a port like this:
        if(!/input port/->empty()){
            for (const auto& x: /input port/ -> getBag()) {
                // x is an input message!
            }
        }
        //your code block goes here
    }

    void output(const /model name/State& state) const override {
    // Here, we can add message to output ports.
        /output port/->addMessage(/value/);
    }

    void internalTransition(/model name/State& state) const override {
        //your code block goes here
    }

    double timeAdvance(const MyAtomicState& state) const override {
        return state.sigma;
    }
};

[[nodiscard]] double timeAdvance(const handState& state) const override {}
//  This method defines the time advance function of your model. It can read state variables and returns the time expiry of that state.
void confluentTransition(handState& state, double e) const override {}
// This method defines the confluent transition function of the model. It has access to the elapsed time, input, and can read and modify the state variables