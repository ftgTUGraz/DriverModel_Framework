#include "InjectorAbstract.h"

InjectorAbstract::InjectorAbstract(long int ego_id)
{
	this->ego_found = false;
	this->current_target_id = 0;
	this->curr_nb_veh_id = 0;
	this->data_injected = false;
	this->current_sim_time = 0;

	this->num_of_lanes = 0;

	this->duration = 0;
	this->start_time = 0;
	this->deadline = 0;

	this->action_id = -1;
	this->pause = 0;
	this->pause_deadline = 0;
	this->pause_set = false;
	this->current_nearby_veh = nullptr;
}

int InjectorAbstract::setInjectorData(long type, long index1, long index2, long long_value, 
															double double_value, char* string_value)
{
	std::ostringstream os;
	long current_lane = LONG_MAX;
	long current_position = LONG_MAX;

	switch (type) {
	case DRIVER_DATA_PATH:
	case DRIVER_DATA_TIMESTEP:
	case DRIVER_DATA_TIME:
		this->current_sim_time = double_value;
		return 1;
	case DRIVER_DATA_USE_UDA:
		return 0; 
	case DRIVER_DATA_VEH_ID:
		utilities::printDebug(std::ostringstream() << "VEH ID: " << long_value << "\n");
		current_target_id = long_value;
		current_target.vehicle_id = current_target_id;
		data_injected = false;
		action_id = -1;

		if (current_target_id == EGO_ID)
		{
			ego_found = true;
		}
		else
		{
			ego_found = false;
		}
		return 1;
	case DRIVER_DATA_VEH_LANE:
		current_target.current_lane = long_value;
	case DRIVER_DATA_VEH_ODOMETER:
	case DRIVER_DATA_VEH_LANE_ANGLE:
	case DRIVER_DATA_VEH_LATERAL_POSITION:
		return 1;
	case DRIVER_DATA_VEH_VELOCITY:
		current_target.current_velocity = double_value;
		return 1;
	case DRIVER_DATA_VEH_ACCELERATION:
		current_target.acceleration = double_value;
		return 1;
	case DRIVER_DATA_VEH_LENGTH:
	case DRIVER_DATA_VEH_WIDTH:
	case DRIVER_DATA_VEH_WEIGHT:
	case DRIVER_DATA_VEH_MAX_ACCELERATION:
		return 1;
	case DRIVER_DATA_VEH_TURNING_INDICATOR:
		current_target.turning_indicator = long_value;
		return 1;
	case DRIVER_DATA_VEH_CATEGORY:
	case DRIVER_DATA_VEH_PREFERRED_REL_LANE:
	case DRIVER_DATA_VEH_USE_PREFERRED_LANE:
		return 1;
	case DRIVER_DATA_VEH_DESIRED_VELOCITY:
		current_target.desired_velocity = double_value;
		return 1;
	case DRIVER_DATA_VEH_X_COORDINATE:
	case DRIVER_DATA_VEH_Y_COORDINATE:
	case DRIVER_DATA_VEH_Z_COORDINATE:
	case DRIVER_DATA_VEH_REAR_X_COORDINATE:
	case DRIVER_DATA_VEH_REAR_Y_COORDINATE:
	case DRIVER_DATA_VEH_REAR_Z_COORDINATE:
	case DRIVER_DATA_VEH_TYPE:
		return 1;
	case DRIVER_DATA_VEH_COLOR:
		current_target.vehicle_color = long_value;
		return 1;
	case DRIVER_DATA_VEH_CURRENT_LINK:
		return 0; // (To avoid getting sent lots of DRIVER_DATA_VEH_NEXT_LINKS messages) 
				  // Must return 1 if these messages are to be sent from VISSIM!         
	case DRIVER_DATA_VEH_NEXT_LINKS:
	case DRIVER_DATA_VEH_ACTIVE_LANE_CHANGE:
	case DRIVER_DATA_VEH_REL_TARGET_LANE:
	case DRIVER_DATA_VEH_INTAC_STATE:
	case DRIVER_DATA_VEH_INTAC_TARGET_TYPE:
	case DRIVER_DATA_VEH_INTAC_TARGET_ID:
	case DRIVER_DATA_VEH_INTAC_HEADWAY:
	case DRIVER_DATA_VEH_UDA:
		//return 1;
	case DRIVER_DATA_NVEH_ID:
		curr_nb_veh_id = long_value;
		current_lane = index1;
		current_position = index2;

		current_nearby_veh = new NearbyVehicle;
		current_nearby_veh->vehicle_id = long_value;
		current_nearby_veh->relative_lane = index1;
		current_nearby_veh->relative_position = index2;
		return 1;
	case DRIVER_DATA_NVEH_LANE_ANGLE:
	case DRIVER_DATA_NVEH_LATERAL_POSITION:
		return 1;
	case DRIVER_DATA_NVEH_DISTANCE:
		current_nearby_veh->distance = double_value; // Distance is negative if vehicle upstream
		return 1;
	case DRIVER_DATA_NVEH_REL_VELOCITY:
		current_nearby_veh->relative_velocity = double_value; // nb vehicle speed difference
		return 1;
	case DRIVER_DATA_NVEH_ACCELERATION:
		current_nearby_veh->acceleration = double_value;
		if (curr_nb_veh_id != -1 && ego_found)
		{
			nearby_vehicles_tmp.insert(std::pair<long int, NearbyVehicle*>(curr_nb_veh_id, 
																			   current_nearby_veh));
		}
		return 1;
	case DRIVER_DATA_NVEH_LENGTH:
		return 1;
	case DRIVER_DATA_NVEH_WIDTH:
	case DRIVER_DATA_NVEH_WEIGHT:
	case DRIVER_DATA_NVEH_TURNING_INDICATOR:
		current_nearby_veh->turning_indicator = long_value;
		return 1;
	case DRIVER_DATA_NVEH_CATEGORY:
	case DRIVER_DATA_NVEH_LANE_CHANGE:
	case DRIVER_DATA_NVEH_TYPE:
	case DRIVER_DATA_NVEH_UDA:
	case DRIVER_DATA_NVEH_X_COORDINATE:
	case DRIVER_DATA_NVEH_Y_COORDINATE:
	case DRIVER_DATA_NVEH_Z_COORDINATE:
	case DRIVER_DATA_NVEH_REAR_X_COORDINATE:
	case DRIVER_DATA_NVEH_REAR_Y_COORDINATE:
	case DRIVER_DATA_NVEH_REAR_Z_COORDINATE:
	case DRIVER_DATA_NO_OF_LANES:
		if (ego_found)
		{
			num_of_lanes = long_value;
		}
		return 1;
	case DRIVER_DATA_LANE_WIDTH:
	case DRIVER_DATA_LANE_END_DISTANCE:
	case DRIVER_DATA_CURRENT_LANE_POLY_N:
	case DRIVER_DATA_CURRENT_LANE_POLY_X:
	case DRIVER_DATA_CURRENT_LANE_POLY_Y:
	case DRIVER_DATA_CURRENT_LANE_POLY_Z:
	case DRIVER_DATA_RADIUS:
	case DRIVER_DATA_MIN_RADIUS:
	case DRIVER_DATA_DIST_TO_MIN_RADIUS:
	case DRIVER_DATA_SLOPE:
	case DRIVER_DATA_SLOPE_AHEAD:
	case DRIVER_DATA_SIGNAL_DISTANCE:
	case DRIVER_DATA_SIGNAL_STATE:
	case DRIVER_DATA_SIGNAL_STATE_START:
	case DRIVER_DATA_SPEED_LIMIT_DISTANCE:
	case DRIVER_DATA_SPEED_LIMIT_VALUE:
		return 1;
	case DRIVER_DATA_DESIRED_ACCELERATION:
		current_target.desired_acceleration = double_value;
		return 1;
	case DRIVER_DATA_DESIRED_LANE_ANGLE:
		current_target.desired_lane_angle = double_value;
		return 1;
	case DRIVER_DATA_ACTIVE_LANE_CHANGE:
		current_target.active_lane_change = long_value;
		return 1;
	case DRIVER_DATA_REL_TARGET_LANE:
		current_target.rel_target_lane = long_value;
		return 1;
	default:
		return 0;
	}
}

