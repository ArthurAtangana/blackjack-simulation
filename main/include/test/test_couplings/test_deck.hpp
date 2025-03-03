#ifndef TEST_DECK_HPP
#define TEST_DECK_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "deck.hpp"
#include "test/mock_models/mockController.hpp"

class test_deck: public cadmium::Coupled {
public:
    test_deck(const std::string& id) : Coupled(id) {
        // Create deck model instance
        auto deckModel = addComponent<deck>("deck");
        auto mockControllerModel = addComponent<mockController>("mockController");
        // couplings
        addCoupling(mockControllerModel->mockOut, deckModel->inPort);
    }
};

#endif
