#ifndef thresholdC_HPP
#define thresholdC_HPP

using namespace cadmium;

#include <limits> //Required for infinity
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/shared_data/commands.hpp"

struct thresholdCState{
    int threshold;
    int comparisonValue;
    double sigma;
    // Defaults
explicit thresholdCState():
    threshold(15), // Not sure how to change this once at start of model, ok as is
    comparisonValue(0),
    sigma(std::numeric_limits<double>::infinity()) {}
};
#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const thresholdCState& state) {
    out << "{threshold: " << state.threshold << ", comparisonValue: " << state.comparisonValue << "}";
    return out;
}
#endif


class thresholdC: public Atomic<thresholdCState> {
    // Port declaration
    public: Port<int> valueIn;
    public: Port<decision> decisionOut;
    public: Port<int> valueOut;

    
    thresholdC(const std::string id) : Atomic<thresholdCState>(id, thresholdCState()) {
        //Constructor of your atomic model. Initialize ports here.
        valueIn = addInPort<int>("valueIn");
        decisionOut = addOutPort<decision>("decisionOut");
        valueOut = addOutPort<int>("valueOut");
    }
    
    void externalTransition(thresholdCState& state, double e) const override {
        // we can read input messages from a port like this:
        if(!valueIn->empty()){
            const int lastInput = (valueIn -> getBag()).back();
            state.comparisonValue = lastInput;
        }
        state.sigma = 0.1; // Not sure how to add variation yet.
    }

    void output(const thresholdCState& state) const override {
    // Here, we can add message to output ports.
        decision res = state.threshold > state.comparisonValue ? decision::HIT : decision::STAND;

        decisionOut->addMessage(res);
        if(res == decision::STAND){
            valueOut->addMessage(state.comparisonValue);
        }
    }

    void internalTransition(thresholdCState& state) const override {
        // Reset
        state.comparisonValue = 0;
        state.sigma = std::numeric_limits<double>::infinity();
    }

    double timeAdvance(const thresholdCState& state) const override {
        return state.sigma;
    }
};

#endif
