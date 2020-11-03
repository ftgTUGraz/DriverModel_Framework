#pragma once
#include "Parameters.h"
#include <iostream>
#include <vector>
#include <Windows.h>


/**
* EgoVehicle class serves the purpose of storing all relevant attributes of the Ego vehicle. Further
* developement may require adition of methods and new attributes.
*/
class EgoVehicle
{ 
public:
	long	vehicle_id = 0;
	double	current_velocity = 0;
	double	acceleration = 0;
	long	turning_indicator = 0;
	double	distance_to_veh = 0;
	long    vehicle_color = RED;
	long    active_lane_change = 0;
	long    rel_target_lane = 0;
	double  desired_acceleration = 0.0;
	double  desired_lane_angle = 0.0;
	double  desired_velocity = 0.0;
	long	current_lane = 0;
	
};