#include <limits>
#include "include/test/test_couplings/controller_lose_test.hpp"
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;

int main() {		//starting point for simulation code
	
	auto model = std::make_shared<controller_lose_test> ("controller_lose_test");
	auto rootCoordinator = RootCoordinator(model);
	// rootCoordinator.setLogger<STDOUTLogger>(";");
	rootCoordinator.setLogger<CSVLogger>("logs/controller_lose.csv", ";");

	rootCoordinator.start();
	rootCoordinator.simulate(100.0); // Max time limit
	rootCoordinator.stop();	
	return 0;
}
