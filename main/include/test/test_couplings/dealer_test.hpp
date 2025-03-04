#ifndef dealer_TEST_HPP
#define dealer_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "test/mock_models/mock_deck.hpp"
#include "src/coupled_models/dealer.hpp"

class dealerTest: public cadmium::Coupled {
public:
    dealerTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto dealerModel = addComponent<dealer>("dealer");
        auto mockModel = addComponent<mockDeck>("mockDeck");

        addCoupling(mockModel->mockOut, dealerModel->dealerCardIn);
    }
};

#endif

