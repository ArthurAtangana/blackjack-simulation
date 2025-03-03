#ifndef THRESHOLD_TEST_HPP
#define THRESHOLD_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "threshold.hpp"

class ThersholdTest: public cadmium::Coupled {
public:
    ThersholdTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto threshold = addComponent<threshold>("threshold");
        auto mockHand = addComponent<mockHand>("mockHand");
    }
};

#endif