int InjectorAbstract::setInjectorDataCoSim(long  type, long   index1, long   index2, 
										   long long_value, double double_value, char* string_value)
{
	std::ostringstream os;
	long current_lane = LONG_MAX;
	long current_position = LONG_MAX;

	switch (type) {
	case DRIVER_DATA_PATH:
	case DRIVER_DATA_TIMESTEP:
	case DRIVER_DATA_TIME:
		this->current_sim_time = double_value;
		return 1;
	case DRIVER_DATA_USE_UDA:
		return 0; /* doesn't use any UDAs */
	case DRIVER_DATA_VEH_ID:
		utilities::printDebug(std::ostringstream() << "VEH ID: " << long_value << "\n");
		current_target_id = long_value;
		current_target.vehicle_id = current_target_id;
		is_target_ref_found = false;
		data_injected = false;
		action_id = -1;
		return 1;
	case DRIVER_DATA_VEH_LANE:
		current_target.current_lane = long_value;
	case DRIVER_DATA_VEH_ODOMETER:
	case DRIVER_DATA_VEH_LANE_ANGLE:
	case DRIVER_DATA_VEH_LATERAL_POSITION:
		return 1;
	case DRIVER_DATA_VEH_VELOCITY:
		current_target.current_velocity = double_value;
		return 1;
	case DRIVER_DATA_VEH_ACCELERATION:
		current_target.acceleration = double_value;
		return 1;
	case DRIVER_DATA_VEH_LENGTH:
	case DRIVER_DATA_VEH_WIDTH:
	case DRIVER_DATA_VEH_WEIGHT:
	case DRIVER_DATA_VEH_MAX_ACCELERATION:
		return 1;
	case DRIVER_DATA_VEH_TURNING_INDICATOR:
		current_target.turning_indicator = long_value;
		return 1;
	case DRIVER_DATA_VEH_CATEGORY:
	case DRIVER_DATA_VEH_PREFERRED_REL_LANE:
	case DRIVER_DATA_VEH_USE_PREFERRED_LANE:
		return 1;
	case DRIVER_DATA_VEH_DESIRED_VELOCITY:
		current_target.desired_velocity = double_value;
		return 1;
	case DRIVER_DATA_VEH_X_COORDINATE:
	case DRIVER_DATA_VEH_Y_COORDINATE:
	case DRIVER_DATA_VEH_Z_COORDINATE:
	case DRIVER_DATA_VEH_REAR_X_COORDINATE:
	case DRIVER_DATA_VEH_REAR_Y_COORDINATE:
	case DRIVER_DATA_VEH_REAR_Z_COORDINATE:
	case DRIVER_DATA_VEH_TYPE:
		return 1;
	case DRIVER_DATA_VEH_COLOR:
		current_target.vehicle_color = long_value;
		return 1;
	case DRIVER_DATA_VEH_CURRENT_LINK:
		return 0; /* (To avoid getting sent lots of DRIVER_DATA_VEH_NEXT_LINKS messages) */
				  /* Must return 1 if these messages are to be sent from VISSIM!         */
	case DRIVER_DATA_VEH_NEXT_LINKS:
	case DRIVER_DATA_VEH_ACTIVE_LANE_CHANGE:
	case DRIVER_DATA_VEH_REL_TARGET_LANE:
	case DRIVER_DATA_VEH_INTAC_STATE:
	case DRIVER_DATA_VEH_INTAC_TARGET_TYPE:
	case DRIVER_DATA_VEH_INTAC_TARGET_ID:
	case DRIVER_DATA_VEH_INTAC_HEADWAY:
	case DRIVER_DATA_VEH_UDA:
		//return 1;
	case DRIVER_DATA_NVEH_ID:
		curr_nb_veh_id = long_value;
		current_lane = index1;
		current_position = index2;

		if (curr_nb_veh_id == EGO_ID && current_lane == 0 && current_position < 0)
		{
			utilities::printDebug(std::ostringstream() << "Ego detected as nb vehicle \n");
			is_target_ref_found = true;
			if (pivot_id == -1)
			{
				pivot_id = current_target_id;
			}
		}
		current_nearby_veh = new NearbyVehicle;
		current_nearby_veh->vehicle_id = long_value;
		current_nearby_veh->relative_lane = index1;
		current_nearby_veh->relative_position = index2;
		return 1;
	case DRIVER_DATA_NVEH_LANE_ANGLE:
	case DRIVER_DATA_NVEH_LATERAL_POSITION:
		return 1;
	case DRIVER_DATA_NVEH_DISTANCE:
		current_nearby_veh->distance = double_value; // Distance is negative if vehicle upstream
		return 1;
	case DRIVER_DATA_NVEH_REL_VELOCITY:
		current_nearby_veh->relative_velocity = double_value; // nb vehicle speed difference
		return 1;
	case DRIVER_DATA_NVEH_ACCELERATION:
		current_nearby_veh->acceleration = double_value;
		if (curr_nb_veh_id == EGO_ID)
		{
			ego_vehicle = *current_nearby_veh;
			return 1;
		}
		if (curr_nb_veh_id != -1)
		{
			nearby_vehicles_tmp.insert(std::pair<long int, NearbyVehicle*>(curr_nb_veh_id, 
																			   current_nearby_veh));
		}
		return 1;
	case DRIVER_DATA_NVEH_LENGTH:
		return 1;
	case DRIVER_DATA_NVEH_WIDTH:
	case DRIVER_DATA_NVEH_WEIGHT:
	case DRIVER_DATA_NVEH_TURNING_INDICATOR:
		current_nearby_veh->turning_indicator = long_value;
		return 1;
	case DRIVER_DATA_NVEH_CATEGORY:
	case DRIVER_DATA_NVEH_LANE_CHANGE:
	case DRIVER_DATA_NVEH_TYPE:
	case DRIVER_DATA_NVEH_UDA:
	case DRIVER_DATA_NVEH_X_COORDINATE:
	case DRIVER_DATA_NVEH_Y_COORDINATE:
	case DRIVER_DATA_NVEH_Z_COORDINATE:
	case DRIVER_DATA_NVEH_REAR_X_COORDINATE:
	case DRIVER_DATA_NVEH_REAR_Y_COORDINATE:
	case DRIVER_DATA_NVEH_REAR_Z_COORDINATE:
	case DRIVER_DATA_NO_OF_LANES:
		num_of_lanes = long_value;
		return 1;
	case DRIVER_DATA_LANE_WIDTH:
	case DRIVER_DATA_LANE_END_DISTANCE:
	case DRIVER_DATA_CURRENT_LANE_POLY_N:
	case DRIVER_DATA_CURRENT_LANE_POLY_X:
	case DRIVER_DATA_CURRENT_LANE_POLY_Y:
	case DRIVER_DATA_CURRENT_LANE_POLY_Z:
	case DRIVER_DATA_RADIUS:
	case DRIVER_DATA_MIN_RADIUS:
	case DRIVER_DATA_DIST_TO_MIN_RADIUS:
	case DRIVER_DATA_SLOPE:
	case DRIVER_DATA_SLOPE_AHEAD:
	case DRIVER_DATA_SIGNAL_DISTANCE:
	case DRIVER_DATA_SIGNAL_STATE:
	case DRIVER_DATA_SIGNAL_STATE_START:
	case DRIVER_DATA_SPEED_LIMIT_DISTANCE:
	case DRIVER_DATA_SPEED_LIMIT_VALUE:
		return 1;
	case DRIVER_DATA_DESIRED_ACCELERATION:
		current_target.desired_acceleration = double_value;
		return 1;
	case DRIVER_DATA_DESIRED_LANE_ANGLE:
		current_target.desired_lane_angle = double_value;
		return 1;
	case DRIVER_DATA_ACTIVE_LANE_CHANGE:
		current_target.active_lane_change = long_value;
		return 1;
	case DRIVER_DATA_REL_TARGET_LANE:
		current_target.rel_target_lane = long_value;
		return 1;
	default:
		return 0;
	}
}


