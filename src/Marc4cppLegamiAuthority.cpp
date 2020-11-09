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
 * Marc4cppLegami.cpp
 *
 *  Created on: 29-dic-2008
 *      Author: Arge
 */


#include "Marc4cppLegamiAuthority.h"
#include "library/CTokenizer.h"
#include "BinarySearch.h"
#include <bits/stringfwd.h>
#include "TbReticoloTit.h"
#include "MarcGlobals.h"
#include "library/macros.h"
#include <library/CMisc.h>
#include <stdlib.h>

#ifdef TRACK_MEMORY_LEAKS
    #include "nvwa/debug_new.h"
#endif
using namespace std;

extern void SignalAnError(	const OrsChar *Module, OrsInt Line, const OrsChar * MsgFmt, ...);
extern void SignalAWarning(	const OrsChar *Module, OrsInt Line, const OrsChar * MsgFmt, ...);

//#define EXPORT_VIAF_TITOLI_UNIFORMI

Marc4cppLegamiAuthority::Marc4cppLegamiAuthority(Marc4cppDocumentoAuthority *marc4cppDocumentoAuthority,
		MarcRecord *marcRecord, // per luoghi
		TbLuogo *tbLuogo,
		TrRepLuo *trRepLuo,
		TbRepertorio *tbRepertorio,
		CFile* trLuoLuoIn, CFile* trLuoLuoOffsetIn,	char* offsetBufferTrLuoLuoPtr, long elementsTrLuoLuo,
		CFile* trLuoLuoRelInvIn, CFile* trLuoLuoRelInvOffsetIn, char* offsetBufferTrLuoLuoRelInvPtr, long elementsTrLuoLuotInvRel,
		int keyPlusOffsetPlusLfLength,
		int trKeyPlusOffsetPlusLfLength,
		int key_length,
		int authority)
{
		this->marc4cppDocumentoAuthority = marc4cppDocumentoAuthority;
		this->marcRecord = marcRecord;
		this->tbLuogo = tbLuogo;
		this->trRepLuo = trRepLuo;
		this->tbRepertorio = tbRepertorio;
		this->trLuoLuoIn = trLuoLuoIn;
		this->trLuoLuoOffsetIn = trLuoLuoOffsetIn;
		this->offsetBufferTrLuoLuoPtr = offsetBufferTrLuoLuoPtr;
		this->elementsTrLuoLuo = elementsTrLuoLuo;
		this->trLuoLuoRelInvIn = trLuoLuoRelInvIn;
		this->trLuoLuoRelInvOffsetIn = trLuoLuoRelInvOffsetIn;
		this->offsetBufferTrLuoLuoRelInvPtr = offsetBufferTrLuoLuoRelInvPtr;
		this->elementsTrLuoLuoInvRel = elementsTrLuoLuoInvRel;
		this->elementsTrLuoLuoRel = elementsTrLuoLuoRel;

		this->keyPlusOffsetPlusLfLength = keyPlusOffsetPlusLfLength;
		this->trKeyPlusOffsetPlusLfLength = trKeyPlusOffsetPlusLfLength;
		this->key_length = key_length;
		this->authority = authority;
		init();
}
Marc4cppLegamiAuthority::Marc4cppLegamiAuthority(Marc4cppDocumentoAuthority *marc4cppDocumentoAuthority,
		MarcRecord *marcRecord, // Autori
		TbAutore *tbAutore,
		TrRepAut *trRepAut,

		TbRepertorio *tbRepertorio,
		CFile* trAutAutIn, CFile* trAutAutOffsetIn,	char* offsetBufferTrAutAutPtr, long elementsTrAutAut,
		CFile* trTitAutRelInvIn, CFile* trTitAutRelInvOffsetIn, char* offsetBufferTrTitAutRelInvPtr, long elementsTrTitAutInvRel,

		CKeyValueVector *tbfBibliotecaKV,
		int keyPlusOffsetPlusLfLength,
		int trKeyPlusOffsetPlusLfLength,
		int key_length,
		int authority,
		TbTitolo *tbTitolo)
{
		this->marc4cppDocumentoAuthority = marc4cppDocumentoAuthority;
		this->marcRecord = marcRecord;


		this->tbAutore = tbAutore;
		this->trRepAut = trRepAut;
		this->tbRepertorio = tbRepertorio;

		this->trAutAutIn = trAutAutIn;
		this->trAutAutOffsetIn = trAutAutOffsetIn;
		this->offsetBufferTrAutAutPtr = offsetBufferTrAutAutPtr;
		this->elementsTrAutAut = elementsTrAutAut;


		this->trTitAutRelInvIn = trTitAutRelInvIn;
		this->trTitAutRelInvOffsetIn = trTitAutRelInvOffsetIn;
		this->offsetBufferTrTitAutRelInvPtr = offsetBufferTrTitAutRelInvPtr;
		this->elementsTrTitAutInvRel = elementsTrTitAutInvRel;
		this->elementsTrAutAutRel = elementsTrAutAutRel;



		this->tbfBibliotecaKV = tbfBibliotecaKV;
		this->keyPlusOffsetPlusLfLength = keyPlusOffsetPlusLfLength;
		this->trKeyPlusOffsetPlusLfLength = trKeyPlusOffsetPlusLfLength;
		this->key_length = key_length;
		this->authority = authority;
		this->tbTitolo = tbTitolo;
		init();
}

Marc4cppLegamiAuthority::Marc4cppLegamiAuthority(Marc4cppDocumentoAuthority *marc4cppDocumentoAuthority,
		MarcRecord *marcRecord, // Soggetti
		TbSoggetto *tbSoggetto,
		TbDescrittore *tbDescrittore,
		TrSogDes *trSogDes,
		TrDesDes *trDesDes,
		TrDesDes *trDesDesInv,
		CKeyValueVector *tbfBibliotecaKV,
		int keyPlusOffsetPlusLfLength,
		int trKeyPlusOffsetPlusLfLength,
		int key_length,
		int authority)
{
	this->marc4cppDocumentoAuthority = marc4cppDocumentoAuthority;
	this->marcRecord = marcRecord;
	this->tbSoggetto = tbSoggetto;
	this->tbDescrittore = tbDescrittore;
	this->trSogDes = trSogDes;
	this->trDesDes = trDesDes;
	this->trDesDesInv = trDesDesInv;
	this->tbfBibliotecaKV = tbfBibliotecaKV;
	this->keyPlusOffsetPlusLfLength = keyPlusOffsetPlusLfLength;
	this->trKeyPlusOffsetPlusLfLength = trKeyPlusOffsetPlusLfLength;
	this->key_length = key_length;
	this->authority = authority;
	init();

}

Marc4cppLegamiAuthority::Marc4cppLegamiAuthority(Marc4cppDocumentoAuthority *marc4cppDocumentoAuthority,
		MarcRecord *marcRecord, // Titoli uniformi
		TbTitolo *tbTitolo,
		TbAutore *tbAutore,
//		TrRepAut *trRepAut,
		TrRepTit *trRepTit,
		TbRepertorio *tbRepertorio,

		CFile* trTitAutRelIn, CFile* trTitAutRelOffsetIn,
		CFile* trTitTitRelIn, CFile* trTitTitRelOffsetIn,

		CFile* trAutAutRelIn, CFile* trAutAutRelOffsetIn, // 05/06/2020 per 500 $9

		char* offsetBufferTrTitAutRelPtr,
		long elementsTrTitAutRel,
		long elementsTrAutAutRel,

		CKeyValueVector *tbfBibliotecaKV,
		int keyPlusOffsetPlusLfLength,
		int trKeyPlusOffsetPlusLfLength,
		int key_length,
		int authority
		)
{
		this->marc4cppDocumentoAuthority = marc4cppDocumentoAuthority;
		this->marcRecord = marcRecord;

		this->tbTitolo = tbTitolo;
		this->tbAutore = tbAutore;

//		this->trRepAut = trRepAut;
		this->trRepTit = trRepTit;

		this->tbRepertorio = tbRepertorio;

		this->trTitAutRelIn = trTitAutRelIn;
		this->trTitAutRelOffsetIn = trTitAutRelOffsetIn;

		this->trAutAutRelIn = trAutAutRelIn;
		this->trAutAutRelOffsetIn = trAutAutRelOffsetIn;



		this->offsetBufferTrTitAutRelPtr = offsetBufferTrTitAutRelPtr;
		this->elementsTrTitAutRel = elementsTrTitAutRel;
		this->elementsTrAutAutRel = elementsTrAutAutRel;



		this->tbfBibliotecaKV = tbfBibliotecaKV;
		this->keyPlusOffsetPlusLfLength = keyPlusOffsetPlusLfLength;
		this->trKeyPlusOffsetPlusLfLength = trKeyPlusOffsetPlusLfLength;
		this->key_length = key_length;
		this->authority = authority;
		init();
}




/*
 * Dati provenienti dalla tb_codici (NABI)
 *
 * 'C' = Collana
 * 'M' = Monografia
 * 'T' = Pubblicato con
 * 'P' = Titolo parallelo
 * 'A' = Titolo di raggruppamento controllato
 * 'D' = Titolo sviluppato o estrapolato
 * 'B' = Titolo di raggruppamento non controllato (Titolo in lingua originale)
 * 'S' = Periodico
 * 'N' = Titolo analitico (spoglio)
 * 'W' = Volume privo di titolo significativo (tipico dell'enciclopedia ed opere in + volumi)
 *
	Legami Titolo/Titolo (LETT)
		01      fa parte di
		02      supplemento di
		03      contiene anche
		04      continuazione di
		05      edizione successiva di
		06      ha per titolo di raggruppamento non controllato
		07      altra edizione di
		08      ha per altro titolo
		09      ha per titolo di raggruppamento controllato
		41      assorbe
		42      si fonde con
		43      continuazione parziale di
		51      contiene
 *
 *
 */
