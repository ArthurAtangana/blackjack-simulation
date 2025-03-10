#include <limits>
#include "include/test/test_couplings/thresholdD_test.hpp"
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;

int main() {		//starting point for simulation code
	
	auto model = std::make_shared<ThresholdDTest>("threshold_d_test");
	auto rootCoordinator = RootCoordinator(model);
	// rootCoordinator.setLogger<STDOUTLogger>(";");
	rootCoordinator.setLogger<CSVLogger>("logs/threshold_d_test.csv", ";");

	rootCoordinator.start();
	rootCoordinator.simulate(30.0); // Max time limit
	rootCoordinator.stop();	
	return 0;
}