int InjectorAbstract::getInjectorData(long   type, long   index1, long   index2, long* long_value, 
														  double* double_value, char** string_value)
{
	bool found = false;
	utilities::printDebug(std::ostringstream() << "IN GET FOR VEH ID: " << current_target_id << "\n");

	if (current_target_id == EGO_ID)
	{
		ego = current_target;
	}

	if (!CO_SIM)
	{
		if (is_action_triggered && deadline > current_sim_time)
		{
			for (auto& it : nearby_vehicles_tmp)
			{
				if (nearby_vehicles.find(it.first) != nearby_vehicles.end())
				{
					*(nearby_vehicles.find(it.first)->second) = *it.second;
				}
			}

			if (!(nearby_vehicles.find(current_target_id) == nearby_vehicles.end()))
			{
				// make this execute only once
				// call the action
				if (action_id != current_target_id)
				{
					action(nearby_vehicles.find(current_target_id)->second, surrounding_vehicles);
					action_id = current_target_id;
				}
				nveh = *nearby_vehicles.find(current_target_id)->second;
				found = true;
			}
			else
			{
				found = false;
			}
		}
		else if (is_action_triggered && deadline <= current_sim_time)
		{
			cleanUp();
			found = false;
			pivot_id = -1;
			data_injected = true;
		}
		else
		{
			if (!data_injected)
			{
				if (!(pause_set && current_sim_time <= pause_deadline))
				{
					captureWrapper();
				}

				if (!is_action_triggered)
				{
					cleanUp();
				}
			}
			// checks if data is to be injected only once per vehicle. Since in one sim step get
			// will be called multiple times on one vehicle in order to get all values, data_injected
			// guards the code from executing captureWrapper multiple times.
			// TODO: rename into something more suitable
			data_injected = true;
		}
		for (auto it = nearby_vehicles_tmp.begin(); it != nearby_vehicles_tmp.end(); it++)
		{
			delete it->second;
		}
		nearby_vehicles_tmp.clear();
	}

	
	if (CO_SIM)
	{
		if (is_action_triggered && deadline > current_sim_time)
		{
			if (current_target_id == pivot_id)
			{
				for (auto& it : nearby_vehicles_tmp)
				{
					if (nearby_vehicles.find(it.first) != nearby_vehicles.end())
					{
						it.second->relative_position -= ego_vehicle.relative_position;
						it.second->distance -= ego_vehicle.distance;
						it.second->relative_velocity -= ego_vehicle.relative_velocity;
						*(nearby_vehicles.find(it.first)->second) = *it.second;
					}
				}
			}

			if (!(nearby_vehicles.find(current_target_id) == nearby_vehicles.end()))
			{
				// make this execute only once
				// call the action
				if (action_id != current_target_id)
				{
					action(nearby_vehicles.find(current_target_id)->second, surrounding_vehicles);
					action_id = current_target_id;			
				}
				nveh = *nearby_vehicles.find(current_target_id)->second;
				found = true;
			}
			else
			{
				found = false;
			}
		}
		else if (is_action_triggered && deadline <= current_sim_time)
		{
			cleanUp();
			found = false;
			pivot_id = -1;
			data_injected = true;
		}
		else
		{
			if (is_target_ref_found && !data_injected)
			{
				NearbyVehicle* tmp = new NearbyVehicle(current_target);
				nearby_vehicles_tmp.insert(std::pair<long int, NearbyVehicle*>(tmp->vehicle_id, tmp));
				if (!(pause_set && current_sim_time <= pause_deadline))
				{
					captureWrapper();
				}
				
				if (!is_action_triggered)
				{
					pivot_id = -1;
					cleanUp();
				}
			}
			data_injected = true;
		}
		for (auto it = nearby_vehicles_tmp.begin(); it != nearby_vehicles_tmp.end(); it++)
		{
			delete it->second;
		}
		nearby_vehicles_tmp.clear();
	}
	
	if (!found)
	{
		nveh = NearbyVehicle(current_target);
	}

	switch (type) {
	case DRIVER_DATA_STATUS:
		*long_value = 0;
		return 1;
	case DRIVER_DATA_VEH_TURNING_INDICATOR:
		*long_value = nveh.turning_indicator;
		return 1;
	case DRIVER_DATA_VEH_DESIRED_VELOCITY:
		// this is only desired, not actuall speed
		*double_value = current_target.desired_velocity;
		return 1;
	case DRIVER_DATA_VEH_COLOR:
		if (found)
		{
			*long_value = nveh.color;
		}
		else if (current_target_id == EGO_ID)
		{
			*long_value = WHITE;
		}
		else
		{
			*long_value = RED;
		}
		return 1;
	case DRIVER_DATA_VEH_UDA:
		return 0; /* doesn't set any UDA values */
	case DRIVER_DATA_WANTS_SUGGESTION:
		*long_value = 1;
		return 1;
	case DRIVER_DATA_DESIRED_ACCELERATION:
		*double_value = nveh.acceleration;
		return 1;
	case DRIVER_DATA_DESIRED_LANE_ANGLE:
		*double_value = nveh.desired_lane_angle;
		return 1;
	case DRIVER_DATA_ACTIVE_LANE_CHANGE:
		*long_value = current_target.active_lane_change;
		return 1;
	case DRIVER_DATA_REL_TARGET_LANE:
		*long_value = nveh.data_rel_target_lane;
		return 1;
	case DRIVER_DATA_SIMPLE_LANECHANGE:
		*long_value = 1;
		return 1;
	case DRIVER_DATA_USE_INTERNAL_MODEL:
		/* must be set to 1 if the internal behavior model of Vissim is to be applied */
		if (found)
		{
			*long_value = 0;
		}
		else
		{
			*long_value = 1;
		}
			
		return 1;
	case DRIVER_DATA_WANTS_ALL_NVEHS:
		/* must be set to 1 if data for more than 2 nearby vehicles per lane and 
		upstream/downstream is to be passed from Vissim 
		*/
		*long_value = 0;
		return 1;
	case DRIVER_DATA_ALLOW_MULTITHREADING:
		/* must be set to 1 to allow a simulation run to be started with multiple cores used in 
		the simulation parameters 
		*/
		*long_value = 1;
		return 1;
	default:
		return 0;
	}
}


