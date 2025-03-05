#ifndef THRESHOLDD_TEST_HPP
#define THRESHOLDD_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "test/mock_models/mock_hand.hpp"
#include "src/atomic_models/threshold-d.hpp"

class ThresholdDTest: public cadmium::Coupled {
public:
    ThresholdDTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto thresholdModel = addComponent<thresholdD>("threshold-d");
        auto mockHandModel = addComponent<mockHand>("mockHand");

        addCoupling(mockHandModel->mockOut, thresholdModel->valueIn);
    }
};

#endif

