#ifndef THRESHOLD_TEST_HPP
#define THRESHOLD_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "mock_hand.hpp"

class ThresholdTest: public cadmium::Coupled {
public:
    ThresholdTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto threshold = addComponent<threshold>("threshold");
        auto mockHandModel = addComponent<mockHand>("mockHand");
    }
};

#endif

