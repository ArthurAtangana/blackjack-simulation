#ifndef DECK_MODEL_HPP
#define DECK_MODEL_HPP

using namespace cadmium;

#include <random>
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

struct deck_modelState {
    double sigma;
    //you can have as many state variables as you want/ need

    explicit deck_modelState(): sigma(1){
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const deck_modelState& state) {
    out  << "{" << state.sigma << "}";
    return out;
}
#endif

class atomic_model : public Atomic<deck_modelState> {
    public:

    //Declare your ports here

    atomic_model(const std::string id) : Atomic<deck_modelState>(id, deck_modelState()) {
        //Constructor of your atomic model. Initialize ports here.
    }

    // inernal transition
    void internalTransition(deck_modelState& state) const override {
        //your internal transition function goes here
        state.sigma += 1;
    }

    // external transition
    void externalTransition(deck_modelState& state, double e) const override {
        //your external transition function hoes here
    }
    
    
    // output function
    void output(const deck_modelState& state) const override {
        //your output function goes here
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const deck_modelState& state) const override {     
            return state.sigma;
    }
};


#endif
