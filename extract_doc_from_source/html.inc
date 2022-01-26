
header_html="<html xmlns='http://www.w3.org/1999/xhtml'>
<head>
<meta http-equiv='Content-Type' content='text/xhtml;charset=UTF-8'/>
<meta http-equiv='X-UA-Compatible' content='IE=9'/>
<meta name='generator' content='Doxygen 1.8.11'/>
<title>Export unimarc TAGS</title>
<link href='tabs.css' rel='stylesheet' type='text/css'/>
<link href='doxygen.css' rel='stylesheet' type='text/css' />
</head>
<body>"


data_etrazione=`date +"%d/%m/%Y %H:%M"`

index_html_p1="<html xmlns='http://www.w3.org/1999/xhtml'>
<head>
<meta http-equiv='Content-Type' content='text/xhtml;charset=UTF-8'/>
<meta http-equiv='X-UA-Compatible' content='IE=9'/>
<meta name='generator' content='Doxygen 1.8.11'/>
<title>Export unimarc TAGS</title>
<link href='tabs.css' rel='stylesheet' type='text/css'/>
<link href='doxygen.css' rel='stylesheet' type='text/css' />
</head>
<body>

<br>
<h1>Documentazione delle etichette Unimarc estratte per INDICE e POLO</h1>
<h2>a partire dai sorgenti della procedura 'offlineExportUnimarc'</h2>
<p>Documentazione prodotta da procedura in data $data_etrazione</p>
<br>
<hr>

<div class='memproto'>
<table class='mlabels'>
  <tbody><tr>
  <td class='mlabels-left'>
      <table class='memname'>
        <tbody><tr>
          <td colspan='4'class='memname'>Indice generale offlineExportUnimarc</td>
        </tr>
      </tbody></table>
  </td>
  <td class='mlabels-right'>
<span class='mlabels'><span class='mlabel'>"  

index_html_p2="</span></span></td>
  </tr>
</tbody></table>
</div>
<div class='memdoc'>
<table class='doxtable'>
<tbody><tr>
<th valign='top'>Blocco</th><th>Descrizione </th></tr>
<tr><td valign='top'>LDR</td><td><a href="#tag_LDR_leader">Record leader</a></td></tr>
<tr><td valign='top'>0xx</td><td>Blocco dei numeri di identificazione</td></tr>
<tr><td valign='top'>1xx</td><td>Blocco delle informazioni codificate</td></tr>
<tr><td valign='top'>2xx</td><td>Blocco delle informazioni descrittive</td></tr>
<tr><td valign='top'>3xx</td><td>Blocco delle note</td></tr>
<tr><td valign='top'>4xx</td><td>Blocco dei legami </td></tr>
<tr><td valign='top'>5xx</td><td>Bolocco dei titoli correlati</td></tr>
<tr><td valign='top'>6xx</td><td>Blocco dei dati semantici (soggetti, classificazioni, termini di thesaurus) </td></tr>
<tr><td valign='top'>7xx</td><td>Blocco delle responsabilità intellettuali</td></tr>
<tr><td valign='top'>8xx</td><td>Blocco dati per uso internazionale</td></tr>
<tr><td valign='top'>9xx</td><td>Blocco riservato per uso nazionale/locale </td></tr>
</tbody></table>
</div>
<ul>
  <li><a href='#tag_LDR_leader'>Leader record unimarc</a> 
