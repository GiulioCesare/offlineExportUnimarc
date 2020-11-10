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
 * Marc4cppDocumentoAuthority.cpp
 *
 *  Created on: 29-dic-2008
 *      Author: Arge
 *
        0-- Identification Block
		1-- Coded Information Block
		2-- Heading Block
		3-- Notes Block
		4-- See Reference Tracing Block
		5-- See Also Reference Tracing Block
		6-- Classification Number Block
		7-- Linking Heading Block
		8-- Source Information Block
		9-- National Use Block
 *
 */
#include <stdio.h>
#include <stdlib.h>


#include "Marc4cppDocumentoAuthority.h"
#include "BinarySearch.h"
#include "library/CMisc.h"
#include "MarcGlobals.h"
#ifdef TRACK_MEMORY_LEAKS
    #include "nvwa/debug_new.h"
#endif

//#include "C210.h"
extern void SignalAnError(	const OrsChar *Module, OrsInt Line, const OrsChar * MsgFmt, ...);
extern void SignalAWarning(	const OrsChar *Module, OrsInt Line, const OrsChar * MsgFmt, ...);

//Authority luogo 05/11/2020
Marc4cppDocumentoAuthority::Marc4cppDocumentoAuthority(MarcRecord *marcRecord, TbLuogo *tbLuogo, char *polo, char *tagsToGenerateBufferPtr, int tagsToGenerate, int aurthority)

{

	this->tbLuogo = tbLuogo;
	init (marcRecord, polo, tagsToGenerateBufferPtr, tagsToGenerate, aurthority);
}

Marc4cppDocumentoAuthority::Marc4cppDocumentoAuthority(MarcRecord *marcRecord, TbAutore *tbAutore, char *polo, char *tagsToGenerateBufferPtr, int tagsToGenerate, int aurthority)

{

	this->tbAutore = tbAutore;
	init (marcRecord, polo, tagsToGenerateBufferPtr, tagsToGenerate, aurthority);
}

Marc4cppDocumentoAuthority::Marc4cppDocumentoAuthority(MarcRecord *marcRecord, TbSoggetto *tbSoggetto, TbDescrittore *tbDescrittore, char *polo, char *tagsToGenerateBufferPtr, int tagsToGenerate, int authority)

{
	this->tbSoggetto = tbSoggetto;
	this->tbDescrittore = tbDescrittore;
	init (marcRecord, polo, tagsToGenerateBufferPtr, tagsToGenerate, authority);
}

// 04/04/2016
Marc4cppDocumentoAuthority::Marc4cppDocumentoAuthority(MarcRecord *marcRecord, TbAutore *tbAutore, TbTitolo *tbTitolo, TbTitSet2 *tbTitSet2,
		TbComposizione *tbComposizione, TbMusica *tbMusica, char *polo, char *tagsToGenerateBufferPtr, int tagsToGenerate, int authority)
{
	this->tbAutore = tbAutore;
	this->tbTitolo = tbTitolo;
	this->tbTitSet2 = tbTitSet2;
	this->tbComposizione = tbComposizione; // 24/04/2020
	this->tbMusica = tbMusica;
	init (marcRecord, polo, tagsToGenerateBufferPtr, tagsToGenerate, authority);
}


void Marc4cppDocumentoAuthority::init(MarcRecord *marcRecord, char *polo, char *tagsToGenerateBufferPtr, int tagsToGenerate, int authority)
{
	this->tagsToGenerateBufferPtr = tagsToGenerateBufferPtr;
	this->tagsToGenerate = tagsToGenerate;

	this->marcRecord = marcRecord;

	this->polo = polo;
	this->authority = authority;

} // End init





Marc4cppDocumentoAuthority::~Marc4cppDocumentoAuthority()
{
//	stop();
}
//void Marc4cppDocumentoAuthority::~stop()
//{
//
//}


/*
bool Marc4cppDocumentoAuthority::isAnnoBeforeSeparatore(CString &stringa) {
        int n = 2;
//        CString coda = "";
        long from = stringa.Length()-1;

        while (n < from) {
            //coda = stringa.substring(n);
            if (stringa.StartsWithFrom(" ; ", from) || stringa.StartsWithFrom(" : ", from) || stringa.StartsWithFrom(", ", from))
                break;
            from--;
        }
        CString anno = stringa.SubstringData(from);
        return contieneAnno(anno);
    } // End isAnnoBeforeSeparatore
*/
/**
 * Verifica se esiste una sequenza consecutiva di 4 caratteri numerici, il cui
 * valore sia > 1450.
 * Su richiesta di ICCU modificato: controlla che esista un numero di 2 cifre.
 * @return
 */
/*
bool Marc4cppDocumentoAuthority::contieneAnno(CString &stringa) {
        int numeri = 0;
    int x = 0;
        for (int i = 0; i < stringa.Length(); i++) {
            if (isdigit(stringa.GetChar(i))) {
                numeri++;
                if (numeri == 2) {
           //MANTIS 1750 Aggiunta if x > -1. se non c'� il trattino da errore
                  x = i;
                  x-=2;
          if(x > -1) {
          //Per evitare che i numeri civici vengano considerati anni scriviamo
                  //questa boiata.
            if (stringa.GetChar(x) == '-') {
            //Solo per il caso 'Il sole -24 ore'
            return false;
            }
            while (x>=0) {
            char c = stringa.GetChar(x);
            if (isalnum(c)) {
              break;
            } else {
              x--;
            }
            }
            while (x>=0) {
            char c = stringa.GetChar(x);
            if (isalnum(c)) {
              x--;
            } else {
              break;
            }
            }
            x++;
            char c = stringa.GetChar(x);
            if (isalnum(c)) {
            if (c == 'n' || c=='N') {
              return false;
            }
            }
            //fine boiata
            return true;
          }
                }
            } else
                numeri = 0;
        }
        if (stringa.Length() != 0) {
      if (stringa.Length() == numeri) {
        return true;
      } else {
        return false;
      }
        } else
      return false;
    } // End contieneAnno
*/

/*
	// 001 Identificativo di record
	Obbligatorio
	Non ripetibile
	Nessun indicatore di campo
	Nessun indicatore di sottocampo
*/
ControlField * Marc4cppDocumentoAuthority::creaTag001_IdentificatoreRecord()
{
	ControlField *cf;
	cf = new ControlField();
	cf->setTag("001");

	if (authority == AUTHORITY_AUTORI)
	{
		//cf->setData(tbAutore->getField(tbAutore->vid));
		char * vid = tbAutore->getField(tbAutore->vid);
		if (TIPO_SCARICO == TIPO_SCARICO_UNIMARC
				&& DATABASE_ID != DATABASE_INDICE // 08/03/2013
		)
			cf->setData(vid, 10);
		else // TIPO_SCARICO_OPAC
		{
			CString id("IT\\ICCU\\", 8);
			int pos = 4;
			id.AppendString(vid, pos); // Prendi il Polo
			id.AppendChar('\\');
			id.AppendString(vid+pos, 10-pos);	 // Prendi resto del bid
			cf->setData(&id);
		}
	}
	else if (authority == AUTHORITY_SOGGETTI)
		cf->setData(tbSoggetto->getFieldString(tbSoggetto->cid));
	else if (authority == AUTHORITY_TITOLI_UNIFORMI)
		cf->setData(tbTitolo->getFieldString(tbTitolo->bid));
	else if (authority == AUTHORITY_LUOGHI)
		cf->setData(tbLuogo->getFieldString(tbLuogo->lid));
//	else
//		cf->setData("??????????");

	marcRecord->addControlField(cf);
	return cf;
} // End creaTag001


/**
 \brief <b>Tag 003 - Permanent link</b>
 <table>
 <tr>
 <th valign=top>Definizione</th><th>Descrizione</th></tr>
 <tr><td valign=top>Tag</td>
     <td>001</td></tr>
 <tr><td valign=top>Descrizione</td>
     <td>Identificatico del record</td></tr>
 <tr><td valign=top>Obbligatorieta'</td>
     <td>Opzionale</td></tr>
 <tr><td valign=top>Ripetibilita'</td>
     <td>Non Ripetibile</td></tr>
 <tr><td valign=top>Indicatore 1</td>
     <td>Nessuno</td></tr>
 <tr><td valign=top>Indicatore 2</td>
     <td>Nessuno</td></tr>
  <tr><td valign=top>Sottocampi</td>
     <td>Nessuno</td></tr>
  <tr><td valign=top>Formato</td>
     <td>
         \li  URL
     </td></tr>

  <tr><td valign=top>NOTE</td>
     <td>Nessuna restrizione sul formato dell'identificativo</td></tr>
 </table>
 */

ControlField * Marc4cppDocumentoAuthority::creaTag003_Permalink() { // 22/04/2020
	ControlField *cf;
	cf = new ControlField();
	cf->setTag((char *)"003");

//tbTitolo->dumpRecord();

	char *bid = tbTitolo->getField(tbTitolo->bid);
	CString pl((char *)"http://id.sbn.it/bid/");
	pl.AppendString(bid);
	cf->setData(&pl);

	marcRecord->addControlField(cf);
	return cf;
} // End creaTag003_Permalink

