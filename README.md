# PTV Vissim DriverModel Framework

PTV Vissim DriverModel Framework is a framework for writing driver model dll used in PTV Vissim. It enables simplistic selection and manipulation of surrounding traffic.

**_DriverModel_DLL_ provided with the PTV Vissim is used as a base for the project.**

## Requirements
* PTV Vissim 10
* Visual Studio 2010 or newer
* Optional: for debugging adequate symbols has to be loaded
* Optional: for running in co-simulation with CarMaker, IPG CarMaker 8.1.1 required

## Usage

User has to implement InjectorAbstract class. The child class is already provided in Implementation filter of VS where *capture* and *action* methods have to be implemented. In *capture* user can select target vehicles and in *action* action which is to be performed on those vehicles is defined.

In the following example, all vehicles surrounding one Ego vehicle which have a velocity greater than 5 m/s are selected as a target. At the end of the capture method, the action is triggered.

```
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

...
```

To all vehicles selected in *capture* as a target, the following action will be applied. Colour of the vehicle will be changed to yellow and acceleration will be set to -2 m/s. Duration of action (in seconds) is given in *startAction* method called in *capture* as a first argument. The second argument defines the minimum pause between two actions.
```

void Injector::action(NearbyVehicle* veh, const std::vector<NearbyVehicle*> actionNveh)
{
	veh->color = YELLOW;
	veh->acceleration = -2;
}

```

Besides *getNearbyVehicles*, user can also query vehicles currently in front or at the back of selected Ego vehicle, by calling *getVehiclesDownstream* and *getVehiclesUpstream*. All attributes of target vehicle which can be manipulated can be seen in *NearbyVehicle* class.

After compiling x64 dll, the path to the external driver model has to be provided in Vissim for the desired vehicle type. In the case of co-simulation, it is enough to provide the path as described and to start the co-simulation.