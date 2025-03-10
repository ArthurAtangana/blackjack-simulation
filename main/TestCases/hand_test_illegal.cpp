#include <limits>
#include "include/test/test_couplings/hand_test_illegal.hpp"
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;

int main() {		//starting point for simulation code
	
	auto model = std::make_shared<handTestIllegal>("handTestIllegal");
	auto rootCoordinator = RootCoordinator(model);
	// rootCoordinator.setLogger<STDOUTLogger>(";");
	rootCoordinator.setLogger<CSVLogger>("logs/hand_test_illegal.csv", ";");

	rootCoordinator.start();
	rootCoordinator.simulate(30.0); // Max time limit
	rootCoordinator.stop();	
	return 0;
}
