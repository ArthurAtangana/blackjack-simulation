#ifndef DECK_INPUT_TEST_HPP
#define DECK_INPUT_TEST_HPP

#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "src/atomic_models/deck.hpp"        //counter atomic model file
#include "src/shared_data/commands.hpp"
#include "src/shared_data/players.hpp"

using namespace cadmium;

struct deck_input_test: public Coupled {

  deck_input_test(const std::string& id): Coupled(id){
    auto deckModel = addComponent<deck>("deck model");
    auto deck_commands = addComponent<lib::IEStream<deckCommand>>("deck commands file", "deck_commands_test.txt");
    auto deck_players = addComponent<lib::IEStream<Players>>("deck players file", "deck_players_test.txt");

    //Internal Couplings
    addCoupling(deck_commands->out, deckModel->commandInPort);
        addCoupling(deck_players->out, deckModel->playerInPort);
  }

};


#endif
