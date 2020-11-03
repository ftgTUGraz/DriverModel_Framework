/*==========================================================================*/
/*  DriverModel.h                                    DLL Module for VISSIM  */
/*                                                                          */
/*  Interface module for external driver models.                            */
/*                                                                          */
/*  Version of 2017-11-02                                   Lukas Kautzsch  */
/*==========================================================================*/

#ifndef __DRIVERMODEL_H
#define __DRIVERMODEL_H

#ifndef _CONSOLE
#include "Injector.h"
#include <windows.h>
#endif

/* In the creation of DriverModel.DLL all files must be compiled */
/* with the preprocessor definition DRIVERMODEL_EXPORTS.         */
/* Programs that use DriverModel.DLL must not be compiled        */
/* with that preprocessor definition.                            */

#ifdef DRIVERMODEL_EXPORTS
#define DRIVERMODEL_API extern "C" __declspec(dllexport)
#else
#define DRIVERMODEL_API extern "C" __declspec(dllimport)
#endif


DRIVERMODEL_API  int  DriverModelSetValue (long   type,
                                           long   index1,
                                           long   index2,
                                           long   long_value,
                                           double double_value,
                                           char   *string_value);

/* Sets the value of a data object of type <type>, selected by <index1> */
/* and possibly <index2>, to <long_value>, <double_value> or            */
/* <*string_value> (object and value selection depending on <type>).    */
/* Return value is 1 on success, otherwise 0.                           */

/*--------------------------------------------------------------------------*/

DRIVERMODEL_API  int  DriverModelGetValue (long   type,
                                           long   index1,
                                           long   index2,
                                           long   *long_value,
                                           double *double_value,
                                           char   **string_value);

/* Gets the value of a data object of type <type>, selected by <index1> */
/* and possibly <index2>, and writes that value to <*double_value>,     */
/* <*float_value> or <**string_value> (object and value selection       */
/* depending on <type>).                                                */
/* Return value is 1 on success, otherwise 0.                           */

/*==========================================================================*/

#define  DRIVER_COMMAND_INIT            0
           /* called from VISSIM once at the start of a simulation run */
           /* values set before: DRIVER_DATA_PATH     */
           /*                    DRIVER_DATA_TIMESTEP */
           /*                    DRIVER_DATA_TIME     */
           /* values got after:  DRIVER_DATA_WANTS_SUGGESTION     */
           /*                    DRIVER_DATA_AUTOMATIC_LANECHANGE */

#define  DRIVER_COMMAND_CREATE_DRIVER   1
           /* called from VISSIM once per vehicle entering the network */
           /* values set before: DRIVER_DATA_VEH_ID               */
           /*                    DRIVER_DATA_VEH_DESIRED_VELOCITY */

#define  DRIVER_COMMAND_KILL_DRIVER     2
           /* called from VISSIM once per vehicle leaving the network */
           /* value set before: DRIVER_DATA_VEH_ID */

#define  DRIVER_COMMAND_MOVE_DRIVER     3
           /* called from VISSIM once per time step during a simulation run */
           /* values set before: all values                      */
           /*                    (driving behaviour data only if */
           /*                     DRIVER_DATA_WANTS_SUGGESTION)  */

/*--------------------------------------------------------------------------*/

DRIVERMODEL_API  int  DriverModelExecuteCommand (long number);

/* Executes the command <number> if that is available in the driver */
/* module. Return value is 1 on success, otherwise 0.               */

/*==========================================================================*/

#endif /* __DRIVERMODEL_H */

/*==========================================================================*/
/*  End of DriverModel.h                                                    */
/*==========================================================================*/
