/*
 * Program       : queries.h
 * Author        : Celso Martinho (celso@ua.pt)
 */

char ret[8096];

/* library/mkpage.c */

#define NSELECT1 "SELECT flags FROM new WHERE location='%s' AND type=%d"
#define NSELECT2 "select title,id,flags,grupobd from new where location='%s' and type=1"
#define NSELECT3 "select id from new where area='%s' and type=1"
#define NSELECT4 "select id from new where area='%s' and type=2"
#define NSELECT5 "select location,title,description,id from new where area='%s' and type=%d order by title"
#define NSELECT6 "select location,title,description,id,mdate from new where area='%s' and type=1 order by mdate"
#define NSELECT7 "select location,title,description,id from new where area='%s' and type=1"
#define NSELECT8 "select location,title from new where area='%s' and type=1"
#define NSELECT9 "SELECT src FROM links WHERE dst=%d AND type=%d"
#define NSELECT10 "select location,title,description,id,mdate,email,flags,area from new where id=%s order by title"
#define NSELECT11 "select location,title,description,id,mdate,email,flags,area from new where id=%s order by mdate"
#define NSELECT12 "select location,title,description,id,mdate,email,flags,area from new where id=%s"
#define NSELECT13 "select location,title,description,id,mdate,email,flags,code from new where area='%s' and type=2 order by title"
#define NSELECT14 "select location,title,description,id,mdate,email,flags,code from new where area='%s' and type=2 order by mdate"
#define NSELECT15 "select location,title,description,id,mdate,email,flags,code from new where area='%s' and type=2"
#define NSELECT16 "SELECT src FROM links WHERE dst=%d AND type=%d"

/* library/bandas.c */

#define SELECT20 "select id,offset,bitmap from grupos where id=%d"
#define SELECT21 "SELECT id,filename,description,url,views,priv_views FROM bandas WHERE id=%d"
#define SELECT22 "select id,offset,bitmap from grupos where id=%d"
#define SELECT23 "SELECT id,filename,description,url,views,priv_views FROM bandas WHERE id=%d"
#define SELECT24 "select id,offset,bitmap,totalcount from grupos where id=%d"
#define SELECT25 "SELECT id,filename,description,url,views,priv_views FROM bandas WHERE id=%d"
#define SELECT26 "select id,offset,bitmap from grupos where id=%d"
#define SELECT27 "SELECT id,filename,description,url,views,priv_views FROM bandas WHERE id=%d"

/* library/queries.c */

#define NSELECT30 "select location from new where id=%d and type=1"
#define NSELECT31 "select id from new where area like '%s%%' and type=1"
#define NSELECT32 "select location from new where id=%d and type=1"
#define NSELECT33 "select id from new where area like '%s%%' and type=2"
#define NSELECT34 "select title from new where id=%d"
#define NSELECT35 "select location from new where id=%d"
#define NSELECT36 "select area from new where id=%d"
#define NSELECT37 "select description from new where id=%d"
#define NSELECT38 "select email from new where id=%d"
#define NSELECT39 "select type from new where id=%d"
#define NSELECT40 "select depth from new where id=%d"

/* library/cmsql.c */

#define SELECT50 "select id from %s where id=%d"
#define SELECT51 "select id from %s where %s = %d"
#define SELECT52 "select %s from %s where id = %d"
#define SELECT53 "SELECT _seq FROM %s"

/* make/make.c */

#define NSELECT60 "select location,type from new where id=%d"
#define NSELECT61 "select location,type,area from new where id=%s"
#define NSELECT62 "select id from new where location like '%s'"
#define NSELECT63 "select area from new where id=%d"
#define NSELECT64 "select location,title,description,depth,id from new where location='%s' and type=1"
#define NSELECT65 "select id from new where area='%s' and type=1"
#define NSELECT66 "select id from new where area='%s' and type=2"
#define NSELECT67 "select location,title,description,email,expire,flags,owner,peso from new where id=%d and type=2"
#define NSELECT68 "select location from new where id=%d"
#define NSELECT69 "select type,location from new where id=%s"

/* bdadm/bdadm.c */

