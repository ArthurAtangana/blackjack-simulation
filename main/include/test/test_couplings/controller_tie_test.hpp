#ifndef CONTROLLER_TIE_TEST_HPP
#define CONTROLLER_TIE_TEST_HPP


#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "src/atomic_models/controller.hpp"
#include "src/shared_data/commands.hpp"

using namespace cadmium;

class controller_tie_test: public cadmium::Coupled {
public:
    controller_tie_test(const std::string& id) : Coupled(id) {
        //Create model instances
        
        auto controllerModel = addComponent<controller>("controller");
        auto hand_value = addComponent<lib::IEStream<int>>("hand_value_tie", "main/include/test/inputs/controller_inputs/controller_hand_value_tie_input.txt");
        auto decision_input = addComponent<lib::IEStream<decision>>("decision_1", "main/include/test/inputs/controller_inputs/controller_decision_input_1.txt");
        auto start = addComponent<lib::IEStream<int>>("start_input", "main/include/test/inputs/controller_inputs/controller_start_input.txt");

        //Coupling
        addCoupling(start->out, controllerModel->startInPort);
        addCoupling(decision_input->out, controllerModel->decisionInPort);
        addCoupling(hand_value->out, controllerModel->handValueInPort);
    }
};
#endif