void Marc4cppLegamiAuthority::initLicr()
{
    tbCodiciKV->Add("A08D", "A517D");
    tbCodiciKV->Add("B08D", "B517D");
    tbCodiciKV->Add("C01C", "C410C");
    tbCodiciKV->Add("C04C", "C430C");
    tbCodiciKV->Add("C05C", "C440C");
    tbCodiciKV->Add("C07C", "C451C");
    tbCodiciKV->Add("C08D", "C517D");
    tbCodiciKV->Add("C08P", "C510P");
    tbCodiciKV->Add("C09A", "C500A");
    tbCodiciKV->Add("M01C", "M410C");
    tbCodiciKV->Add("M01M", "M461M");
    tbCodiciKV->Add("M01S", "M461S");
    tbCodiciKV->Add("M02M", "M422M");
    tbCodiciKV->Add("M02S", "M422S");
    tbCodiciKV->Add("M03T", "M423T");
    tbCodiciKV->Add("M04M", "M430M");
    tbCodiciKV->Add("M04S", "M430S");
    tbCodiciKV->Add("M05M", "M440M");
    tbCodiciKV->Add("M05S", "M440S");
    tbCodiciKV->Add("M06B", "M454B");
    tbCodiciKV->Add("M07C", "M451C");
    tbCodiciKV->Add("M07M", "M451M");
    tbCodiciKV->Add("M07S", "M451S");
    tbCodiciKV->Add("M08D", "M517D");
    tbCodiciKV->Add("M08P", "M510P");
    tbCodiciKV->Add("M09A", "M500A");
    tbCodiciKV->Add("M51M", "M463M");
    tbCodiciKV->Add("M51N", "M464N");
    tbCodiciKV->Add("M51W", "M463W");
    tbCodiciKV->Add("N01C", "N410C");
//    tbCodiciKV->Add("N01M", "N461M");
    tbCodiciKV->Add("N01M", "N463M");
//    tbCodiciKV->Add("N01N", "N461N"); NO. Errore se esiste
//    tbCodiciKV->Add("N01S", "N461S");
    tbCodiciKV->Add("N01S", "N463S");
//    tbCodiciKV->Add("N01W", "N461W");
    tbCodiciKV->Add("N01W", "N463W");
    tbCodiciKV->Add("N06B", "N454B");
    tbCodiciKV->Add("N08D", "N517D");
    tbCodiciKV->Add("N08P", "N510P");
    tbCodiciKV->Add("N09A", "N500A");
    tbCodiciKV->Add("S01C", "S410C");
    tbCodiciKV->Add("S02S", "S422S");
    tbCodiciKV->Add("S04S", "S430S");
    tbCodiciKV->Add("S05S", "S440S");
    tbCodiciKV->Add("S07S", "S451S");
    tbCodiciKV->Add("S08D", "S517D");
    tbCodiciKV->Add("S08P", "S510P");
//    tbCodiciKV->Add("S09A", "S500A");
    tbCodiciKV->Add("S09A", "S530A");
    tbCodiciKV->Add("S41S", "S434S");
    tbCodiciKV->Add("S42S", "S447S");

    tbCodiciKV->Add("S43S", "S431S");
    tbCodiciKV->Add("A08V", "A431V"); // 19/05/16

    tbCodiciKV->Add("A01A", "A531eA"); // 19/05/16
    tbCodiciKV->Add("A02A", "A531fA"); // 19/05/16
    tbCodiciKV->Add("A04A", "A531hA"); // 19/05/16
    tbCodiciKV->Add("A10A", "A531gA"); // 19/05/16


    tbCodiciKV->Add("S51N", "S464N");
    tbCodiciKV->Add("T06B", "T454B");
    tbCodiciKV->Add("T08D", "T517D");
    tbCodiciKV->Add("T08P", "T510P");
    tbCodiciKV->Add("T09A", "T500A");
    tbCodiciKV->Add("W01C", "W410C");
    tbCodiciKV->Add("W01M", "W461M");
    tbCodiciKV->Add("W01S", "W461S");
    tbCodiciKV->Add("W03T", "W423T");
    tbCodiciKV->Add("W08D", "W517D");
    tbCodiciKV->Add("W09A", "W500A");
    tbCodiciKV->Add("W51N", "W464N");
} // end initLicr


Marc4cppLegamiAuthority::~Marc4cppLegamiAuthority() {
	stop();
}


void Marc4cppLegamiAuthority::clearTbCodiciVEctor() {
	TbCodici *tc;
	if (tbCodiciKV)
	{

		for (int i=0; i < tbCodiciKV->Length(); i++)
		{
			tc = (TbCodici *)tbCodiciKV->GetValue(i);
			delete tc;
		}
		tbCodiciKV->Clear();
	}
} // End Marc4cppLegamiAuthority::clearLegamiVector




void Marc4cppLegamiAuthority::getEntityId(char *entryReticolo, char *id)
{
	char *ptr = strchr(entryReticolo, ':');
	ptr = strchr(ptr+1, ':');
	memcpy (id, ptr+1, 10);
}










/*
 * A4A - Legami tra autori in forma (A)ccettata
 * A8R - Legami tra autori in forma (A)ccettata e forma di (R)invio
 *
 * Sembra(dicasi sembra) sufficiente il ciclo sui figli dell' autore al primo livello
 */
void Marc4cppLegamiAuthority::creaLegamiAutoreAutore()
{
	string str;
//	unsigned int pos;
	int pos; // 24/04/2020

	char bid[10+1];	bid[10]=0;
	DataField *df;

	// Cicliamo sul figli di root per cercare gli autori
	tree<std::string>::pre_order_iterator it=reticolo.begin();

	str = *it;
	int bidStart = str.find_last_of(':');
	memcpy (bid, (char *)str.data()+bidStart+1, 10);

//	std::cout << "AUT children of :" << *it << std::endl;
	tree<std::string>::sibling_iterator ch=reticolo.begin().begin(); //h1
	while(ch!=reticolo.end().end()) { // h1
		str = *ch;
		// Troviamo il separatore della gerarchia
		if ((pos=str.find(':'))!=string::npos)
		{
			if (str.find("AUT:", pos+1)!=string::npos)
			{
//				std::cout << std::endl << str ;
				// Andiamo a lavorare sui figli
				tree<std::string>::pre_order_iterator ch1=ch.begin(); // .begin()
				while(ch1 != ch.end()) { // h1
					str = *ch1;
					// Troviamo il separatore della gerarchia
					if ((pos=str.find(':'))!=string::npos)
					{ // figlio puo' essere solo un legame ad autore
						df = creaLegameAutoreAutore((char *)str.data(), pos);
//						if (df)
//							marcRecord->addDataField(df);
					}
				++ch1;
				} // End while ch1
			}
			// Facciamo corrente
			if ((pos=str.find(':'))!=string::npos)
				df = creaLegameAutoreAutore((char *)str.data(), pos);

		}
	   ++ch;
	   }

} // End Marc4cppLegamiAuthority::creaLegamiAutoreAutore


void Marc4cppLegamiAuthority::creaLegamiLuogoLuogo()
{
	string str;
//	unsigned int pos;
	int pos; // 24/04/2020

	char lid[10+1];	lid[10]=0;
	DataField *df;

	// Cicliamo sul figli di root per cercare gli autori
	tree<std::string>::pre_order_iterator it=reticolo.begin();

	str = *it;
	int bidStart = str.find_last_of(':');
	memcpy (lid, (char *)str.data()+bidStart+1, 10);

//	std::cout << "AUT children of :" << *it << std::endl;
	tree<std::string>::sibling_iterator ch=reticolo.begin().begin(); //h1
	while(ch!=reticolo.end().end()) { // h1
		str = *ch;
		// Troviamo il separatore della gerarchia
		if ((pos=str.find(':'))!=string::npos)
		{
			if (str.find("LUO:", pos+1)!=string::npos)
			{
//				std::cout << std::endl << str ;
				// Andiamo a lavorare sui figli
				tree<std::string>::pre_order_iterator ch1=ch.begin(); // .begin()
				while(ch1 != ch.end()) { // h1
					str = *ch1;
					// Troviamo il separatore della gerarchia
					if ((pos=str.find(':'))!=string::npos)
					{ // figlio puo' essere solo un legame ad autore
						df = creaLegameLuogoLuogo((char *)str.data(), pos);
//						if (df)
//							marcRecord->addDataField(df);
					}
				++ch1;
				} // End while ch1
			}
			// Facciamo corrente
			if ((pos=str.find(':'))!=string::npos)
				df = creaLegameLuogoLuogo((char *)str.data(), pos);

		}
	   ++ch;
	   }

} // End Marc4cppLegamiAuthority::creaLegamiLuogoLuogo





// iterate over children only
bool Marc4cppLegamiAuthority::haResponsabilitaPrincipale(const tree<std::string>& tr) // print_children
{
//	char responsabilita;
	string str;
	int pos;
//	char *entryReticoloPtr;

//	tree<std::string>::pre_order_iterator it=tr.begin();
//	std::cout << "children of :" << *it << std::endl;
//printf ("..\n");
	tree<std::string>::sibling_iterator ch=tr.begin().begin(); //h1
	while(ch!=tr.end().end()) { // h1
//	   std::cout << (*ch) << std::endl;
	   str = *ch;
		if ((pos = str.find("AUT:")) != -1)
		{
			// Prendiamo il BID per accedere alla tbTitolo
//			entryReticoloPtr = (char *)str.data();
//			responsabilita = *(entryReticoloPtr+pos+15);
//			if (responsabilita == '1')
//			responsabilita = str.at(pos+15);
			if (str.at(pos+15) == '1') // Controlla se responsabilita principale
				return true;
		}
	   ++ch;
	   }
	return false;
} // End haResponsabilitaPrincipale



/*
	Tag+Def:		400 Rinvii Autori Personali
					This field contains the tracing for a form of personal name referred from.


	--------
	Obbligatorieta':	Facoltativo
	Ripetibilita':	Ripetibile
	Indicatore1:	blank (not defined)
	Indicatore2:	specifies the way the name is entered:
						0  Name entered under forename or direct order
						1  Name entered under surname
	Sottocampi:
		Data Subfields
		--------------
			$a Entry element  Not repeatable.
			$b Part of name other than entry element  Not repeatable.
			$c Additions to names other than dates  Repeatable.
			$d Roman numerals  Not repeatable.
			$f Dates  Not repeatable.
			$g Expansion of initials of forename  Not repeatable.
			$4 Relator code  Repeatable.

			$j Form subdivision  Repeatable.
			$x Topical subdivision  Repeatable.
			$y Geographical subdivision  Repeatable.
			$z Chronological subdivision Repeatable.

		Control Subfields
		-----------------
			$0  Instruction phrase   Not repeatable.
			$2  Subject system code   Not repeatable.
			$3  Authority record identifier    Not repeatable.
			$5  Tracing control   Not repeatable.
			$6  Interfield linking data   Not repeatable.
			$7  Script of cataloguing and script of the base heading  Not repeatable.
			$8  Language of cataloguing and language of the base heading   Not repeatable.

		Notes on field contents
		-----------------------
			The field contains a personal name heading formulated according to the rules used by the cataloguing agency
			which created it. The heading in 400 is a variant or non-preferred form of the heading in 200.


*/
DataField * Marc4cppLegamiAuthority::creaTag400_RinvioAutorePersonale(TbAutore * tbAutoreRinvio)
	{
	DataField *df;

	df = new DataField();

	df->setTag((char *)"400");
	creaTag_40x(df, tbAutoreRinvio);

	marcRecord->addDataField(df);

	return df;
	} // End creaTag790RinvioAutorePersonale




DataField * Marc4cppLegamiAuthority::creaTag500_VediAncheAutorePersonale(TbAutore * tbAutoreRinvio)
	{
	DataField *df;

	df = new DataField();

	df->setTag((char *)"500");
	creaTag_40x(df, tbAutoreRinvio);

	marcRecord->addDataField(df);

	return df;
	} // End creaTag790_RinvioAutorePersonale




/*
Tag+Def:		810 Source Data Found (FONTE BIBLIOGRAFICA ESITO POSITIVO, Repertori)

--------
Obbligatorieta':	Optional
Ripetibilita':	Ripetibile. Il campo e' ripetibile (per SBN non lo e')
Indicatore1:	Non definito
Indicatore2:	Non definito

Sottocampi:

	$a Citation
		Subfield $a contains the citation for a published work or a description of any source or action that
		provided information about the heading. The information provided is sufficient to identify both the work
		and the location within the work. Not repeatable.

	$b Information found
		Subfield $b contains a statement of the information found in the source cited in $a. Not repeatable.

*/

DataField * Marc4cppLegamiAuthority::creaTag_81xRepertorio(char *tag)
{
	DataField *df=0;
	Subfield *sf;

	// Dalla tabella di relazione prendiamo il repertorio
	CString repertorio;

	repertorio = trRepAut->getField(trRepAut->id_repertorio);

	repertorio.leftPadding('0', 10);

	// Andiamo sulla tabella di repertorio a prendere le info
	if (tbRepertorio->loadRecord(repertorio.data()))
	{
//tbRepertorio->dumpRecord();

		df = new DataField();
		df->setTag(tag);

		sf = new Subfield('a', tbRepertorio->getFieldString(tbRepertorio->ds_repertorio));
	    //sf->setData();
		df->addSubfield(sf);

		marcRecord->addDataField(df);
	}
	else
	{
		SignalAnError(__FILE__, __LINE__, "\nRepertorio %s non trovato nella tabella dei repertori", repertorio.data());
	}

	return df;
}

