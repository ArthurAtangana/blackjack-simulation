#ifndef deck_test_HPP
#define deck_test_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/atomic_models/deck.hpp"
#include "test/mock_models/mockController.hpp"

class deck_test: public cadmium::Coupled {
public:
    deck_test(const std::string& id) : Coupled(id) {
        // Create deck model instance
        auto deckModel = addComponent<deck>("deck");
        auto mockControllerModel = addComponent<mockController>("mockController");
        // couplings
        addCoupling(mockControllerModel->commandOutPort, deckModel->commandInPort);
        addCoupling(mockControllerModel->playerOutPort, deckModel->playerInPort);
    }
};

#endif
