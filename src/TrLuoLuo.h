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
 * LuoLuo.h
 *
 *  Created on: 3-nov-2020
 *      Author: Hassan
 */


#ifndef TRLUOLUO_H_
#define TRLUOLUO_H_

#include "Tb.h"

class TrLuoLuo: public Tb {

public:

	enum fieldId {
		lid_base,
		lid_coll,
		tp_legame,
		ute_ins,
		ts_ins,
		ute_var,
		ts_var,
		fl_canc
	};

	TrLuoLuo(CFile *TrAutAutIn, CFile *TrAutAutOffsetIn, char *offsetBufferTrAutAutPtr, long elementsTrAutAut, int keyPlusOffsetPlusLfLength, int key_length);
	virtual ~TrLuoLuo();
	bool loadRecord(const char *key);
	bool loadNextRecordDaIndice(const char *key, bool inverted);

};

#endif /* TRLUOLUO_H_ */