/*
	// 005 Identificatore della versione
	Facoltativo (raccomandato)
	Non ripetibile
	Nessun indicatore di campo
	Nessun indicatore di sottocampo
*/
ControlField * Marc4cppDocumentoAuthority::creaTag005_IdentificatoreVersione()
{
	ControlField *cf;
	cf = new ControlField();
	char dateBuf[8+6+2+1]; // YYYYMMDDHHMMSS.T+ EOL
	*(dateBuf+8+6+2)=0;
	cf->setTag("005");
	if (DATABASE_ID != DATABASE_INDICE) // 03/05/2012
	{
		time_t rawtime;
		time(&rawtime);
		struct tm * timeinfo = localtime(&rawtime);
		CMisc::formatDate3(timeinfo, dateBuf);
		cf->setData(dateBuf, 16); // YYYYMMDDHHMMSS.T
	}
	else
	{
		if (authority == AUTHORITY_AUTORI)
		{
			CMisc::formatDate2(tbAutore->getField(tbAutore->ts_var), dateBuf); // 30/11/2015
		cf->setData(dateBuf, 16); // YYYYMMDDHHMMSS.T
				}
		else if (authority == AUTHORITY_LUOGHI)
		{
			CMisc::formatDate1(tbLuogo->getField(tbLuogo->ts_var), dateBuf); // YYYYMMDD   05/11/2020
		cf->setData(dateBuf, 8); // YYYYMMDD
				}
		else if (authority == AUTHORITY_SOGGETTI)
		{
			CMisc::formatDate2(tbSoggetto->getField(tbSoggetto->ts_var), dateBuf); // YYYYMMDDHHMMSS.T
		cf->setData(dateBuf, 16); // YYYYMMDDHHMMSS.T
					}
		else if (authority == AUTHORITY_TITOLI_UNIFORMI)
			{
			CMisc::formatDate2(tbTitolo->getField(tbTitolo->ts_var), dateBuf); // YYYYMMDDHHMMSS.T
			cf->setData(dateBuf, 16); // YYYYMMDDHHMMSS.T
			}
		else
			{
			printf("creaTag005 Authority not found: %s", authority);
			delete cf;
			return 0;
			cf->setData(dateBuf, 16); // YYYYMMDDHHMMSS.T
			}

	}


	marcRecord->addControlField(cf);
	return cf;
} // End creaTag005


/*
	 015 International Standard Authority Data Number
	 Optional. Non Repeatable.
	 Indicatori non definiti
	 Sottocampi:
 */

DataField * Marc4cppDocumentoAuthority::creaTag015_Isadn()
{
	DataField *df=0;
	Subfield *sf;

	CString isadn;
	isadn = tbAutore->getField(tbAutore->isadn);

	if (isadn.isEqual("null") || isadn.IsEmpty())
		return df;

	df = new DataField();
	df->setTag("015");
	sf = new Subfield('a', &isadn);
	//sf->setData();

	df->addSubfield(sf);

	marcRecord->addDataField(df);

	return df;
}// End creaTag015


// 17/11/15 I dati ISADN sono tati sostituiti con i dati ISNI
DataField * Marc4cppDocumentoAuthority::creaTag010_Isni()
{
	DataField *df=0;
	Subfield *sf;

//tbAutore->dumpRecord();

	CString isni;
	isni = tbAutore->getField(tbAutore->isadn);

	if (isni.isEqual("null") || isni.IsEmpty())
		return df;

	df = new DataField();
	df->setTag("010");
	sf = new Subfield('a', &isni);
	//sf->setData();

	df->addSubfield(sf);

	marcRecord->addDataField(df);

	return df;
}// End creaTag010

// 05/11/2020 X Authority Luoghi
DataField * Marc4cppDocumentoAuthority::creaTag035_Istat()
{
	if (authority == AUTHORITY_LUOGHI)
	{
	//	CMisc::formatDate1(tbLuogo->getField(tbLuogo->ts_var), dateBuf); // YYYYMMDD   05/11/2020
		CString* sPtr;
		sPtr=tbLuogo->getFieldString(tbLuogo->nota_luogo);
		int pos=sPtr->First('#');
		if(!(pos < 0))
		{
			char *istatPtr=sPtr->SubstringData(pos+1);
			if(istatPtr)
			{
				DataField *df;
				Subfield *sf;
				df = new DataField();
				df->setTag("035");
		//		df->setData(istatPtr,sPtr->getBufferSubStringLength());
				sf = new Subfield('a', istatPtr);
				df->addSubfield(sf);
				marcRecord->addDataField(df);
					return df;
			}
		}
		else

		{
			return 0;
		}
	}
	else
	{
		printf("creaTag035 Authority not found: %s", authority);
		return 0;
	}

}// End creaTag035_Istat

/*
	// 100 General Processing Data

	Definizione:	This field contains basic coded data applicable to all types of authority records.
	Obbligatorieta':	Obbligatorio
	Ripetibilita':	Non Ripetibile
	Indicatore1:	Non definito
	Indicatore2:	Non definito
	Sottocampi:		Certain data elements, marked "(mandatory)", are not permitted to be occupied by the fill character.

	a - General processing data.
		Mandatory. Not repeatable.

	    0-7 	Date entered on file (Mandatory)
	    8 		Status of authority heading code
				a = established.  	Heading is established.
				c = provisional. 	Heading cannot be established definitively due to inadequate information; when the
									heading is next used, it should be reconsidered in the light of any additional information.
				x = not applicable.	The record is a reference entry record or a general explanatory entry record and, therefore,
									the 2-- record heading field contains a variant heading.

		9-11	Language of Cataloguing (Mandatory)
				A three-character code indicates the language used in cataloguing.
				The 2-- heading appears as it would in a catalogue based on the language specified here.
	    12		Transliteration Code
				A one-character code indicates the transliteration system used for the first 2-- base heading in the record.
				a = ISO transliteration scheme
				b = other
				c = multiple transliterations: ISO or other schemes. Code �c� will usually be used when multiple scripts are recorded in $7 heading fields.
				d = Transliteration table established by the National Bibliographic Agency
				e = Transliteration without any identified transliteration table
				f = Other identified transliteration scheme(s)
				y = no transliteration scheme used



	    13-16  	Character Set (Mandatory)
				These four character positions indicate the principal graphic character sets used in the record.  Positions

				13-14 designate the G0 set and positions 15-16 designate the G1 set.  If a G1 set is not needed, positions
				15-16 contain blanks.

					01 = ISO 646, IRV version (basic Latin set)
					02 = ISO Registration #37 (basic Cyrillic set)
					03 = ISO 5426 (extended Latin set)
					04 = ISO 5427 (extended Cyrillic set)
					05 = ISO 5428 (Greek set)
					06 = ISO 6438 (African coded character set)
					07 = ISO 10586 (Georgian character set)
					08 = ISO 8957 (Hebrew character set) Table 1
					09 = ISO 8957 (Hebrew character set) Table 2
					10 = [Reserved]
					11 = ISO 5426-2 (Latin characters used in minor European languages and obsolete typography)
					50 = ISO 10646 Level 3

		17-20  	Additional Character Set
				Two two-character codes indicate up to two additional graphic character sets used in communication of
				the record.  The codes are the same as those used in character positions 13-16.  Positions 17-18 designate
				the G2 set and positions 19-20 designate the G3 set.  If no additional character sets are needed, the bytes
				contain blanks.  The UNIMARC - Manual Bibliographic Format, Appendix J, describes the action
				required when more than four sets must be accessed.  If no additional sets are involved, the four positions
				contain blanks.

		21-22  Script of Cataloguing
				A two-character code indicates the script used in cataloguing.  In authority records, the 2-- qualifiers,
				notes and other instructional information appear in this script.

				ba = Latin      ha = Hebrew
				ca = Cyrillic   ia = Thai
				da = Japanese   -- script unspecified  ja = Devanagari
				db = Japanese   -- Kanji  ka = Korean
				dc = Japanese   -- Kana  la = Tamil
				ea = Chinese    ma = Georgian
				fa = Arabic     mb = Armenian
				ga = Greek      zz = Other

		23  	Direction of Script of Cataloguing
				A single-character code indicates the direction of the script used in cataloguing, as coded in character
				positions 100/21-22.

				0 = left to right
				1 = right to left

*/

DataField * Marc4cppDocumentoAuthority::creaTag100()
{
	CString s;
	DataField *df;
	Subfield *sf;
	char dateBuf[8+1];
	*(dateBuf+8)=0;
	CString* cdLivello;

	df = new DataField();
	df->setTag("100");

	if (authority == AUTHORITY_AUTORI)
	{
		CMisc::formatDate1(tbAutore->getField(tbAutore->ts_ins), dateBuf);
		cdLivello = tbAutore->getFieldString(tbAutore->cd_livello);
	}

	else if (authority == AUTHORITY_LUOGHI)
	{
//tbLuogo->dumpRecord();
		CMisc::formatDate1(tbLuogo->getField(tbLuogo->ts_ins), dateBuf);
		cdLivello = tbLuogo->getFieldString(tbLuogo->cd_livello);
	}
	else if (authority == AUTHORITY_SOGGETTI)
	{
		CMisc::formatDate1(tbSoggetto->getField(tbSoggetto->ts_ins), dateBuf);
		cdLivello = tbSoggetto->getFieldString(tbSoggetto->cd_livello);

	}
	else if (authority == AUTHORITY_TITOLI_UNIFORMI)
	{
		CMisc::formatDate1(tbTitolo->getField(tbTitolo->ts_ins), dateBuf);
		cdLivello = tbTitolo->getFieldString(tbTitolo->cd_livello);

	}
	s.AppendString(dateBuf, 8);

	if (EXPORT_VIAF)
	{
		if (cdLivello->isEqual("97") || cdLivello->isEqual("95")) // 28/09/2014 Mail 27 Mar 2014 Di Franca Papi
			s.AppendChar('a');
		else
			s.AppendChar('x');
	}

	else
	{
		if (cdLivello->isEqual("97") || authority == AUTHORITY_LUOGHI)
			s.AppendChar('a');
		else
			s.AppendChar('x');
	}
	s.AppendString("itaa50      ba0", 15);
	sf = new Subfield('a', &s);

	//sf->setData();

	df->addSubfield(sf);
	marcRecord->addDataField(df);
	return df;
}// End creaTag100


