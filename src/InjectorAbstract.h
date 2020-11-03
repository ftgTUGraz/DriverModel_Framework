#pragma once
#include "Parameters.h"
#include "EgoVehicle.h"
#include "NearbyVehicle.h"
#include "Utilities.h"
#include "VissimValues.h"
#include "DataStorage.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>
#include <sstream>
#include <windows.h>
#include <unordered_map>


/**
* InjectorAbstract is a class tasked with reading, tracking, updating and filtering vehicles which 
* are using this driver model. It provides a user with various useful methods which can be accessed
* in user intrface. 
*/

class InjectorAbstract
{
private:
    std::unordered_map<long int, NearbyVehicle*>nearby_vehicles;
    std::unordered_map<long int, NearbyVehicle*>nearby_vehicles_tmp;
    std::vector<NearbyVehicle*> front_vehicles;
    std::vector<NearbyVehicle*> rear_vehicles;
    std::vector<NearbyVehicle*> surrounding_vehicles;
    double current_sim_time;

    NearbyVehicle nveh;
    long pivot_id = -1;

    bool store_data = false;
    bool interval_mode = false;
    bool is_target_ref_found = false;

    bool is_action_triggered = false;
    double duration;
    double start_time;
    double deadline;
    bool pause_set = false;
    double pause;
    double pause_deadline;

    long action_id;

    bool ego_found;
    bool data_injected;
    long current_target_id;
    long curr_nb_veh_id;
    long num_of_lanes;

    NearbyVehicle* current_nearby_veh;
    
public:

    EgoVehicle	current_target;
    EgoVehicle	ego;
    NearbyVehicle ego_vehicle;

	InjectorAbstract(long int ego_id);

    /**
    * Method which is interfacing between Vissim and driver model. All the data fed into the driver
    * model are recieved through this method.
    * 
    * For detailed description of the arguments, refer to the Vissim Interface Description:
    * DriverModelSetValue.
    */
	int setInjectorData(long type, long index1, long index2, long long_value, double double_value, 
                                                                                char* string_value);
    
    
    /**
    * Method which is interfacing between Vissim and driver model. All the data fed into the driver
    * model are recieved through this method. The difference to the previous one is that CoSim 
    * version is used in co-simulation mode of operation.
    *
    * For detailed description of the arguments, refer to the Vissim Interface Description:
    * DriverModelSetValue.
    */
    int setInjectorDataCoSim(long type, long index1, long index2, long long_value, 
                                                           double double_value, char* string_value);
	
    
    /**
    * Method which is interfacing between Vissim and driver model. All the data read by Vissim from
    * the driver model is done through this metod.
    *
    * For detailed description of the arguments, refer to the Vissim Interface Description:
    * DriverModelGetValue.
    */
    int getInjectorData(long type, long index1, long index2, long* long_value, double* double_value, 
                                                                               char** string_value);

    /**
    * capture is a virtual method which is implemeted by the Injector class which serves the purpose
    * of the interface.
    */
	virtual void InjectorAbstract::capture() = 0;

    /**
    * action is a virtual method which is implemeted by the Injector class which serves the purpose
    * of the interface.
    */
    virtual void action(NearbyVehicle* veh, const std::vector<NearbyVehicle*> action_nvehs) = 0;

    /**
    * captureWrapper prepare everything for the execution of the capture
    */
    void captureWrapper();
    /**
    * prepareData method prepares the date for the execution of capture method. Vehicles are sorted
    * into different lists (e.g. front/rear vehicles), all necessary data calculated (e.g. relative
    * speed, distance...).
    */
    void prepareData();
    void prepareDataCoSim();
    /**
    * Returns the vector containing all nearby vehicles which are detected by the selected ego 
    * vehicle.
    */
    std::vector<NearbyVehicle*> getNearbyVehicles();
    /**
    * Returns the vector containing all nearby vehicles currently in front of ego vehicle.
    */
    std::vector<NearbyVehicle*> getVehiclesDownstream();
    /**
    * Returns the vector containing all nearby vehicles currently behind of ego vehicle.
    */
    std::vector<NearbyVehicle*> getVehiclesUpstream();
    /**
    * Returns current simulation time.
    */
    double getCurrentSimTime();

    void cleanUp();

    /**
    * TODO: To be implemented.
    */
    void startStoringData(bool start, bool interval);

    /**
    * Calling this method marks the start of the action. From the moment of the method execution,
    * execution of capture is not scheduled until duration of action expires (+ pause if specified).
    *
    * @params[duration] time which action will take
    * @params[pause] optional parameter which specifies minimum pause between two actions
    */
    bool startAction(double duration, double pause = -1);

    /**
    * Returns the time of the last action start.
    */
    double getActionStartTime();

    /**
    * TODO: To be removed.
    */
    double getCurrentVehicleVelocity();

    ~InjectorAbstract();

};

