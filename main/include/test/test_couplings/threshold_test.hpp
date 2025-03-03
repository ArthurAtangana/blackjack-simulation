#ifndef THRESHOLD_TEST_HPP
#define THRESHOLD_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "test/mock_models/mock_hand.hpp"
#include "src/atomic_models/threshold.hpp"

class ThresholdTest: public cadmium::Coupled {
public:
    ThresholdTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto thresholdModel = addComponent<threshold>("threshold");
        auto mockHandModel = addComponent<mockHand>("mockHand");

        addCoupling(mockHandModel->mockOut, thresholdModel->valueIn);
    }
};

#endif

