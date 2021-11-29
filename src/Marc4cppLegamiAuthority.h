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
 * Marc4cppLegamiAuthority.h
 *
 *  Created on: 20-jul-2009
 *      Author: Arge
 */


#ifndef MARC4CPPLEGAMIAUTHORITY_H_
#define MARC4CPPLEGAMIAUTHORITY_H_

#include "MarcRecord.h"
#include "TbAutore.h"
#include "TbLuogo.h"
#include "TbCodici.h"
#include "library/tree.hh"
#include "library/CKeyValueVector.h"
//#include "Marc4cppDocumento.h"
#include "library/tvvector.h"
#include "library/CKeyValueVector.h"
#include "library/CFile.h"
#include "Marc4cppLegami.h"
#include "TrRepAut.h"
#include "TrRepTit.h"
#include "TbRepertorio.h"
#include "TbSoggetto.h"
#include "TbDescrittore.h"
#include "TrSogDes.h"
#include "TrDesDes.h"
#include "TrRepLuo.h"
#include "TrIdsbnIdaltri.h"

#include "library/CTokenizer.h"
#include "MarcGlobals.h"
#include "Marc4cppDocumentoAuthority.h"


class Marc4cppLegamiAuthority {
	Marc4cppDocumentoAuthority *marc4cppDocumentoAuthority;
	CKeyValueVector *legamiVectorKV;
	CKeyValueVector *tbCodiciKV;
	int authority;
	tree<std::string>::sibling_iterator siArg; // causa problemi di memoria provo a passare non tramite argument

	MarcRecord 		*marcRecord;
	//Marc4cppLegami *marc4cppLegami;

    char rootId[10+1];

    TbTitolo 		*tbTitolo;

	TbAutore		*tbAutore;
	TbSoggetto		*tbSoggetto;
	TbDescrittore	*tbDescrittore;
	CKeyValueVector *tbfBibliotecaKV; //*descBibKV, *anagrafeBibKV;

	TrRepAut *trRepAut;
	TrRepTit *trRepTit;

	TbRepertorio *tbRepertorio;
	TrSogDes *trSogDes;
	TrDesDes *trDesDes;
	TrDesDes *trDesDesInv;

//	CFile* trAutAutIn;
//	CFile* trAutAutOffsetIn;
//	char* offsetBufferTrAutAutPtr;
//	long elementsTrAutAut;

	TrAutAut *trAutAut;

	CFile* trTitAutRelInvIn;
	CFile* trTitAutRelInvOffsetIn;
	char* offsetBufferTrTitAutRelInvPtr;
	long elementsTrTitAutInvRel;

	// 12/04/2016
	CFile* trTitAutRelIn;
	CFile* trTitAutRelOffsetIn;
	char* offsetBufferTrTitAutRelPtr;
	long elementsTrTitAutRel;

	// 05/06/2020
	CFile* trAutAutRelIn;
	CFile* trAutAutRelOffsetIn;
	char* offsetBufferTrAutAutRelPtr;
	long elementsTrAutAutRel;


	CFile* trIdsbnIdaltriAuRelIn;
	CFile* trIdsbnIdaltriAuRelOffsetIn;
	char* offsetBuffertrIdsbnIdaltriAuRelPtr;
	long elementstrIdsbnIdaltriAuRel;

	TrIdsbnIdaltri* trIdsbnIdaltriAu;
	TbfBiblioteca* tbfBiblioteca;

	TbLuogo* tbLuogo;
	TrRepLuo* trRepLuo;
	CFile* trLuoLuoIn;
	CFile* trLuoLuoOffsetIn;
	char* offsetBufferTrLuoLuoPtr;
	long elementsTrLuoLuo;
	CFile* trLuoLuoRelInvIn;
	CFile*trLuoLuoRelInvOffsetIn;
	char* offsetBufferTrLuoLuoRelInvPtr;
	long elementsTrLuoLuoInvRel;
	long elementsTrLuoLuoRel;


	int keyPlusOffsetPlusLfLength;
	int classeKeyPlusOffsetPlusLfLength;
	int trKeyPlusOffsetPlusLfLength;
	int key_length;

	tree<std::string> reticolo;
	void getEntityId(char *entryReticolo, char *id);

	void creaLegamiTitoloTitolo();
	DataField * creaLegameTitoloTitolo(char *entryReticoloPtr, int pos);

	void creaLegamiTitoloAutore(bool isTitoloOpera);
	DataField * creaLegameTitoloAutore(char *entryReticoloPtr, int pos, bool isTitoloOpera);
	void creaTag50x(DataField *df, CString *ds_nome, char tp_nome,	CString *bid, CString *cdRelazione); // 23/04/2020
	char getQualificazioneType(char *parteDiQualificazione, int nth, char tipoNome); // 23/04/2020


	void creaLegamiAutoreAutore();
	void creaLegamiLuogoLuogo();
	void creaLegamiSoggettoDescrittori();
	void creaTag931_LegameSoggettoDescrittore();
	void creaLegamiDescrittoriDescrittori(char *didBase);
	void creaTag932_LegameDescrittoreDescrittore(CString *tpLegame, CString *didBase);


	DataField * creaLegameAutoreAutore(char *entryReticoloPtr, int pos);
	DataField * creaLegameLuogoLuogo(char *entryReticoloPtr, int pos);
	void creaLegamiautoriDiRinvio(DataField *df, char *vid);