#define SELECT70 "select id from bandas where id=%d"
#define SELECT71 "select id,bitmap,description from grupos where id=%d"
#define SELECT72 "select id,url,description,filename from bandas where id=%d"
#define SELECT73 "select id,bitmap,description from grupos where id=%s"
#define SELECT74 "select id,filename,description,url,hits,views,email from bandas where id=%d"
#define SELECT75 "select id,description,bitmap,totalcount,initcount from grupos order by id"
#define SELECT76 "select id,description,bitmap from grupos where id=%s"
#define SELECT77 "select id,url,description,filename,email,creation,expire,owner from bandas where id=%s"
#define SELECT78 "select id,url,description,filename from bandas where id=%s"
#define SELECT79 "select id,url,description,filename,email,creation from bandas where id=%s"
#define SELECT80 "select id from grupos"
#define SELECT81 "select id,filename,description,url,hits,views,email,expire,owner,creation from bandas where active=1 order by id DESC"
#define SELECT82 "select id,expire from bandas where id=%d"
#define SELECT83 "select id,bitmap,description from grupos where id=%d"
#define SELECT84 "select id,filename,description,url,hits,views,email,expire,owner,creation from bandas where active=0 order by id"
#define SELECT85 "select id,description from grupos"
#define SELECT86 "select id,termo,grupo,creation,expire from palavras order by grupo"
#define SELECT87 "select grupo from palavras where termo like '%s'"
#define SELECT88 "select description from grupos where id=%s"
#define SELECT89 "select user_id,id from records order by id"

/* SUPER/cladm/cladm.c */

#define SELECT90 "select id,empresa,fax_geral,tel_geral,email_geral,morada,www,contacto1,descricao1,tel1,email1,www1,contacto2,descricao2,tel2,email2,www2,contacto3,descricao3,tel3,email3,www3 from clientes where id=%s"
#define SELECT91 "select id,empresa,fax_geral,tel_geral,email_geral,www,contacto1,contacto2,contacto3,email1,www1,email2,www2,email3,www3 from clientes where id=%ld"
#define SELECT92 "select id,empresa,fax_geral,tel_geral,email_geral,www,contacto1,contacto2,contacto3,email1,www1,email2,www2,email3,www3 from clientes"
#define SELECT93 "select id,empresa,fax_geral,tel_geral,email_geral,morada,www,contacto1,descricao1,tel1,email1,www1,contacto2,descricao2,tel2,email2,www2,contacto3,descricao3,tel3,email3,www3 from clientes"
#define SELECT94 "select id,empresa,fax_geral,tel_geral,email_geral,morada,www,contacto1,descricao1,tel1,email1,www1,contacto2,descricao2,tel2,email2,www2,contacto3,descricao3,tel3,email3,www3 from clientes where id=%s"
#define SELECT95 "select id,empresa from clientes where id=%s"

/* SUPER/getbd/getbd.c */

#define SELECT100 "select url,hits,priv_hits from bandas where id=%d"

/* SUPER/dprefs/dprefs.c */

#define NSELECT110 "select location,title,description,depth,id,flags,grupobd,miolo,peso from new where location='%s' and type=1"

/* SUPER/bdmaint/bdmaint.c */

#define SELECT120 "select id,description,bitmap from grupos order by id"
#define SELECT121 "select id,email,hits,views,url,description,owner,srv_lastreset,srv_lasthits,srv_lastviews,srv_lastpercent1,srv_lastpercent2,srv_lastpercent3 from bandas where srv_lastreset < %d"

/* SUPER/best/best.c */

#define SELECT130 "SELECT owner from bandas where id=%d"
#define SELECT131 "select id,filename,description,url,priv_hits,priv_views,email,expire,lastreset,lastmod,hits,views,active from bandas where id=%d"
#define SELECT132 "SELECT id,filename,description,url,priv_hits,priv_views,email,expire,lastreset,lastmod,hits,views,active FROM bandas WHERE owner LIKE '%s' ORDER BY id DESC"
#define SELECT133 "select id,url,description,filename,email,creation,expire from bandas where id=%s"
#define SELECT134 "select id,url,description,filename,active from bandas where id=%s"
#define SELECT135 "select id,expire from bandas where id=%d"

/* SAPO/SUPER/addnew/addnew.c */

