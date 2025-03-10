#ifndef players_TEST_HPP
#define players_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "test/mock_models/mock_deck.hpp"
#include "src/coupled_models/players.hpp"
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "src/shared_data/cards.hpp"

class playersTest: public cadmium::Coupled {
public:
    playersTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto playersModel = addComponent<players>("players");
        auto dealerIn = addComponent<lib::IEStream<Cards>>("dealer cards", "main/include/test/inputs/player_inputs/dealer_in.txt");
        auto chalIn = addComponent<lib::IEStream<Cards>>("challenger cards", "main/include/test/inputs/threshold_inputs/challenger_in.txt");

        addCoupling(dealerIn->out, playersModel->dealerIn);
        addCoupling(chalIn->out, playersModel->challengerIn);
    }
};

#endif

