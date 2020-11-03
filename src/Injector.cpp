#include "Injector.h"

/*
Here all Injector variables should be initialized
*/
Injector::Injector() :InjectorAbstract(EGO_ID)
{

}


void Injector::capture()
{
	auto n_vehicles = this->getNearbyVehicles();
	
	for (auto& veh : n_vehicles)
	{
		if (veh->relative_velocity > 5)
		{
			veh->setAsTarget();
		}
	}
	startAction(10, 5);
}

void Injector::action(NearbyVehicle* veh, const std::vector<NearbyVehicle*> actionNveh)
{
	veh->color = YELLOW;
	veh->acceleration = -2;
}


/*
Here user methods can be specified. Also take a look into capture.h. 

User is also allowed to write own classes which can specify functionality
and instance of it can be used within the capture.
*/