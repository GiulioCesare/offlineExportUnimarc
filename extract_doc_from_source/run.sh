#!/bin/bash

# 01/12/2021 Argentino
# Script to document offlieExport unimarc TAGS from doxygen comments in source code

SOURCE_DIR=/home/argentino/workspace/cdt/offlineExportUnimarc
OUT_DIR=steps
OUT_DXY_DIR=$OUT_DIR/01_dxy
OUT_TAG_DIR=$OUT_DIR/02_tag
OUT_HTML_DIR=$OUT_DIR/03_html
TAG_SOURCE_FILENAME=tag_source_list.txt
SW_VERSION="" # "Versione 12.11.06 30/11/2021"





check_dir_exists()
{

if [ ! -d "./$OUT_DIR" ]; then
    echo "Crea cartella $OUT_DIR"
    mkdir $OUT_DIR
fi

if [ ! -d "./$OUT_DXY_DIR" ]; then
    echo "Crea cartella $OUT_DXY_DIR"
    mkdir $OUT_DXY_DIR
fi

if [ ! -d "./$OUT_TAG_DIR" ]; then
    echo "Crea cartella $OUT_TAG_DIR"
    mkdir $OUT_TAG_DIR
fi

if [ ! -d "./$OUT_HTML_DIR" ]; then
    echo "Crea cartella $OUT_HTML_DIR"
    mkdir $OUT_HTML_DIR
fi

} # end check_dir_exists

extract_doxygen_comments()
{
    in_pathname=$1
    out_filename=$2

    # echo "out_filename="$out_filename
    sed -n '/^\/\*\! *$/, /\*\/$/p' $in_pathname > $out_filename
}

build_tag_html()
{
    echo "build_tag_html"
    in_filename=$1
    out_filename=$2

    echo " in_filename: " $in_filename
    echo " out_filename: " $out_filename

    awk  -v sw_version="$SW_VERSION" -v tag_dir=$OUT_TAG_DIR -v out_filename=$out_filename -f build_tag.awk  $in_filename

    # Specifichiamo l'authority laddove era multipla (sostituzione con sed in place)
    sed -r -i 's/\[.*autore.*\]/\[ authority autore \]/g' $OUT_TAG_DIR"/all.dxy.tag.authority_autore"
    sed -r -i 's/\[.*luogo.*\]/\[ authority luogo \]/g' $OUT_TAG_DIR"/all.dxy.tag.authority_luogo"
    sed -r -i 's/\[.*soggetto.*\]/\[ authority soggetto \]/g' $OUT_TAG_DIR"/all.dxy.tag.authority_soggetto"
    sed -r -i 's/\[.*titolo uniforme.*\]/\[ authority titolo uniforme \]/g' $OUT_TAG_DIR"/all.dxy.tag.authority_titolo_uniforme"

} # End build_tag_html




get_tag_source_files()
{
    echo "get_tag_source_files"
    grep -Ril "<b>Tag " ../src > $TAG_SOURCE_FILENAME
    # echo $tag_files
}


estrai_dxy()
{
    # Estraiamo tutti i dxy dai cpp
    # =============================
    while IFS= read -r source; do
        echo "Elaborazione di " $source
        fname=$(basename -- "$source")
        fname="${fname%.*}"
        # echo "fname="$fname
        # printf '%s\n' "$source"
        extract_doxygen_comments $source $OUT_DXY_DIR"/"$fname".dxy"
    done < $TAG_SOURCE_FILENAME
} # end estrai_dxy


concatena_dxy()
{
    # Concateniamo tutti i dxy
    # ========================
    if [ -f "./"$OUT_TAG_DIR"/all.dxy" ]; then
        echo "Remove all.dxy"
        rm "./"$OUT_TAG_DIR"/all.dxy"
    fi
    while IFS= read -r source; do
        echo "Concatenazione di " $source
        fname=$(basename -- "$source")
        fname="${fname%.*}"
        cat $OUT_DXY_DIR"/"$fname".dxy" >> $OUT_TAG_DIR"/"all.dxy
    done < $TAG_SOURCE_FILENAME

} # end concatena_dxy


