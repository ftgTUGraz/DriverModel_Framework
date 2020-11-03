#pragma once
#include "InjectorAbstract.h"

/**
* The Injector class is a subclass of InjectorAbstract and it provides a simple interface for the 
* user. It contains all the methods of the InjectorAbstract but moves the unnecessary code from the 
* user. The interface is comprised out of capture() and action() methods where user defines traffic
* situation required for the action to occure and actual action applied to the traffic.
*
* Capture and action methods are minimum requirement needed for the framework to run. Addition of 
* the user defined methods and variables is possible.
*/

class Injector : public InjectorAbstract
{
private:
	Injector();

	// user defined


public:
	static Injector& instance()
	{
		static Injector instance;
		return instance;
	}
	/**
	* Here all the vehicles can be accessed but none should be modified. This method serves to 
	* capture the current traffic and to check if the current traffic situation matches the 
	* requirements. If so, action can be started with startAction and only vehicles which are marked 
	* as 'selected_as_target' will be kept for the further manipulation. Example of that can be seen
	* in github repo on branch framework implementation. When startAction method is called, one 
	* argument has to be specified and the second one is optional. The first determines for how long 
	* action will take effect (specified inseconds), e.g. startAction(10). In this case, action will 
	* be valid for next 10 seconds. The second argument which is optional can be specified to make a 
	* delay between end of the action (e.g. 10 seconds period) and next call to the capture function 
	* in which we can trigger new action.
	*
	* During action execution, capture method is not executed at any time. Only when action is done 
	* + optional delay, capture is again executed.
	*/
	void capture();

	/**
	* Here the action which is to be executed on the individual car is to be specified. The first 
	* argument is the vehicle which values shall be manipulated and changed. Second argument 
	* provides us with the rest of the vehicles which are marked as targets (relevant) and they 
	* shall not be modified since there is no guarantee that changes made there will be propagated 
	* to the actual vehicle. Only changes made to the vehicle specified by the first argument are 
	* guaranteed to take an effect.
	*
	* Second argument serves the purpose of taking other vehicles into the consideration if needed 
	* for calculation/manipulation of the parameters of current vehicle.
	*
	* After time of the action exceedes, it is not executed until the new startAction in capture is 
	* called.
	*
	* @param[veh] the vehicle object to which action is to be applied.
	* @param[selected_vehicles] is a list of vehicles which are selected to be scheduled for an 
	* action. In this context it offers a possibility to access attributes of other selected 
	* vehicles. Changes applied to the objects of the list are not guaranteed to
	*/
	void action(NearbyVehicle* veh, const std::vector<NearbyVehicle*> selected_vehicles);

	// user defined
};

