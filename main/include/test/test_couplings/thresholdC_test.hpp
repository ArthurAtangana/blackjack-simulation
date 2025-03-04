#ifndef THRESHOLD_TEST_HPP
#define THRESHOLD_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "test/mock_models/mock_hand.hpp"
#include "src/atomic_models/threshold-c.hpp"

class ThresholdDTest: public cadmium::Coupled {
public:
    ThresholdDTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto thresholdModel = addComponent<thresholdC>("threshold");
        auto mockHandModel = addComponent<mockHand>("mockHand");

        addCoupling(mockHandModel->mockOut, thresholdModel->valueIn);
    }
};

#endif

