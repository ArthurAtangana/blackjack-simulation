#ifndef TEST_CONTROLLER_HPP
#define TEST_CONTROLLER_HPP

#include "cadmium/modeling/devs/coupled.hpp"
// #include "cadmium/modeling/devs/atomic.hpp"
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "src/atomic_models/controller.hpp"
#include "test/mock_models/mock_game.hpp"
#include "src/shared_data/commands.hpp"

using namespace cadmium;

class controllerTest: public cadmium::Coupled {
public:
    controllerTest(const std::string& id) : Coupled(id) {
        //Create model instances
        
        auto controllerModel = addComponent<controller>("controller");
        // auto mockGameModel = addComponent<mock_game>("mock_game");
        auto hand_value = addComponent<lib::IEStream<int>>("hand_value_lose", "main/include/test/inputs/controller_inputs/controller_hand_value_lose_input.txt");
        auto decision_input = addComponent<lib::IEStream<decision>>("decision_1", "main/include/test/inputs/controller_inputs/controller_decision_input_1.txt");
        auto start = addComponent<lib::IEStream<int>>("start_input", "main/include/test/inputs/controller_inputs/controller_start_input.txt");

        //Coupling
        addCoupling(start->out, controllerModel->startInPort);
        addCoupling(decision_input->out, controllerModel->decisionInPort);
        addCoupling(hand_value->out, controllerModel->handValueInPort);
        // addCoupling(mockGameModel->startPort, controllerModel->startInPort);
        // addCoupling(mockGameModel->decisionOutPort, controllerModel->decisionInPort);
        // addCoupling(mockGameModel->handValueOutPort, controllerModel->handValueInPort);
    }
};
#endif