</ul>
<ul>
  <li><a href='#indice_authority_documento'>Blocco BIBLIOGRAFICO</a> 
    [
    <a href='#indice_authority_documento_0xx'>0xx</a>,
    <a href='#indice_authority_documento_1xx'>1xx</a>,
    <a href='#indice_authority_documento_2xx'>2xx</a>,
    <a href='#indice_authority_documento_3xx'>3xx</a>,
    <a href='#indice_authority_documento_4xx'>4xx</a>,
    <a href='#indice_authority_documento_5xx'>5xx</a>,
    <a href='#indice_authority_documento_6xx'>6xx</a>,
    <a href='#indice_authority_documento_7xx'>7xx</a>,
    <a href='#indice_authority_documento_8xx'>8xx</a>,
    <a href='#indice_authority_documento_9xx'>9xx</a>
    ] 
  </li>
  <li><a href='#indice_authority_autore'>Blocco authority AUTORE</a>
    [
    <a href='#indice_authority_autore_0xx'>0xx</a>,
    <a href='#indice_authority_autore_1xx'>1xx</a>,
    <a href='#indice_authority_autore_2xx'>2xx</a>
    <a href='#indice_authority_autore_3xx'>3xx</a>,
    <a href='#indice_authority_autore_4xx'>4xx</a>,
    <a href='#indice_authority_autore_5xx'>5xx</a>,
<!--
    <a href='#indice_authority_autore_6xx'>6xx</a>,
    <a href='#indice_authority_autore_7xx'>7xx</a>,
-->    
    <a href='#indice_authority_autore_8xx'>8xx</a>,
    <a href='#indice_authority_autore_9xx'>9xx</a>
    ] 
  </li>
  <li><a href='#indice_authority_soggetto'>Blocco authority SOGGETTO</a>
    [
    <a href='#indice_authority_soggetto_0xx'>0xx</a>,
    <a href='#indice_authority_soggetto_1xx'>1xx</a>,
    <a href='#indice_authority_soggetto_2xx'>2xx</a>,
    <a href='#indice_authority_soggetto_3xx'>3xx</a>,
<!--
    <a href='#indice_authority_soggetto_4xx'>4xx</a>,
    <a href='#indice_authority_soggetto_5xx'>5xx</a>,
    <a href='#indice_authority_soggetto_6xx'>6xx</a>,
    <a href='#indice_authority_soggetto_7xx'>7xx</a>,
-->    
    <a href='#indice_authority_soggetto_8xx'>8xx</a>,
    <a href='#indice_authority_soggetto_9xx'>9xx</a>
    ] 
  </li>
  <li><a href='#indice_authority_luogo'>Blocco authority LUOGO</a>
    [
    <a href='#indice_authority_luogo_0xx'>0xx</a>,
    <a href='#indice_authority_luogo_1xx'>1xx</a>,
    <a href='#indice_authority_luogo_2xx'>2xx</a>,
    <a href='#indice_authority_luogo_3xx'>3xx</a>,
<!--
    <a href='#indice_authority_luogo_4xx'>4xx</a>,
    <a href='#indice_authority_luogo_5xx'>5xx</a>,
    <a href='#indice_authority_luogo_6xx'>6xx</a>,
    <a href='#indice_authority_luogo_7xx'>7xx</a>,
-->
    <a href='#indice_authority_luogo_8xx'>8xx</a>,
<!--
    <a href='#indice_authority_luogo_9xx'>9xx</a>
-->
  ]
  </li>
  <li><a href='#indice_authority_titolo_uniforme'>Blocco authority TITOLO UNIFORME</a>
    [
    <a href='#indice_authority_titolo_uniforme_0xx'>0xx</a>,
    <a href='#indice_authority_titolo_uniforme_1xx'>1xx</a>,
    <a href='#indice_authority_titolo_uniforme_2xx'>2xx</a>,
    <a href='#indice_authority_titolo_uniforme_3xx'>3xx</a>,
<!--
    <a href='#indice_authority_titolo_uniforme_4xx'>4xx</a>,
    <a href='#indice_authority_titolo_uniforme_5xx'>5xx</a>,
    <a href='#indice_authority_titolo_uniforme_6xx'>6xx</a>,
    <a href='#indice_authority_titolo_uniforme_7xx'>7xx</a>,
-->
    <a href='#indice_authority_titolo_uniforme_8xx'>8xx</a>,
<!--
    <a href='#indice_authority_titolo_uniforme_9xx'>9xx</a>
-->
  ]
  </li>
</ul>"


header_indice_p1="<a name='"
# indice_authority_documento
header_indice_p2="'>
<div class='memproto'>
<table class='mlabels'>
  <tbody><tr>
  <td class='mlabels-left'>
      <table class='memname'>
        <tbody><tr>
          <td colspan='4'class='memname'>"
# Indice authority Documento
header_indice_p3="</td>
        </tr>
      </tbody></table>
  </td>
  <td class='mlabels-right'>
<span class='mlabels'><span class='mlabel'>"
# Version
header_indice_p4="</span></span></td>
  </tr>
</tbody></table>
</div>"

tail_html="</body></html>" 