DataField * Marc4cppLegamiAuthority::creaTag_81xLuogoRepertorio(char *tag)
{
	DataField *df=0;
	Subfield *sf;

	// Dalla tabella di relazione prendiamo il repertorio
	CString repertorio;

	repertorio = trRepLuo->getField(trRepLuo->id_repertorio);

	repertorio.leftPadding('0', 10);

	// Andiamo sulla tabella di repertorio a prendere le info
	if (tbRepertorio->loadRecord(repertorio.data()))
	{
//tbRepertorio->dumpRecord();

		df = new DataField();
		df->setTag(tag);

		sf = new Subfield('a', tbRepertorio->getFieldString(tbRepertorio->ds_repertorio));
		df->addSubfield(sf);

		if(!strcmp(tag,"810"))
		{
			if(! trRepLuo->getFieldString(trRepLuo->nota_rep_luo)->IsEmpty())
			{
				sf = new Subfield('b', trRepLuo->getFieldString(trRepLuo->nota_rep_luo));
		df->addSubfield(sf);
			}
		}
		marcRecord->addDataField(df);
	}
	else
	{
		SignalAnError(__FILE__, __LINE__, "\nRepertorio %s non trovato nella tabella dei repertori", repertorio.data());
	}

	return df;
}
DataField * Marc4cppLegamiAuthority::creaTag_81xRepertorio_Titolo(char *tag)
{
	DataField *df=0;
	Subfield *sf;

	// Dalla tabella di relazione prendiamo il repertorio
	CString repertorio;

	repertorio = trRepTit->getField(trRepTit->id_repertorio);

	repertorio.leftPadding('0', 10);

	// Andiamo sulla tabella di repertorio a prendere le info
	if (tbRepertorio->loadRecord(repertorio.data()))
	{
//tbRepertorio->dumpRecord();

		df = new DataField();
		df->setTag(tag);

//		sf = new Subfield('a', tbRepertorio->getFieldString(tbRepertorio->ds_repertorio));
//		sf = new Subfield('a', tbRepertorio->getFieldString(tbRepertorio->id_repertorio));
		sf = new Subfield('a', tbRepertorio->getFieldString(tbRepertorio->cd_sig_repertorio));
		df->addSubfield(sf);

		marcRecord->addDataField(df);
	}
	else
	{
		SignalAnError(__FILE__, __LINE__, "\nRepertorio %s non trovato nella tabella dei repertori", repertorio.data());
	}

	return df;
}











/*
	// 931 Descrittori di soggetto
			This field contains a topical subject heading.
	Obbligatorieta':
	Ripetibilita':
	Indicatore1:
	Indicatore2:
	Sottocampi:
	-----------
		Data Subfields
		--------------

		Control Subfields
		-----------------

*/
void Marc4cppLegamiAuthority::creaLegamiSoggettoDescrittori()
{

	bool retb;
	long position;
	//long offset;
	char *entryPtr;
	CString entryFile;


	const char *cid, *cid2;
	cid = tbSoggetto->getField(tbSoggetto->cid);

	// Dalla tabella tr_sog_des troviamo i legami ai descrittori
	// Dal cid vediamo se abbiamo almeno un legame ad un descrittore

//	if (trSogDes->getOffsetBufferTbPtr())
//		retb = BinarySearch::search(trSogDes->getOffsetBufferTbPtr(), trSogDes->getElementsTb(), keyPlusOffsetPlusLfLength, cid, key_length, position, &entryPtr);
//	else
//	{
//		retb = BinarySearch::search(trSogDes->getTbOffsetIn(), trSogDes->getElementsTb(), keyPlusOffsetPlusLfLength, cid, key_length, position, &entryFile);
//		entryPtr = entryFile.data();
//	}
//
//
//	if (retb)
//	{
		if (trSogDes->existsRecord(cid)) // NonUnique. Offset del CID punta al primo della serie
		{
//			while (trSogDes->loadNextRecord(cid))  // Prendiamo un descrittore alla volta
			while (trSogDes->loadNextRecord())  // Prendiamo un descrittore alla volta
			{
				// Stiamo cambiando CID?
				cid2 = trSogDes->getField(trSogDes->cid);
				if (strcmp (cid, cid2))
					break; // fine

				retb = tbDescrittore->loadRecord(trSogDes->getField(trSogDes->did)); // Carica il record del descrittore
				if (!retb)
				{
					SignalAnError(__FILE__, __LINE__, "\nDescrittore % s per soggetto %s", trSogDes->getField(trSogDes->did), cid);
					continue;
				}
				creaTag931_LegameSoggettoDescrittore();
			} // end while
		} // End se esiste legame soggetto/descrittore
//	}



	//return df;
} // End






void Marc4cppLegamiAuthority::creaLegamiAutoreRepertori()
{
	bool retb;
	long position;
	//long offset;
	char *entryPtr;
	CString entryFile;


	const char *vid;
	vid = tbAutore->getField(tbAutore->vid);

	// Dal vid vediamo se abbiamo almeno un legame autore/repertorio
//	retb = BinarySearch::search(trRepAut->getOffsetBufferTbPtr(), trRepAut->getElementsTb(), keyPlusOffsetPlusLfLength, vid, key_length, position, &entryPtr);

	if (trRepLuo->getOffsetBufferTbPtr())
		retb = BinarySearch::search(trRepAut->getOffsetBufferTbPtr(), trRepAut->getElementsTb(), keyPlusOffsetPlusLfLength, vid, key_length, position, &entryPtr);
	else
	{
		retb = BinarySearch::search(trRepAut->getTbOffsetIn(), trRepAut->getElementsTb(), keyPlusOffsetPlusLfLength, vid, key_length, position, &entryFile);
		entryPtr = entryFile.data();
	}

	if (retb)
	{
		if (trRepLuo->existsRecordNonUnique(vid))
		{
			while (trRepAut->loadNextRecord(vid))  // Prendiamo un repertotrio alla volta
			{
				if (*trRepAut->getField(trRepAut->fl_trovato) == 'S')
					creaTag_81xRepertorio((char *)"810");
				else
					creaTag_81xRepertorio((char *)"815");
			} // end while
		} // End se esiste legame autore/repertorio
	}


} // End Marc4cppLegamiAuthority::creaLegamiAutoreRepertori

void Marc4cppLegamiAuthority::creaLegamiLuogoRepertori()
{
	bool retb;
	long position;
	//long offset;
	char *entryPtr;
	CString entryFile;


	const char *lid;
	lid = tbLuogo->getField(tbLuogo->lid);

	// Dal vid vediamo se abbiamo almeno un legame autore/repertorio
//	retb = BinarySearch::search(trRepAut->getOffsetBufferTbPtr(), trRepAut->getElementsTb(), keyPlusOffsetPlusLfLength, vid, key_length, position, &entryPtr);

	if (trRepLuo->getOffsetBufferTbPtr())
		retb = BinarySearch::search(trRepLuo->getOffsetBufferTbPtr(), trRepLuo->getElementsTb(), keyPlusOffsetPlusLfLength, lid, key_length, position, &entryPtr);
	else
	{
		retb = BinarySearch::search(trRepLuo->getTbOffsetIn(), trRepLuo->getElementsTb(), keyPlusOffsetPlusLfLength, lid, key_length, position, &entryFile);
		entryPtr = entryFile.data();
	}

	if (retb)
	{
		if (trRepLuo->existsRecordNonUnique(lid))
		{
			while (trRepLuo->loadNextRecord(lid))  // Prendiamo un repertotrio alla volta
			{
			//	if (*trRepLuo->getField(trRepLuo->fl_trovato) == 'S')
					creaTag_81xLuogoRepertorio((char *)"810");
//				else
//					creaTag_81xRepertorio((char *)"815");
			} // end while
		} // End se esiste legame luogo/repertorio
	}


} // End Marc4cppLegamiAuthority::creaLegamiAutoreRepertori

void Marc4cppLegamiAuthority::creaLegamiTitoloRepertori()
{
	bool retb;
	long position;
	//long offset;
	char *entryPtr;
	CString entryFile;
	DataField *df;


	const char *bid = tbTitolo->getField(tbTitolo->bid);

	if (trRepTit->getOffsetBufferTbPtr())
		retb = BinarySearch::search(trRepTit->getOffsetBufferTbPtr(), trRepTit->getElementsTb(), keyPlusOffsetPlusLfLength, bid, key_length, position, &entryPtr);
	else
	{
		retb = BinarySearch::search(trRepTit->getTbOffsetIn(), trRepTit->getElementsTb(), keyPlusOffsetPlusLfLength, bid, key_length, position, &entryFile);
		entryPtr = entryFile.data();
	}

	if (retb)
	{
		if (trRepTit->existsRecordNonUnique(bid))
		{
			while (trRepTit->loadNextRecord(bid))  // Prendiamo un repertotrio alla volta
			{
				if (*trRepTit->getField(trRepTit->fl_trovato) == 'S')
				{

//trRepTit->dumpRecord();

					df = creaTag_81xRepertorio_Titolo((char *)"810");

					CString * sPtr = trRepTit->getFieldString(trRepTit->nota_rep_tit);
					if (! sPtr->IsEmpty())
					{
//						Subfield *sf = new Subfield('b', tbTitolo->getField(tbTitolo->nota_cat_tit));
						Subfield *sf = new Subfield('b', sPtr);

						df->addSubfield(sf);
					}

				}
				else
					creaTag_81xRepertorio_Titolo((char *)"815");
			} // end while
		} // End se esiste legame autore/repertorio
	}


} // End Marc4cppLegamiAuthority::creaLegamiTitoloRepertori










void Marc4cppLegamiAuthority::init()
{
	legamiVectorKV = new CKeyValueVector(tKVSTRING, tKVVOID);
	siArg = 0;
	tbCodiciKV = new CKeyValueVector(tKVSTRING, tKVSTRING);
	initLicr();
}



void Marc4cppLegamiAuthority::clearLegamiVector() {
	DataField *df;
	if (legamiVectorKV)
	{
		// Dobbiamo rimuovere i DataFields else MEMORY LEAK
		for (int i=0; i < legamiVectorKV->Length(); i++)
		{
			df = (DataField *)legamiVectorKV->GetValue(i);
			delete df;
		}
		legamiVectorKV->Clear();
	}
} // End Marc4cppLegamiAuthority::clearLegamiVector



void Marc4cppLegamiAuthority::stop() {
	clearLegamiVector();
	delete legamiVectorKV;

	delete tbCodiciKV;
}



DataField * Marc4cppLegamiAuthority::creaTag410_RinvioAutoreCollettivo(TbAutore * tbAutoreRinvio)
	{
	DataField *df;

	df = new DataField();
	df->setTag((char *)"410");
	creaTag_41x(df, tbAutoreRinvio);

	marcRecord->addDataField(df);

	return df;
	} // End creaTag410_RinvioAutoreCollettivo




