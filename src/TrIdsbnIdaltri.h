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
 * TrIdsbnIdaltri.h
 *
 *  Created on: 20-nov-2020
 *      Author: Hassan
 */


#ifndef TRIDSBNIDALTRI_H_
#define TRIDSBNIDALTRI_H_

#include "Tb.h"

class TrIdsbnIdaltri: public Tb {

public:

	enum fieldId {
		cd_polo,
		cd_biblioteca,
		tp_oggetto,
		id_ind,
		id_polo,
		ute_ins,
		ts_ins,
		ute_var,
		ts_var,
		fl_canc
	};

	TrIdsbnIdaltri(CFile *TrIdsbnIdaltriIn, CFile *TrIdsbnIdaltriOffsetIn, char *offsetBufferTrIdsbnIdaltriPtr, long elementsTrIdsbnIdaltri, int keyPlusOffsetPlusLfLength, int key_length);
	virtual ~TrIdsbnIdaltri();
	bool loadRecord(const char *key);
	bool loadNextRecordDaIndice(const char *key, bool inverted);

};

#endif /* TRIDSBNIDALTRI_H_ */