/*
	//

	Tag+Def:		101 LINGUA DELLA ENTITA'
					This field contains coded information relating to the language or languages used by the entity identified by 2--.
					The entity may be an author (i.e., a person, a family, a corporate body) or a work
	--------
	Obbligatorieta':
	Ripetibilita':	Non Ripetibile
	Indicatore1:	Non definito
	Indicatore2:	Non definito
	Sottocampi:
	    a - Language used by the entity
*/
DataField * Marc4cppDocumentoAuthority::creaTag101_autore()
{
	DataField *df = 0;
	CString cdLingua;
	cdLingua = tbAutore->getField(tbAutore->cd_lingua); // Testo intermedio
	cdLingua.ToLower();

	if (cdLingua.isEqual("null") || cdLingua.IsEmpty())
		return df;
	Subfield *sf;
	df = new DataField();
	df->setTag("101");
	sf = new Subfield('a', &cdLingua);
	//sf->setData();
	df->addSubfield(sf);
	marcRecord->addDataField(df);
	return df;
} // End creaTag101_autore

DataField * Marc4cppDocumentoAuthority::creaTag101_titolo()
{
	DataField *df = 0;
	CString cdLingua;
	cdLingua = tbTitolo->getField(tbTitolo->cd_lingua_1);
	cdLingua.ToLower();

//tbTitolo->dumpRecord();

	if (cdLingua.isEqual("null") || cdLingua.IsEmpty())
		return df;
	Subfield *sf;
	df = new DataField();
	df->setTag("101");

	sf = new Subfield('a', &cdLingua);
	df->addSubfield(sf);

	cdLingua = tbTitolo->getField(tbTitolo->cd_lingua_2);
	cdLingua.ToLower();
	if (!cdLingua.isEqual("null") && !cdLingua.IsEmpty())
		{
		sf = new Subfield('a', &cdLingua);
		df->addSubfield(sf);

		cdLingua = tbTitolo->getField(tbTitolo->cd_lingua_3);
		cdLingua.ToLower();

		if (!cdLingua.isEqual("null") && !cdLingua.IsEmpty())
			{
			sf = new Subfield('a', &cdLingua);
			df->addSubfield(sf);
			}
		}

	marcRecord->addDataField(df);
	return df;
} // End creaTag101_titolo



/*
	Tag+Def:		102 Nationality of the Entity
					This field contains coded information relating to the nationality of a person,  corporate body,
					family, a trademark and a work.
	Obbligatorieta':	Mandatory when applicable.
	Ripetibilita':	Non Ripetibile
	Indicatore1:	Non definito
	Indicatore2:	Non definito
	Sottocampi:
	    a - Country of nationality
	    b - Locality
*/
DataField * Marc4cppDocumentoAuthority::creaTag102()
{
	DataField *df;
	Subfield *sf;
	CString s;
	CString cdPaese;
	if (authority == AUTHORITY_AUTORI)
	{
	cdPaese = tbAutore->getField(tbAutore->cd_paese);
	}
	else if(authority == AUTHORITY_LUOGHI)
	{
		cdPaese = tbLuogo->getField(tbLuogo->cd_paese);
	}
	if (cdPaese.isEqual("null") || cdPaese.IsEmpty())
		return df;

	df = new DataField();
	df->setTag("102");

	sf = new Subfield('a', &cdPaese);


	//s = ;
	//sf->setData(&s);
	df->addSubfield(sf);

	// b

	marcRecord->addDataField(df);
	return df;
}// End creaTag102


DataField * Marc4cppDocumentoAuthority::creaTag102TitoliUniformi()
{
	DataField *df = 0;
	CString cdPaese;
	cdPaese = tbTitolo->getField(tbTitolo->cd_paese);
//	cdPaese.ToLower(); // 29/05/2020 UC su richiesta Roveri (Jira)

	if (cdPaese.IsEmpty() || cdPaese.isEqual("null") )
		return df;
	Subfield *sf;
	df = new DataField();
	df->setTag("102");

	sf = new Subfield('a', &cdPaese);
	df->addSubfield(sf);

	marcRecord->addDataField(df);
	return df;
}// End creaTag102TitoliUniformi


/*
 * Rules
 * This field identifies the rule system under which the
 * 2-- heading and its accompanying reference structure were formulated.
 */

DataField * Marc4cppDocumentoAuthority::creaTag152_autore()
{
	DataField *df=0;
	Subfield *sf;

	CString cdNormeCat;
//	cdNormeCat = tbAutore->getField(tbAutore->cd_norme_cat);
//	if (cdNormeCat.IsEmpty())
//		cdNormeCat="RICA";
//		cdNormeCat="REICAT"; // 15/12/2016 Martini, Negrini a voce

	cdNormeCat = tbAutore->getField(tbAutore->cd_norme_cat);	// Mail Mataloni 23/05/2017, Giangregorio 24/05/2017
	if (!cdNormeCat.IsEmpty())
	{
		df = new DataField();
		df->setTag("152");
		sf = new Subfield('a', &cdNormeCat);
		//sf->setData();
		df->addSubfield(sf);

		marcRecord->addDataField(df);
	}

	return df;
}


