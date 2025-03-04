#ifndef HAND_TEST_HPP
#define HAND_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "test/mock_models/mock_deck.hpp"
#include "src/atomic_models/hand.hpp"

class handTest: public cadmium::Coupled {
public:
    handTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto handModel = addComponent<hand>("hand");
        auto mockModel = addComponent<mockDeck>("mockDeck");

        addCoupling(mockModel->mockOut, handModel->cardIn);
    }
};

#endif