void InjectorAbstract::cleanUp()
{
	for (auto& it : surrounding_vehicles)
	{
		delete it;
	}
	front_vehicles.clear();
	rear_vehicles.clear();
	surrounding_vehicles.clear();
	nearby_vehicles.clear();

	this->is_action_triggered = false;
	this->duration = 0;
	this->start_time = 0;
	this->deadline = 0;
}


void InjectorAbstract::prepareData()
{
	front_vehicles.clear();
	rear_vehicles.clear();
	surrounding_vehicles.clear();
	nearby_vehicles.clear();

	auto ref = current_target;
	long ego_index2 = ego_vehicle.relative_position;
	double ego_distance = ego_vehicle.distance;

	for (auto& it : nearby_vehicles_tmp) {
		utilities::printDebug(std::ostringstream() << "EGO ID: " << this->ego.vehicle_id << "\n");
		utilities::printDebug(std::ostringstream() << "ID: " << it.second->vehicle_id << "\n");
		utilities::printDebug(std::ostringstream() << "Distance: " << it.second->distance << "\n");
		utilities::printDebug(std::ostringstream() << "Velocity: " << it.second->relative_velocity << "\n");
		utilities::printDebug(std::ostringstream() << "Acceleration: " << it.second->acceleration << "\n");

		NearbyVehicle* nnv = new NearbyVehicle;
		*nnv = *it.second;

		nearby_vehicles.insert(std::pair<long int, NearbyVehicle*>(nnv->vehicle_id, nnv));
		surrounding_vehicles.push_back(nnv);
		if (nnv->relative_position >= 0)
		{
			front_vehicles.push_back(nnv);
		}
		else
		{
			rear_vehicles.push_back(nnv);
		}
	}
}