DataField * Marc4cppLegamiAuthority::creaLegameAutoreAutore(char *entryReticoloPtr, int pos)
{
	bool retb;
	DataField *df = 0;
//	DataField *dfDup = 0;
	char tipoLegame = *(strchr (entryReticoloPtr, ',')+1);
	CString cdRelazione;
	int posCdRelazione = pos + 5 + 11 + 1 + 1;
	cdRelazione.AppendString( entryReticoloPtr + posCdRelazione, 3);

	// Prendiamo la c�lasse per accedere alla tbClasse
	char vid[10+1];	vid[10]=0;

	memcpy (vid, entryReticoloPtr+pos+5, 10);

	TbAutore * tbAutoreRinvio = new TbAutore(tbAutore);


	if (true)
	{

	retb = tbAutoreRinvio->loadRecord(vid);
	if (!retb)
		return 0; // Record non trovato

	char tpNomeAut = *tbAutoreRinvio->getField(tbAutoreRinvio->tp_nome_aut);
	if ( tpNomeAut == 'A' ||
		tpNomeAut == 'B' ||
		tpNomeAut == 'C' ||
		tpNomeAut == 'D')
	{
		if (tipoLegame == '8')
			df = creaTag400_RinvioAutorePersonale(tbAutoreRinvio);
		else if (tipoLegame == '4')
		{
			// Legame invertito (SEE ALSO)
			df = creaTag500_VediAncheAutorePersonale(tbAutoreRinvio);
		}
		else {
			SignalAnError(__FILE__, __LINE__, "\nTipo legame autore/autore sconosciuto %c", tipoLegame);
			return df;
		}
	}
	else
	{
		if (tipoLegame == '8')
			df = creaTag410_RinvioAutoreCollettivo(tbAutoreRinvio);
		else if (tipoLegame == '4')
		{
			// Legame invertito (SEE ALSO)
			df = creaTag510_VediAncheAutoreCollettivo(tbAutoreRinvio);
		}
		else {
			SignalAnError(__FILE__, __LINE__, "\nTipo legame autore/autore sconosciuto %c", tipoLegame);
			return df;
		}


	}
	}
	delete tbAutoreRinvio;
	return df;
} // End Marc4cppLegamiAuthority::creaLegameAutoreAutore

DataField * Marc4cppLegamiAuthority::creaLegameLuogoLuogo(char *entryReticoloPtr, int pos)
{
	bool retb;
	DataField *df = 0;
//	DataField *dfDup = 0;
	char tipoLegame = *(strchr (entryReticoloPtr, ',')+1);
	CString cdRelazione;
	int posCdRelazione = pos + 5 + 11 + 1 + 1;
	cdRelazione.AppendString( entryReticoloPtr + posCdRelazione, 3);

	// Prendiamo la c�lasse per accedere alla tbClasse
	char lid[10+1];	lid[10]=0;

	memcpy (lid, entryReticoloPtr+pos+5, 10);

	TbLuogo * tbLuogoRinvio = new TbLuogo(tbLuogo);

	retb = tbLuogoRinvio->loadRecord(lid);
	if (!retb)
	{
      //  SignalAWarning(__FILE__, __LINE__, "\Luogo con lid %s non trovato", lid);
		delete tbLuogoRinvio;
		return 0; // Record non trovato
	}
	df=new DataField();
	df->setTag("460");
	Subfield *sf;
	sf = new Subfield('3', lid, 10);
	df->addSubfield(sf);
	sf = new Subfield('d', tbLuogoRinvio->getField(tbLuogoRinvio->ds_luogo), tbLuogoRinvio->getFieldLength(tbLuogoRinvio->ds_luogo));
	df->addSubfield(sf);
	marcRecord->addDataField(df);
	delete tbLuogoRinvio;

	return df;
} // End Marc4cppLegamiAuthority::creaLegameLuogoLuogo



void Marc4cppLegamiAuthority::creaTag_40x(DataField *df, TbAutore * tbAutoreRinvio)
{
	Subfield *sf;
	string str;
	char *nomePtr = tbAutoreRinvio->getField(tbAutoreRinvio->ds_nome_aut);
	char *breakPtr=0;
	df->setIndicator1(' ');
	const char *tpNome = tbAutoreRinvio->getField(tbAutoreRinvio->tp_nome_aut);
	if (*tpNome == 'A' || *tpNome == 'a' || *tpNome == 'B' || *tpNome == 'b')
		df->setIndicator2('0');
	else
		df->setIndicator2('1');


	if (*tpNome == 'A' || *tpNome == 'a' || *tpNome == 'B' || *tpNome == 'b')
		breakPtr = strstr(nomePtr, " <");
	else if (*tpNome == 'C' || *tpNome == 'c' || *tpNome == 'D' || *tpNome == 'd')
		breakPtr = strstr(nomePtr, ", ");

	int len;
	if (breakPtr)
	{
		*breakPtr = 0; // EOS
		len = breakPtr-nomePtr;
	}
	else
		len = tbAutoreRinvio->getFieldLength(tbAutoreRinvio->ds_nome_aut);



	sf = new Subfield('a', nomePtr, len);


	//sf->setData(); // tbAutore->getField(tbAutore->ds_nome_aut)
	df->addSubfield(sf);

	if (*tpNome == 'C' || *tpNome == 'c' || *tpNome == 'D' || *tpNome == 'd')
	{
		if (breakPtr)
		{
			*breakPtr = ','; // rimetti
			sf = new Subfield('b', breakPtr, tbAutoreRinvio->getFieldLength(tbAutoreRinvio->ds_nome_aut)-len);
			//sf->setData();
			df->addSubfield(sf);
		}

	}

	//Qualificazione
	if (*tpNome == 'A' || *tpNome == 'a' || *tpNome == 'B' || *tpNome == 'b')
	{
		if (breakPtr)
		{

			sf = new Subfield('c', breakPtr+1, tbAutoreRinvio->getFieldLength(tbAutoreRinvio->ds_nome_aut)-len-1);
//			sf->setData();
			df->addSubfield(sf);

		}

	}

//tbAutoreRinvio->dumpRecord();

//	sf->setData(tbAutoreRinvio->getField(tbAutoreRinvio->vid));
	char * vid = tbAutoreRinvio->getField(tbAutoreRinvio->vid);
	if (TIPO_SCARICO == TIPO_SCARICO_UNIMARC
			&& DATABASE_ID != DATABASE_INDICE  // 08/03/2013
	)
		sf = new Subfield('3', vid, 10);
		//sf->setData();
	else // TIPO_SCARICO_OPAC
	{
//		CString id = "IT\\ICCU\\";
		CString id((char *)"IT\\ICCU\\", 8);
		int pos = 4;
		id.AppendString(vid, pos); // Prendi il Polo
		id.AppendChar('\\');
		id.AppendString(vid+pos, 10-pos);	 // Prendi resto del bid
		sf = new Subfield('3', &id);
		//sf->setData();
	}
	df->addSubfield(sf);

} // End creaTag_40x

void Marc4cppLegamiAuthority::creaTag_41x(DataField *df, TbAutore * tbAutoreRinvio)
{
    Subfield *sf;
    string str;
    char *tpNome;
    char *ptr, *breakPtr;

    char *nomePtr = tbAutoreRinvio->getField(tbAutoreRinvio->ds_nome_aut);

    tpNome = tbAutoreRinvio->getField(tbAutoreRinvio->tp_nome_aut);
    if (*tpNome == 'E' || *tpNome == 'e' || *tpNome == 'G' || *tpNome == 'g')
        df->setIndicator1('0');
    else
        df->setIndicator1('1');

    if (*tpNome == 'G' || *tpNome == 'g')
        df->setIndicator2('1');
    else
        df->setIndicator2('2');

     breakPtr = strstr(nomePtr, " <");

    if ((*tpNome == 'G' || *tpNome == 'g') && !breakPtr)
        breakPtr = strstr(nomePtr, " : ");

//    if (breakPtr)
//        *breakPtr = 0; // EOS
	int len;
	if (breakPtr)
	{
		*breakPtr = 0; // EOS
		len = breakPtr-nomePtr;
	}
	else
		len = tbAutoreRinvio->getFieldLength(tbAutoreRinvio->ds_nome_aut);



    CString s;
    if (ptr = strchr (nomePtr, '*')) // abbiamo almeno un asterisco?
    {
    	if (ptr != nomePtr)
    	{
			*ptr = 0;
			s = NSB.data();	// No sort begin
			s.AppendString(nomePtr, ptr-nomePtr);
			s.AppendString(&NSE); // No sort end
    	}
    	nomePtr = ptr+1;
    }

    CString s2;s2 = nomePtr;
    s2.removeCharacterOccurances('*');

    s.AppendString(&s2);

    sf = new Subfield('a', &s);
    //sf->setData(); // nomePtr
    df->addSubfield(sf);


    if (*tpNome == 'G' || *tpNome == 'g')
    {
    	if (breakPtr)
    	{
            *breakPtr = ' ';
            s = breakPtr;
            s.removeCharacterOccurances('*');
            sf = new Subfield('b', &s);
            //sf->setData();
            df->addSubfield(sf);
    	}
    }

    //Qualificazione
    if (breakPtr && *(breakPtr+1) == '<')
    {
        if(ptr = strstr (breakPtr, " ; "))
            *ptr = 0;

        sf = new Subfield('c', breakPtr+1, tbAutoreRinvio->getFieldLength(tbAutoreRinvio->ds_nome_aut)-len-1);
        //sf->setData();
        df->addSubfield(sf);
    }

//    sf->setData(tbAutoreRinvio->getField(tbAutoreRinvio->vid));
	char * vid = tbAutoreRinvio->getField(tbAutoreRinvio->vid);
	if (TIPO_SCARICO == TIPO_SCARICO_UNIMARC
			&& DATABASE_ID != DATABASE_INDICE  // 08/03/2013
			)
	    sf = new Subfield('3', vid, 10);
		//sf->setData();
	else // TIPO_SCARICO_OPAC
	{

//		CString id = "IT\\ICCU\\";
		CString id((char *)"IT\\ICCU\\", 8);
		int pos = 4;
		id.AppendString(vid, pos); // Prendi il Polo
		id.AppendChar('\\');
		id.AppendString(vid+pos, 10-pos);	 // Prendi resto del bid
	    sf = new Subfield('3', &id);
		//sf->setData();
	}





    df->addSubfield(sf);

} // End creaTag_41x



DataField * Marc4cppLegamiAuthority::creaTag510_VediAncheAutoreCollettivo(TbAutore * tbAutoreRinvio)
	{
	DataField *df;

	df = new DataField();
	df->setTag((char *)"510");
	creaTag_41x(df, tbAutoreRinvio);

	marcRecord->addDataField(df);

	return df;
	} // End creaTag510_VediAncheAutoreCollettivo



void Marc4cppLegamiAuthority::creaLegamiDescrittoriDescrittori(char *didBasePtr)
{
	bool retb;
	long position;
	//long offset;
	char *entryPtr;
	const char *didBase2, *didColl;
	CString entryFile;
	CString didBase = didBasePtr;

	// Dal descrittore base troviamo i descrittori collegati
		if (trDesDes->existsRecordNonUnique(didBase.data()))
		{
			while (trDesDes->loadNextRecord())  // Prendiamo un descrittore alla volta
			{
				// Stiamo cambiando descrittore
				didBase2 = trDesDes->getField(trDesDes->did_base);
				if (strcmp (didBase.data(), didBase2))
					break; // fine

				didColl = trDesDes->getField(trDesDes->did_coll);
				retb = tbDescrittore->loadRecord(didColl);
				if (!retb)
				{
					SignalAnError(__FILE__, __LINE__, "\nDescrittore base % s per descrittore coll %s", didBase.data(), didColl);
					continue;
				}
				creaTag932_LegameDescrittoreDescrittore(trDesDes->getFieldString(trDesDes->tp_legame), &didBase);
			} // end while
		} // End se esiste legame descrittore base descrittore collegato



} // End creaLegamiDescrittoriDescrittori



