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

### Example
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

### Example
Here is another example of *capture* and *action* implementation:

Here the traffic is not observed for the first 15 seconds of the simulation. After that, all vehicles currently located in front of our ego vehicle are selected as targets.
```
void Injector::capture()
{
	if (this->getCurrentSimTime() > 15)
	{
		auto n_vehicles = this->getVehiclesDownstream();

		for (auto& veh : n_vehicles)
		{
				veh->setAsTarget();
		}
		startAction(8, 8);
	}
}
...
```

```
void Injector::action(NearbyVehicle* veh, const std::vector<NearbyVehicle*> actionNveh)
{
	veh->color = YELLOW;
	veh->acceleration = -1;
}
```

This example in action can be seen in the following video:

[![DriverModel Framework presentation](https://img.youtube.com/vi/zmbCSA0oH9o/0.jpg)](https://www.youtube.com/watch?v=zmbCSA0oH9o)

In the video, the white vehicle is selected ego vehicle which ID can be specified in the Parameters file. After 15 seconds, the first action is triggered and all vehicles coloured in yellow are detected target vehicles in front of the ego. Action has a duration of 8 seconds during which target vehicles deaccelerate at the constant rate. After action expires, no new action is triggered for at least following 8 seconds from the previous action end due to startAction(8, 8).


## Practical Application

For those interested in one of the practical implementations of the DriverModel Framework, following presentation at IPG Automotive TECH WEEKS is recommended:

[![Deterministic Stress Testing Method](https://img.youtube.com/vi/47oo-10XZRA/0.jpg)](https://www.youtube.com/watch?v=47oo-10XZRA)