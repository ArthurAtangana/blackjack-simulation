#ifndef HAND_TEST_HPP
#define HAND_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/atomic_models/hand.hpp"
#include "cadmium/lib/iestream.hpp"          //iestream header

class handTestCumulative: public cadmium::Coupled {
public:
handTestCumulative(const std::string& id) : Coupled(id) {
        // Create model instances
        auto handModel = addComponent<hand>("hand");
        auto mockModel = addComponent<lib::IEStream<int>>("hand input", "main/include/test/inputs/hand_inputs/hand_in_cumulative.txt");

        addCoupling(mockModel->out, handModel->cardIn);
    }
};

#endif
