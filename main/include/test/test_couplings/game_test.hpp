#ifndef GAME_TEST_HPP
#define GAME_TEST_HPP


#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "src/coupled_models/game.hpp"
#include "src/shared_data/commands.hpp"

using namespace cadmium;

class game_test: public cadmium::Coupled {
public:
    game_test(const std::string& id) : Coupled(id) {
        //Create model instances
        
        auto game_model = addComponent<game>("game");
        auto start = addComponent<lib::IEStream<int>>("start", "main/include/test/inputs/game_inputs/game_start_input.txt");

        //Coupling
        addCoupling(start->out, game_model->gameStartInPort);
    }
};
#endif
