#ifndef players_HPP
#define players_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "include/src/shared_data/cards.hpp"
#include "include/src/shared_data/commands.hpp"
#include "include/src/atomic_models/threshold-d.hpp"
#include "include/src/atomic_models/hand.hpp"

class players: public cadmium::Coupled {
public:
    Port<Cards> dealerIn;
    Port<Cards> challengerIn;
    Port<decision> playerDecisionOut;

    players(const std::string& id) : Coupled(id) {
        // Create model instances
        auto dealerModel = addComponent<dealer>("dealer");
        auto challengerModel = addComponent<challenger>("challenger");

        // Add ports
        dealerIn = addInPort<Cards>("dealerIn");
        challengerIn = addInPort<Cards>("challengerIn");
        playerDecisionOut = addOutPort<decision>("playerDecisionOut");

        // External
        addCoupling(this->dealerIn, dealerModel->dealerCardIn);
        addCoupling(this->challengerIn, challengerModel->challengerCardIn);
        addCoupling(challengerModel->challengerDecisionOut, this->playerDecisionOut);
        addCoupling(dealerModel->dealerDecisionOut, this->playerDecisionOut);
    }
};

#endif
