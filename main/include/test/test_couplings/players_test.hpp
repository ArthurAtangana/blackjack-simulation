#ifndef players_TEST_HPP
#define players_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "test/mock_models/mock_deck.hpp"
#include "src/coupled_models/players.hpp"

class playersTest: public cadmium::Coupled {
public:
    playersTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto playersModel = addComponent<players>("players");
        auto mockModel = addComponent<mockDeck>("mockDeck");
        auto mockModel2 = addComponent<mockDeck>("mockDeck2");

        addCoupling(mockModel->mockOut, playersModel->dealerIn);
        addCoupling(mockModel2->mockOut, playersModel->challengerIn);
    }
};

#endif