void InjectorAbstract::prepareDataCoSim()
{
	front_vehicles.clear();
	rear_vehicles.clear();
	surrounding_vehicles.clear();
	nearby_vehicles.clear();

	auto ref = current_target;
	long ego_index2 = ego_vehicle.relative_position;
	double ego_distance = ego_vehicle.distance;

	for (auto& it : nearby_vehicles_tmp) {
		// calculate corrected data
		it.second->relative_position -= ego_index2;
		it.second->distance -= ego_distance;
		it.second->relative_velocity -= ego_vehicle.relative_velocity;
		
		NearbyVehicle* nnv = new NearbyVehicle;
		*nnv = *it.second;

		nearby_vehicles.insert(std::pair<long int, NearbyVehicle*>(nnv->vehicle_id, nnv));
		surrounding_vehicles.push_back(nnv);
		if (nnv->relative_position >= 0)
		{
			front_vehicles.push_back(nnv);
		}
		else
		{
			rear_vehicles.push_back(nnv);
		}
	}
}

bool InjectorAbstract::startAction(double duration, double pause)
{
	// Time threshold under which action is not started
	if (duration < 2)
	{
		return false;
	}

	std::vector<long> not_selected;
	bool selected = false;

	for (auto it : surrounding_vehicles) {
		if (it->selected_as_target)
		{
			selected = true;
			break;
		}
	}

	if (!selected)
	{
		return false;
	}

	for (auto it = surrounding_vehicles.begin(); it != surrounding_vehicles.end(); ) {
		if (!(*it)->selected_as_target)
		{
			not_selected.push_back((*it)->vehicle_id);
			it = surrounding_vehicles.erase(it);
		}
		else
		{
			it++;
		}
	}

	for (auto it = rear_vehicles.begin(); it != rear_vehicles.end(); ) {
		if (!(*it)->selected_as_target)
		{
			delete* it;
			it = rear_vehicles.erase(it);
		}
		else
		{
			it++;
		}
	}

	for (auto it = front_vehicles.begin(); it != front_vehicles.end(); ) {
		if (!(*it)->selected_as_target)
		{
			delete* it;
			it = front_vehicles.erase(it);
		}
		else
		{
			it++;
		}
	}

	for (long index : not_selected)
	{
		// change to DataNveh[index]
		nearby_vehicles.erase(index);
	}

	this->is_action_triggered = true;
	this->duration = duration;
	this->start_time = current_sim_time;
	this->deadline = this->start_time + this->duration + 0.1;

	if (pause > 0)
	{
		this->pause_set = true;
		this->pause = pause;
		this->pause_deadline = current_sim_time + pause + duration;
	}

	return true;
}

