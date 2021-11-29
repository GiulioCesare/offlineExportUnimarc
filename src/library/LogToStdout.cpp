/*******************************************************************************
  * Copyright (C) 2019 ICCU - Istituto Centrale per il Catalogo Unico
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Affero General Public License as published
  * by the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU Affero General Public License for more details.
  *
  * You should have received a copy of the GNU Affero General Public License
  * along with this program. If not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************/
/***************************************************************************
* Program : SignalError.cpp                                                *
* Purpose : Eror handling                                                  *
* Author  : Argentino Trombin                                              *
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ors/Const.h>
#include <errno.h>
#ifdef TRACK_MEMORY_LEAKS
    #include "nvwa/debug_new.h"
#endif


//OrsInt	SignalledErrors = 0;
extern int log_level;

void logToStdout(	const OrsChar *Module, OrsInt Line, int level, const OrsChar * MsgFmt, ...);

OrsChar *log_level_msg[] = {"unused",
						"TRACE",
					   "DEBUG",
					   "INFO",
					   "WARNING",
					   "ERROR",
					   "FATAL",
					   "PROGRESS"};




void logToStdout(	const OrsChar *Module,
					OrsInt Line,
					int level,
					const OrsChar * MsgFmt, ...)
	{
	if (level < log_level || level > LOG_PROGRESS)
		return;

//	if (level > LOG_FATAL)
//	{
//		printf("\nlogToStdout: Module=%s Line=%d invalid log level %d", level);
//		retrun;
//	}

	va_list argptr;
	OrsChar loc_buf[512];

	// Expand message with supplied arguments (if there are any)
	va_start(argptr, MsgFmt);
	vsprintf(loc_buf, MsgFmt, argptr);
	va_end(argptr);

	if (level == LOG_PROGRESS)
		printf("\n%s: %s", log_level_msg[level], loc_buf);
	else
		printf("\n%s: Module=%s Line=%d Msg: %s", log_level_msg[level], Module, Line, loc_buf);

//	SignalledErrors++;

	} // End logToStdout


