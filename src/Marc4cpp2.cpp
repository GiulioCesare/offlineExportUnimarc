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
 * Marc4cpp2.cpp
 *
 *  Created on: 16-lug-2009
 *      Author: Arge
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Marc4cpp.h"
#include "library/CTokenizer.h"
#include "string"
#include "BinarySearch.h"
#include "library/CFile.h"
#include "library/GenericError.h"
#include "TbfBibliotecaInPolo.h"
#include "library/Cini.h"
#include "library/macros.h"
#include <malloc.h>

#ifdef TRACK_MEMORY_LEAKS
    #include "nvwa/debug_new.h"
#endif

extern void logToStdout(	const OrsChar *Module, OrsInt Line, int level, const OrsChar * MsgFmt, ...);


bool Marc4cpp::CreaUnimarcAuthority(long iniziaElaborazioneDaRiga, bool positionByOffset, long elaboraNRighe, int logOgniXRighe)
{
	long ctr=0;
	long erratoCtr=0;
//	char chr;
	long idCtr=0;
	CString *sPtr = new CString(); // 1024

	if (iniziaElaborazioneDaRiga > 0)
		printf ("\nInizio elaborazione AUTHORITY da riga %ld", iniziaElaborazioneDaRiga);


	if (iniziaElaborazioneDaRiga > 0 && positionByOffset)
	{
		long offset = (iniziaElaborazioneDaRiga-1)*(BID_LENGTH+1);
		idXunimarcIn->SeekTo(offset); // marc4cpp->
		idCtr = iniziaElaborazioneDaRiga;
	}

	while(sPtr->ReadLine(idXunimarcIn)) // WithPrefixedMaxSize
	{

//		chr = sPtr->GetFirstChar();
		if (sPtr->GetFirstChar() == '#' || sPtr->IsEmpty())
			continue;

		idCtr++;
		if (iniziaElaborazioneDaRiga && idCtr < iniziaElaborazioneDaRiga)
			continue;


		if (sPtr->Length() > 10)
		{
			if (!creaRecordUnimarcAuthority(sPtr->SubstringData(0,10)))
				erratoCtr++;
		}
		else
		{
			if (!creaRecordUnimarcAuthority(sPtr->data()))
				erratoCtr++;
		}


		ctr++;
		if (!logOgniXRighe || (!(ctr & logOgniXRighe))) //  0xff
		{
//		printf ("\nElaborati %ld records, ultimo bid: %s", ctr, sPtr->data());
		sPtr->ExtractLastChar(); // Remove newline
		logToStdout(__FILE__, __LINE__, LOG_PROGRESS, "Elaborati %ld records, ultimo bid: %s", ctr, sPtr->data());

		}


		if (elaboraNRighe && (ctr == elaboraNRighe))
			break;
	}

//	printf ("\n\nTotale record %ld", ctr);
//	printf ("\nTotale record errati %ld", erratoCtr);
//	printf ("\nTotale record scritti %ld", ctr-erratoCtr);
//	printf ("\n\nTotale records non documento %ld", recordsNonDocumento); // marc4cpp->
//	printf ("\nTotale records elaborati %ld", ctr-recordsNonDocumento); // marc4cpp->

	logToStdout(__FILE__, __LINE__, LOG_PROGRESS, "Totale record %ld", ctr);
	logToStdout(__FILE__, __LINE__, LOG_PROGRESS, "Totale record errati %ld", erratoCtr);
	logToStdout(__FILE__, __LINE__, LOG_PROGRESS, "Totale record scritti %ld", ctr-erratoCtr);
	logToStdout(__FILE__, __LINE__, LOG_PROGRESS, "Totale records non documento %ld", recordsNonDocumento);
	logToStdout(__FILE__, __LINE__, LOG_PROGRESS, "Totale records elaborati %ld", ctr-recordsNonDocumento);


	delete sPtr;
	return true;
	} // End CreaUnimarcAuthority







/*
 * Il reticolo di un'authority deve contenere legami a AUTORI, ENTI, LUOGHI, REPERTORI
 */
/*
tree<std::string> *Marc4cpp::creaReticoloAuthorityAutore(char * id)
{
	bool retb;
	long position;
	long offset;
	CString *sPtr = new CString (1024);
	char buf[80];
	char *entryPtr;

	tree<std::string> * reticolo = new tree<std::string>();

//  	tree<std::string>::pre_order_iterator node;

  	sprintf (buf, "1:AUT:%s", id);
    reticolo->set_head(buf); // root strdup(buf)

    CreaReticoloAutoreAddNodeChildren(reticolo, reticolo->begin(), id, "1", 1);

    if (reticoliOut)
    	writeReticolo(*reticolo, reticolo->begin(), reticolo->end());

#ifdef DEBUG_CONSOLE
    print_tree(*reticolo, reticolo->begin(), reticolo->end());
//    print_children(*reticolo);
#endif
    delete sPtr;

    return reticolo;
} // End Marc4cpp::creaReticoloAuthorityAutore
*/

















