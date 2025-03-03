#ifndef SAMPLE_TOP_HPP
#define SAMPLE_TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "deck.hpp"

using namespace cadmium;

struct deck_coupled : public Coupled {

    /**
     * Constructor function for the blinkySystem model.
     * @param id ID of the blinkySystem model.
     */
    deck_coupled(const std::string& id) : Coupled(id) {
        auto deck = addComponent<deck_model>("deck");
    }
};

#endif
