#ifndef THRESHOLD_HPP
#define THRESHOLD_HPP

using namespace cadmium;

#include <limits> //Required for infinity
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/shared_data/commands.hpp"

struct thresholdState{
    int threshold;
    int comparisonValue;
    double sigma;
    // Defaults
explicit thresholdState():
    threshold(18), // Not sure how to change this once at start of model
    comparisonValue(0),
    sigma(std::numeric_limits<double>::infinity()) {}
};
#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const thresholdState& state) {
    out << "{threshold: " << state.threshold << ", comparisonValue: " << state.comparisonValue << "}";
    return out;
}
#endif


class threshold: public Atomic<thresholdState> {
    // Port declaration
    public: Port<int> valueIn;
    public: Port<decision> decisionOut;
    public: Port<int> valueOut;

    
    threshold(const std::string id) : Atomic<thresholdState>(id, thresholdState()) {
        //Constructor of your atomic model. Initialize ports here.
        valueIn = addInPort<int>("valueIn");
        decisionOut = addOutPort<decision>("decisionOut");
        valueOut = addOutPort<int>("valueOut");
    }
    
    void externalTransition(thresholdState& state, double e) const override {
        // we can read input messages from a port like this:
        if(!valueIn->empty()){
            const int lastInput = (valueIn -> getBag()).back();
            state.comparisonValue = lastInput;
        }
        state.sigma = 0.1; // Not sure how to add variation yet.
    }

    void output(const thresholdState& state) const override {
    // Here, we can add message to output ports.
        decision res = state.threshold > state.comparisonValue ? HIT : STAND;

        decisionOut->addMessage(res);
        if(res == decision::STAND){
            valueOut->addMessage(state.comparisonValue);
        }
    }

    void internalTransition(thresholdState& state) const override {
        // Reset
        state.comparisonValue = 0;
        state.sigma = std::numeric_limits<double>::infinity();
    }

    double timeAdvance(const thresholdState& state) const override {
        return state.sigma;
    }
};

#endif