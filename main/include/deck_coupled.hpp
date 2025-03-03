#ifndef DECK_COUPLED_HPP
#define DECK_COUPLED_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "deck.hpp"

class deck_coupled: public cadmium::Coupled {
public:
    deck_coupled(const std::string& id) : Coupled(id) {
        // Create deck model instance
        auto deck = addComponent<deck_model>("deck");
    }
};

#endif