/*
	Tag+Def:		200 Personal Name
	--------
	Obbligatorieta':	Optional
	Ripetibilita':	Repeatable for alternative script forms.
	Indicatore1:	Non definito

	Indicatore2:	 specifies the way the name is entered:
					0  Name entered under forename or direct order
					1  Name entered under surname

	Data Subfields:

		$a Entry element
			The portion of the name used as the entry element in the heading; that part of the name by which the
			name is entered in ordered lists. This subfield must be present when the field is present. Not repeatable.

		$b  Part of name other than entry element
			The remainder of the name, used when the entry element is a surname or family name (EX 1, 3, 4). It
			contains forenames and other given names. The form of name indicator should be set to 1 when this
			subfield is used. Printing expansions of initials should be entered in $g. Not repeatable.

		$c  Additions to names other than dates
			Any additions to names (other than dates) which do not form an integral part of the name itself including
			titles, epithets or indications of office (EX 2). Repeatable for second or subsequent occurrences of such
			additions (EX 5, 6).

		$d Roman numerals
			Roman numerals associated with names of certain popes, royalty and ecclesiastics (EX 2). If an epithet
			(or a further forename) is associated with the numeration, this too should be included (EX 7). The form of
			name indicator should be set to 0 when this subfield is used. Not repeatable.

		$f Dates
			The dates attached to personal names together with abbreviations or other indications of the nature of the
			dates. Any indications of the type of date (e.g., flourished, born, died) should be entered in the subfield in
			full or abbreviated form (EX 1-4, 8). All the dates for the person named in the field should be entered in
			$f. Not repeatable.

		$g  Expansion of initials of forename
			The full form of forenames when initials are recorded in subfield $b as the preferred form and when both
			initials and the full form are required (EX 4). Not repeatable.

		$4 Relator code
			The code used to designate the relationship between the person named in the field and the bibliographic
			item to which the record refers. This subfield is primarily intended  for use with UNIMARC Manual -
			Bibliographic Format. The list of codes is to be found in UNIMARC Manual - Bibliographic Format
			Appendix C. Repeatable.

		$j Form subdivision
			A term added to a subject heading to further specify the kind(s) or genre(s) of material (EX 9). Agencies
			not using this subdivision should use $x instead. Repeatable.

		$x Topical subdivision
			A term added to a subject heading to further specify the topic the subject heading represents (EX 10-12).
			Repeatable.

		$y Geographical subdivision
			A term added to a subject heading to specify a place in relation to a person which the subject heading
			represents (EX 11). Repeatable.

		$z Chronological subdivision
			A term added to a subject heading to specify the period in time in relation to a person whom the subject
			heading represents (EX 12). Repeatable.

	Control Subfields

		$7  Script of cataloguing and script of the base heading
			See specification of Control Subfields above.  Not repeatable.

		$8  Language of cataloguing and language of the base heading
			See specification of Control Subfields above.  Not repeatable.

	Notes on field contents
		The field contains the preferred form of a personal name, formulated in accordance with the descriptive
		cataloguing rules in use by the agency which creates it.

*/
DataField * Marc4cppDocumentoAuthority::creaTag200()
{
	DataField *df=0;
	string str;
	Subfield *sf;

	ATTValVector <CString *> stringVect;
	ATTValVector <CString *> stringVect2;
	ATTValVector <CString *> stringVect3; // 03/05/2017 gestione $c e $f in specificazione

	CString cs;

	// Controlliamo che sia una forma Accettata 'A' e non di Rinvio 'R'
	if (*tbAutore->getField(tbAutore->tp_forma_aut) == 'R')
		return df;
	// Controlliamo se e' un autore personale
	char tpNomeAut = *tbAutore->getField(tbAutore->tp_nome_aut);
	if (tpNomeAut != 'A' && tpNomeAut != 'B' && tpNomeAut != 'C' && tpNomeAut != 'D')
		return df; // Sara' un ente

	CString dsNomeAut;
	dsNomeAut = tbAutore->getField(tbAutore->ds_nome_aut);

//dsNomeAut.Strip(','); // TEST

	dsNomeAut.Split(stringVect, ',');


	df = new DataField();
	//df->setIndicator1(' ');
	if (tpNomeAut == 'C' || tpNomeAut == 'D')
		df->setIndicator2('1');
	else
		df->setIndicator2('0');

	df->setTag("200");

	if (stringVect.length() == 1)
	{
		stringVect.Entry(0)->Split(stringVect2, '<');
		sf = new Subfield('a', stringVect2.Entry(0));
		df->addSubfield(sf);

		if (stringVect2.length() > 1)
		{
			creaSottocampiQualificazione(df, stringVect2.Entry(1));

//			stringVect2.Entry(1)->PrependChar('<');
//
//			stringVect2.Entry(1)->Split(stringVect3, ';');	// 03/05/2017 Specificazione in 2 parti?
//			for (int i=0; i < stringVect3.length(); i++)
//			{
//				cs = stringVect3.Entry(i)->data();
//				cs.Strip(CString::leading, '<');
//				cs.Strip(CString::trailing, '>');
//				cs.Strip(CString::both, ' ');
//
//				if (CMisc::isDate(cs.data()))
//					sf = new Subfield('f', &cs);
//				else
//					sf = new Subfield('c', &cs);
//				df->addSubfield(sf);
//			}
//
//			stringVect3.DeleteAndClear();
		}

		stringVect2.DeleteAndClear(); //20/10/2009 11.11
	}
	else
	{
		sf = new Subfield('a', stringVect.Entry(0));
		df->addSubfield(sf);

		if (stringVect.length() > 1)
		{
			stringVect.Entry(1)->Split(stringVect2, '<');

			if (!stringVect2.Entry(0)->IsEmpty())	// 04/06/15
			{
				stringVect2.Entry(0)->PrependChar(',');
				sf = new Subfield('b', stringVect2.Entry(0));
				//sf->setData();
				df->addSubfield(sf);
			}

			if (stringVect2.length() > 1)
			{
				creaSottocampiQualificazione(df, stringVect2.Entry(1));

//				stringVect2.Entry(1)->PrependChar('<');
//
//				stringVect2.Entry(1)->Split(stringVect3, ';');	// 03/05/2017 Specificazione in 2 parti?
//				for (int i=0; i < stringVect3.length(); i++)
//				{
//					cs = stringVect3.Entry(i)->data();
//					cs.Strip(CString::leading, '<');
//					cs.Strip(CString::trailing, '>');
//					cs.Strip(CString::both, ' ');
//
//					if (CMisc::isDate(cs.data()))
//						sf = new Subfield('f', &cs);
//					else
//						sf = new Subfield('c', &cs);
//					df->addSubfield(sf);
//				}
//
//				stringVect3.DeleteAndClear();
			}
			stringVect2.DeleteAndClear(); //20/10/2009 11.11
		}
	}

	stringVect.DeleteAndClear();

	marcRecord->addDataField(df);


	return df;
} // End creaTag200

void Marc4cppDocumentoAuthority::creaSottocampiQualificazione(DataField *df, CString *csPtr)
{
	ATTValVector <CString *> stringVect3;
	CString cs;
	Subfield *sf;


	csPtr->Split(stringVect3, ';');	// 03/05/2017 Specificazione in 2 parti?
	for (int i=0; i < stringVect3.length(); i++)
	{
		cs = stringVect3.Entry(i)->data();
		cs.Strip(CString::both, ' ');


		if (CMisc::isDate(cs.data()))
			sf = new Subfield('f');
		else
			sf = new Subfield('c');

		if (!i)
			cs.PrependChar('<');
		else
			cs.PrependString(" ; ");
		sf->setData(&cs);

		df->addSubfield(sf);
	}

	stringVect3.DeleteAndClear();

}




/*
	Tag+Def:		210 Corporate Body Name
					This field contains a corporate or meeting name heading.  Territorial names followed by a corporate body
					subheading are considered corporate body names (tag 210); territorial names alone or only with subject
					subdivisions as additions are considered territorial names (tag 215).
	--------
	Obbligatorieta':	Facoltativo
	Ripetibilita':	Non Ripetibile
	Indicatore1:	specifies the kind of corporate body:
						0 Corporate name
						1 Meeting
	Indicatore2:	specifies the way the name is entered:
						0  Name in inverted form
						1  Name entered under place or jurisdiction
						2  Name entered under name in direct order
	Sottocampi:
	--------------
	$a Entry element
		The portion of the name used as the entry element in the heading; that part of the name by which the
		name is entered in ordered lists; i.e. the part of the name up to the first filing boundary. This subfield is
		not repeatable but must be present if the field is present.

	$b Subdivision
		The name of a lower level in a hierarchy when the name includes a hierarchy (EX 1, 4); or the name of
		the corporate body when it is entered under place (EX 2, 8). This subfield excludes additions to the name
		added by the cataloguer to distinguish it from other institutions of the same name (see $c, $g, $h).
		Repeatable if there is more than one lower level in the hierarchy.

	$c  Addition to name or qualifier
		Any addition to the name of the corporate body added by the cataloguer, other than number, place and
		date of conference. Repeatable. (EX 3, 4)

	$d  Number of meeting and/or number of part  of meeting
		The number of a meeting when the meeting belongs to a numbered series. Not repeatable. (EX 4)

	$e Location of meeting
		The place where a meeting was held when it is required as part of the heading. Not repeatable. (EX 4, 5)

	$f  Date of meeting
		The date of a meeting when it is required as part of the heading. Not repeatable. (EX 4, 5)

	$g Inverted element
		Any part of the name of the corporate body which is removed from the beginning of the name in order to
		enter the body under a word which is more likely to be sought. Not repeatable. This subfield is more
		commonly used in see references tracings. (See EX 5 under Field 410.)

	$h  Part of name other than entry element and inverted element
		In a heading with an inverted element, the part of the name following the inversion. Not repeatable.

	$4 Relator code
		The code used to designate the relationship between the corporate body named in the field and the
		bibliographic item to which the record refers. This subfield is primarily intended  for use with UNIMARC
		Manual - Bibliographic Format. The list of codes is to be found in UNIMARC Manual - Bibliographic
		Format Appendix C. Repeatable.

	$j Form subdivision
		A term added to a subject heading to further specify the kind(s) or genre(s) of material (EX 6). Agencies
		not using this subdivision should use $x instead (EX 5). Repeatable.

	$x Topical subdivision
		A term added to a subject heading to further specify the topic the subject heading represents (EX 5, 7, 8).
		Repeatable.

	$y Geographical subdivision
		A term added to a subject heading to specify a place in relation to a corporate body which the subject
		heading represents (EX 7). Repeatable.

	$z Chronological subdivision
		A term added to a subject heading to specify the period in time in relation to a corporate body which the
		subject heading represents (EX 8). Repeatable.

	Control Subfields
	-----------------
	$7  Script of cataloguing and script of the base heading
		See specification of Control Subfields above.  Not repeatable.

	$8  Language of cataloguing and language of the base heading
		See specification of Control Subfields above.  Not repeatable.

	Notes on field contents
		The field contains the preferred form of a corporate body name, formulated in accordance with the descriptive
		cataloguing rules in use by the agency which creates it.

*/
DataField * Marc4cppDocumentoAuthority::creaTag210()
{
	DataField *df=0;
	Subfield *sf;
//	CString *sPtr;
	CString daData;
	ATTValVector <CString *> stringVect;
	ATTValVector <CString *> stringVect2;
//	bool retb;
	CString luogoDiStampa;



	// Controlliamo che sia una forma Accettata 'A' e non di Rinvio 'R'
// 11/03/2013 Rimosso controllo forma accettata
//	if (*tbAutore->getField(tbAutore->tp_forma_aut) == 'R')
//		return df;


	// Controlliamo se e' un autore personale
	char tpNomeAut = *tbAutore->getField(tbAutore->tp_nome_aut);
	if (tpNomeAut != 'E' && tpNomeAut != 'G' && tpNomeAut != 'R')
		return df; // Sara' un individuo

	CString dsNomeAut;
	dsNomeAut = tbAutore->getField(tbAutore->ds_nome_aut);

	dsNomeAut.Split(stringVect, ':');


	df = new DataField();
	df->setTag("210");

	if (tpNomeAut == 'R')
		df->setIndicator1('1');	// Meeting
	else
		df->setIndicator1('0');	// Corporate name


//	if (tpNomeAut == 'E')
//		df->setIndicator2('0');
//
//	else if (tpNomeAut == 'R')
//		df->setIndicator2('1');
//	else if (tpNomeAut == 'G')
//		df->setIndicator2('2');
//	else
		df->setIndicator2('2'); // Sembra fisso da scarico indice 26/08/2010, Name entered under name in direct order


	stringVect.Entry(0)->removeCharacterOccurances('*');

	if (stringVect.length() > 1)
	{
		stringVect.Entry(1)->removeCharacterOccurances('*');
		stringVect.Entry(1)->Split(stringVect2, '<');
	}
	else
		stringVect.Entry(0)->Split(stringVect2, '<');


	if (stringVect.length() > 1)
		sf = new Subfield('a', stringVect.Entry(0));
	else
		sf = new Subfield('a', stringVect2.Entry(0));
	df->addSubfield(sf);




	if (stringVect.length() > 1)
	{
		stringVect2.Entry(0)->PrependString(" :");
		sf = new Subfield('b', stringVect2.Entry(0));
		//sf->setData();
		df->addSubfield(sf);
	}

	if (stringVect2.length() > 1)
	{// Gestiamo le qualificazioni
		stringVect2.Last()->ExtractLastChar();
		ATTValVector <CString *> stringVect3;
		stringVect2.Entry(1)->Split(stringVect3, ';');

		// 29/01/2013 Gestione $c e tpNomeAut 'E'
		bool numeroMeetingDone=false;
		bool dateMeetingDone=false;
		bool luogoMeetingDone=false;

		int ctr=1;
		for (int i=0; i < stringVect3.Length(); i++)
		{
			stringVect3.Entry(i)->Strip(CString::both, ' ');


			char qualificazione = getQualificazioneType(stringVect3.Entry(i));
			if (qualificazione == 'd') // Number of meeting
			{
				numeroMeetingDone=true;
			}
			if (qualificazione == 'f' && dateMeetingDone == false)
				dateMeetingDone = true;

//				else
//				{
//					if ()
//					qualificazione = 'c'; // data gia' fatta. Probabilmente manca il numero di meeting
//				}
			if (qualificazione == 'e')
			{
				luogoMeetingDone = true;

				if (tpNomeAut == 'E' || ctr > 3)
					qualificazione = 'c';	// generic info
			}


//				if ((tpNomeAut == 'E' &&
//					qualificazione == 'e') || // luogo meeting
//					ctr > 3) // numero/data/luogo + altro
//					qualificazione = 'c';	// generic infog

			sf = new Subfield(qualificazione, stringVect3.Entry(i));
			df->addSubfield(sf);
			ctr++;
		}




		stringVect3.DeleteAndClear();

	} // End qualificazioni


	stringVect.DeleteAndClear();	// 20/10/2009 11.11
	stringVect2.DeleteAndClear(); 	// 20/10/2009 11.11

	marcRecord->addDataField(df);

	return df;
} // End creaTag210

