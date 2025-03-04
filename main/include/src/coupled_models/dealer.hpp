#ifndef dealer_HPP
#define dealer_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "include/src/shared_data/cards.hpp"
#include "include/src/shared_data/commands.hpp"
#include "include/src/atomic_models/threshold-d.hpp"
#include "include/src/atomic_models/hand.hpp"

class dealer: public cadmium::Coupled {
public:
    Port<Cards> dealerCardIn;
    Port<decision> dealerDecisionOut;
    Port<int> scoreOut;

    dealer(const std::string& id) : Coupled(id) {
        // Create model instances
        auto thresholdModel = addComponent<thresholdD>("threshold-d");
        auto handModel = addComponent<hand>("hand");

        // Add ports
        dealerCardIn = addInPort<Cards>("cardIn");
        dealerDecisionOut = addOutPort<decision>("handValueOut");
        scoreOut = addOutPort<int>("scoreOut");

        // External
        addCoupling(this->dealerCardIn, handModel->cardIn);
        addCoupling(thresholdModel->decisionOut, this->dealerDecisionOut);
        addCoupling(thresholdModel->valueOut, this->scoreOut);

        // Internal
        addCoupling(handModel->handValueOut, thresholdModel->valueIn);
    }
};

#endif
