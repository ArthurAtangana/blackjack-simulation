#ifndef thresholdD_HPP
#define thresholdD_HPP

using namespace cadmium;

#include <limits> //Required for infinity
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/shared_data/commands.hpp"

struct thresholdDState{
    int threshold;
    int comparisonValue;
    double sigma;
    // Defaults
explicit thresholdDState():
    threshold(17), // Not sure how to change this once at start of model
    comparisonValue(0),
    sigma(std::numeric_limits<double>::infinity()) {}
};
#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const thresholdDState& state) {
    out << "{threshold: " << state.threshold << ", comparisonValue: " << state.comparisonValue << "}";
    return out;
}
#endif


class thresholdD: public Atomic<thresholdDState> {
    // Port declaration
    public: Port<int> valueIn;
    public: Port<decision> decisionOut;
    public: Port<int> valueOut;

    
    thresholdD(const std::string id) : Atomic<thresholdDState>(id, thresholdDState()) {
        //Constructor of your atomic model. Initialize ports here.
        valueIn = addInPort<int>("valueIn");
        decisionOut = addOutPort<decision>("decisionOut");
        valueOut = addOutPort<int>("valueOut");
    }
    
    void externalTransition(thresholdDState& state, double e) const override {
        // we can read input messages from a port like this:
        if(!valueIn->empty()){
            const int lastInput = (valueIn -> getBag()).back();
            state.comparisonValue = lastInput;
        }
        state.sigma = 0.1; // Not sure how to add variation yet.
    }

    void output(const thresholdDState& state) const override {
    // Here, we can add message to output ports.
        decision res = state.threshold > state.comparisonValue ? HIT : STAND;

        decisionOut->addMessage(res);
        if(res == decision::STAND){
            valueOut->addMessage(state.comparisonValue);
        }
    }

    void internalTransition(thresholdDState& state) const override {
        // Reset
        state.comparisonValue = 0;
        state.sigma = std::numeric_limits<double>::infinity();
    }

    double timeAdvance(const thresholdDState& state) const override {
        return state.sigma;
    }
};

#endif