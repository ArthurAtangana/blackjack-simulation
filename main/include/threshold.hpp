#ifndef THRESHOLD_HPP
#define THRESHOLD_HPP

using namespace cadmium;

#include <limits> //Required for infinity
#include "cadmium/modeling/devs/atomic.hpp"

enum decision{
    HIT,
    STAND
};

struct thresholdState{
    int threshold;
    int comparisonValue;
    double sigma;
    // Defaults
explicit thresholdState():
    value(17), 
    card(0),
    sigma(infinity()) {}
};

class threshold: public Atomic<thresholdState> {
    // Port declaration
    public Port<int> valueIn;
    public Port<decision> decisionOut;

    
    atomic_model(const std::string id) : Atomic<deck_modelState>(id, deck_modelState()) {
        //Constructor of your atomic model. Initialize ports here.
        valueIn = addInPort<int>("valueIn");
        decisionOut = addOutPort<decisionOut>("decisionOut");
    }
    
    void externalTransition(thresholdState& state, double e) const override {
        // we can read input messages from a port like this:
        if(!/input port/->empty()){
            for (const auto& x: /input port/ -> getBag()) {
                // x is an input message!
            }
        }
        //your code block goes here
    }

    void output(const thresholdState& state) const override {
    // Here, we can add message to output ports.
        /output port/->addMessage(/value/);
    }

    void internalTransition(thresholdState& state) const override {
        //your code block goes here
    }

    double timeAdvance(const thresholdState& state) const override {
        return state.sigma;
    }
};