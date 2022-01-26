# Print the document for an authority according to the tags in documentation
function print_authority_body(tag_auth_AR, output_filename)
    {
    n=asort(tag_auth_AR)
    print "<BR><HR><BR>" > output_filename
    for ( i=1; i<=n; i++) {
        print tag_auth_AR[i] > output_filename
        }    
    } # end print_authority_doc

# Print the index for an authority according to the tags in documentation
function print_authority_index(tag_index_auth_AR, authority_name, output_filename)
{

    header_index_xxx_p1="<BR><a name='";
    # VARIABLE indice_authority_documento_0xx
    header_index_xxx_p2="'>\n\
    <div class='memproto'>\n\
    <table class='mlabels'>\n\
      <tbody><tr>\n\
      <td class='mlabels-left'>\n\
          <table class='memname'>\n\
            <tbody><tr>\n\
              <td colspan='4'class='memname'>";
    # VARIABLE 0xx - Numeri di identificazione del record
    header_index_xxx_p3="</td>\n\
            </tr>\n\
          </tbody></table>\n\
      </td>\n\
      <td class='mlabels-right'>\n\
    <span class='mlabels'><span class='mlabel'>"sw_version"</span></span></td>\n\
      </tr>\n\
    </tbody></table>\n\
    </div>\n\
    <div class='memdoc'>\n\
    <table class='doxtable'>\n\
    <tbody><tr>\n\
    <th valign='top'>Tag</th><th>Descrizione </th></tr>";


    tail_index="</table></div>";

    last_tag_key_first_char="?"
    # Stampa index file del documento
    n=asort(tag_index_auth_AR)
    for ( i=1; i<=n; i++) {
        split(tag_index_auth_AR[i],ar," ");

        tag_key_first_char=substr(ar[4],1,1);
# print "tag: " ar[4];
        if (last_tag_key_first_char != tag_key_first_char)
            {

# print "tag_key_first_char: " tag_key_first_char
# print "authority_name: " authority_name

            if (last_tag_key_first_char != "?")
                print tail_index > output_filename
          
            if (tag_key_first_char == "0")
             {
                header_index = header_index_xxx_p1 "indice_authority_"authority_name"_0xx"  header_index_xxx_p2 "0xx - Numeri di identificazione del record" header_index_xxx_p3 ;
                print header_index > output_filename
# print "authority_name: " authority_name
# print header_index                
             }
            else if (tag_key_first_char == "1")
                {
                header_index = header_index_xxx_p1 "indice_authority_"authority_name"_1xx"  header_index_xxx_p2 "1xx- Informazioni codificate" header_index_xxx_p3 ;
                print header_index > output_filename
                }
            else if (tag_key_first_char == "2")
                {
                header_index = header_index_xxx_p1 "indice_authority_"authority_name"_2xx"  header_index_xxx_p2 "2xx - Descrizione secondo quanto previsto dallo standard ISBD" header_index_xxx_p3 ;
                print header_index > output_filename
                }
            else if (tag_key_first_char == "3")
                {
                header_index = header_index_xxx_p1 "indice_authority_"authority_name"_3xx"  header_index_xxx_p2 "3xx - Area delle note" header_index_xxx_p3 ;
                print header_index > output_filename
                }
            else if (tag_key_first_char == "4")
                {
                header_index = header_index_xxx_p1 "indice_authority_"authority_name"_4xx"  header_index_xxx_p2 "4xx - Legami tra le varie registrazioni bibliografiche" header_index_xxx_p3 ;
                print header_index > output_filename
                }
            else if (tag_key_first_char == "5")
                {
                header_index = header_index_xxx_p1 "indice_authority_"authority_name"_5xx"  header_index_xxx_p2 "5xx - Varie forme del titolo" header_index_xxx_p3 ;
                print header_index > output_filename
                }
            else if (tag_key_first_char == "6")
                {
                header_index = header_index_xxx_p1 "indice_authority_"authority_name"_6xx"  header_index_xxx_p2 "6xx - Dati semantici (soggetti, classificazioni, termini di thesaurus) " header_index_xxx_p3 ;
                print header_index > output_filename
                }
            else if (tag_key_first_char == "7")
                {
                header_index = header_index_xxx_p1 "indice_authority_"authority_name"_7xx"  header_index_xxx_p2 "7xx - Responsabilità intellettuale (autore) " header_index_xxx_p3 ;
                print header_index > output_filename
                }
            else if (tag_key_first_char == "8")
                {
                header_index = header_index_xxx_p1 "indice_authority_"authority_name"_8xx"  header_index_xxx_p2 "8xx - Dati internazionali (p.e. informazioni sulla localizzazione della risorsa elettronica) " header_index_xxx_p3 ;
                print header_index > output_filename
                }
            else if (tag_key_first_char == "9")
                {
                header_index = header_index_xxx_p1 "indice_authority_"authority_name"_9xx"  header_index_xxx_p2 "9xx -     Riservato per campi ad uso nazionale/locale " header_index_xxx_p3 ;
                print header_index > output_filename
                }

            last_tag_key_first_char = tag_key_first_char
            }
        print tag_index_auth_AR[i] > output_filename # out_filename".doc.ndx"
        }  
    print tail_index > output_filename # out_filename".doc.ndx" # close last block
    } # end print_authority_index




    BEGIN {FS=" "; 

    header_start="<BR><div class='memproto'>\n\
    <table class='mlabels'>\n\
      <tbody><tr>\n\
      <td class='mlabels-left'>\n\
          <table class='memname'>\n\
            <tbody><tr>\n\
              <td colspan='4'class='memname'>";

          # Tag 001 - Identificativo del record

    header_end="      </td>\n\
            </tr>\n\
          </tbody></table>\n\
      </td>\n\
      <td class='mlabels-right'>\n\
        <span class='mlabels'><span class='mlabel'>"sw_version"</span></span></td>\n\
          </tr>\n\
        </tbody>\n\
    </table>\n\
</div>";



    in_table=0;

    # split tag_AR[""] = "";

    split("", tag_leader_AR)
    split("", tag_index_leader_AR)

    split("", tag_documento_AR)
    split("", tag_index_documento_AR)

    split("", tag_authority_autore_AR)
    split("", tag_index_authority_autore_AR)

    split("", tag_authority_soggetto_AR)
    split("", tag_index_authority_soggetto_AR)

    split("", tag_authority_luogo_AR)
    split("", tag_index_authority_luogo_AR)


    split("", tag_authority_titolo_uniforme_AR)
    split("", tag_index_authority_titolo_uniforme_AR)


    tag_key;
    tag_index;
    tag_data;


    } # end BEGIN 

    { # EXECUTE
    if ($1 ~ "*/") # $1 == "/*!" || 
        {
            # print "<<<<<" tag_data ">>>>>>"
            
            if (tag_key == "LDR")
                {
                tag_anchor = "<a name=\"tag_" tag_key "_leader\">\n"
                tag_leader_AR [tag_key] = tag_anchor tag_data "<BR>"
                idx="<tr><td valign=\"top\"><a href=\"#tag_" tag_key "_leader\">" substr(tag_desc,2,7) "</a></td><td>"substr(tag_desc,12)"</td></tr>"
                tag_index_leader_AR [tag_key] = idx
                }
            if (authority ~ "documento" )
                {
                tag_anchor = "<a name=\"tag_" tag_key "_documento\">\n"
                tag_documento_AR [tag_key] = tag_anchor tag_data "<BR>"
                idx="<tr><td valign=\"top\"><a href=\"#tag_" tag_key "_documento\">" substr(tag_desc,2,7) "</a></td><td>"substr(tag_desc,12)"</td></tr>"
                tag_index_documento_AR [tag_key] = idx
                }
            if (authority ~ "autore" )
                {
                tag_anchor = "<a name=\"tag_" tag_key "_authority_autore\">\n"
                tag_authority_autore_AR [tag_key] = tag_anchor tag_data "<BR>"
                idx="<tr><td valign=\"top\"><a href=\"#tag_" tag_key "_authority_autore\">" substr(tag_desc,2,7) "</a></td><td>"substr(tag_desc,12)"</td></tr>"
                tag_index_authority_autore_AR [tag_key] = idx
                }
            if (authority ~ "soggetto" )
                {
                tag_anchor = "<a name=\"tag_" tag_key "_authority_soggetto\">\n"
                tag_authority_soggetto_AR [tag_key] = tag_anchor tag_data "<BR>"
                idx="<tr><td valign=\"top\"><a href=\"#tag_" tag_key "_authority_soggetto\">" substr(tag_desc,2,7) "</a></td><td>"substr(tag_desc,12)"</td></tr>"
                tag_index_authority_soggetto_AR [tag_key] = idx
                }
            if (authority ~ "luogo" )
                {
                tag_anchor = "<a name=\"tag_" tag_key "_authority_luogo\">\n"
                tag_authority_luogo_AR [tag_key] = tag_anchor tag_data "<BR>"
                idx="<tr><td valign=\"top\"><a href=\"#tag_" tag_key "_authority_luogo\">" substr(tag_desc,2,7) "</a></td><td>"substr(tag_desc,12)"</td></tr>"
                tag_index_authority_luogo_AR [tag_key] = idx
                }
            if (authority ~ "titolo uniforme" )
                {
                tag_anchor = "<a name=\"tag_" tag_key "_authority_titolo_uniforme\">\n"
                tag_authority_titolo_uniforme_AR [tag_key] = tag_anchor tag_data "<BR>"
                idx="<tr><td valign=\"top\"><a href=\"#tag_" tag_key "_authority_titolo_uniforme\">" substr(tag_desc,2,7) "</a></td><td>"substr(tag_desc,12)"</td></tr>"
                tag_index_authority_titolo_uniforme_AR [tag_key] = idx
                }

        }
    else if ($0 ~ "authority" )
        {
            authority=$0
        }
    else if ($1 ~ "<table>" )
        {

            # do nothing
        }
    else if ($1 ~ "</table>" )
        {
        tag_data = tag_data $0 "</div>\n"
        # print $0 "</div>"
        }
    else if ($0 ~ / *<tr> *$/ )
        {
        tag_data = tag_data "<div class='memdoc'>\n"authority "\n<table class='doxtable'>\n<tbody>\n<tr>\n"
        }
    else if ($1 == "\\brief" )
      {
        tag_desc = substr($0,7)
        tag_key = $3
# print tag_key

        gsub("<b>", "", tag_desc)
        gsub("</b>", "", tag_desc)

        
        # tag_index_AR[tag_key] = tag_desc

        # tag_data = "<a name=\"tag_" tag_key "_documento\">\n" header_start "\n"
        tag_data = header_start "\n" tag_desc header_end "\n"

        # print "====> "tag_data
      } 
    else
        {
        tag_data = tag_data $0 "\n"
        # print $0;
        }

    } # End EXECUTE
    
    END {
        # Stampa corpo ed indice del leader
        print_authority_body(tag_leader_AR, out_filename".ldr")
        print_authority_index(tag_index_leader_AR, "ldr", out_filename".ldr.ndx")

        # Stampa corpo ed indice dell'authority documento
        print_authority_body(tag_documento_AR, out_filename".doc")
        print_authority_index(tag_index_documento_AR, "documento", out_filename".doc.ndx")

        # Stampa tag file dell authority autore
        print_authority_body(tag_authority_autore_AR, out_filename".authority_autore")
        print_authority_index(tag_index_authority_autore_AR, "autore", out_filename".authority_autore.ndx")

        # Stampa tag file dell authority soggetto
        print_authority_body(tag_authority_soggetto_AR, out_filename".authority_soggetto")
        print_authority_index(tag_index_authority_soggetto_AR, "soggetto", out_filename".authority_soggetto.ndx")

        # Stampa tag file dell authority luogo
        print_authority_body(tag_authority_luogo_AR, out_filename".authority_luogo")
        print_authority_index(tag_index_authority_luogo_AR, "luogo", out_filename".authority_luogo.ndx")

        # Stampa tag file dell authority titolo uniforme
        print_authority_body(tag_authority_titolo_uniforme_AR, out_filename".authority_titolo_uniforme")
        print_authority_index(tag_index_authority_titolo_uniforme_AR, "titolo_uniforme", out_filename".authority_titolo_uniforme.ndx")

    } # end END