char Marc4cppDocumentoAuthority::getQualificazioneType(CString *parteDiQualificazione)
{
	// Controllo semantico
	if (parteDiQualificazione->GetLastChar() == '.')
		return 'd'; // numero di meeting

	char chr = parteDiQualificazione->GetFirstChar();
	if ( chr >= '0' && chr <= '9')
		return 'f'; // Data di meeting
	else
		return 'e'; // luogo di meeting

} // end getQualificazioneType




/*
	// 250 Topical Subject (Soggetti)
			This field contains a topical subject heading.
	Obbligatorieta':	Optional
	Ripetibilita':	Repeatable for alternative script forms.
	Indicatore1:	blank (not defined)
	Indicatore2:	blank (not defined)
	Sottocampi:
	-----------
		Data Subfields
		--------------
			$a Topical subject
				The term in the form prescribed by the system of subject headings used. Not repeatable.

			$j Form subdivision
				A term added to a subject heading to further specify the kind(s) or genre(s) or material (EX 4). Agencies
				not using this subdivision should use $x instead (EX 5). Repeatable.

			$x Topical subdivision
				A term added to a subject heading to further specify the topic the subject heading represents (EX 2).
				Repeatable.

			$y Geographical subdivision
				A term added to a subject heading to specify a place in relation to a topic that the subject heading
				represents (EX 1). Repeatable.

			$z Chronological subdivision
				A term added to a subject heading to specify the period in time in relation to a topic that the subject
				heading represents (EX 3). Repeatable.

		Control Subfields
		-----------------
			$7  Script of cataloguing and script of the base heading
				See specification of Control Subfields above.  Not repeatable.

			$8  Language of cataloguing and language of the base heading
				See specification of Control Subfields above.  Not repeatable.

			Notes on field contents
				The field contains the authorized form of a topical subject heading formulated in accordance with the subject
				system in use by the agency which created the record.

*/
DataField * Marc4cppDocumentoAuthority::creaTag250Soggetti()
{
	DataField *df;
	Subfield *sf;

	df = new DataField();
	df->setTag("250");

	CString soggetto;
	ATTValVector <CString *> stringVect;


	soggetto = tbSoggetto->getField(tbSoggetto->ds_soggetto);
	soggetto.Split(stringVect, " - ");


	sf = new Subfield('a', stringVect.Entry(0)); // prima parte del soggetto
	//sf->setData();
	df->addSubfield(sf);

	for (int i=1; i < stringVect.length(); i++)
	{
		sf = new Subfield('x',stringVect.Entry(i)); // altra parte del soggetto
		//sf->setData();
		df->addSubfield(sf);
	}

	CString *soggettario;

	if (DATABASE_ID == DATABASE_INDICE)
		{
		soggettario = tbSoggetto->getFieldString(tbSoggetto->cd_soggettario);
		}
	else
	{
		soggettario = tbSoggetto->getFieldString(tbSoggetto->cd_edizione);	// 09/10/2013 Richiesta di Renato per il POLO
		soggettario->PrependChar('F');
	}

	sf = new Subfield('2', soggettario);

	//sf->setData();
	df->addSubfield(sf);

	stringVect.DeleteAndClear(); // 20/10/2009 11.11

	marcRecord->addDataField(df);

	return df;
}














/*
// 260 Place Access (LUOGO DI PUBBLICAZIONE NORMALIZZATO)
		This field contains an access point form of a place of publication, production, etc.   The field may include the
		name of a country, state or province, county and/or city.
Obbligatorieta':	Optional
Ripetibilita':	Repeatable for alternative script forms.
Indicatore1:	blank (not defined)
Indicatore2:	blank (not defined)
Sottocampi:
-----------
	Data Subfields
	--------------
		$a  Country           Not repeatable.
		$b  State or Province etc.         Not repeatable.
		$c  County            Not repeatable.
		$d  City              Not repeatable.

	Control Subfields
	-----------------
		$7  Script of cataloguing and script of the base heading
			See specification of Control Subfields above.  Not repeatable.

		$8  Language of cataloguing and language of the base heading
			See specification of Control Subfields above.  Not repeatable.

		Notes on Field Contents
			This field contains a place access heading formulated in accordance with the rules in use by the agency which
			creates the record.
*/
DataField * Marc4cppDocumentoAuthority::creaTag260LuogoDiPubblicazioneNormalizzzato()
{
	DataField *df;
	Subfield *sf;
	if (authority == AUTHORITY_LUOGHI)
	 {
		df = new DataField();
		df->setTag("260");
		sf = new Subfield('a');
		sf->setData(tbLuogo->getFieldString(tbLuogo->cd_paese));
		df->addSubfield(sf);
		sf = new Subfield('d');
		sf->setData(tbLuogo->getFieldString(tbLuogo->ds_luogo));
		df->addSubfield(sf);
		marcRecord->addDataField(df);
	 }
	return df;
}
/*

	Tag+Def:		300 Information Note
					his field is used in an authority entry or a reference record to assist in explaining the relationship between the
					2-- heading and other entities.  This field is also used to provide information which helps to identify a heading.
	--------
	Obbligatorieta':	Facoltativo
	Ripetibilita':	Ripetibile
	Indicatore1:	specifies the type of note:
						0  Note concerns name or title use of heading
						1 Note concerns subject use of heading
	Indicatore2:	Non definito
	Sottocampi:
		Data Subfield
		-------------
			$a Information note
				An information note in natural language. Not repeatable.

		Control Subfields
		-----------------
			$6  Interfield linking data
				See specification of Control Subfields above.  Not repeatable.

			$7  Script of cataloguing and baseheading
				See specification of Control Subfields above.  Not repeatable.

 */
DataField * Marc4cppDocumentoAuthority::creaTag300Note()
{
	DataField *df=0;
	Subfield *sf;

	CString nota;

	if (authority == AUTHORITY_AUTORI)
		nota = tbAutore->getField(tbAutore->nota_aut);
	else if (authority == AUTHORITY_SOGGETTI)
	{
		if (DATABASE_ID != DATABASE_INDICE)
			nota = tbSoggetto->getField(tbSoggetto->nota_soggetto);
	}
	else if (authority == AUTHORITY_TITOLI_UNIFORMI)
	{
			nota = tbTitolo->getField(tbTitolo->nota_inf_tit);
	}
	else if (authority == AUTHORITY_LUOGHI)
	{
		nota=tbLuogo->getField(tbLuogo->nota_luogo);
		int pos=nota.First('#');
		if(!(pos < 0))
		{
			nota.CropRightFrom(pos);
		}
	}
	if (nota.StartsWith("null") || nota.IsEmpty())
		return df;

	df = new DataField();
	df->setTag("300");

	sf = new Subfield('a', &nota);
	df->addSubfield(sf);

	marcRecord->addDataField(df);

    return df;
} // End creaTag300


