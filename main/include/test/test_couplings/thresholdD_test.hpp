#ifndef THRESHOLDD_TEST_HPP
#define THRESHOLDD_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/atomic_models/threshold-d.hpp"
#include "cadmium/lib/iestream.hpp"          //iestream header

class ThresholdDTest: public cadmium::Coupled {
public:
    ThresholdDTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto thresholdModel = addComponent<thresholdD>("threshold-d");
        auto mockHandModel = addComponent<lib::IEStream<int>>("threshold-d-input", "main/include/test/inputs/threshold_inputs/threshold_d_in.txt");

        addCoupling(mockHandModel->out, thresholdModel->valueIn);
    }
};

#endif

