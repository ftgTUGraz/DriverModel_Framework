
/*==========================================================================*/
/*  DriverModel.cpp                                  DLL Module for VISSIM  */
/*                                                                          */
/*  Interface module for external driver models.                            */
/*  Dummy version that does nothing (uses Vissim's internal model).         */
/*                                                                          */
/*  Version of 2017-11-02                                   Lukas Kautzsch  */
/*==========================================================================*/

#include "DriverModel.h"


/*==========================================================================*/

BOOL APIENTRY DllMain(HANDLE  hModule,
	DWORD   ul_reason_for_call,
	LPVOID  lpReserved)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

/*==========================================================================*/

DRIVERMODEL_API  int  DriverModelSetValue(long   type,
	long   index1,
	long   index2,
	long   long_value,
	double double_value,
	char* string_value)
{
	if (CO_SIM)
	{
		return Injector::instance().setInjectorDataCoSim(type, index1, index2, long_value, double_value, string_value);
	}
	return Injector::instance().setInjectorData(type, index1, index2, long_value, double_value, string_value);

}

/*--------------------------------------------------------------------------*/

DRIVERMODEL_API  int  DriverModelGetValue(long   type,
	long   index1,
	long   index2,
	long* long_value,
	double* double_value,
	char** string_value)
{
	return Injector::instance().getInjectorData(type, index1, index2, long_value, double_value, string_value);
}

/*==========================================================================*/

DRIVERMODEL_API  int  DriverModelExecuteCommand(long number)
{
	/* Executes the command <number> if that is available in the driver */
	/* module. Return value is 1 on success, otherwise 0.               */
	utilities::printDebug(std::ostringstream() << "In driver model Execute command for number: " << number << "\n");

	switch (number) {
	case DRIVER_COMMAND_INIT:
		return 1;
	case DRIVER_COMMAND_CREATE_DRIVER:
		return 1;
	case DRIVER_COMMAND_KILL_DRIVER:
		utilities::printDebug(std::ostringstream() << "KILLING IT\n");
		return 1;
	case DRIVER_COMMAND_MOVE_DRIVER:
		return 1;
	default:
		return 0;
	}

	
}

/*==========================================================================*/
/*  End of DriverModel.cpp                                                  */
/*==========================================================================*/
