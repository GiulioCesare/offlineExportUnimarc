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
/*
 * TbParola.cpp
 *
 *  Created on: 30-set-2010
 *      Author: Arge
 */


#include "TbParola.h"
#include "MarcConstants.h"
#include "MarcGlobals.h"
#include "BinarySearch.h"
#ifdef TRACK_MEMORY_LEAKS
    #include "nvwa/debug_new.h"
#endif

extern void logToStdout(	const OrsChar *Module, OrsInt Line, int level, const OrsChar * MsgFmt, ...);



TbParola::TbParola(CFile *tbIn, CFile *tbOffsetIn, char *offsetBufferTbPtr, long elementsTb, int keyPlusOffsetPlusLfLength, int key_length) :
	Tb (tbIn, tbOffsetIn, offsetBufferTbPtr, elementsTb, keyPlusOffsetPlusLfLength, key_length) {
	tbFields = 8;

	init();

}

TbParola::~TbParola() {
}

bool TbParola::loadRecord(const char *key)
{
	if (!Tb::loadRecord(key))
	{
//		SignalAnError(__FILE__, __LINE__, "Derived class TbParola::loadRecord");
//	    SignalAnError(__FILE__, __LINE__, "Record non trovato per chiave %s", key);
		logToStdout(__FILE__, __LINE__, LOG_INFO, "Record non trovato per chiave %s", key);
		return false;
	}
	return true;
} // End loadRecord
