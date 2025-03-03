#ifndef mockHand_HPP
#define mockHand_HPP

using namespace cadmium;

#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

struct mockHandState {
    //State variables
    std::vector<int> mockOutput;

    explicit mockHandState() {
        // FIFO init, input in order
        mockOutput.push_back(18);
        mockOutput.push_back(10);
        mockOutput.push_back(44);
        mockOutput.push_back(22);
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const mockHandState& state) {
    out << "{mockOutput(num): " << state.mockOutput.size() << ", mockOutput(next): " << state.mockOutput.back() << "}";
    return out;
}
#endif



class mockHand : public Atomic<mockHandState> {
    //Declare your ports here
    public:
    Port<int> mockOut;

    mockHand(const std::string id) : Atomic<mockHandState>(id, mockHandState()) {
        //Constructor of your atomic model. Initialize ports here.
        //Initialize output ports
        mockOut = addOutPort<int>("mockOut");
    }

    // inernal transition
    void internalTransition(mockHandState& state) const override {
        //your internal transition function goes here
        state.mockOutput.pop_back();
    }

    // external transition
    void externalTransition(mockHandState& state, double e) const override {
        // Should never trigger, no input ports.
        return;
    }
    
    
    // output function
    void output(const mockHandState& state) const override {
        //your output function goes here
        mockOut->addMessage(state.mockOutput.back());
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const mockHandState& state) const override {     
        // 11 seconds between all inputs, highest TA in system is 10. Simple way to avoid race conditions
        return 11; // Should be based on a constant defined somewhere maybe.
    }
};


#endif