crea_tag_html()
{
    # Creiamo i tag in formato html
    # =============================
    if [ -f "./"$OUT_TAG_DIR"/all.dxy.tag" ]; then
        echo "Remove all.dxy.tag"
        rm "./"$OUT_TAG_DIR"/all.dxy.tag"
    fi
    build_tag_html ./$OUT_TAG_DIR"/all.dxy" ./$OUT_TAG_DIR"/all.dxy.tag"

} # end crea_tag_html





get_sw_version()
{
    # Perl regex
    # cmd="grep -P \"^\t+printf.+Versione\"" $SOURCE_DIR"/src/test2.cpp"
    # cmd="grep -P "^\\t+printf.+Versione" /home/argentino/workspace/cdt/offlineExportUnimarc/src/test2.cpp"

    cmd="grep -P "^\\t+printf.+Versione" ../src/test2.cpp"
    

    # echo $cmd
    sw_version=$($cmd)

    # Redefine sw_version to version_array using parenthesis
    version_array=($sw_version)
    # echo "sw_version="$sw_version
    # echo ${version_array[1]:6}
    # echo ${version_array[2]}
    # echo ${version_array[3]:0:10}
    SW_VERSION="offlineExportUnimarc - "${version_array[1]:6}" "${version_array[2]}" "${version_array[3]:0:10}
    echo "$SW_VERSION"


} # end get_sw_version


test()
{
    echo "test"
    # Concatenate text and files
    # cat <(echo "Argentino") ./header.html > tmp.txt 
}

# Creiamo html per browser
# ========================
build_html()
{
    echo "build_html"
    source html.inc
    
    fname=$1

# echo "fname: " $fname


    in_leader_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.ldr"
    index_html="$index_html_p1 $SW_VERSION  $index_html_p2"
    out_html_doc_index_filename="./$OUT_HTML_DIR/"$fname".dxy.tag.doc.ndx.html"

    iad1="indice_authority_documento"
    iad2="Indice blocco BIBLIOGRAFICO"

    iaa1="indice_authority_autore"
    iaa2="Indice blocco authority AUTORE"

    ias1="indice_authority_soggetto"
    ias2="Indice blocco authority SOGGETTO"

    ial1="indice_authority_luogo"
    ial2="Indice blocco authority LUOGO"

    iatu1="indice_authority_titolo_uniforme"
    iatu2="Indice blocco authority TITOLO UNIFORME"


    header_indice_documento="$header_indice_p1$iad1$header_indice_p2$iad2$header_indice_p3 $SW_VERSION   $header_indice_p4"
    header_indice_autore="$header_indice_p1$iaa1$header_indice_p2$iaa2$header_indice_p3 $SW_VERSION   $header_indice_p4"
    header_indice_soggetto="$header_indice_p1$ias1$header_indice_p2$ias2$header_indice_p3 $SW_VERSION   $header_indice_p4"
    header_indice_luogo="$header_indice_p1$ial1$header_indice_p2$ial2$header_indice_p3 $SW_VERSION   $header_indice_p4"
    header_indice_titolo_uniforme="$header_indice_p1$iatu1$header_indice_p2$iatu2$header_indice_p3 $SW_VERSION   $header_indice_p4"

# echo "header_indice_documento: " $header_indice_documento


    # Authority documento (bibliografico)
    in_index_doc_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.doc.ndx"
    in_doc_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.doc"

    # Authority autore
    in_index_autore_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.authority_autore.ndx"
    in_autore_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.authority_autore"

    # Authority soggetto
    in_index_soggetto_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.authority_soggetto.ndx"
    in_soggetto_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.authority_soggetto"

    # Authority luogo
    in_index_luogo_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.authority_luogo.ndx"
    in_luogo_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.authority_luogo"

    # Authority titolo uniforme
    in_index_titolo_uniforme_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.authority_titolo_uniforme.ndx"
    in_titolo_uniforme_filename="./$OUT_TAG_DIR/"$fname".dxy.tag.authority_titolo_uniforme"



    cat <(echo $index_html) \
            $in_leader_filename \
            <(echo $header_indice_documento) $in_index_doc_filename $in_doc_filename \
            <(echo $header_indice_autore) $in_index_autore_filename  $in_autore_filename \
            <(echo $header_indice_soggetto) $in_index_soggetto_filename $in_soggetto_filename \
            <(echo $header_indice_luogo) $in_index_luogo_filename $in_luogo_filename \
            <(echo $header_indice_titolo_uniforme) $in_index_titolo_uniforme_filename $in_titolo_uniforme_filename \
            <(echo $tail_html) \
         > $out_html_doc_index_filename 


     
} # end build_html