	DataField * creaTag400_RinvioAutorePersonale(TbAutore * tbAutoreRinvio);
	DataField * creaTag410_RinvioAutoreCollettivo(TbAutore * tbAutoreRinvio);
	DataField * creaTag500_VediAncheAutorePersonale(TbAutore * tbAutoreRinvio);
	DataField * creaTag510_VediAncheAutoreCollettivo(TbAutore * tbAutoreRinvio);



	void creaLegamiAutoreRepertori();
	DataField * creaTag_81xRepertorio(char *tag);

	void creaLegamiLuogoRepertori();   // 09/11/2020
	DataField * creaTag_81xLuogoRepertorio(char *tag);

	void creaLegamiTitoloRepertori();
	DataField * creaTag_81xRepertorio_Titolo(char *tag);

	void creaLegamiAutoreBasiDati();


	void creaTag_40x(DataField *df, TbAutore * tbAutoreRinvio);
	void creaTag_41x(DataField *df, TbAutore * tbAutoreRinvio);

	void init();
	void initLicr();
	void stop();
	void clearLegamiVector();
	void clearTbCodiciVEctor();
	bool haResponsabilitaPrincipale(const tree<std::string>& tr);


public:
	//authority luoghi 05/11/2020

	Marc4cppLegamiAuthority(Marc4cppDocumentoAuthority *marc4cppDocumentoAuthority,
				MarcRecord *marcRecord, // per luoghi
				TbLuogo *tbLuogo,
				TrRepLuo *trRepLuo,
				TbRepertorio *tbRepertorio,
				CFile* trLuoLuoIn, CFile* trLuoLuoOffsetIn,	char* offsetBufferTrLuoLuoPtr, long elementsTrLuoLuo,
				CFile* trLuoLuoRelInvIn, CFile* trLuoLuoRelInvOffsetIn, char* offsetBufferTrLuoLuoRelInvPtr, long elementsTrLuoLuotInvRel,
				int keyPlusOffsetPlusLfLength,
				int trKeyPlusOffsetPlusLfLength,
				int key_length,
				int authority
				);

	Marc4cppLegamiAuthority(Marc4cppDocumentoAuthority *marc4cppDocumentoAuthority,
			MarcRecord *marcRecord, // per autori
			TbAutore *tbAutore,
			TrRepAut *trRepAut,
			TbRepertorio *tbRepertorio,
			TrAutAut *trAutAut, // 17/09/2021
//			CFile* trAutAutIn, CFile* trAutAutOffsetIn,	char* offsetBufferTrAutAutPtr, long elementsTrAutAut,
			CFile* trTitAutRelInvIn, CFile* trTitAutRelInvOffsetIn, char* offsetBufferTrTitAutRelInvPtr, long elementsTrTitAutInvRel,
			TrIdsbnIdaltri *trIdsbnIdaltriAu,
			CFile* trIdsbnIdaltriAuRelIn, CFile* trIdsbnIdaltriAuRelOffsetIn, char* offsetBuffertrIdsbnIdaltriAuRel, long elementstrIdsbnIdaltriAuRel,

			TbfBiblioteca *tbfBiblioteca,
			CKeyValueVector *tbfBibliotecaKV,
			int keyPlusOffsetPlusLfLength,
			int trKeyPlusOffsetPlusLfLength,
			int key_length,
			int authority,
			TbTitolo *tbTitolo
			);
	Marc4cppLegamiAuthority(Marc4cppDocumentoAuthority *marc4cppDocumentoAuthority,
			MarcRecord *marcRecord, // per soggetti
			TbSoggetto *tbSoggetto,
			TbDescrittore *tbDescrittore,
			TrSogDes *trSogDes,
			TrDesDes *trDesDes,
			TrDesDes *trDesDesInv,
			CKeyValueVector *tbfBibliotecaKV,
			int keyPlusOffsetPlusLfLength,
			int trKeyPlusOffsetPlusLfLength,
			int key_length,
			int authority);


	Marc4cppLegamiAuthority(Marc4cppDocumentoAuthority *marc4cppDocumentoAuthority,
			MarcRecord *marcRecord, // per titoli uniformi
			TbTitolo *tbTitolo,
			TbAutore *tbAutore,

			TrRepTit *trRepTit,
			TrAutAut *trAutAut,

			TbRepertorio *tbRepertorio,

			CFile* trTitAutRelIn,
			CFile* trTitAutRelOffsetIn,

			CFile* trTitTitRelIn,
			CFile* trTitTitRelOffsetIn, // 08/05/2020

			CFile* trAutAutRelIn,
			CFile* trAutAutRelOffsetIn, // 05/06/2020 per 500 $9


			char* offsetBufferTrTitAutRelPtr,
			char* offsetBufferTrAutAutRelPtr, // 10/11/2020

			long elementsTrTitAutRel,
			long elementsTrAutAutRel,


			CKeyValueVector *tbfBibliotecaKV,
			int keyPlusOffsetPlusLfLength,
			int trKeyPlusOffsetPlusLfLength,
			int key_length,
			int authority
			);



	virtual ~Marc4cppLegamiAuthority();
	bool elaboraDatiLegamiAuthority(const tree<std::string>& reticolo, bool isTitoloOpera);
	bool elaboraDatiViaf(char *id, int exportMaxViafs);
	bool getTitoliViafConResponabilita(CString *sPtr, char responsabilita, CKeyValueVector *cdLivelloVidIsbdKV, int exportMaxViafs);
	bool getTitoliUniformiViaf(CString *sPtr, char responsabilita, CKeyValueVector *cdLivelloVidIsbdKV, int exportMaxViafs);

};

#endif /* MARC4CPPLEGAMIAUTHORITY_H_ */
