#ifndef dealer_TEST_HPP
#define dealer_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/coupled_models/dealer.hpp"
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "src/shared_data/cards.hpp"

class dealerTest: public cadmium::Coupled {
public:
    dealerTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto dealerModel = addComponent<dealer>("dealer");
        auto mockModel = addComponent<lib::IEStream<Cards>>("dealer in", "main/include/test/inputs/player_inputs/dealer_in.txt");

        addCoupling(mockModel->out, dealerModel->dealerCardIn);
    }
};

#endif

