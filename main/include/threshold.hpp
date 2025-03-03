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
        if(!valueIn->empty()){
            for (const auto& x: valueIn -> getBag()) {
                state.card = x;
            }
        }
        state.sigma = 0.1; // Not sure how to add variation yet.
    }

    void output(const thresholdState& state) const override {
    // Here, we can add message to output ports.
        decision res = state.threshold > state.comparisonValue ? HIT : STAND;

        decisionOut->addMessage(res);
    }

    void internalTransition(thresholdState& state) const override {
        // Reset
        state.comparisonValue = 0;
        state.sigma = infinity();
    }

    double timeAdvance(const thresholdState& state) const override {
        return state.sigma;
    }
};