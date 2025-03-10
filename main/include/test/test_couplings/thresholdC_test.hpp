#ifndef THRESHOLDC_TEST_HPP
#define THRESHOLDC_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "test/mock_models/mock_hand.hpp"
#include "src/atomic_models/threshold-c.hpp"

class ThresholdCTest: public cadmium::Coupled {
public:
    ThresholdCTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto thresholdModel = addComponent<thresholdC>("threshold-c");
        auto mockHandModel = addComponent<lib::IEStream<int>>("threshold-c_input", "main/include/test/inputs/controller_inputs/threshold_c_in.txt");

        addCoupling(mockHandModel->mockOut, thresholdModel->valueIn);
    }
};

#endif