DataField * Marc4cppDocumentoAuthority::creaTag305(char *areaStartPtr, char *areaEndPtr)
{
	DataField *df;
	Subfield *sf;

	df = new DataField();
	df->setTag("305");
	sf = new Subfield('a', areaStartPtr, areaEndPtr-areaStartPtr);
	//sf->setData() ;
	df->addSubfield(sf);

	return df;
}

/*
	Tag+Def:		676 Classificazione Decimale Dewey
	--------
	Obbligatorieta':	Facoltativo
	Ripetibilita':	Ripetibile
	Indicatore1:	Non definito
	Indicatore2:	Non definito
	Sottocampi:
	    a - Numero
	    v - Edizione
*/
DataField * Marc4cppDocumentoAuthority::creaTag676()
{
	DataField *df;
//	Subfield *sf;
	CString s;

	df = new DataField();
	df->setIndicator1(' ');
	df->setIndicator2(' ');
	df->setTag("676");

//	sf = new Subfield('a');
//	s = tbClasse->getField(tbClasse->classe);
//    sf->setData(s.Strip(s.trailing, ' '));
//    df->addSubfield(sf);
//
//	sf = new Subfield('c');
//	s = tbClasse->getField(tbClasse->ds_classe);
//    sf->setData(s.Strip(s.trailing, ' '));
//    df->addSubfield(sf);
//
//	sf = new Subfield('v');
//	s = tbClasse->getField(tbClasse->cd_edizione);
//    sf->setData(s.Strip(s.trailing, ' '));
//    df->addSubfield(sf);


    return df;
} // End creaTag676ClassificazioneDecimaleDewey

/*
	// 686 Altra classificazione
	Facoltativo
	Ripetibile
	Indicatori non definiti
	Sottocampi:
	    a - Numero di classificazione
	    b - Numero del libro
	    c - Suddivizione della classificazione
	    2 - Sistema di codifica
*/
DataField * Marc4cppDocumentoAuthority::creaTag686()
{
	DataField *df;
//	Subfield *sf;

	df = new DataField();
	df->setTag("686");

//	sf = new Subfield('a');
//	CString s;s = tbClasse->getField(tbClasse->classe);
//    sf->setData(s.Strip(s.trailing, ' '));
//    df->addSubfield(sf);
//
//	sf = new Subfield('c');
//	s = tbClasse->getField(tbClasse->ds_classe);
//    sf->setData(s.Strip(s.trailing, ' '));
//    df->addSubfield(sf);
//
//	sf = new Subfield('v');
//	s = tbClasse->getField(tbClasse->cd_sistema);
//    sf->setData(s.Strip(s.trailing, ' '));
//    df->addSubfield(sf);

	return df;
} // End creaTag686AltraClassificazione

/*
	Tag+Def:		801 Fonte di provenienza del record
					This field identifies the agency responsible for the creation of the record and the date of the entry.  It is
					repeatable to show the transcribing, modifying or issuing agency.  The date for new records is the date of the
					creation of the entry.  For revised records, the date recorded is the date of the latest revision.
	--------
	Obbligatorieta':	Mandatory
	Ripetibilita':	Non ripetibile. Il campo e' ripetibile (per SBN non lo e')
	Indicatore1:	Non definito
	Indicatore2:	specifies the function performed by the agency:
						0 Original cataloguing agency
						1 Transcribing agency
						2 Modifying agency
						3 Issuing agency

	Sottocampi:
		$a Country
			The country of the issuing agency in 2 character form.The country is coded according to ISO 3166. The
			full list of codes will be found in the UNIMARC Manual - Bibliographic Format, Appendix B. Not
			repeatable.

		$b Agency
			The name of the agency may be in coded form using the identifiers found in the Guidelines for Authority
			and Reference Entries, Appendix B; the codes from MARC Code List for Organisations which include
			many non-U.S. library agencies; or the full name of the agency or a national code. Not repeatable.

		$c  Date of latest transaction
			The date of latest transaction should be recorded according to ISO 8601, i.e., in the form YYYYMMDD.
			Not repeatable.

		Notes on Field Contents
			In many cases the same agency will have carried out some or all indicated functions; however the field should
			be repeated only when there are changes to transaction dates, cataloguing rules or formats; where there are no
			changes only the earliest occurrence of the field should be included.


*/
DataField * Marc4cppDocumentoAuthority::creaTag801FonteDiProvenienza()
	{
//	bool retb;
	DataField *df = 0;
	Subfield *sf;
	CString cdPaese, tsIns;
	char dateBuf[8 + 1];
	*(dateBuf + 8) = 0;


	if (authority == AUTHORITY_AUTORI)
	{
		cdPaese = tbAutore->getField(tbAutore->cd_paese);
		tsIns = tbAutore->getField(tbAutore->ts_ins);
	}
	else if (authority == AUTHORITY_LUOGHI)
	{
		cdPaese = tbLuogo->getField(tbLuogo->cd_paese);
		tsIns = tbLuogo->getField(tbLuogo->ts_ins);
	}

	else if (authority == AUTHORITY_SOGGETTI)
		tsIns = tbSoggetto->getField(tbSoggetto->ts_ins);

	if (cdPaese.isEqual("null") || cdPaese.IsEmpty())
			cdPaese = "IT";

	CMisc::formatDate1(tsIns.data(), dateBuf);


	df = new DataField();
	df->setTag("801");
	df->setIndicator2('3');

	sf = new Subfield('a', &cdPaese);
    //sf->setData();
    df->addSubfield(sf);
	sf = new Subfield('b', "ICCU");//&BIBLIOTECARICHIEDENTESCARICO
    //sf->setData();
    df->addSubfield(sf);




    if (DATABASE_ID != DATABASE_INDICE) // 08/03/2013
    {

    	CMisc::formatDate1(tsIns.data(), dateBuf);
    	sf = new Subfield('c', dateBuf, 8);

    	//sf->setData(); // tbTitolo->getField(tbTitolo->ts_ins)
    	df->addSubfield(sf);
    }

    else
    { // 801 per indice

    	// CFI vuole il time stamp dell'export (Verifica UNIMARC1)
    	time_t rawtime;
    	time(&rawtime);
    	struct tm * timeinfo = localtime(&rawtime);
    	CMisc::formatDate4(timeinfo, dateBuf);

    	sf = new Subfield('c', dateBuf, 8);
    	//sf->setData();
    	df->addSubfield(sf);
    }



	marcRecord->addDataField(df);

    return df;
	} // End creaTag801FonteDiProvenienza



DataField * Marc4cppDocumentoAuthority::creaTag801FonteDiProvenienza_titoli()
	{

	DataField *df = 0;
	Subfield *sf;
//	char dateBuf[8 + 1];
//	*(dateBuf + 8) = 0;

	df = new DataField();
	df->setIndicator2('3'); // ICCU Roveri unimarc_11_08_2010.doc 14/09/2010 10.35
	df->setTag("801");

	sf = new Subfield('a', "IT", 2);
	//sf->setData();
	df->addSubfield(sf);


	sf = new Subfield('b', "ICCU"); // &bibliotecaRichiedenteScarico
	df->addSubfield(sf);


//	CMisc::formatDate1(tbTitolo->getField(tbTitolo->ts_ins), dateBuf);

	char dateBuf[10 + 1];
	*(dateBuf + 10) = 0;

	time_t rawtime;
	time(&rawtime);
	struct tm * timeinfo = localtime(&rawtime);
//	CMisc::formatDate_dd_mm_yyyy(timeinfo, dateBuf);
	CMisc::formatDate4(timeinfo, dateBuf);

	sf = new Subfield('c', dateBuf, 8);

	//sf->setData(); // tbTitolo->getField(tbTitolo->ts_ins)
	df->addSubfield(sf);

	marcRecord->addDataField(df);

    return df;
	} // End creaTag801FonteDiProvenienza_titoli












/*
	Tag+Def:		830 General Cataloguer's Note
					This field is used to record biographical, historical, or other information about the heading
	--------
	Obbligatorieta':	Optional
	Ripetibilita':	Repeatable.
	Indicatore1:	Non definito
	Indicatore2:	Non definito

	Sottocampi:
		$a Note text
			Subfield $a contains the text of the note. Repeatable.

*/

DataField * Marc4cppDocumentoAuthority::creaTag830NoteCatalogatoreAutore()
{
	DataField *df=0;
	Subfield *sf;

	CString notaCatalogatore;
	if(authority==AUTHORITY_AUTORI)
	{
	notaCatalogatore = tbAutore->getField(tbAutore->nota_cat_aut);
	}
	else if(authority==AUTHORITY_LUOGHI){
		notaCatalogatore = tbLuogo->getField(tbLuogo->nota_catalogatore);
	}
	else
	{
		return df;
	}

//tbAutore->dumpRecord();
	if (notaCatalogatore.isEqual("null") || notaCatalogatore.IsEmpty())
		return df;


	df = new DataField();
	df->setTag("830");

	sf = new Subfield('a', &notaCatalogatore);
	//sf->setData();
    df->addSubfield(sf);

	marcRecord->addDataField(df);

	return df;
}

