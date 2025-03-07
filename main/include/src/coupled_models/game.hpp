#ifndef GAME_HPP
#define GAME_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "include/src/shared_data/cards.hpp"
#include "include/src/shared_data/commands.hpp"
#include "include/src/atomic_models/controller.hpp"
#include "include/src/atomic_models/deck.hpp"
#include "include/src/coupled_models/players.hpp"


class game: public cadmium::Coupled {
public:
    //Out ports
    Port<int> startOutPort;
    Port<outcome> outcomeOutPort;

    game(const std::string& id) : Coupled(id) {
        //Create model instances
        auto controllerModel = addComponent<controller>("controller");
        auto deckModel = addComponent<deck>("deck");
        auto playersModel = addComponent<players>("players");

        //Add Ports
        startOutPort = addOutPort<int>("startOutPort");
        outcomeOutPort = addOutPort<outcome>("outcomeOutPort");

        //External Couplings
        addCoupling(this->startOutPort, controllerModel->startInPort);
        addCoupling(controllerModel->outcomeOutPort, this->outcomeOutPort);

        //Internal Couplings
        //
        addCoupling(controllerModel->commandOutPort, deckModel->commandInPort);
        addCoupling(controllerModel->playerOutPort, deckModel->playerInPort);
        addCoupling(deckModel->challengerCardOutPort, playersModel->challengerIn);
        addCoupling(deckModel->dealerCardOutPort, playersModel->dealerIn);
        addCoupling(deckModel->hitOutPort, controllerModel->decisionInPort);
        addCoupling(playersModel->playerDecisionOut, controllerModel->decisionInPort);
    }

};

#endif