void Marc4cppLegamiAuthority::creaTag932_LegameDescrittoreDescrittore(CString *tpLegame, CString *didBase)
{
	DataField *df=0;
	Subfield *sf;
	CString nota;

	df = new DataField();
	df->setTag((char *)"932");

	sf = new Subfield('a', tbDescrittore->getFieldString(tbDescrittore->ds_descrittore));
	//sf->setData();
	df->addSubfield(sf);

	nota = tbDescrittore->getField(tbDescrittore->nota_descrittore);
	if (!nota.IsEmpty()) // !nota.StartsWith("null") &&
	{
		sf = new Subfield('b', &nota);
		df->addSubfield(sf);
	}

	sf = new Subfield('2', tbDescrittore->getFieldString(tbDescrittore->cd_soggettario));
	df->addSubfield(sf);

	sf = new Subfield('3', tbDescrittore->getFieldString(tbDescrittore->did));
	df->addSubfield(sf);

	sf = new Subfield('4', didBase);
	df->addSubfield(sf);

	tpLegame->Strip(tpLegame->trailing, ' ');
	sf = new Subfield('5', tpLegame);
	df->addSubfield(sf);


	marcRecord->addDataField(df);
} // End creaTag932_LegameDescrittoreDescrittore

void Marc4cppLegamiAuthority::creaTag931_LegameSoggettoDescrittore()
{
	DataField *df=0;
	Subfield *sf;
	CString nota;

	df = new DataField();
	df->setTag((char *)"931");

	sf = new Subfield('a', tbDescrittore->getFieldString(tbDescrittore->ds_descrittore));
	df->addSubfield(sf);

	nota = tbDescrittore->getField(tbDescrittore->nota_descrittore);
	if (!nota.IsEmpty()) // !nota.StartsWith("null") &&
	{
		sf = new Subfield('b', &nota);
		df->addSubfield(sf);
	}

	sf = new Subfield('2', tbDescrittore->getFieldString(tbDescrittore->cd_soggettario));
	df->addSubfield(sf);


	sf = new Subfield('3', tbDescrittore->getFieldString(tbDescrittore->did));
	df->addSubfield(sf);


	marcRecord->addDataField(df);

	creaLegamiDescrittoriDescrittori((char*)tbDescrittore->getField(tbDescrittore->did));
} // End creaTag931_LegameSoggettoDescrittore


bool Marc4cppLegamiAuthority::elaboraDatiViaf(char *id, int exportMaxViafs)
{
// Per ogni titolo prendiamo solo il livello di autorita' dal + alto al + basso
// Esportiamo il titolo come tag 910
//printf ("\nExporting viafs per vid: %s", id);

// Dal vid troviamo tutti i titoli per cui l'autore ha il cd_livello1
// spazzolandoci il file di relazioni invertite

//Prendiamo i bid dal file delle relazioni
bool retb;
long position;
//long offset;
int offset; // 18/03/2014 32 bit
CString *sPtr, s;
sPtr = new CString (2048);

char buf[80];
int leafId = 0;
tree<std::string>::pre_order_iterator nodeIter;
char childBid[10+1];
childBid[10]=0; // eos
char *entryPtr;
char curLevel[80];
CString entryFile;

bool haLegameTitolo = false;

// Troviamo le relazioni autore/autore
// -----------------------------------
//	retb = BinarySearch::search(offsetBufferTrAutAutRelPtr, elementsTrAutAutRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);


if (offsetBufferTrTitAutRelInvPtr)
	retb = BinarySearch::search(offsetBufferTrTitAutRelInvPtr, elementsTrTitAutInvRel, keyPlusOffsetPlusLfLength, id, BID_KEY_LENGTH, position, &entryPtr);
else
{
	retb = BinarySearch::search(trTitAutRelInvOffsetIn, elementsTrTitAutInvRel, keyPlusOffsetPlusLfLength, id, BID_KEY_LENGTH, position, &entryFile);
	entryPtr = entryFile.data();
}

if (retb)
{
	// Questo bid ha legami ad altri titoli
	// Dalla posizione prendiamo l'offset
//	offset = atol (entryPtr+BID_KEY_LENGTH); // offsetBufferTrAutAutPtr+position
	if (OFFSET_TYPE == OFFSET_TYPE_BINARY) // 09/02/2015
//		memcpy (&offset, entryPtr+ BID_KEY_LENGTH, 4);	// OFFSET BINARI
		offset =  *((int*)(entryPtr+BID_KEY_LENGTH)); // 24/03/2015
	else
		offset = atoi (entryPtr+BID_KEY_LENGTH); // OFFSET in ASCII

	// Dall'offset del file delle relazioni andiamo a prendere la relazione titolo/titolo
	trTitAutRelInvIn->SeekTo(offset);
	if (!sPtr->ReadLine(trTitAutRelInvIn))
	{
        SignalAnError(__FILE__, __LINE__, "read file delle relazioni failed");
        return false;
	}


	CKeyValueVector *cdLivelloVidIsbdKV = new CKeyValueVector(tKVSTRING, tKVSTRING);

	for (char resp = '1'; resp <= '3'; resp++)
	{
// 02/08/2016
#ifndef	EXPORT_VIAF_TITOLI_UNIFORMI
		// Prendiamo i titoli legati ad autore con responsabilita' 1
		if (!getTitoliViafConResponabilita(sPtr, resp, cdLivelloVidIsbdKV, exportMaxViafs))
			return false;
		if (cdLivelloVidIsbdKV->Length() >= exportMaxViafs)
			break;
#else
		if (!getTitoliUniformiViaf(sPtr, resp, cdLivelloVidIsbdKV, exportMaxViafs))
			return false;
#endif
	}

//	// Prendiamo i titoli legati ad autore con responsabilita' 1
//	if (!getTitoliViavConResponabilita(sPtr, '1', cdLivelloVidIsbdKV, exportMaxViafs))
//		return false;
//
//	// Abbiamo un numero sufficiente di titoli?
//	if (cdLivelloVidIsbdKV->Length() < exportMaxViafs)
//		{
//		// NO! Allora cerchiamo i titoli legati ad autore con responsabilita' 3! Richiesta Di geso 24/02/2014
//		if (!getTitoliViavConResponabilita(sPtr, '3', cdLivelloVidIsbdKV,  exportMaxViafs))
//			return false;
//		}


	// Ordiniamo in ordine discendente per cd_livello
	cdLivelloVidIsbdKV->SortDescendingByKey();

	CString key;

	DataField *df=0;
	Subfield *sf;
	int viafCtr=0;
	CString vid, value;

	if (cdLivelloVidIsbdKV->Length())
		haLegameTitolo = true;

	for (int i=0; i < cdLivelloVidIsbdKV->Length(); i++)
	{
		value.Clear();

		key = (char *)cdLivelloVidIsbdKV->GetKey(i);
		value = (char *)cdLivelloVidIsbdKV->GetValue(i);

//		printf ("\n%s : %s", key.data(), value.data());

		df = new DataField();
		df->setTag((char *)"910");

		vid = value.SubstringData(0,10);


		value.CropLeftBy(10);
		sf = new Subfield('a', &value); // TITLE
		df->addSubfield(sf);


		sf = new Subfield('b', &key); // cd_livello autorita'
		df->addSubfield(sf);


		CString id((char *)"IT\\ICCU\\", 8);
		int pos = 3;
		id.AppendString(vid.data(), pos); // Prendi il Polo
		id.AppendChar('\\');
		id.AppendString(vid.data()+pos, 10-pos);	 // Prendi resto del bid
		sf = new Subfield('3', &id);
		df->addSubfield(sf);


		marcRecord->addDataField(df);

		viafCtr++;
// 02/08/2016
#ifndef	EXPORT_VIAF_TITOLI_UNIFORMI
		if (viafCtr == exportMaxViafs)
			break;
#endif
	}

delete cdLivelloVidIsbdKV;
//		print_tree(*reticolo, reticolo->begin(), reticolo->end());
}
delete sPtr;

if (!haLegameTitolo)
{
	printf ("\nVID %s non ha legami verso un titolo con responsabilita' 1, 2 o 3", id );
	return false;
}

return true;
} // End elaboraDatiViaf



bool Marc4cppLegamiAuthority::getTitoliViafConResponabilita(CString *sPtr, char responsabilita, CKeyValueVector *cdLivelloVidIsbdKV, int exportMaxViafs)
	{
	CTokenizer *Tokenizer = new CTokenizer("|");
	OrsChar *Token;

	// Splittiamo la riga negli n elementi che la compongono
	Tokenizer->Assign(sPtr->data());
	Token = Tokenizer->GetToken(); // Remove root
	CString value;
	while(*(Token = Tokenizer->GetToken()))
	{
//		sprintf (curLevel, "%s.%d", level,++leafId);
//		sprintf (buf, "%s:AUT:%s", curLevel, Token);
//		nodeIter = reticolo->append_child(startNodeIter, buf);
		//printf ("\nToken=%s", Token);


		if (*(Token+11) == responsabilita) // Pizzichiamo direttamente tpResponsabilita
		{
//			printf ("\nElabora Token=%s", Token);
			*(Token+10)=0; // EOS // prendiamo il bid
			// Cerchiamo nella tbTitolo il titolo
			if (!tbTitolo->loadRecord(Token))
			{
		        SignalAnError(__FILE__, __LINE__, "read file dei titoli failed");
		        return false;
			}
//			tbTitolo->dumpRecord();
			// Mettiamo i titoli in un vettore per ordinarli in base al cd_livello
			int cdLivello = atoi (tbTitolo->getField(tbTitolo->cd_livello));
			char *natura = tbTitolo->getField(tbTitolo->cd_natura);
			if (*natura != 'M') // Per evitare le nature 'T'
				continue;
				value =  tbTitolo->getField(tbTitolo->bid);
				CString isbd = tbTitolo->getField(tbTitolo->isbd);
				int posCompTit = isbd.IndexSubString(PUNTEGGIATURA_AREA_TITOLO_INIZIO_COMPLEMENTO_TITOLO); // " : "

				int endAreaTitolo = isbd.IndexSubString(". - "); // Fine area
				if (posCompTit != -1 && endAreaTitolo > posCompTit)
				{
					CString title = isbd.SubstringData(0,posCompTit);
					// 29/05/13 Controlliamo che il titolo non sia un solo numero (problema VIAF)
					bool isDigit=true;
					for (int i=0; i < title.Length(); i++)
						if (!isdigit(title.GetChar(i)))
						{
							isDigit=false;
							break;
						}
					if (isDigit && title.Length() < 4) // 4 potrebbe essere un anno
					{
						isbd.CropLeftBy(posCompTit+3);
						isbd.PrependString(": ");
						isbd.PrependString(title.data());
					}
					else
						isbd.CropRightFrom(endAreaTitolo); // posCompTit
				}
				else
				{
				if (endAreaTitolo != -1)
					isbd.CropRightFrom(endAreaTitolo);
				}
				value.AppendString(isbd.data());

				cdLivelloVidIsbdKV->Add(tbTitolo->getField(tbTitolo->cd_livello),value.data());

				if (cdLivelloVidIsbdKV->Length() == exportMaxViafs)
				{
					delete Tokenizer;
					return true;
				}
		}
		else
		{
			// printf ("\nSkip Token=%s", Token); troppo rumore
		}
	} // end while tokens
	delete Tokenizer;

	return true;
	} // End getTitoliViavConResponabilita





