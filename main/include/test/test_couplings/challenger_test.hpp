#ifndef CHALLENGER_TEST_HPP
#define CHALLENGER_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/coupled_models/challenger.hpp"
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "src/shared_data/cards.hpp"

class challengerTest: public cadmium::Coupled {
public:
    challengerTest(const std::string& id) : Coupled(id) {
        // Create model instances
        auto challengerModel = addComponent<challenger>("challenger");
        auto mockModel = addComponent<lib::IEStream<Cards>>("challenger in", "main/include/test/inputs/player_in/challenger_in.txt");

        addCoupling(mockModel->out, challengerModel->challengerCardIn);
    }
};

#endif