process_tag_sources()
{
    echo "process_tag_sources"
    estrai_dxy
    concatena_dxy
    crea_tag_html
    build_html all
} # End process_tag_sources

#====================================
# MAIN 
# -------
# Risorse
# -------
# Documento ICCU                        /home/argentino/indice/Unimarc-Sbnmarcv7f.xls
# authotity bibliografico in Italiano   http://unimarc-it.wikidot.com/
# authotity persona:                    https://www.sba.unipi.it/sites/default/files/pages_documents/record_di_authority_2.4_1.pdf
# Documento SNS                         http://venti2bib.sns.it/manuale_UNIMARC_A.pdf
# Ifla 2008                             http://archive.ifla.org/VI/8/unimarc-concise-bibliographic-format-2008.pdf
# Ifla 3rd edition with updates         https://www.ifla.org/g/unimarc-rg/unimarc-bibliographic-3rd-edition-with-updates/
# 
# - I primi tre numeri della versione sono: anno dalla nascita, mese, progressivo in mese
#   Versione 1.12.1 08/12/2021
#
# Controllo della corrispondenza della documentazione etichette con il codice
#   Controllo etichette documento:  
#       Numeri di identificazione del record :  - 001,003,005,010,011,012,013,016,017,020,022,035,071,072,073,090
#       Informazioni codificate:                - 100,101,102,105,110,116,120,121,123,124,125,127,128,181,182,183
#       Descrizione secondo standard ISBD:      - 200,205,206,207,208,210,215,225,230
#       Area delle note:                        - 300,311,312,314,316,317,326,327,330,336,337
#       Legami tra registrazioni bibliografiche:- 410,422,423,430,431,434,440,441,447,451,454,461,462,463,464,488
#       Varie forme del titolo:                 - 500,506,510,517,520,530,532,560,576
#       Dati semantici:                         - 606,620,676,686,689,696
#       Responsabilità intellettuale (autore)   - 700,701,702,710,711,712
#       Dati internazionali                     - 801,850,856,899
#       Riservato per campi ad uso nazionale    - 921,922,923,926,927,928,929,950,951,960
# 
#   Controllo etichette authority autore:       - 001,005,
#                                               - 100,101,102,152
#                                               - 200,210
#                                               - 300,305
#                                               - 400,410
#                                               - 500,510
#                                               - 676,686
#                                               - 801,810,815,830
#                                               - 899
# 
#   Controllo etichette authority soggetto:     - 001,005,
#                                               - 100
#                                               - 250
#                                               - 300
#                                               - 801
#                                               - 931,932
# 
#   Controllo etichette authority luogo:        - 001,005,035
#                                               - 100,102
#                                               - 260
#                                               - 300
#                                               - 460
#                                               - 801,810,815,830
# 
#   Controllo etichette authority tit. uniforme:- 001,003,005,
#                                               - 100,101,102,152
#                                               - 230,231,240,241
#                                               - 300
#                                               - 431,441
#                                               - 801,810,815,830
#====================================
# 
# test


# check_dir_exists

get_sw_version
get_tag_source_files
process_tag_sources






