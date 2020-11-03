#pragma once

/*==========================================================================*/
/*  utilities.h										   Class for VISSIM DLL */
/*                                                                          */
/*  Heade for functions which are needed in other classes.                  */
/*                                                                          */
/*  Version of 22.10.2019						Christoph Wellershaus,BSc   */
/*==========================================================================*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include "Parameters.h"


class utilities
{


public:

	utilities();
	~utilities();

	static void printDebug(std::ostringstream& os)
	{
		if (DEBUG_PRINT)
		{
			OutputDebugString(os.str().c_str());
			os.str("");
		}
	}
};