#define SELECT136 "SELECT url FROM ntoadd WHERE id=%d"
#define NSELECT137 "SELECT location,area FROM new WHERE location like '%s'"
#define SELECT138 "SELECT areas,title,description,url,netbi,mdate,flags FROM ntoadd WHERE id=%d"
#define SELECT139 "SELECT title,description,url,netbi,id FROM ntoadd WHERE url CLIKE '%%%s%%'"
#define SELECT140 "SELECT title,description,url,netbi,id FROM ntoadd"
#define SELECT141 "SELECT nome,email FROM ficha WHERE id=%s"

/* SAPO/SUPER/mkdir/mkdir.c */

#define NSELECT150 "select area,id,depth from new where area like '%s'"
#define NSELECT151 "select id from new where location='%s' and type=1"

/* SUPER/newloc/newloc.c */

#define NSELECT160 "select location,title,description,depth,id from new where location='%s' and type=1"
#define NSELECT161 "select id from new where area='%s' and type=1"
#define NSELECT162 "select id from new where area='%s' and type=2"

/* SUPER/newptr/newptr.c */

#define NSELECT170 "select location,type from new where id=%d"
#define NSELECT171 "select location,title,description,depth,id from new where location='%s' and type=1"
#define NSELECT172 "select id from new where area='%s' and type=1"
#define NSELECT173 "select id from new where area='%s' and type=2"
#define NSELECT174 "select id from users where login like '%d'"
#define NSELECT175 "select email from ficha where id=%s"

/* SUPER/navigator/navigator.c */

#define NSELECT180 "select area,title,description,id from tree where location='%s'"
#define NSELECT181 "select location,id from tree where area='%s'"
#define NSELECT182 "select location,id from tree order by id"

/* SUPER/move/move.c */

#define NSELECT190 "SELECT id,type,depth,location,area FROM new WHERE location LIKE '%s%%' AND type=%d"
#define NSELECT191 "SELECT id,type,depth,location,area FROM new WHERE area LIKE '%s' AND type=%d"

/* SAPO/addurl/naddurl.c */

#define NSELECT200 "SELECT id,login,passwd FROM users WHERE login LIKE '%s'"
#define NSELECT201 "SELECT id,area,title,location,description FROM new WHERE id=%d"
#define NSELECT202 "SELECT flags FROM ficha WHERE id=%s"

/* SAPO/addurl/alturl.c */

#define NSELECT300 "SELECT id,login,passwd FROM users WHERE login LIKE '%s'"
#define NSELECT301 "SELECT flags FROM ficha WHERE id=%s"

/* library/bandas.c */

#define UPDATE1 "UPDATE bandas SET views=%d,priv_views=%d WHERE id=%d"
/* #define UPDATE2 "UPDATE grupos SET offset=%d WHERE id=%d" */
#define UPDATE3 "UPDATE bandas SET views=%d,priv_views=%d WHERE id=%d"
#define UPDATE4 "UPDATE grupos SET offset=%d,totalcount=%d WHERE id=%d"
#define UPDATE5 "UPDATE palavras SET termo='%s',creation=%d WHERE id=%d"

/* SUPER/getbd/getbd.c */

#define UPDATE10 "update bandas set hits=%d,priv_hits=%d where id=%d"

/* SUPER/dprefs/dprefs.c */

#define UPDATE20 "update new set title='%s',description='%s',flags=%d,grupobd=%d,miolo=%d,peso=%d where id=%ld"

/* SUPER/bdmaint/bdmaint.c */

#define UPDATE30 "update bandas SET srv_lastpercent1=%d,srv_lastpercent2=%d,srv_lastpercent3=%d,srv_lastreset=%d,srv_lasthits=%d,srv_lastviews=%d WHERE id=%s"

/* SUPER/best/best.c */

#define UPDATE40 "UPDATE bandas SET priv_views=0,priv_hits=0,lastreset=%d WHERE id=%s"
#define UPDATE41 "UPDATE bandas SET url='%s',description='%s',email='%s',lastmod=%d WHERE id=%d"

/* SUPER/newptr/newptr.c */

#define UPDATE50 "UPDATE new SET location='%s',title='%s',description='%s',email='%s',expire=%d,flags=%d,owner=%d,peso=%d WHERE id=%d"
#define UPDATE51 "UPDATE new SET code='%s' WHERE id=%d"

