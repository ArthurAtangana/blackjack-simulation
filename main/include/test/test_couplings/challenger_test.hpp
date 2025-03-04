#ifndef CHALLENGER_TEST_HPP
#define CHALLENGER_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "test/mock_models/mock_deck.hpp"
#include "src/coupled_models/challenger.hpp"

class challengerTest: public cadmium::Coupled {
public:
    challengerTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto challengerModel = addComponent<challenger>("challenger");
        auto mockModel = addComponent<mockDeck>("mockDeck");

        addCoupling(mockModel->mockOut, challengerModel->challengerCardIn);
    }
};

#endif

