#pragma once

/***************************************************************************/
/*                                Paramaterfile                            */
/*                                                                         */
/***************************************************************************/

/*  TTC Parameters  */

#define CO_SIM 0
#define EGO_ID 5
#define NUM_OF_NVEH 8
#define TTCTreshold  4.0		// Critical TTC Value
#define	SameLane  false			// If true, the DriverModell considers only the Nveh in the same lane
#define NVEH_THRESHOLD 1
#define TIME_THRESHOLD 30 // time_steps

#define RED 4294640660
#define WHITE -000001

#define ORANGE -888000
#define YELLOW -400000

#define ON 1
#define OFF 0

#define DEBUG_PRINT ON

#define NVEH_THRESHOLD_ENABLE 1 // 1 disabled, 0 enabled
#define TIME_THRESHOLD_ENABLE 1 // 1 disabled, 0 enabled

#define NUM_OF_LANES 2
#define NUM_OF_COLS 2

#define NO_LANE -5


#define XX -1

#if NUM_OF_LANES == 2
#define COMBINATIONS 9
#else
#define COMBINATIONS 12
#endif

#define COMP_MATRIX_2_ROW 9
#define COMP_MATRIX_2_COL 6

#define COMP_MATRIX_3_ROW 12
#define COMP_MATRIX_3_COL 9

#define REPETITION_THRESHOLD 3

#define TRIGGER_INTERVAL 90 // defined in seconds
#define EVENT_LENGTH 15 // length of an event during which data is stored, in seconds

#define VEH_VELOCITY 83 // in m/s


#define T1 2
#define T2 4
#define T3 6
#define T4 8