void InjectorAbstract::captureWrapper()
{
	if (!CO_SIM)
	{
		prepareData();
	}
	else
	{
		prepareDataCoSim();
	}
	capture();
}


std::vector<NearbyVehicle*> InjectorAbstract::getNearbyVehicles()
{
	return surrounding_vehicles;
}

std::vector<NearbyVehicle*> InjectorAbstract::getVehiclesDownstream()
{
	return front_vehicles;
}
std::vector<NearbyVehicle*> InjectorAbstract::getVehiclesUpstream()
{
	return rear_vehicles;
}

double InjectorAbstract::getCurrentSimTime()
{
	return current_sim_time;
}


void InjectorAbstract::startStoringData(bool start, bool interval = true)
{
	this->store_data = start;
	this->interval_mode = interval;
}


void InjectorAbstract::action(NearbyVehicle* veh, const std::vector<NearbyVehicle*> actionNveh)
{
	utilities::printDebug(std::ostringstream() << "Action: " << getCurrentSimTime() << "\n");
}


InjectorAbstract::~InjectorAbstract() 
{
	for (auto& it : this->nearby_vehicles)
	{
		if (it.second != nullptr) {
			delete it.second;
		}
	}
}

double InjectorAbstract::getActionStartTime()
{
	return start_time;
}

double InjectorAbstract::getCurrentVehicleVelocity()
{
	return current_target.current_velocity;
}