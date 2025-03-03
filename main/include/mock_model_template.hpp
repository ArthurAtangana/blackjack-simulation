#ifndef mock/mockedModel/_HPP
#define mock/mockedModel/_HPP

using namespace cadmium;

#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

struct mock/mockedModel/State {
    //State variables
    std::vector</MOCK OUTPUT TYPE/> mockOutput;

    explicit mock/mockedModel/State() {
        // TODO: Initialize mockOutput
    }
};


class mock/mockedModel/ : public Atomic<mock/mockedModel/State> {
    //Declare your ports here
    public: Port</MOCK OUTPUT TYPE/> mockOut;

    mock/mockedModel/(const std::string id) : Atomic<mock/mockedModel/State>(id, mock/mockedModel/State()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize output ports
        mockOut = addOutPort</MOCK OUTPUT TYPE/>("mockOut");
    }

    // inernal transition
    void internalTransition(mock/mockedModel/State& state) const override {
        //your internal transition function goes here
        state.mockOutput.pop_back();
    }

    // external transition
    void externalTransition(mock/mockedModel/State& state, double e) const override {
        // Should never trigger, no input ports.
        return;
    }
    
    
    // output function
    void output(const mock/mockedModel/State& state) const override {
        //your output function goes here
        mockOut->addMessage(state.mockOutput.back());
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const mock/mockedModel/State& state) const override {     
        // 11 seconds between all inputs, highest TA in system is 10. Simple way to avoid race conditions
        return 11; // Should be based on a constant defined somewhere maybe.
    }
};


#endif
