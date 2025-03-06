#ifndef TEST_DECK_HPP
#define TEST_DECK_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/modeling/devs/atomic.hpp"
#include "src/atomic_models/controller.hpp"
#include "test/mock_models/mock_game.hpp"

class controllerTest: public cadmium::Coupled {
public:
    controllerTest(const std::string& id) : Coupled(id) {
        //Create model instances
        auto controllerModel = addComponent<controller>("controller");
        auto mockGameModel = addComponent<mock_game>("mock_game");

        //Coupling
        addCoupling(mockGameModel->startPort, controllerModel->startInPort);
        addCoupling(mockGameModel->decisionOutPort, controllerModel->decisionInPort);
        addCoupling(mockGameModel->handValueOutPort, controllerModel->handValueInPort);
    }
};
#endif
