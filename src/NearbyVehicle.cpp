#include "NearbyVehicle.h"
#include "Utilities.h"


NearbyVehicle::NearbyVehicle(EgoVehicle ego)
{
	this->turning_indicator = ego.turning_indicator;
	this->acceleration = ego.desired_acceleration;
	this->desired_velocity = ego.desired_velocity;
	this->relative_velocity = 0;
	this->distance = 0;
	this->vehicle_id = ego.vehicle_id;
	this->relative_lane = 0;
	this->relative_position = 0;
	this->selected_as_target = false;
	this->desired_lane_angle = ego.desired_lane_angle;
	this->data_rel_target_lane = ego.rel_target_lane;
}

NearbyVehicle::NearbyVehicle()
{
	this->selected_as_target = false;
	this->turning_indicator = 0;
	this->desired_velocity = VEH_VELOCITY;
}

void NearbyVehicle::setAsTarget(bool val)
{
	this->selected_as_target = val;
}