bool Marc4cppLegamiAuthority::elaboraDatiLegamiAuthority(const tree<std::string>& reticolo, bool isTitoloOpera)
{
	this->reticolo = reticolo;
    clearLegamiVector();
	tree<std::string>::pre_order_iterator it = reticolo.begin();

    rootId[10]=0;

    string str;
	char* entryReticolo;
    str = *it;
    entryReticolo = (char*)str.data();

    getEntityId(entryReticolo, rootId);

	if (authority == AUTHORITY_AUTORI)
	{
	    CString rootRecord; rootRecord = tbAutore->getStringRecordData();
		creaLegamiAutoreAutore();
		creaLegamiAutoreRepertori();
	}
	else if (authority == AUTHORITY_LUOGHI)
	{
	    CString rootRecord; rootRecord = tbLuogo->getStringRecordData();
	    if(marc4cppDocumentoAuthority->isTagToGenerate("460"))
	    	creaLegamiLuogoLuogo();
		if(marc4cppDocumentoAuthority->isTagToGenerate("810"))
			creaLegamiLuogoRepertori();
	}
	else if(authority == AUTHORITY_SOGGETTI)
	{
	    CString rootRecord; rootRecord = tbSoggetto->getStringRecordData();
		creaLegamiSoggettoDescrittori();
		//creaLegamiDescrittoriDescrittori();
	}
	else if(authority == AUTHORITY_TITOLI_UNIFORMI)
	{
	    CString rootRecord; rootRecord = tbTitolo->getStringRecordData();
		creaLegamiTitoloAutore(isTitoloOpera);

		creaLegamiTitoloRepertori(); // 08/06/2020

		creaLegamiTitoloTitolo(); // 19/05/2016

	}


	return true;
} // End Marc4cppLegamiAuthority::elaboraDatiLegamiAlDocumento


void Marc4cppLegamiAuthority::creaLegamiTitoloAutore(bool isTitoloOpera)
{
	string str;
//	unsigned int pos;
	int pos; // 24/04/2020

//	char bid[10+1];	bid[10]=0;
	DataField *df=0;

	// Cicliamo sul figli di root per cercare gli autori
	tree<std::string>::pre_order_iterator it=reticolo.begin();

	str = *it;
//	int bidStart = str.find_last_of(':');
//	memcpy (bid, (char *)str.data()+bidStart+1, 10);

//	std::cout << "AUT children of :" << *it << std::endl;
	tree<std::string>::sibling_iterator ch=reticolo.begin().begin(); //h1
	while(ch!=reticolo.end().end()) { // h1
		str = *ch;
		// Troviamo il separatore della gerarchia
		if ((pos=str.find(':'))!=string::npos)
		{
			if (str.find("AUT:", pos+1)!=string::npos)
			{
////				std::cout << std::endl << str ;
//				// Andiamo a lavorare sui figli
//				tree<std::string>::pre_order_iterator ch1=ch.begin(); // .begin()
//				while(ch1 != ch.end()) { // h1
//					str = *ch1;
//					// Troviamo il separatore della gerarchia
//					if ((pos=str.find(':'))!=string::npos)
//					{ // figlio puo' essere solo un legame ad autore
//						df = creaLegameTitoloAutore((char *)str.data(), pos);
//					}
//				++ch1;
//				} // End while ch1

				// Facciamo corrente
//			if ((pos=str.find(':'))!=string::npos)
				df = creaLegameTitoloAutore((char *)str.data(), pos, isTitoloOpera);
			}

		}
	   ++ch;
	   }

} // End Marc4cppLegamiAuthority::creaLegamiTitoloAutore




// Crea legami tra titoli di authority
void Marc4cppLegamiAuthority::creaLegamiTitoloTitolo() // bool isTitoloOpera
{
	string str;
//	unsigned int pos;
	int pos; // 24/04/2020
	char bid[10+1];	bid[10]=0;
	DataField *df=0;

	// Cicliamo sul figli di root per cercare gli autori
	tree<std::string>::pre_order_iterator it=reticolo.begin();

	str = *it;
	int bidStart = str.find_last_of(':');
	memcpy (bid, (char *)str.data()+bidStart+1, 10);

//	std::cout << "AUT children of :" << *it << std::endl;
	tree<std::string>::sibling_iterator ch=reticolo.begin().begin(); //h1
	while(ch!=reticolo.end().end()) { // h1
		str = *ch;
		// Troviamo il separatore della gerarchia
//		if ((pos=str.find(':'))!=string::npos)
//		{
//			if (str.find("TIT:", pos+1)!=string::npos)
//			{
////				std::cout << std::endl << str ;
//				// Andiamo a lavorare sui figli
//				tree<std::string>::pre_order_iterator ch1=ch.begin(); // .begin()
//				while(ch1 != ch.end()) { // h1
//					str = *ch1;
//					// Troviamo il separatore della gerarchia
//					if ((pos=str.find(':'))!=string::npos)
//					{ // figlio puo' essere solo un legame ad autore
//						df = creaLegameTitoloAutore((char *)str.data(), pos);
//					}
//				++ch1;
//				} // End while ch1
//			}

			// Facciamo corrente
			pos = str.find("TIT:");
			if (pos != string::npos)
				df = creaLegameTitoloTitolo((char *)str.data(), pos+4);
//		}
	   ++ch;
	   }

} // End Marc4cppLegamiAuthority::creaLegamiTitoloTitolo

DataField * Marc4cppLegamiAuthority::creaLegameTitoloTitolo(char *entryReticoloPtr, int pos) {
	DataField *df = 0;
	DataField *df1 = 0;
	Subfield *sf=0;

	// Prendiamo il bid per accedere alla tb_titolo
	char bid[10 + 1];
	bid[10] = 0;
	CString cdRelazione; // , cdStrumentoMusicale
	char cdNaturaDa, cdNaturaA;


	char *BufTailPtr, *aString;
	BufTailPtr = bid;
	aString =  entryReticoloPtr + pos;
	MACRO_COPY_FAST(10);


	CString cs = aString;
	ATTValVector <CString *> stringVect;
	cs.Split(stringVect, ',');


//	memcpy(vid, entryReticoloPtr + pos + 5, 10);
//	int posCdRelazione = pos + 10 + 5;

	cdNaturaDa = stringVect.Entry(3)->GetFirstChar();// *(entryReticoloPtr + posCdRelazione);
	cdNaturaA = stringVect.Entry(4)->GetFirstChar(); // *(entryReticoloPtr + posCdRelazione + 2);

	cdRelazione = stringVect.Entry(1)->data(); //.AppendString( entryReticoloPtr + posCdRelazione, 3);

	stringVect.DeleteAndClear();
	bool hasTitolo=true;
	if (!tbTitolo->loadRecord(bid))
	{
        SignalAnError(__FILE__, __LINE__, "read file dei titoli failed");
//        return df;
        hasTitolo=false;
	}
	CString isbd;
	if (hasTitolo)
		isbd = tbTitolo->getField(tbTitolo->isbd);
	int idx = isbd.IndexSubString(". - ");
	if (idx > -1)
		isbd.CropRightFrom(idx);
	// Se opera con autore ce lo dice la 241, se esiste
	DataField *df241 = marcRecord->getDataField((char *)"241");


	if (cdNaturaDa == 'A' &&  cdRelazione.isEqual("08") && (cdNaturaA == 'V' || cdNaturaA == 'D'))
	{
		bool retb;

//		isbd.Split(stringVect, ". ");
//		CString *sPtr = stringVect.Entry(0);
		CString *sPtr = &isbd;

		if ((idx = sPtr->IndexCharFrom('*', 0, CString::forward)) > 0) // abbiamo almeno un asterisco?
		{
			sPtr->PrependString(NSB.data());
			sPtr->Replace("*", NSE.data(), 1);
		}
		else
		{
			if (sPtr->GetFirstChar() == '*')
				sPtr->ExtractFirstChar();
		}



		// Troviamo le relazioni agli autori
		// ---------------------------------
		long position;
		char *entryPtr;
		CString entryFile;

//		if (offsetBufferTrTitAutRelPtr)
//			retb = BinarySearch::search(offsetBufferTrTitAutRelPtr, elementsTrTitAutRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryPtr);
//		else
//			retb = BinarySearch::search(trTitAutRelOffsetIn, elementsTrTitAutRel, keyPlusOffsetPlusLfLength, bid, BID_KEY_LENGTH, position, &entryFile);

		// Se opera con autore ce lo dice la 241, se esiste
		DataField *df241 = marcRecord->getDataField((char *)"241");

		if (df241 && marc4cppDocumentoAuthority->isTagToGenerate("441"))
		{ // Rinvio ad opera con autore

			df = new DataField((char *)"441", 3);
			sf = new Subfield('a', sPtr);
			df->addSubfield(sf);

//			sf = new Subfield('9', bid, 10);
			sf = new Subfield('3', bid, 10);	// 12/05/2020
			df->addSubfield(sf);

		}
		else
		{ // Rinvio ad opera senza autore
			if (marc4cppDocumentoAuthority->isTagToGenerate("431"))
			{
				df = new DataField((char *)"431", 3);
				sf = new Subfield('a', sPtr);
				df->addSubfield(sf);
//				sf = new Subfield('9', bid, 10);
				sf = new Subfield('3', bid, 10);	// 12/05/2020
				df->addSubfield(sf);
			}
		}

		stringVect.DeleteAndClear();



	} // end if legame A08V/D
	else
	{
//		if (df231 && marc4cppDocumentoAuthority->isTagToGenerate("531"))
		if (df241 && marc4cppDocumentoAuthority->isTagToGenerate("531"))
			df = new DataField((char *)"531", 3);
		else
		{	if (marc4cppDocumentoAuthority->isTagToGenerate("530"))
				df = new DataField((char *)"530", 3);
		}

		if (!df)
			return df;


		sf = new Subfield('3', bid, 10);
		df->addSubfield(sf);
		sf = 0;
		if (cdNaturaDa == 'A' &&  cdRelazione.isEqual("01") && cdNaturaA == 'A')
			sf = new Subfield('5', (char *)"xxe", 3); // Sezione o Parte
		else if (cdNaturaDa == 'A' &&  cdRelazione.isEqual("02") && cdNaturaA == 'A')
			sf = new Subfield('5', (char *)"xxf", 3); // supplemento
		else if (cdNaturaDa == 'A' &&  cdRelazione.isEqual("04") && cdNaturaA == 'A')
			sf = new Subfield('5', (char *)"xxh", 3); // continuazione
		else if (cdNaturaDa == 'A' &&  cdRelazione.isEqual("10") && cdNaturaA == 'A')
			sf = new Subfield('5', (char *)"xxg", 3); // opera correlata
		if (sf)
			df->addSubfield(sf);


		if (isbd.Length())
		{
			// Scompattiamo il titolo nelle sue parti
			ATTValVector <CString *> stringVect;
			if (cdNaturaDa == 'A' &&  cdRelazione.isEqual("01") && cdNaturaA == 'A')
				isbd.Split(stringVect, ". ");
			else
				stringVect.Add(new CString (isbd.data()));


			CString *sPtr = stringVect.Entry(0);

			if ((idx = sPtr->IndexCharFrom('*', 0, CString::forward)) > 0) // abbiamo almeno un asterisco?
			{
				sPtr->PrependString(NSB.data());
				sPtr->Replace("*", NSE.data(), 1);
			}
			else
			{
				if (sPtr->GetFirstChar() == '*')
					sPtr->ExtractFirstChar();
			}
			sf = new Subfield('a', sPtr);
			df->addSubfield(sf);

			for (int i=1; i < stringVect.length(); i++)
			{
				sf = new Subfield('i', stringVect.Entry(i));
				df->addSubfield(sf);
			}
			stringVect.DeleteAndClear();
		}


	}


	marcRecord->addDataField(df);

//	} // end if

	return df;
} // End Marc4cppLegamiAuthority::creaLegameTitoloTitolo