DataField * Marc4cppDocumentoAuthority::creaTag830NoteCatalogatoreTitolo()
{
	DataField *df=0;
	Subfield *sf;

	CString notaCatalogatore;
	notaCatalogatore = tbTitolo->getField(tbTitolo->nota_cat_tit);

//tbAutore->dumpRecord();
	if (notaCatalogatore.isEqual("null") || notaCatalogatore.IsEmpty())
		return df;


	df = new DataField();
	df->setTag("830");

	sf = new Subfield('a', &notaCatalogatore);
	//sf->setData();
    df->addSubfield(sf);

	marcRecord->addDataField(df);

	return df;
}


DataField * Marc4cppDocumentoAuthority::creaTag928(char *areaStartPtr, char *areaEndPtr)
{
	DataField *df;
	Subfield *sf;

	df = new DataField();
	df->setTag("928");

	sf = new Subfield('a', areaStartPtr, areaEndPtr-areaStartPtr);
	//sf->setData();
	df->addSubfield(sf);

	return df;
}

DataField * Marc4cppDocumentoAuthority::creaTag930(char *areaStartPtr, char *areaEndPtr)
{
	DataField *df;
	Subfield *sf;

	df = new DataField();
	df->setTag("930");
	sf = new Subfield('a', areaStartPtr, areaEndPtr-areaStartPtr);
	//sf->setData();
	df->addSubfield(sf);

	return df;
}

DataField * Marc4cppDocumentoAuthority::creaTag931(char *areaStartPtr, char *areaEndPtr)
{
	DataField *df;
	Subfield *sf;

	df = new DataField();
	df->setTag("931");
	sf = new Subfield('a', areaStartPtr, areaEndPtr-areaStartPtr);
	//sf->setData();
	df->addSubfield(sf);

	return df;
}







//bool Marc4cppDocumentoAuthority::isTagToGenerate(const char *nomeTag)
//{
//	char *entryPtr;
//	long position;
//	bool retb;
//
//	int tag = atoi (nomeTag);
//	if (*(tagsToGenerateBufferPtr+tag) == 1)
//		return true;
//	else
//		return false;
//}
//
//bool Marc4cppDocumentoAuthority::isTagToGenerate(const int tag)
//{
//	if (*(tagsToGenerateBufferPtr+tag))
//		return true;
//	else
//		return false;
//}




bool Marc4cppDocumentoAuthority::elaboraDatiDocumento(bool isTitoloOpera)
{
	creaTag001_IdentificatoreRecord(); // Numero di record
	if (authority == AUTHORITY_TITOLI_UNIFORMI && DATABASE_ID == DATABASE_INDICE && IS_TAG_TO_GENERATE(003)) // 22/04/2020)
	{
		creaTag003_Permalink();
	}
	creaTag005_IdentificatoreVersione(); // Identificatore della versione

	if (authority == AUTHORITY_AUTORI)
	{
		if (IS_TAG_TO_GENERATE(010))
			creaTag010_Isni();
	}
	else if (authority == AUTHORITY_LUOGHI)
	{
		if (IS_TAG_TO_GENERATE(35))
			creaTag035_Istat();
	}
	if (IS_TAG_TO_GENERATE(100))
		creaTag100(); // General Processing Data

	if (authority == AUTHORITY_LUOGHI)
		{
		if (IS_TAG_TO_GENERATE(102))
			creaTag102(); // Nationality of the Entity
		if (IS_TAG_TO_GENERATE(152))
			{
			DataField *df = new DataField();
				df->setTag("152");
				Subfield *sf = new Subfield('a', "Catalogazione in SBN, Authority, Luoghi");
				//sf->setData();
				df->addSubfield(sf);

				marcRecord->addDataField(df);
			}
		if (IS_TAG_TO_GENERATE(260))
			creaTag260LuogoDiPubblicazioneNormalizzzato(); // LUOGO DI PUBBLICAZIONE NORMALIZZATO
		}
	else if (authority == AUTHORITY_AUTORI)
		{
		if (IS_TAG_TO_GENERATE(101))
			creaTag101_autore(); // LINGUA DELLA ENTITA'
		if (IS_TAG_TO_GENERATE(102))
			creaTag102(); // Nationality of the Entity
		if (IS_TAG_TO_GENERATE(152))
				creaTag152_autore(); // Rules
		creaTag200(); // Personal Name
		creaTag210(); // Ente

		}
	else if (authority == AUTHORITY_TITOLI_UNIFORMI)
	{
		if (IS_TAG_TO_GENERATE(101))
			creaTag101_titolo(); // LINGUA DELLA ENTITA'
		if (IS_TAG_TO_GENERATE(102))
			creaTag102TitoliUniformi(); // codice paese
		if (IS_TAG_TO_GENERATE(152))
			creaTag152_titolo(); // Regole di catalogazione

		if (IS_TAG_TO_GENERATE(230) || IS_TAG_TO_GENERATE(231))
		{
			if (!isTitoloOpera)
				creaTag230TitoloUniforme(); // titolo uniforme
			else
				creaTag231TitoloDellOpera(); // titolo dell'opera
		}

	}

	if (authority == AUTHORITY_SOGGETTI && IS_TAG_TO_GENERATE(250))
		creaTag250Soggetti();

	if (IS_TAG_TO_GENERATE(300))
		creaTag300Note();

	if (IS_TAG_TO_GENERATE(801))
		{
		if(authority == AUTHORITY_AUTORI || authority == AUTHORITY_SOGGETTI || authority == AUTHORITY_LUOGHI)
			creaTag801FonteDiProvenienza();

		else if (authority == AUTHORITY_TITOLI_UNIFORMI)
			creaTag801FonteDiProvenienza_titoli();
		}
	if(IS_TAG_TO_GENERATE(830))
	{
	if (authority == AUTHORITY_TITOLI_UNIFORMI)
			creaTag830NoteCatalogatoreTitolo();  // Nota del catalogatore
	else if (authority == AUTHORITY_AUTORI || authority == AUTHORITY_LUOGHI  )
		creaTag830NoteCatalogatoreAutore();
	}
	return true;
} // End Marc4cppDocumentoAuthority::elaboraDatiDocumento



/*
 * 856 Electronic Location and Access
 */

DataField * Marc4cppDocumentoAuthority::creaTag856()
{
	DataField *df;
	Subfield *sf;

	df = new DataField();
	df->setTag("856");
	sf = new Subfield('a');
	df->addSubfield(sf);

	return df;
}


/*
 * Rules
 * This field identifies the rule system under which the
 * 2-- heading and its accompanying reference structure were formulated.
 */

DataField * Marc4cppDocumentoAuthority::creaTag152_titolo()
{
	DataField *df=0;
	Subfield *sf;

	CString cdNormeCat;
//	cdNormeCat = tbTitolo->getField(tbTitolo->cd_norme_cat);

//	if (cdNormeCat.IsEmpty())
//		cdNormeCat = "RICA";
//	cdNormeCat="REICAT"; // 15/12/2016 Martini, Negrini a voce

	cdNormeCat = tbTitolo->getField(tbTitolo->cd_norme_cat);	// Mail Mataloni 23/05/2017, Giangregorio 24/05/2017
	if (!cdNormeCat.IsEmpty())
	{
		df = new DataField();
		df->setTag("152");
		sf = new Subfield('a', &cdNormeCat);
		df->addSubfield(sf);

		marcRecord->addDataField(df);
	}
	return df;
}