tree<std::string> *Marc4cpp::creaReticoloAuthority(char * id)
{
//	bool retb;
//	long position;
//	long offset;
	CString *sPtr = new CString (2048);
	char buf[80];
//	char *entryPtr;

	tree<std::string> * reticolo = new tree<std::string>();

//  	tree<std::string>::pre_order_iterator node;
	if (authority == AUTHORITY_AUTORI)
	{
		sprintf (buf, "1:AUT:%s", id);
	    reticolo->set_head(buf); // root strdup(buf)
		CreaReticoloAutoreAddNodeChildren(reticolo, reticolo->begin(), id, "1", 1);
	}
	else if (authority == AUTHORITY_SOGGETTI)
	{
		sprintf (buf, "1:SOG:%s", id);
	    reticolo->set_head(buf); // root strdup(buf)
		CreaReticoloSoggettoAddNodeChildren(reticolo, reticolo->begin(), id, "1", 1);
	}
	else if (authority == AUTHORITY_TITOLI_UNIFORMI)
	{
		sprintf (buf, "1:TIT:%s", id);
	    reticolo->set_head(buf); // root strdup(buf)
		CreaReticoloTitoloUniformeAddNodeChildren(reticolo, reticolo->begin(), id, "1", 1);
	}
	else if (authority == AUTHORITY_LUOGHI)
		{
			sprintf (buf, "1:LUO:%s", id);
		    reticolo->set_head(buf); // root strdup(buf)
			CreaReticoloLuogoAddNodeChildren(reticolo, reticolo->begin(), id, "1", 1);
		}

    if (reticoliOut)
    	writeReticolo(*reticolo, reticolo->begin(), reticolo->end());

    delete sPtr;
//printf ("Reticolo size=%d", reticolo->size());
    return reticolo;
} // End Marc4cpp::creaReticoloAuthority





bool Marc4cpp::creaRecordUnimarcAuthority(char *id)
{

	try {
		marcRecord->clear();
	tree<std::string>  *reticolo;

	try{

			reticolo = creaReticoloAuthority(id);

	} catch (GenericError e) {
		std::cout << e.errorMessage;
		return false;
	}

	if (creaRecordAuthority(marcRecord, *reticolo, reticolo->begin(), reticolo->end()))
	{
        marcRecord->sortDataFields();
		writeRecordUnimarc();
		if (marcOutTxt)
			writeRecordUnimarcTxt();
		delete reticolo;
		reticolo = 0;
		return true;
	}
	else
	{
		delete reticolo;
		reticolo = 0;
		return false;

	}

	} catch (GenericError e) {
		std::cout << e.errorMessage;
//		stop();
	}


 } // End Marc4cpp::creaRecordUnimarcAuthority