bool Marc4cppLegamiAuthority::getTitoliUniformiViaf(CString *sPtr, char responsabilita, CKeyValueVector *cdLivelloVidIsbdKV, int exportMaxViafs)
	{
	CTokenizer *Tokenizer = new CTokenizer("|");
	OrsChar *Token;

	// Splittiamo la riga negli n elementi che la compongono
	Tokenizer->Assign(sPtr->data());
	Token = Tokenizer->GetToken(); // Remove root
	CString value;
	int ctr=0;
	while(*(Token = Tokenizer->GetToken()))
	{
//		sprintf (curLevel, "%s.%d", level,++leafId);
//		sprintf (buf, "%s:AUT:%s", curLevel, Token);
//		nodeIter = reticolo->append_child(startNodeIter, buf);
printf ("\nN.%d: Token=%s", ++ctr, Token);


		if (*(Token+11) == responsabilita) // Pizzichiamo direttamente tpResponsabilita
		{
//			printf ("\nElabora Token=%s", Token);
			*(Token+10)=0; // EOS // prendiamo il bid
			// Cerchiamo nella tbTitolo il titolo
			if (!tbTitolo->loadRecord(Token))
			{
		        SignalAnError(__FILE__, __LINE__, "read file dei titoli failed");
		        return false;
			}
//			tbTitolo->dumpRecord();
			// Mettiamo i titoli in un vettore per ordinarli in base al cd_livello
			int cdLivello = atoi (tbTitolo->getField(tbTitolo->cd_livello));
			char *natura = tbTitolo->getField(tbTitolo->cd_natura);
			if (*natura != 'A' || cdLivello != 97)
				continue;
				value =  tbTitolo->getField(tbTitolo->bid);
				CString isbd = tbTitolo->getField(tbTitolo->isbd);
				int posCompTit = isbd.IndexSubString(PUNTEGGIATURA_AREA_TITOLO_INIZIO_COMPLEMENTO_TITOLO); // " : "

				int endAreaTitolo = isbd.IndexSubString(". - "); // Fine area
				if (posCompTit != -1 && endAreaTitolo > posCompTit)
				{
					CString title = isbd.SubstringData(0,posCompTit);
					// 29/05/13 Controlliamo che il titolo non sia un solo numero (problema VIAF)
					bool isDigit=true;
					for (int i=0; i < title.Length(); i++)
						if (!isdigit(title.GetChar(i)))
						{
							isDigit=false;
							break;
						}
					if (isDigit && title.Length() < 4) // 4 potrebbe essere un anno
					{
						isbd.CropLeftBy(posCompTit+3);
						isbd.PrependString(": ");
						isbd.PrependString(title.data());
					}
					else
						isbd.CropRightFrom(endAreaTitolo); // posCompTit
				}
				else
				{
				if (endAreaTitolo != -1)
					isbd.CropRightFrom(endAreaTitolo);
				}
				value.AppendString(isbd.data());

				cdLivelloVidIsbdKV->Add(tbTitolo->getField(tbTitolo->cd_livello),value.data());

//				if (cdLivelloVidIsbdKV->Length() == exportMaxViafs)
//				{
//					delete Tokenizer;
//					return true;
//				}
		}
		else
		{
			// printf ("\nSkip Token=%s", Token); troppo rumore
		}
	} // end while tokens
	delete Tokenizer;

	return true;
	} // End getTitoliUniformiViaf









// 23/04/2020 = a creaTag70xNew
void Marc4cppLegamiAuthority::creaTag50x(DataField *df, CString *ds_nome, char tp_nome,	CString *id, CString *cdRelazione)
{
	Subfield *sf;
	string str;
	CString s;


	char *vid = id->data(); // 28/04/10 // const
	if (TIPO_SCARICO == TIPO_SCARICO_UNIMARC)
		sf = new Subfield('3', vid);
	else // TIPO_SCARICO_OPAC
	{
		CString id((char *)"IT\\ICCU\\", 8);
		id.AppendString(vid, 4);
		id.AppendChar('\\');
		id.AppendString(vid+4, 10-4);
		sf = new Subfield('3', &id);
		//sf->setData();
	}
	df->addSubfield(sf);

	CString *tagPtr = df->getTagString();
//	if (tagPtr->isEqual("501") || tagPtr->isEqual("511"))
	if (tagPtr->isEqual("500"))
	{
		sf = new Subfield('5', "xxxxa"); // pos. 4 a=autore alternativo. NB: le posizioni non valorizzate che precedono la posizione valorizzata vanno riepite con x
		df->addSubfield(sf);

	}





	ds_nome->Strip(ds_nome->trailing, ' ');  // Mantis 0004381. 26/04/2010
	char *nomePtr = ds_nome->data(); // tbAutore->getField(tbAutore->ds_nome_aut);
	char *qualificazionePtr = 0;
	//	char *datePtr = 0;
	char *commaPtr = 0;
	char *colonPtr = 0;

	df->setIndicator1(' ');
	if (tp_nome == 'A' || tp_nome == 'a' || tp_nome == 'B' || tp_nome == 'b')
		df->setIndicator2('0');
	else
		df->setIndicator2('1');

	qualificazionePtr = strstr(nomePtr, " <");
	if (qualificazionePtr) // Qualificazione parte dele testo?
	{
		int idx = ds_nome->IndexCharFrom('>', 0, CString::forward);
		if (idx < (ds_nome->Length()-1))
			qualificazionePtr = 0;
	}


    // Gestiamo il no sort
    nomePtr = ds_nome->data();
	int pos;
	char *ptr;
	if ((pos = ds_nome->First('*')) != -1) // abbiamo almeno un asterisco?
	{
	    if (pos) // Se non primo carattere
	    {
	        s = NSB.data(); // No sort begin
	        s.AppendString(ds_nome->SubstringData(0, pos), pos);
	        s.AppendString(&NSE); // No sort end
	        ptr = ds_nome->SubstringData(pos + 1);
	        s.AppendString(ptr, ds_nome->getBufferSubStringLength());

	        if (df->getTagString()->StartsWith("51"))
	        	s.Strip('*');

	        nomePtr = s.data();
	    } else
	    {
	        ds_nome->ExtractFirstChar();
	        if (df->getTagString()->StartsWith("51"))
	        	ds_nome->Strip('*'); // rimuovi altri asterischi
	        nomePtr = ds_nome->data();
	    }
	}

	qualificazionePtr = strstr(nomePtr, " <");
	if (qualificazionePtr) // Qualificazione parte dele testo?
	{
		int idx = ds_nome->IndexCharFrom('>', 0, CString::forward);
		if (idx < (ds_nome->Length())) // -1 05/11/2010 14.11
		{
			*qualificazionePtr = 0;
			qualificazionePtr += 1;
		}

	}

	if (tp_nome == 'C' || tp_nome == 'c' || tp_nome == 'D' || tp_nome == 'd')
		commaPtr = strstr(nomePtr, ", ");
	if (commaPtr)
		*commaPtr = 0; // EOS


	sf = new Subfield('a', nomePtr, strlen(nomePtr));
	//sf->setData(); // tbAutore->getField(tbAutore->ds_nome_aut)
	df->addSubfield(sf);

	if (tp_nome == 'C' || tp_nome == 'c' || tp_nome == 'D' || tp_nome == 'd') {
		if (commaPtr) {
			*commaPtr = ','; // rimetti Richiesta CFI 04/02/2010 14.55
			sf = new Subfield('b', commaPtr, strlen(commaPtr));
			df->addSubfield(sf);
		}

	}

	if (qualificazionePtr) {
		char *ptrStart = qualificazionePtr;
		char *ptr;
		int ctr = 0;
		char subfieldId;
		while (ptr = strstr(ptrStart, " ; ")) {
			if (ptr)
				*ptr = 0;

			if (*ptrStart == '<')
			{
				subfieldId = getQualificazioneType(ptrStart+1, ctr, tp_nome);
		}
			else
				subfieldId = getQualificazioneType(ptrStart, ctr, tp_nome);

			if (subfieldId)
			{


				if (!ctr) // *ptrStart == '<'
					sf = new Subfield(subfieldId, (char *)" ", 1); // qualificazione
					//sf->appendData();
				else
					sf = new Subfield(subfieldId, (char *)" ; ", 3); // qualificazione
					//sf->appendData();

				sf->appendData(ptrStart); // , ds_nome->data()-ptrStart+ds_nome->Length()
				df->addSubfield(sf);
			}
			*ptr = ' ';
			ptrStart = ptr += 3;
			ctr++;
		}
		// ultima parte
		if (*ptrStart == '<')
			subfieldId = getQualificazioneType(ptrStart+1, ctr, tp_nome);
		else
			subfieldId = getQualificazioneType(ptrStart, ctr, tp_nome);
		if (subfieldId)
		{
			//		sf = new Subfield('c'); // qualificazione
			if (!ctr) // *ptrStart == '<'
				sf = new Subfield(subfieldId, (char *)" ", 1); // qualificazione
				//sf->appendData();
			else
				sf = new Subfield(subfieldId, (char *)" ; ", 3); // qualificazione
			//sf->appendData();
			sf->appendData(ptrStart, strlen(ptrStart)); // , ds_nome->data()-ptrStart+ds_nome->Length()
			df->addSubfield(sf);
		}
		*(qualificazionePtr - 1) = ' ';
	}

	if ((tp_nome == 'A' || tp_nome == 'a' || tp_nome == 'B' || tp_nome == 'b') && colonPtr) {
		sf = new Subfield('c', colonPtr, strlen(colonPtr)); // qualificazione
		df->addSubfield(sf);
		*(colonPtr - 1) = ':';
	}


	if (!cdRelazione->IsEmpty()) {
		Subfield *sf = new Subfield('4', cdRelazione);
		df->addSubfield(sf);
	}


	// Crea legami ad autori di rinvio
	creaLegamiautoriDiRinvio(df, vid);


} // End creaTag50x

void Marc4cppLegamiAuthority::creaLegamiautoriDiRinvio(DataField *df, char *vid)
{
    // Troviamo le relazioni agli autori
    // ---------------------------------
	bool retb;
	char *entryPtr;
	CString entryFile;
	long position;
	int offset;
	Subfield *sf;


	if (offsetBufferTrAutAutRelPtr)
		retb = BinarySearch::search(offsetBufferTrAutAutRelPtr, elementsTrAutAutRel, keyPlusOffsetPlusLfLength, vid, BID_KEY_LENGTH, position, &entryPtr);
	else
	{
		retb = BinarySearch::search(trAutAutRelOffsetIn, elementsTrAutAutRel, keyPlusOffsetPlusLfLength, vid, BID_KEY_LENGTH, position, &entryFile);
		entryPtr = entryFile.data();
	}

	if (retb)
	{ // Questo Vid accettato ha legami ad autori di rinvio

		// Dalla posizione prendiamo l'offset
//		offset = atol (entryPtr+BID_KEY_LENGTH); // offsetBuffertrTitAutRelPtr+position
		if (OFFSET_TYPE == OFFSET_TYPE_BINARY) // 09/02/2015
			//memcpy (&offset, entryPtr+ BID_KEY_LENGTH, 4);	// OFFSET BINARI
			offset =  *((int*)(entryPtr+BID_KEY_LENGTH)); // 24/03/2015

		else
			offset = atoi (entryPtr+BID_KEY_LENGTH); // OFFSET in ASCII

		// Dall'offset del file delle relazioni andiamo a prendere la relazione titolo/titolo
		trAutAutRelIn->SeekTo(offset);

		CString *sPtr = new CString(4096);

		if (!sPtr->ReadLineWithPrefixedMaxSize(trAutAutRelIn))
	        SignalAnError(__FILE__, __LINE__, "read failed");

		CTokenizer *Tokenizer = new CTokenizer("|");

		// Splittiamo la riga negli n elementi che la compongono
		Tokenizer->Assign(sPtr->data());
		OrsChar *Token;


		Token = Tokenizer->GetToken(); // Remove root
		TbAutore * tbAutoreRinvio = new TbAutore(tbAutore);
//		retb = tbAutoreRinvio->loadRecord(Token); // rimuovi autore principale

		char vid_rinvio[10+1];
		vid_rinvio[10]=0;

		while(*(Token = Tokenizer->GetToken()))
		{
//			printf ("vid=%s", Token);
			memcpy (vid_rinvio, Token, 10);

			retb = tbAutoreRinvio->loadRecord(vid_rinvio);
//tbAutoreRinvio->dumpRecord();
//
//retb = tbAutoreRinvio->loadRecord(vid);
//tbAutoreRinvio->dumpRecord();

			if (!retb)
			{
				//return 0; // Record non trovato
				SignalAnError(__FILE__, __LINE__, "\nVID %s non trovato nella tabella degli autori", vid);
				continue;
			}

			sf = new Subfield('9', tbAutoreRinvio->getFieldString(tbAutoreRinvio->ds_nome_aut)->Strip('*')); // 24/06/2020 tolti asterischi


			df->addSubfield(sf);

		}

		delete tbAutoreRinvio;
		delete sPtr;
		delete Tokenizer;

	} // End if ha legami

} // End Marc4cppLegamiAuthority::creaLegamiautoriDiRinvio

