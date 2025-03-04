#ifndef CHALLENGER_HPP
#define CHALLENGER_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "include/src/shared_data/cards.hpp"
#include "include/src/shared_data/commands.hpp"
#include "include/src/atomic_models/threshold-c.hpp"
#include "include/src/atomic_models/hand.hpp"

class challenger: public cadmium::Coupled {
public:
    Port<Cards> challengerCardIn;
    Port<decision> challengerDecisionOut;
    Port<int> scoreOut;

    challenger(const std::string& id) : Coupled(id) {
        // Create model instances
        auto thresholdModel = addComponent<thresholdC>("threshold");
        auto handModel = addComponent<hand>("hand");

        // Add ports
        challengerCardIn = addInPort<Cards>("cardIn");
        challengerDecisionOut = addOutPort<decision>("handValueOut");
        scoreOut = addOutPort<int>("scoreOut");

        // External
        addCoupling(this->challengerCardIn, handModel->cardIn);
        addCoupling(thresholdModel->decisionOut, this->challengerDecisionOut);
        addCoupling(thresholdModel->valueOut, this->scoreOut);

        // Internal
        addCoupling(handModel->handValueOut, thresholdModel->valueIn);
    }
};

#endif