/* SUPER/cladm/cladm.c */

#define UPDATE60 "UPDATE clientes SET empresa='%s',fax_geral='%s',tel_geral='%s',email_geral='%s',morada='%s',www='%s',contacto1='%s',descricao1='%s',tel1='%s',email1='%s',www1='%s',contacto2='%s',descricao2='%s',tel2='%s',email2='%s',www2='%s',contacto3='%s',descricao3='%s',tel3='%s',email3='%s',www3='%s' WHERE id=%ld"

/* SUPER/bdadm/bdadm.c */

#define UPDATE70 "UPDATE bandas SET views=0,hits=0,lastreset=%d WHERE id=%s"
#define UPDATE71 "UPDATE grupos SET bitmap='%s' where id=%d"
#define UPDATE72 "UPDATE bandas SET url='%s',description='%s',email='%s',expire=%d,owner='%s' WHERE id=%d"
#define UPDATE73 "UPDATE grupos SET bitmap='%s' where id=%d"
#define UPDATE74 "UPDATE bandas SET active=0 where id=%s"
#define UPDATE75 "UPDATE bandas SET active=1 where id=%s"
#define UPDATE76 "UPDATE grupos SET description='%s' where id=%s"

/* SUPER/move/move.c */

#define UPDATE80 "UPDATE new SET area='%s',location='%s',depth=%d WHERE id=%ld"
#define UPDATE81 "UPDATE new SET area='%s',depth=%d WHERE id=%ld"

/* SUPER/make/make.c */

#define INSERT1 "insert into links values (%s,%d,%d,%d)"

/* SUPER/newptr/newptr.c */

#define INSERT10 "INSERT INTO new VALUES (%s,%d,'%s','%s','%s','%s','%s',%d,0,%d,0,0,%d,0,%d,%d,'%s')"

/* SUPER/cladm/cladm.c */

#define INSERT20 "INSERT INTO clientes VALUES (%ld,%ld,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"

/* SUPER/mkdir/mkdir.c */

#define INSERT30 "INSERT INTO new VALUES (%s,%d,'%s','%s','%s','%s','',%d,%d,%d,%d,%d,0,0,0,%d,'')"

/* SUPER/bdadm/bdadm.c */

#define INSERT40 "INSERT INTO grupos VALUES (NULL,NULL,0,'%s','',%d,%d,%d)"
#define INSERT41 "INSERT INTO bandas VALUES (NULL,NULL,0,0,'%s','%s','%s','%s',%d,%d,%d,%d,'%s',0,0,0,0,0,0,0,0,1,%d,%d,%d,%d)"
#define INSERT42 "INSERT INTO palavras VALUES (NULL,'%s',%d,%d,%d)"

/* SUPER/convcls/convcls.c */

#define INSERT50 "INSERT INTO clientes VALUES (%ld,%ld,'%s','%s','%s','%s','%s','%s','%s','','','','','','','','','','','','','','')"

/* SUPER/convnptrs/convnptrs.c */

/* #define INSERT60 "INSERT INTO toadd VALUES (%ld,%ld,'%s','%s','%s','%s','%s',%d,%d)" */

/* SUPER/make/make.c */ 

#define DELETE1 "delete from links where src=%d AND dst=%d"

/* SUPER/delete/delete.c */

#define DELETE10 "delete from new where area like '%s%%'"
#define DELETE11 "delete from new where id=%ld"
#define DELETE12 "delete from links where dst=%ld"
#define DELETE13 "delete from new where id=%ld"
#define DELETE14 "delete from links where src=%ld"

/* SUPER/bdadm/bdadm.c */

#define DELETE20 "delete from grupos where id=%s"
#define DELETE21 "delete from bandas where id=%s"
#define DELETE22 "delete from palavras where id=%s"

/* SUPER/cladm/cladm.c */

#define DELETE30 "delete from clientes where id=%s"

/* SUPER/newptr/newptr.c */

#define DELETE40 "delete from ntoadd where id=%s"

/* SUPER/addnew/addnew.c */

#define DELETE50 "DELETE FROM ntoadd WHERE id=%s"