/*




#ifdef DEBUG_LEGAMI
printf ("\n\nBid+Offset=%s", entryPtr);
printf ("\nLegami tit_aut=%s", sPtr->data());
#endif




//		print_tree(*reticolo, reticolo->begin(), reticolo->end());
	}



*/







/*
VERDONE
=======
Autori personali
----------------

A Nome personale in forma diretta il cui gruppo principale e costituito da un solo elemento.
    Ordine delle qualificazioni
    I. Espressione verbale
    2. Numero d'ordine (per i sovrani, papi, etc.), trascritto sempre in cifre arabe seguite da un punto
    3. Specificazione cronologica

    eg. <regina di Gran Bretagna ; 2.>

B Nome personale in forma diretta il cui gruppo principale e costituito da pin elementi.
    Ordine delle qualificazioni

    I. Espressione verbale
    2. Numero d'ordine (per i sovrani, papi, etc.), trascritto sempre in cifre arabe seguite da un  punto
    3. Specificazione cronologica
    eg. <papa; 2.>

C Nome personale in forma inversa il cui gruppo principale e costituito da un solo elemento.
    Ordine delle qualificazioni

    I. Espressione verbale
    2. Numero d'ordine, trascritto sempre in cifre arabe seguite da un punto
    3. Specificazione cronologica

D Nome personale in forma inversa il cui gruppo principale e costituito da pin elementi.

    Ordine delle qualificazioni

    1. Espressione verbale
    2. Numero d'ordine, trascritto sempre in cifre arabe seguite da un punto
    3. Specificazione cronologica


$c Espressione verbale
$d Numero d'ordine non trattato
$f Specificazione cronologica





Autori collettivi
----------------
E Nome di ente.
    Ordine delle qualifi:azioni

    1. Numero d'ordine, trascritto sempre in cifre arabe seguite da un punto
    2. Qualificazione verbale
    3. Qualificazione geografica
    4. Specificazione cronologica

    eg. <Governo provvisorio ; 1958-1962>
        <Italia ; 1831>

R Nome di ente a carattere temporaneo.

    Ordine delle qualificazioni

    ] . Numero d'ordine, trascritto sempre in cifre arabe seguite da un punto
    2. Specificazione cronologica
    3. Qualificazione geografica
    eg. < 1. ; 1981 ; Firenze>

G Nome di ente subordinato.
    Ordine delle qualificazioni

    1. Numero d'ordine, trascritto sempre in cifre arabe seguite da un punto
    2. Qualificazione verbale
    3. Qualificazione geografica
    4. Specificazione cronologica

    eg. <Governo provvisorio ; 1958-1962>
        <Italia ; 1831>

$c Espressione verbale
$d Numero d'ordine non trattato
$e Qualificazione geografica
$f Specificazione cronologica
 *
 */
char Marc4cppLegamiAuthority::getQualificazioneType(char *parteDiQualificazione, int nth, char tipoNome)
{
//printf ("\nparteDiQualificazione=%s", parteDiQualificazione);

	// Controllo semantico
	char chr = *parteDiQualificazione, subfieldId = 0;

//	if (*qualificazionePtr == '<')
//		qualificazionePtr++;

	int len = strlen(parteDiQualificazione);
	if (!len)
		return subfieldId;

	chr = *(parteDiQualificazione+len-1);
	if (chr == '>')
		chr = *(parteDiQualificazione+len-2);


	if ( CMisc::isDate(parteDiQualificazione))
		subfieldId = 'f'; // Specificazione cronologica

	else if (chr == '.')
	{
		//*(parteDiQualificazione+len-1) = 0; // EOL
		while (*parteDiQualificazione++)
			if (!isdigit(*parteDiQualificazione))
				break;

//		if (!(*parteDiQualificazione) || *parteDiQualificazione == '>')
		if (!(*parteDiQualificazione) || *parteDiQualificazione == '.')
			subfieldId = 'd'; // Numero d'ordine se numerico
		else
		{
//			subfieldId = 'c'; // espressione verbale
			if (!nth) // 13/10/2010
				subfieldId = 'c'; // espressione verbale
			else
			{
				if (tipoNome == 'E' || tipoNome == 'e' || tipoNome == 'R' || tipoNome == 'r' )
					subfieldId = 'e'; // qualificazione geografica
				else
					subfieldId = 'c'; // espressione verbale
			}

		}
	}

	else if (chr != ' ')
	{
		if (!nth)
			subfieldId = 'c'; // espressione verbale
		else
		{
			if (tipoNome == 'E' || tipoNome == 'e' || tipoNome == 'R' || tipoNome == 'r' )
				subfieldId = 'e'; // qualificazione geografica
			else
				subfieldId = 'c'; // espressione verbale
		}
	}
	else
		subfieldId =  0;

//printf (" - subfieldId=%c", subfieldId);
	return subfieldId;


} // end getQualificazioneType













DataField * Marc4cppLegamiAuthority::creaLegameTitoloAutore(char *entryReticoloPtr, int pos, bool isTitoloOpera) {
	DataField *df = 0;
	DataField *df1 = 0;
	Subfield *sf=0;
	ControlField *cf = 0;

	// Prendiamo il VID per accedere alla tbAutore
	char vid[10 + 1];
	vid[10] = 0;
	CString cdRelazione, cdStrumentoMusicale;

	char *BufTailPtr, *aString;
	BufTailPtr = vid;
	aString =  entryReticoloPtr + pos + 5;
	MACRO_COPY_FAST(10);

//	memcpy(vid, entryReticoloPtr + pos + 5, 10);
	int posCdRelazione = pos + 5 + 11 + 1 + 1;
	cdRelazione.AppendString( entryReticoloPtr + posCdRelazione, 3);

//	Subfield *sfDollaro3Personale=0;
//	Subfield *sfDollaro3Ente=0;

	const int TIPO_NOME_PERSONALE=1;
	const int TIPO_NOME_ENTE=2;
	int tipo_nome=0;
	DataField *df239=0;

	int retb = tbAutore->loadRecord(vid);
	if (!retb)
		return 0; // Record non trovato

	char tipoResponsabilita = *(entryReticoloPtr + pos + 5 + 11);
	if (tipoResponsabilita == TP_RESP_1_RESPONSABILITA_PRINCIPALE
		|| tipoResponsabilita == TP_RESP_2_RESPONSABILITA_ALTERNATIVA // 24/06/2020
		|| tipoResponsabilita == TP_RESP_3_RESPONSABILITA_SECONDARIA

		)
	{
		if (*tbAutore->getField(tbAutore->tp_nome_aut) == 'A'
				|| *tbAutore->getField(tbAutore->tp_nome_aut) == 'B'
				|| *tbAutore->getField(tbAutore->tp_nome_aut) == 'C'
				|| *tbAutore->getField(tbAutore->tp_nome_aut) == 'D')
			{ // Nome Personale
			tipo_nome = TIPO_NOME_PERSONALE;
//cf = new ControlField((char *)"001");
//cf->setData(vid,10);

			df = new DataField();
			df->setTag((char *)"200");	// Personal name
			creaTag_40x(df, tbAutore);
			}
		else
			{ // Nome di ente
			tipo_nome = TIPO_NOME_ENTE;

			}


DataField *df241 = marcRecord->getDataField("241");


		if (isTitoloOpera && IS_TAG_TO_GENERATE(241))
		{
			if (df241)
			{
				df1=df241;
			}
			else
			{
				df1 = new DataField();
				df1->setTag((char *)"241");
			}

//			df1->setIndicator1(' ');
//			df1->setIndicator2(' ');
		}
		else
		{

			if (IS_TAG_TO_GENERATE(240))
			{
				df1 = new DataField();
				df1->setTag((char *)"240");
			}

		}


		if (df1)
		{

//			sf = new Subfield('1', df->toSubTag()); // 200
//			df1->addSubfield(sf);

			delete df; df=0;

			// Accodiamo la 230 o 231
			if (isTitoloOpera && IS_TAG_TO_GENERATE(231))
				df = marcRecord->getDataField((char *)"231");
			else
			{

				if (IS_TAG_TO_GENERATE(230))
					df = marcRecord->getDataField((char *)"230");

			}

			if (df)
			{
				sf = new Subfield('1', df->toSubTag());
				df1->addSubfield(sf);

				// Accodiamo la 239 (titolo completo se presente)
				df239 = marcRecord->getDataField((char *)"239");
				if (df239)
				{
					sf = new Subfield('1', df239->toSubTag());
					df1->addSubfield(sf);
				}


			}
//			if (cf)
//			{
//				sf = new Subfield('1', cf->toSubTag());
//				df1->addSubfield(sf);
//			}

//			delete cf; cf=0; // 24/05/2017

			if (!df241)
				marcRecord->addDataField(df1);
		}



		if (!isTitoloOpera)
			marcRecord->removeDataFields(230);
		else
		{
			marcRecord->removeDataFields(231);
			if (df239)
				marcRecord->removeDataFields(239);
		}



		char tp_nome = *tbAutore->getField(tbAutore->tp_nome_aut);
		CString *ds_nome_autore_ptr = tbAutore->getFieldString(tbAutore->ds_nome_aut);
		CString *vidPtr = tbAutore->getFieldString(tbAutore->vid);

		if (tipo_nome == TIPO_NOME_PERSONALE)
		{
			df = new DataField();

			if (tipoResponsabilita == TP_RESP_1_RESPONSABILITA_PRINCIPALE)
			{
				df->setTag((char *)"500");
			}
			else if (tipoResponsabilita == TP_RESP_3_RESPONSABILITA_SECONDARIA
					|| tipoResponsabilita == TP_RESP_2_RESPONSABILITA_ALTERNATIVA)
			{
				df->setTag((char *)"501");
			}

			creaTag50x(df, ds_nome_autore_ptr , tp_nome, vidPtr, &cdRelazione);
			marcRecord->addDataField(df);

		}
		else if (tipo_nome == TIPO_NOME_ENTE)
		{
			df = new DataField();
			if (tipoResponsabilita == TP_RESP_1_RESPONSABILITA_PRINCIPALE)
			{
				df->setTag((char *)"510");
//				creaTag50x(df, ds_nome_autore_ptr , tp_nome, vidPtr, &cdRelazione);
			}
			else if (tipoResponsabilita == TP_RESP_3_RESPONSABILITA_SECONDARIA)
			{
				df->setTag((char *)"511");
//				creaTag50x(df, ds_nome_autore_ptr , tp_nome, vidPtr, &cdRelazione);
			}
			creaTag50x(df, ds_nome_autore_ptr , tp_nome, vidPtr, &cdRelazione);
			marcRecord->addDataField(df);
		}


		}
		else
		{ // Altre responsabilita' non gestite

		}


	return df;


} // End Marc4cppLegamiAuthority::creaLegameTitoloAutore