bool Marc4cpp::setupAuthSoggetti(
		char *tagsToGenerateBufferPtr,
		int tagsToGenerate,
		char *marcFilename,
		char *marcTxtFilename,
		char *polo,
		ATTValVector<CString *> *entitaVector,
		ATTValVector<CString *> *relazioniVector,
		ATTValVector<CString *> *offsetVector,
		char *bidXunimarcFilename,
		char *reticoliFilename)
	{
	bool retb;

	authority = AUTHORITY_SOGGETTI;

	retb = setupCommon(tagsToGenerateBufferPtr,
			tagsToGenerate,
			marcFilename,
			marcTxtFilename,
			0,
//			polo,
//			descPolo,
			entitaVector, relazioniVector, offsetVector, 0,
			bidXunimarcFilename,
			reticoliFilename, 0);

	tabelleVector.Add(tbSoggetto = new TbSoggetto(tbSoggettoIn, tbSoggettoOffsetIn, offsetBufferTbSoggettoPtr, elementsTbSoggetto, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
	tabelleVector.Add(tbDescrittore = new TbDescrittore(tbDescrittoreIn, tbDescrittoreOffsetIn, offsetBufferTbDescrittorePtr, elementsTbDescrittore, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
	tabelleVector.Add(trSogDes = new TrSogDes(trSogDesIn, trSogDesOffsetIn, offsetBufferTrSogDesPtr, elementsTrSogDes, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
	tabelleVector.Add(trDesDes = new TrDesDes(trDesDesIn, trDesDesOffsetIn, offsetBufferTrDesDesPtr, elementsTrDesDes, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
	tabelleVector.Add(trDesDesInv = new TrDesDes(trDesDesInvIn, trDesDesInvOffsetIn, offsetBufferTrDesDesInvPtr, elementsTrDesDesInv, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));



// 02/042011
//	// Creiamo l'elenco delle biblioteche codice/descrizione
//	tbfBibliotecaInPoloKV = new CKeyValueVector(tKVSTRING, tKVVOID);
//	if (!loadTbfBibliotecaInPoloRecords(tbfBibliotecaInPoloFilename.data(), polo))
//		return false;

	marc4cppDocumentoAuthority = new Marc4cppDocumentoAuthority(marcRecord, tbSoggetto, tbDescrittore, polo, tagsToGenerateBufferPtr, tagsToGenerate, authority); // , tbTitolo

	marc4cppLegamiAuthority = new Marc4cppLegamiAuthority(marc4cppDocumentoAuthority, marcRecord,
			tbSoggetto,
			tbDescrittore,
			trSogDes,
			trDesDes,
			trDesDesInv,
			tbfBibliotecaInPoloKV,
			keyPlusOffsetPlusLfLength,
			trKeyPlusOffsetPlusLfLength,
			BID_KEY_LENGTH,
			authority
	);


	printf ("\n\nFine Marc4cpp::setupAuthSoggetti");
//marc4CppMallinfo();
	return retb;
} // End Marc4cpp::setupAuthSoggetti









/*
*	Aggiungiamo i legami di un autore
*/
void Marc4cpp::CreaReticoloAutoreAddNodeChildren(tree<std::string>* reticolo, tree<std::string>::pre_order_iterator startNodeIter, const char* bid, const char* level, int levelPos)
{
	bool retb;
	long position;
//	long offset;
	int offset; // 18/03/2014 32 bit

	CString *sPtr, s;
	sPtr = new CString (2048);

	char buf[80];
	int leafId = 0;
	CTokenizer *Tokenizer = new CTokenizer("|");

	OrsChar *Token;
  	tree<std::string>::pre_order_iterator nodeIter;
	char childBid[10+1];
	childBid[10]=0; // eos
	char *entryPtr;
	char curLevel[80];
	CString entryFile;

    // Troviamo le relazioni autore/autore
    // -----------------------------------
//	retb = BinarySearch::search(offsetBufferTrAutAutRelPtr, elementsTrAutAutRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);


	if (offsetBufferTrAutAutRelPtr)
		retb = BinarySearch::search(offsetBufferTrAutAutRelPtr, elementsTrAutAutRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);
	else
	{
		retb = BinarySearch::search(trAutAutRelOffsetIn, elementsTrAutAutRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryFile);
		entryPtr = entryFile.data();
	}



	if (retb)
	{
		// Questo bid ha legami ad altri titoli
		// Dalla posizione prendiamo l'offset
//		offset = atol (entryPtr+BID_KEY_LENGTH); // offsetBufferTrAutAutPtr+position
		if (OFFSET_TYPE == OFFSET_TYPE_BINARY) // 09/02/2015
			//memcpy (&offset, entryPtr+ BID_KEY_LENGTH, 4);	// OFFSET BINARI
			offset =  *((int*)(entryPtr+BID_KEY_LENGTH)); // 24/03/2015

		else
			offset = atoi (entryPtr+BID_KEY_LENGTH); // OFFSET in ASCII

		// Dall'offset del file delle relazioni andiamo a prendere la relazione titolo/titolo
		trAutAutRelIn->SeekTo(offset);
		if (!sPtr->ReadLineWithPrefixedMaxSize(trAutAutRelIn))
			logToStdout(__FILE__, __LINE__, LOG_ERROR, "trAutAutRelIn read failed");


		// Splittiamo la riga negli n elementi che la compongono
		Tokenizer->Assign(sPtr->data());

		Token = Tokenizer->GetToken(); // Remove root

		while(*(Token = Tokenizer->GetToken()))
		{
			sprintf (curLevel, "%s.%d", level,++leafId);

			sprintf (buf, "%s:AUT:%s", curLevel, Token);
			nodeIter = reticolo->append_child(startNodeIter, buf);

		}
//		print_tree(*reticolo, reticolo->begin(), reticolo->end());
	}

    // Troviamo le relazioni inverse autore/autore (tipo legame 4)
    // -----------------------------------
//	retb = BinarySearch::search(offsetBufferTrAutAutRelInvPtr, elementsTrAutAutInvRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);

	if (offsetBufferTrAutAutRelInvPtr)
		retb = BinarySearch::search(offsetBufferTrAutAutRelInvPtr, elementsTrAutAutInvRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);
	else
	{
		retb = BinarySearch::search(trAutAutRelInvOffsetIn, elementsTrAutAutInvRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryFile);
		entryPtr = entryFile.data();
	}

	if (retb)
	{
		// Questo bid ha legami ad altri titoli
		// Dalla posizione prendiamo l'offset
//		offset = atol (entryPtr+BID_KEY_LENGTH); // offsetBufferTrAutAutPtr+position
		if (OFFSET_TYPE == OFFSET_TYPE_BINARY) // 09/02/2015
			//memcpy (&offset, entryPtr+ BID_KEY_LENGTH, 4);	// OFFSET BINARI
			offset =  *((int*)(entryPtr+BID_KEY_LENGTH)); // 24/03/2015

		else
			offset = atoi (entryPtr+BID_KEY_LENGTH); // OFFSET in ASCII

		// Dall'offset del file delle relazioni andiamo a prendere la relazione titolo/titolo
		trAutAutRelInvIn->SeekTo(offset);
		if (!sPtr->ReadLineWithPrefixedMaxSize(trAutAutRelInvIn))
			logToStdout(__FILE__, __LINE__, LOG_ERROR, "trAutAutRelInvIn read failed");


		// Splittiamo la riga negli n elementi che la compongono
		Tokenizer->Assign(sPtr->data());


		// La prima relazione va invertita
		s = Tokenizer->GetToken();

		Token = Tokenizer->GetToken();

		sprintf (curLevel, "%s.%d", level,++leafId);

		//sprintf (buf, "%s:AUT:%s%s", curLevel, s.data(), Token+10);
		sprintf (buf, "%s:AUT:%s", curLevel, Token);	// 11/03/2013 prendi il vid invertito
		nodeIter = reticolo->append_child(startNodeIter, buf);



		while(*(Token = Tokenizer->GetToken()))
		{
			sprintf (curLevel, "%s.%d", level,++leafId);

			sprintf (buf, "%s:AUT:%s", curLevel, Token);
//printf (buf, "arge %s:AUT:%s", curLevel, Token);
			nodeIter = reticolo->append_child(startNodeIter, buf);

			// Crea i figli
//				memcpy(childBid,Token, 10);
//				CreaReticoloAddNodeChildren(reticolo, nodeIter, childBid, curLevel);
		}
//		print_tree(*reticolo, reticolo->begin(), reticolo->end());
	}





delete Tokenizer;
delete sPtr;


} // End Marc4cpp::CreaReticoloAutoreAddNodeChildren





bool Marc4cpp::setupAuthAutori(
		char *tagsToGenerateBufferPtr,
		int tagsToGenerate,
		char *marcFilename,
		char *marcTxtFilename,
		char *polo,
		ATTValVector<CString *> *entitaVector, ATTValVector<CString *> *relazioniVector, ATTValVector<CString *> *offsetVector,
		char *bidXunimarcFilename,
		char *reticoliFilename,
		bool exportViaf,
		int exportMaxViafs
		)
	{
	bool retb;
	this->authority = AUTHORITY_AUTORI;
	this->exportViaf = exportViaf;
	this->exportMaxViafs = exportMaxViafs;

	retb = setupCommon(tagsToGenerateBufferPtr,
			tagsToGenerate,
			marcFilename,
			marcTxtFilename,
			0,
//			polo,
//			descPolo,
			entitaVector, relazioniVector, offsetVector, 0,
			bidXunimarcFilename,
			reticoliFilename,
			0);



	tabelleVector.Add(tbTitolo = new TbTitolo(tbTitoloIn, tbTitoloOffsetIn, offsetBufferTbTitoloPtr, elementsTbTitolo, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
	tabelleVector.Add(tbAutore = new TbAutore(tbAutoreIn, tbAutoreOffsetIn, offsetBufferTbAutorePtr, elementsTbAutore, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
    tabelleVector.Add(tbRepertorio = new TbRepertorio(tbRepertorioIn, tbRepertorioOffsetIn, offsetBufferTbRepertorioPtr, elementsTbRepertorio, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
    tabelleVector.Add(trRepAut = new TrRepAut(trRepAutIn, trRepAutOffsetIn, offsetBufferTrRepAutPtr, elementsTrRepAut, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
    tabelleVector.Add(trIdsbnIdaltriAu = new TrIdsbnIdaltri(trIdsbnIdaltriAuIn, trIdsbnIdaltriAuOffsetIn, offsetBuffertrIdsbnIdaltriAuPtr, elementstrIdsbnIdaltriAu, keyPlusOffsetPlusLfLength, VID_KEY_LENGTH));
    tabelleVector.Add(tbfBiblioteca = new TbfBiblioteca(tbfBibliotecaIn, tbfBibliotecaOffsetIn, offsetBufferTbfBibliotecaPtr, elementsTbfBiblioteca, bibliotecaKeyPlusOffsetPlusLfLength, BIBLIOTECA_KEY_LENGTH)); // BIBLIOTECA_KEY_LENGTH+OFFSET_LENGTH+LF_LENGTH

//	tabelleVector.Add(trTitAutRelInv = new TrTitAutRel(trTitAutRelInvIn, trTitAutRelInvOffsetIn, offsetBufferTrTitAutRelInvPtr, elementsTrTitAutInvRel, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));

    tabelleVector.Add(trAutAut = new TrAutAut(trAutAutIn, trAutAutOffsetIn, offsetBufferTrAutAutPtr, elementsTrAutAut, keyPlusOffsetPlusLfLength, VID_KEY_LENGTH));




// 25/08/2010
//	// Creiamo l'elenco delle biblioteche codice/descrizione
//	tbfBibliotecaInPoloKV = new CKeyValueVector(tKVSTRING, tKVVOID);
//	if (!loadTbfBibliotecaInPoloRecords(tbfBibliotecaInPoloFilename.data(), polo))
//		return false;

	marc4cppDocumentoAuthority = new Marc4cppDocumentoAuthority(marcRecord, tbAutore, polo, tagsToGenerateBufferPtr, tagsToGenerate, authority);

	marc4cppLegamiAuthority = new Marc4cppLegamiAuthority(marc4cppDocumentoAuthority, marcRecord,
			tbAutore,
			trRepAut,
			tbRepertorio,
			trAutAut, // 17/09/2021
			trTitAutRelInvIn, trTitAutRelInvOffsetIn, offsetBufferTrTitAutRelInvPtr, elementsTrTitAutInvRel,
			trIdsbnIdaltriAu,
			trIdsbnIdaltriAuRelIn, trIdsbnIdaltriAuRelOffsetIn, offsetBuffertrIdsbnIdaltriAuRel, elementstrIdsbnIdaltriAuRel,
			tbfBiblioteca,
			tbfBibliotecaInPoloKV,
			keyPlusOffsetPlusLfLength,
			trKeyPlusOffsetPlusLfLength,
			BID_KEY_LENGTH,
			authority,
			tbTitolo);


	printf ("\n\nFine Marc4cpp::setupAuthAutorin");
//marc4CppMallinfo();
	return retb;
} // End Marc4cpp::setupAuthAutori


/*
*	Aggiungiamo i legami ai descrittori
*/
void Marc4cpp::CreaReticoloSoggettoAddNodeChildren(tree<std::string>* reticolo, tree<std::string>::pre_order_iterator startNodeIter, const char* bid, const char* level, int levelPos)
{


} // End Marc4cpp::CreaReticoloSoggettoAddNodeChildren






bool Marc4cpp::creaRecordAuthority(MarcRecord *marcRecord, const tree<std::string>& reticolo, tree<std::string>::pre_order_iterator it, tree<std::string>::pre_order_iterator end)
{
	bool isTitoloOpera=false;
	this->marcRecord = marcRecord;
    char id[10+1];
    id[10]=0;
	string str;
	char* entryReticolo;
    str = *it;
    entryReticolo = (char*)str.data();
    getEntityId(entryReticolo, id);


	if (authority == AUTHORITY_AUTORI)
	{
	    if (!tbAutore->loadRecord(id))
	    	return false;

		// Controlliamo che sia una forma Accettata 'A' e non di Rinvio 'R'
	    char tp_forma_aut = *tbAutore->getField(tbAutore->tp_forma_aut);
		if (tp_forma_aut == 'R') // 18/08/2021
			return false;


	}
	else if (authority == AUTHORITY_LUOGHI) // 05/11/2020
	{
	    if (!tbLuogo->loadRecord(id))
	    	return false;
	}
	else if (authority == AUTHORITY_SOGGETTI)
	{
	    if (!tbSoggetto->loadRecord(id))
	    	return false;
	}
	else if (authority == AUTHORITY_TITOLI_UNIFORMI)
	{
	    if (!tbTitolo->loadRecord(id))
	    	return false;

	    char cd_natura = *tbTitolo->getField(tbTitolo->cd_natura);
	    if (cd_natura != 'A') // 16/09/2021 solo forma accettata (mail Mataloni prima meta' 09/2021)
	    	return false;

	 //   if (POLO.isEqual("INDICE"))
	    if (POLO.isEqual("IND"))
	    {
			isTitoloOpera=true; // SEMPRE
//		    if (!tbTitSet2->loadRecord(id)) // 20/07/2017
//		    	return false;

	    }
		else 		//else if (tbTitSet2->existsRecord(id)) isTitoloOpera=true;
			isTitoloOpera=false;
	}

//tbAutore->dumpRecord();
//tbLuogo->dumpRecord();

	elaboraLeader();


	marc4cppDocumentoAuthority->elaboraDatiDocumento(isTitoloOpera);

	//tbAutore->dumpRecord();

	marc4cppLegamiAuthority->elaboraDatiLegamiAuthority(reticolo, isTitoloOpera);

	if (authority == AUTHORITY_AUTORI && exportViaf)
	{

		if (!marc4cppLegamiAuthority->elaboraDatiViaf(id, exportMaxViafs))
			return false;
	}

	// Se esiste la Sf nella 200 mettiamola anche nella 300 (se esiste)
	// Richiesta Di Geso 24/02/2014
// Richiesta annullata 26/02/2014
//	DataField *df = marcRecord->getDataField("200");
//	if (df)
//	{
//		Subfield *sf = df->getSubfield('f');
//		if (sf)
//		{
//			df = marcRecord->getDataField("300");
//			if (df)
//			{
//				Subfield *sf2 = df->getSubfield('a');
//				sf2->appendData(sf->getData());
//			}
//		}
//	}

	if (authority == AUTHORITY_TITOLI_UNIFORMI)
	{
		Leader *leader = marcRecord->getLeader();
		DataField *df = marcRecord->getDataField("241");
		if (df)
			leader->setPos9Undefined('h');	// 9, typeOfEntity
		else // 231
			leader->setPos9Undefined('f');	// 9, typeOfEntity

		// Controlliamo se abbiamo una 500
		df = marcRecord->getDataField("500");
		if (!df)
		{
			df = marcRecord->getDataField("501"); // abbiamo almeno una 501?
			if (df)
			{
				df->setTag("500"); // Facciamo diventare un 501 una 500 (in quanto obbligatoria)
			}
		}

	}



	return true;
} // End Marc4cpp::creaRecordAuthority




// 04/04/2016
bool Marc4cpp::setupAuthTitoliUniformi(
		char *tagsToGenerateBufferPtr,
		int tagsToGenerate,
		char *marcFilename,
		char *marcTxtFilename,
		char *polo,
		ATTValVector<CString *> *entitaVector,
		ATTValVector<CString *> *relazioniVector,
		ATTValVector<CString *> *offsetVector,
		char *bidXunimarcFilename,
		char *reticoliFilename)
	{
	bool retb;

	authority = AUTHORITY_TITOLI_UNIFORMI;

	retb = setupCommon(tagsToGenerateBufferPtr,
			tagsToGenerate,
			marcFilename,
			marcTxtFilename,
			0,
//			polo,
//			descPolo,
			entitaVector, relazioniVector, offsetVector, 0,
			bidXunimarcFilename,
			reticoliFilename, 0);


	tabelleVector.Add(tbAutore = new TbAutore(tbAutoreIn, tbAutoreOffsetIn, offsetBufferTbAutorePtr, elementsTbAutore, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
    tabelleVector.Add(tbTitolo = new TbTitolo(tbTitoloIn, tbTitoloOffsetIn, offsetBufferTbTitoloPtr, elementsTbTitolo, titoloKeyPlusOffsetPlusLfLength, BID_KEY_LENGTH)); // LONG LONG
    tabelleVector.Add(tbTitSet2 = new TbTitSet2(tbTitSet2In, tbTitSet2OffsetIn, offsetBufferTbTitSet2Ptr, elementsTbTitSet2, titset2KeyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
    tabelleVector.Add(tbRepertorio = new TbRepertorio(tbRepertorioIn, tbRepertorioOffsetIn, offsetBufferTbRepertorioPtr, elementsTbRepertorio, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
    tabelleVector.Add(trRepAut = new TrRepAut(trRepAutIn, trRepAutOffsetIn, offsetBufferTrRepAutPtr, elementsTrRepAut, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));

    // 08/06/2020
    tabelleVector.Add(trRepTit = new TrRepTit(trRepTitIn, trRepTitOffsetIn, offsetBufferTrRepTitPtr, elementsTrRepTit, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));

    // 24/02/2020 Per Titolo dell'opera
    tabelleVector.Add(tbComposizione = new TbComposizione(tbComposizioneIn, tbComposizioneOffsetIn, offsetBufferTbComposizionePtr, elementsTbComposizione, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
    tabelleVector.Add(tbMusica = new TbMusica(tbMusicaIn, tbMusicaOffsetIn, offsetBufferTbMusicaPtr, elementsTbMusica, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));

    // 20/09/2021
    tabelleVector.Add(trAutAut = new TrAutAut(trAutAutIn, trAutAutOffsetIn, offsetBufferTrAutAutPtr, elementsTrAutAut, keyPlusOffsetPlusLfLength, VID_KEY_LENGTH));




	marc4cppDocumentoAuthority = new Marc4cppDocumentoAuthority(marcRecord, tbAutore, tbTitolo, tbTitSet2, tbComposizione, tbMusica, polo, tagsToGenerateBufferPtr, tagsToGenerate, authority);

	marc4cppLegamiAuthority = new Marc4cppLegamiAuthority(marc4cppDocumentoAuthority, marcRecord,
		tbTitolo,
		tbAutore,

//		trRepAut,
		trRepTit,
		trAutAut,
		tbRepertorio,

		trTitAutRelIn, trTitAutRelOffsetIn,
		trTitTitRelIn, trTitTitRelOffsetIn,	// 08/05/2020
		trAutAutRelIn, trAutAutRelOffsetIn,	// 05/06/2020




		offsetBufferTrTitAutRelPtr,
		offsetBufferTrAutAutRelPtr,

		elementsTrTitAutRel,
		elementsTrAutAutRel,

		tbfBibliotecaInPoloKV,
		keyPlusOffsetPlusLfLength,
		trKeyPlusOffsetPlusLfLength,
		BID_KEY_LENGTH,
		authority
);


	printf ("\n\nFine Marc4cpp::setupTitoliUniformi");
//marc4CppMallinfo();
	return retb;
} // End Marc4cpp::setupAuthTitoliUniformi


/*
*	11/04/2016 Aggiungiamo i legami autore al titolo uniforme
*	17/05/2016 Aggiungiamo i legami al titolo
*/
void Marc4cpp::CreaReticoloTitoloUniformeAddNodeChildren(tree<std::string>* reticolo, tree<std::string>::pre_order_iterator startNodeIter, const char* bid, const char* level, int levelPos)
{
	bool retb;
	long position;
	int offset;
	char *entryPtr;
	char curLevel[80];
	CString entryFile;
	CString *sPtr = new CString (4096);
	CTokenizer *Tokenizer = new CTokenizer("|");
	OrsChar *Token;
	char buf[80];
	int leafId = 0;
  	tree<std::string>::pre_order_iterator nodeIter;
	char *BufTailPtr, *aString;
	char childBid[10+1];

    // Troviamo le relazioni agli autori
    // ---------------------------------
	if (offsetBufferTrTitAutRelPtr)
		retb = BinarySearch::search(offsetBufferTrTitAutRelPtr, elementsTrTitAutRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);
	else
	{
		retb = BinarySearch::search(trTitAutRelOffsetIn, elementsTrTitAutRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryFile);
		entryPtr = entryFile.data();
	}


	if (retb)
	{ // Questo Bid ha legami ad autori

		// Dalla posizione prendiamo l'offset
//		offset = atol (entryPtr+BID_KEY_LENGTH); // offsetBuffertrTitAutRelPtr+position
		if (OFFSET_TYPE == OFFSET_TYPE_BINARY) // 09/02/2015
			//memcpy (&offset, entryPtr+ BID_KEY_LENGTH, 4);	// OFFSET BINARI
			offset =  *((int*)(entryPtr+BID_KEY_LENGTH)); // 24/03/2015

		else
			offset = atoi (entryPtr+BID_KEY_LENGTH); // OFFSET in ASCII

		// Dall'offset del file delle relazioni andiamo a prendere la relazione titolo/titolo
		trTitAutRelIn->SeekTo(offset);
		if (!sPtr->ReadLineWithPrefixedMaxSize(trTitAutRelIn))
			logToStdout(__FILE__, __LINE__, LOG_ERROR, "trTitAutRelIn read failed");

//#ifdef DEBUG_LEGAMI
//printf ("\n\nBid+Offset=%s", entryPtr);
//printf ("\nLegami tit_aut=%s", sPtr->data());
//#endif


		// Splittiamo la riga negli n elementi che la compongono
		Tokenizer->Assign(sPtr->data());

		Token = Tokenizer->GetToken(); // Remove root

		while(*(Token = Tokenizer->GetToken()))
		{
			sprintf (curLevel, "%s.%d", level,++leafId);

//			sprintf (buf, "%s.%d:AUT:%s", level,++leafId, Token);
			sprintf (buf, "%s:AUT:%s", curLevel, Token);
//printf ("\nCreaReticoloAddNodeChildren %s", buf);
			nodeIter = reticolo->append_child(startNodeIter, buf);

//			levelPos++;
//printf ("\nargepf buf=%s",buf);
			// Crea i legami agli autori
			BufTailPtr = childBid;
			aString = Token;
			MACRO_COPY_FAST(10);
//			memcpy(childBid,Token, 10);

//			CreaReticoloAddNodeChildren(reticolo, nodeIter, childBid, curLevel, levelPos+1);
		}

//		print_tree(*reticolo, reticolo->begin(), reticolo->end());
	}

    // Troviamo le relazioni ai titoli
    // ---------------------------------
	if (offsetBufferTrTitTitRelPtr)
		retb = BinarySearch::search(offsetBufferTrTitTitRelPtr, elementsTrTitTitRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);
	else
	{
		retb = BinarySearch::search(trTitTitRelOffsetIn, elementsTrTitTitRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryFile);
		entryPtr = entryFile.data();
	}
	if (retb)
	{ // Questo Bid ha legami a titoli

		// Dalla posizione prendiamo l'offset
		if (OFFSET_TYPE == OFFSET_TYPE_BINARY)
			offset =  *((int*)(entryPtr+BID_KEY_LENGTH));

		else
			offset = atoi (entryPtr+BID_KEY_LENGTH);

		// Dall'offset del file delle relazioni andiamo a prendere la relazione titolo/titolo
		trTitTitRelIn->SeekTo(offset);
		if (!sPtr->ReadLineWithPrefixedMaxSize(trTitTitRelIn))
			logToStdout(__FILE__, __LINE__, LOG_ERROR, "trTitTitRelIn read failed");

//#ifdef DEBUG_LEGAMI
//printf ("\n\nBid+Offset=%s", entryPtr);
//printf ("\nLegami tit_aut=%s", sPtr->data());
//#endif


		// Splittiamo la riga negli n elementi che la compongono
		Tokenizer->Assign(sPtr->data());
		Token = Tokenizer->GetToken(); // Remove root
		while(*(Token = Tokenizer->GetToken()))
		{
			sprintf (curLevel, "%s.%d", level,++leafId);
//			sprintf (buf, "%s.%d:AUT:%s", level,++leafId, Token);
			sprintf (buf, "%s:TIT:%s", curLevel, Token);
//printf ("\nCreaReticoloAddNodeChildren %s", buf);
			nodeIter = reticolo->append_child(startNodeIter, buf);

//			levelPos++;
//printf ("\nargepf buf=%s",buf);
			// Crea i legami agli autori
			BufTailPtr = childBid;
			aString = Token;
			MACRO_COPY_FAST(10);
		}
//		print_tree(*reticolo, reticolo->begin(), reticolo->end());
	}




delete Tokenizer;
delete sPtr;


} // End Marc4cpp::CreaReticoloTitoloUniformeAddNodeChildren

bool Marc4cpp::setupAuthLuoghi(
		char *tagsToGenerateBufferPtr,
		int tagsToGenerate,
		char *marcFilename,
		char *marcTxtFilename,
		char *polo,
		ATTValVector<CString *> *entitaVector, ATTValVector<CString *> *relazioniVector, ATTValVector<CString *> *offsetVector,
		ATTValVector<CString *> *codiciVector,
		char *bidXunimarcFilename,
		char *reticoliFilename
		)
	{
	bool retb;
	this->authority = AUTHORITY_LUOGHI;

	retb = setupCommon(tagsToGenerateBufferPtr,
			tagsToGenerate,
			marcFilename,
			marcTxtFilename,
			0,
			entitaVector, relazioniVector, offsetVector, codiciVector,
			bidXunimarcFilename,
			reticoliFilename,
			0);
	codiciPaesKV = new CKeyValueVector(tKVSTRING, tKVSTRING);	// 17/11/2020
	loadDictionary_KV("tb_codici_paes", codiciPaesKV);
	codiciPaesKV->SortAscendingByKey();

	tabelleVector.Add(tbLuogo = new TbLuogo(tbLuogoIn, tbLuogoOffsetIn, offsetBufferTbLuogoPtr, elementsTbLuogo, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
	tabelleVector.Add(tbRepertorio = new TbRepertorio(tbRepertorioIn, tbRepertorioOffsetIn, offsetBufferTbRepertorioPtr, elementsTbRepertorio, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));

	tabelleVector.Add(trRepLuo = new TrRepLuo(trRepLuoIn, trRepLuoOffsetIn, offsetBufferTrRepLuoPtr, elementsTrRepLuo, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));

	tabelleVector.Add(trLuoLuo = new TrLuoLuo(trLuoLuoIn, trLuoLuoOffsetIn, offsetBufferTrLuoLuoPtr, elementsTrLuoLuo, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
	//tabelleVector.Add(trLuoLuoRelInv = new TrLuoLuoRel(trLuoLuoRelInvIn, trLuoLuoRelInvOffsetIn, offsetBufferTrLuoLuoRelInvPtr, elementsTrTitAutInvRel, keyPlusOffsetPlusLfLength, BID_KEY_LENGTH));
     marc4cppDocumentoAuthority = new Marc4cppDocumentoAuthority(marcRecord, tbLuogo, polo, tagsToGenerateBufferPtr, tagsToGenerate, authority);
     marc4cppLegamiAuthority = new Marc4cppLegamiAuthority(marc4cppDocumentoAuthority, marcRecord,
     			tbLuogo,
     			trRepLuo,
     			tbRepertorio,
				trLuoLuoRelIn, trLuoLuoRelOffsetIn, offsetBufferTrLuoLuoRelPtr, elementsTrLuoLuoRel,
				trLuoLuoRelInvIn, trLuoLuoRelInvOffsetIn, offsetBufferTrLuoLuoRelInvPtr, elementsTrLuoLuoRelInv,
     			keyPlusOffsetPlusLfLength,
     			trKeyPlusOffsetPlusLfLength,
     			BID_KEY_LENGTH,
     			authority
     			);
     printf ("\n\nFine Marc4cpp::setupAuthLuoghi\n");
	/*

//marc4CppMallinfo();
 */
	return retb;
} // End Marc4cpp::setupAuthLuoghi

/*
*	Aggiungiamo i legami di un luogo
*/
void Marc4cpp::CreaReticoloLuogoAddNodeChildren(tree<std::string>* reticolo, tree<std::string>::pre_order_iterator startNodeIter, const char* bid, const char* level, int levelPos)
{
	bool retb;
	long position;
//	long offset;
	int offset; // 18/03/2014 32 bit

	CString *sPtr, s;
	sPtr = new CString (2048);

	char buf[80];
	int leafId = 0;
	CTokenizer *Tokenizer = new CTokenizer("|");

	OrsChar *Token;
  	tree<std::string>::pre_order_iterator nodeIter;
	char childBid[10+1];
	childBid[10]=0; // eos
	char *entryPtr;
	char curLevel[80];
	CString entryFile;

    // Troviamo le relazioni autore/autore
    // -----------------------------------
//	retb = BinarySearch::search(offsetBufferTrAutAutRelPtr, elementsTrAutAutRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);


	if (offsetBufferTrLuoLuoRelPtr)
		retb = BinarySearch::search(offsetBufferTrLuoLuoRelPtr, elementsTrLuoLuoRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);
	else
	{
		retb = BinarySearch::search(trLuoLuoRelOffsetIn, elementsTrLuoLuoRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryFile);
		entryPtr = entryFile.data();
	}



	if (retb)
	{
		// Questo bid ha legami ad altri titoli
		// Dalla posizione prendiamo l'offset
//		offset = atol (entryPtr+BID_KEY_LENGTH); // offsetBufferTrAutAutPtr+position
		if (OFFSET_TYPE == OFFSET_TYPE_BINARY) // 09/02/2015
			//memcpy (&offset, entryPtr+ BID_KEY_LENGTH, 4);	// OFFSET BINARI
			offset =  *((int*)(entryPtr+BID_KEY_LENGTH)); // 24/03/2015

		else
			offset = atoi (entryPtr+BID_KEY_LENGTH); // OFFSET in ASCII

		// Dall'offset del file delle relazioni andiamo a prendere la relazione titolo/titolo
		trLuoLuoRelIn->SeekTo(offset);
		if (!sPtr->ReadLineWithPrefixedMaxSize(trLuoLuoRelIn))
			logToStdout(__FILE__, __LINE__, LOG_ERROR, "trLuoLuoRelIn read failed");


		// Splittiamo la riga negli n elementi che la compongono
		Tokenizer->Assign(sPtr->data());

		Token = Tokenizer->GetToken(); // Remove root
//		CString level = "1.";

		while(*(Token = Tokenizer->GetToken()))
		{
			sprintf (curLevel, "%s.%d", level,++leafId);

			sprintf (buf, "%s:LUO:%s", curLevel, Token);
			nodeIter = reticolo->append_child(startNodeIter, buf);

		}
//		print_tree(*reticolo, reticolo->begin(), reticolo->end());
	}

    // Troviamo le relazioni inverse Luogo/luogo (tipo legame 4)
    // -----------------------------------
	if (offsetBufferTrLuoLuoRelInvPtr)
		retb = BinarySearch::search(offsetBufferTrLuoLuoRelInvPtr, elementsTrLuoLuoRelInv, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);
	else
	{
		retb = BinarySearch::search(trLuoLuoRelInvOffsetIn, elementsTrLuoLuoRelInv, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryFile);
		entryPtr = entryFile.data();
	}

	if (retb)
	{
		// Questo bid ha legami ad altri titoli
		// Dalla posizione prendiamo l'offset
//		offset = atol (entryPtr+BID_KEY_LENGTH); // offsetBufferTrAutAutPtr+position
		if (OFFSET_TYPE == OFFSET_TYPE_BINARY) // 09/02/2015
			//memcpy (&offset, entryPtr+ BID_KEY_LENGTH, 4);	// OFFSET BINARI
			offset =  *((int*)(entryPtr+BID_KEY_LENGTH)); // 24/03/2015

		else
			offset = atoi (entryPtr+BID_KEY_LENGTH); // OFFSET in ASCII

		// Dall'offset del file delle relazioni andiamo a prendere la relazione luogo/luogo
		trLuoLuoRelInvIn->SeekTo(offset);
		if (!sPtr->ReadLineWithPrefixedMaxSize(trLuoLuoRelInvIn))
			logToStdout(__FILE__, __LINE__, LOG_ERROR, "trLuoLuoRelInvIn read failed");


		// Splittiamo la riga negli n elementi che la compongono
		Tokenizer->Assign(sPtr->data());


		// La prima relazione va invertita
		s = Tokenizer->GetToken();

		Token = Tokenizer->GetToken();

		sprintf (curLevel, "%s.%d", level,++leafId);

		//sprintf (buf, "%s:Luo:%s%s", curLevel, s.data(), Token+10);
		sprintf (buf, "%s:Luo:%s", curLevel, Token);	// 11/03/2013 prendi il vid invertito
		nodeIter = reticolo->append_child(startNodeIter, buf);



		while(*(Token = Tokenizer->GetToken()))
		{
			sprintf (curLevel, "%s.%d", level,++leafId);

			sprintf (buf, "%s:LUO:%s", curLevel, Token);
//printf (buf, "arge %s:LUO:%s", curLevel, Token);
			nodeIter = reticolo->append_child(startNodeIter, buf);

			// Crea i figli
//				memcpy(childBid,Token, 10);
//				CreaReticoloAddNodeChildren(reticolo, nodeIter, childBid, curLevel);
		}
//		print_tree(*reticolo, reticolo->begin(), reticolo->end());
	}





delete Tokenizer;
delete sPtr;


} // End Marc4cpp::CreaReticoloLuogoAddNodeChildren