/*
	// 230 Uniform Title
			This field contains a uniform title heading.  A uniform title heading is intended to bring together the records for
			issues of a work that has been published under different titles or items in series.

	Obbligatorieta':	Optional
	Ripetibilita':	Repeatable for alternative script forms.
	Indicatore1:	blank (not defined)
	Indicatore2:	blank (not defined)
	Sottocampi:
	-----------
				Data Subfields
				--------------
					$a Entry element
						The title by which the work is known without any qualifications or mention of any part. This subfield
						should be present whenever field 230 is used. Not repeatable.

					$b  General material designation
						Text of general material designation. Repeatable.

					$h  Number of section or part
						The number of a part when the item to which the uniform title is being applied is only a part of the work
						named in the uniform title (EX 10). Repeatable for a subdivided part (EX 11).

					$i  Name of section or part
						The name of a part when the item to which the uniform title is being applied is only a part of the work
						named in the uniform title (EX 11). Repeatable for a subdivided part.

					$k Date of publication
						The date of publication of the item when it is added to the uniform title. Not repeatable.

					$1 Form subheading
						Standard phrase added to a heading to further specify the uniform title (EX 1). Not repeatable.

					$m  Language (when part of a heading)
						The language of the item, when required as part of the uniform title (EX 1, 5, 10). Not repeatable. If the
						work is in more than one language, both languages should be entered in a single subfield $m (EX 13).

					$n Miscellaneous information
						Any information not provided for in any other subfield. Repeatable.

					$q  Version (or date of version)
						An identification of the version of the work represented by the item; this may be the name or the original
						date of the version (EX 1). Not repeatable.

					$r  Medium of performance (for music)
						The instrumentation, etc., of the item (EX 12). Repeatable.

					$s  Numeric designation (for music)
						A number assigned by the composer or others to distinguish works. The number may be the serial, opus
						(EX 12) or thematic index number or date used as a number. Repeatable.

					$u  Key (for music)
						The musical key used as part of the uniform title (EX 12). Not repeatable.

					$w  Arranged statement (for music)
						The statement that a musical work is an arrangement (EX 2). Not repeatable.

					$j Form subdivision
						A term added to a subject heading to further specify the kind(s) or genre(s) of material (EX 3). Agencies
						not using this subdivision should use $x instead. Repeatable.

					$x Topical subdivision
						A term added to a subject heading to specify further the topic that the heading represents (EX 3, 6).
						Repeatable.

					$y Geographical subdivision
						A term added to a subject heading to specify a place in relation to a uniform title which the subject
						heading represents (EX 6). Repeatable.

					$z Chronological subdivision
						A term added to a subject heading to specify the period in time in relation to a uniform title which the
						subject heading represents. Repeatable.

				Control Subfields
				-----------------
					$7  Script of cataloguing and script of the base heading
						See specification of Control Subfields above.  Not repeatable.

					$8  Language of cataloguing and language of the base heading
						See specification of Control Subfields above.  Not repeatable.

		Notes on field contents
			The field contains the preferred form of a uniform title formulated in accordance with the descriptive
			cataloguing rules or subject system in use by the agency which creates it.

*/
	DataField * Marc4cppDocumentoAuthority::creaTag230TitoloUniforme()
	{
		DataField *df;
		Subfield *sf;

		df = new DataField("230", ' ', ' ');
		sf = new Subfield('a');

		CString * sPtr = tbTitolo->getFieldString(tbTitolo->isbd);

		int pos = sPtr->IndexSubString(". - "); // Fermati a fine area titolo
		if (pos != -1)
			sPtr->CropRightFrom(pos);

		int idx;	// 20/05/2014
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


		sf->setData(sPtr);
		df->addSubfield(sf);
		marcRecord->addDataField(df);

		return df;
	}

	DataField * Marc4cppDocumentoAuthority::creaTag231TitoloDellOpera()
	{
		DataField *df;
		Subfield *sf;


//		CString *sPtr;
//		sPtr = new CString ("TODO"); //tbTitSet2->getFieldString(tbTitSet2->s231_titolo);

		CString * sPtr = tbTitolo->getFieldString(tbTitolo->isbd);

		int pos = sPtr->IndexSubString(". - "); // Fermati a fine area titolo
		if (pos != -1)
			sPtr->CropRightFrom(pos);

		int idx;	// 20/05/2014
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


		// Get bid dal tb_titolo
		CString *bid = tbTitolo->getFieldString(tbTitolo->bid);
		char tp_materiale = *tbTitolo->getField(tbTitolo->tp_materiale);
		bool hasTbComposizioneRecord=false;


		df = new DataField("231", ' ', ' ');
		if (tp_materiale != TP_MATERIALE_MUSICA_U)
		{
			sf = new Subfield('a', sPtr);
			df->addSubfield(sf);
		}
		else
		{
			DataField *df239 = new DataField("239", ' ', ' '); // oltre alla 231
			sf = new Subfield('a', sPtr);
			df239->addSubfield(sf);
			marcRecord->addDataField(df239);
		}


		if (tp_materiale == TP_MATERIALE_MUSICA_U)
		{
			if (tbComposizione->loadRecord(tbTitolo->getField(tbTitolo->bid)))
			{
				int hasTbMusicaRecord = tbMusica->loadRecord(tbTitolo->getField(tbTitolo->bid));
				hasTbComposizioneRecord=true;


				sPtr = tbComposizione->getFieldString(tbComposizione->ky_ord_den);
				if (!sPtr->IsEmpty())
				{
					int idx;	// 23/06/2020
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
				}


				if (!tbComposizione->getFieldString(tbComposizione->cd_forma_1)->IsEmpty()) {
					sf = new Subfield('c', tbComposizione->getFieldString(tbComposizione->cd_forma_1)->Strip(CString::trailing, ' ')); // forma della composizione

					if (!tbComposizione->getFieldString(tbComposizione->cd_forma_2)->IsEmpty()) {
						sf->appendData(";");
						sf->appendData(tbComposizione->getFieldString(tbComposizione->cd_forma_2)->Strip(CString::trailing, ' '));
					}
					if (!tbComposizione->getFieldString(tbComposizione->cd_forma_3)->IsEmpty()) {
						sf->appendData(";");
						sf->appendData(tbComposizione->getFieldString(tbComposizione->cd_forma_3)->Strip(CString::trailing, ' '));
					}

					df->addSubfield(sf);
				}

				sPtr = tbComposizione->getFieldString(tbComposizione->datazione);
				if (!sPtr->IsEmpty())
				{
					sf = new Subfield('d', sPtr->Strip(sPtr->trailing));
					df->addSubfield(sf);
				}

				/*

				928 $b	tb_musica	org_sint
				928 $c	tb_musica	org_anal


				929 $a	tb_composizione	numero_ordine
				929 $b	tb_composizione	numero_opera
				929 $c	tb_composizione	numero_cat_tem
				929 $d	tb_composizione	datazione
				929 $e	tb_composizione	cd_tonalita
				929 $f	tb_composizione	ds_sezioni
				929 $h	tb_composizione	ky_est_den	ky_est_nor_pre	ky_est_ric
				929 $i	tb_composizione	ky_app_den	ky_app_nor_pre	ky_app_ric

				*/

				sPtr = tbComposizione->getFieldString(tbComposizione->ky_est_den);
				if (!sPtr->IsEmpty())
				{
					sf = new Subfield('i', sPtr);
					df->addSubfield(sf);
				}

				sPtr = tbComposizione->getFieldString(tbComposizione->ds_sezioni);
				if (!sPtr->IsEmpty())
				{
					sPtr->Strip(sPtr->trailing);
					sf = new Subfield('k', sPtr);
					df->addSubfield(sf);
				}

				if (hasTbMusicaRecord)
				{	// Organico della composizione (Musica)

//					sf = new Subfield('a', tbMusica->getFieldString(tbMusica->)); // 928 $g
//					df->addSubfield(sf);


					if (!tbMusica->getFieldString(tbMusica->ds_org_sint)->IsEmpty())
						sf = new Subfield('r', tbMusica->getFieldString(tbMusica->ds_org_sint)); // organico sintetico della composizione
					else
						sf = new Subfield('r', "-"); // organico sintetico della composizione assente
					df->addSubfield(sf);


					if (!tbMusica->getFieldString(tbMusica->ds_org_anal)->IsEmpty())
						sf = new Subfield('r', tbMusica->getFieldString(tbMusica->ds_org_anal)); // organico analitico della composizione
					else
						sf = new Subfield('r', "-"); // organico analitico della composizione assente
					df->addSubfield(sf);

				}

				// Designazione numerica
				sPtr = tbComposizione->getFieldString(tbComposizione->numero_ordine);
				if (!sPtr->IsEmpty())
					sf = new Subfield('s', sPtr->Strip(sPtr->trailing)); // Numero d'ordine
				else
					sf = new Subfield('s', "-"); // Numero d'ordine assente

				df->addSubfield(sf);

				tbComposizione->getFieldString(tbComposizione->numero_opera)->Strip(CString::trailing, ' ');
				sPtr = tbComposizione->getFieldString(tbComposizione->numero_opera);
				if (!sPtr->IsEmpty())
					sf = new Subfield('s', sPtr); // numero d'opera
				else
					sf = new Subfield('s', "-"); // numero d'opera assente
				df->addSubfield(sf);

				tbComposizione->getFieldString(tbComposizione->numero_cat_tem)->Strip(CString::trailing, ' ');
				sPtr = tbComposizione->getFieldString(tbComposizione->numero_cat_tem);
				if (!sPtr->IsEmpty())
					sf = new Subfield('s', sPtr); // numero di catalogo tematico
				else
					sf = new Subfield('s', "-"); // numero di catalogo tematico assente
				df->addSubfield(sf);

				sPtr = tbComposizione->getFieldString(tbComposizione->cd_tonalita);
				if (!sPtr->IsEmpty())
				{
					sf = new Subfield('u', sPtr);
					df->addSubfield(sf);
				}


			}
		}


		if (tbTitSet2->loadRecord(bid->data()))
		{
			if (tp_materiale != TP_MATERIALE_MUSICA_U)
			{
				sPtr = tbTitSet2->getFieldString(tbTitSet2->s231_forma_opera);
				if (!sPtr->IsEmpty())
				{
					sf = new Subfield('c', sPtr);
					df->addSubfield(sf);
				}
			}



			sPtr = tbTitSet2->getFieldString(tbTitSet2->s231_data_opera);
			if (!sPtr->IsEmpty())
			{
				sf = new Subfield('d', sPtr);
				df->addSubfield(sf);
			}

			if (!hasTbComposizioneRecord)
			{
				sPtr = tbTitSet2->getFieldString(tbTitSet2->s231_altre_caratteristiche);
				if (!sPtr->IsEmpty())
				{
					sf = new Subfield('k', sPtr);
					df->addSubfield(sf);
				}
			}



		} // End if tbTitSet2->loadRecord


		marcRecord->addDataField(df);
		return df;
	} // End creaTag231TitoloDellOpera()


