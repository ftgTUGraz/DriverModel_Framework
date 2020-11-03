#pragma once
#include "Parameters.h"
#include "EgoVehicle.h"
#include <iostream>
#include <vector>
#include <tuple>


/**
* NearbyVehicle class serves the purpose of storing all relevant attributes of the nearby vehicles. 
* Further developement may require adition of methods and new attributes.
*/
class NearbyVehicle
{
public:
	NearbyVehicle();
	NearbyVehicle(EgoVehicle ego);
	
	long turning_indicator;
	long vehicle_id = 0;
	double distance = 0.0;
	double relative_velocity = 0.0;
	double acceleration = 0.0;
	long relative_lane = 0;
	long relative_position = 0;
	long long color = RED;
	double desired_velocity = 0;
	double desired_lane_angle = 0;
	long data_rel_target_lane = 0;
	bool selected_as_target;

	/**
	* This method has to be called in capture method if nearby vehicle is to be selected as a target
	* vehicle. 
	*/
	void setAsTarget(bool val = true);

	/**
	* TODO: To be removed.
	*/
	std::tuple<int, int> calculateDistanceCol(double speed_ego);
};