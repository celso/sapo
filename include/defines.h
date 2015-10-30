/*
 * General stuff
 */

#undef	NULL
#define	NULL 0

#define MYSQL_HOST	"sql.sapo.pt"

/*
 * Nao esquecer o "/" no fim de alguns defines
 */

#define HOME_DIR "/home/sapo/"

#define LOG_DIR			"/servers/logs/"
#define DMOZ_DIR			HOME_DIR"GOOGLE/tree/"
#define BANCO_IMAGENS		HOME_DIR"CANAIS/tree/gfx"
#define NOTICIAS_WWW_DIR 	HOME_DIR"NOTICIAS/"
#define TSF_WWW_DIR 		HOME_DIR"TSF/"
#define LUSA_WWW_DIR 		HOME_DIR"LUSA/"
#define GAMEOVER_WWW_DIR 		HOME_DIR"GAMEOVER/"
#define SUPERSITE_WWW_DIR 		HOME_DIR"SUPERSITE/"
#define BIGBROTHER_WWW_DIR 		HOME_DIR"BIGBROTHER/"
#define NEW_WWW_DIR 		HOME_DIR"WWW/tree/"
#define TEMPO_WWW_DIR 		HOME_DIR"TEMPO/tree/"
#define NEWS_WWW_DIR 		HOME_DIR"NEWS/tree/"
#define NEW_WWW_DIR_NS 		HOME_DIR"WWW/tree"
#define CARTOON 		HOME_DIR"CARTOON/tree"
#define CINEMA	 		HOME_DIR"CINEMA/tree/"
#define NESQUIK_WWW_DIR 	HOME_DIR"NESQUIK/"
#define WAP	 		HOME_DIR"WAP/tree/"
#define TMP_DIR 		HOME_DIR"tmp/"
#define NEW_DIR 		HOME_DIR"new/"
#define LOGS_DIR 		"/home/apache/logs/"
#define TEMPLATES_DIR 		NEW_WWW_DIR"templates/"
#define INCLUDES_DIR 		NEW_WWW_DIR"include/"
#define TEMPO_TEMPLATES_DIR 	HOME_DIR"TEMPO/tree/templates/"
#define NEWS_TEMPLATES_DIR 	HOME_DIR"NEWS/tree/templates/"
#define BASE_TEMPLATES_DIR 	HOME_DIR"BASE/tree/templates/"
#define WWW_BANDAS 		"/bandas/"
#define WWW_ROOT 		"http://www.sapo.pt/"
#define WWW_SECURE 		"http://secure.sapo.pt/"
#define WWW_ROOT_NS 		"http://www.sapo.pt"
#define WWW_ROOT_DIR 		"/"
#define NATAL_WWW_DIR		HOME_DIR"NATAL/"

#define AD_SERVER 		"http://ads.sapo.pt/"

#define BDLOG_DIR 		HOME_DIR"bdlogs/"

#define BANDAS_DIR 		"/home/ads/www/bandas/"
#define BU_DIR 			"/home/ads/www/bandas/uploads/"
#define BU_WWW_DIR 		"http://ads.sapo.pt/bandas/uploads/"
#define SEC_BU_WWW_DIR 		"https://ads.sapo.pt/bandas/uploads/"

#define NENUFAR_DIR 		HOME_DIR"tree/"
#define BANDAS_WWW 		"http://ads.sapo.pt/bandas/"
#define PUBSTATS_DIR 		HOME_DIR"tree/info/pubstats/"
#define PRIVSTATS_DIR 		HOME_DIR"tree/info/stats/"

#define DICTIONARY		HOME_DIR"dbase/dictionary.idx"

/*
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * Super SAPO
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 */

#define SUPER_HOME_DIR "/home/sapo/super/"
#define SWORK_DIR SUPER_HOME_DIR"super/"
#define SROOT_DIR SUPER_HOME_DIR"super/docs/"
#define SROOT_DIR_NS SUPER_HOME_DIR"docs"
#define SFILES_DIR SUPER_HOME_DIR"files/"
#define STEMPLATES_DIR SUPER_HOME_DIR"templates/"
#define SLOGS_DIR SUPER_HOME_DIR"logs/"
#define SBASE_DIR SUPER_HOME_DIR"dbase/"
#define SWWW_ROOT "http://super.sapo.pt/"
#define SWWW_ROOT_NS "http://super.sapo.pt"

/*
 * Outros
 */

#define MAIL_CMD "/usr/bin/mail"
#define SENDMAIL_CMD "/usr/sbin/sendmail"
#define MKDIR_CMD "/bin/mkdir"
#define TOUCH_CMD "/usr/bin/touch"
#define TAR_CMD "/bin/tar"
#define FIND_CMD "/usr/bin/find"
#define SORT_CMD "/usr/bin/sort"

/*
 * Merdas para isto compilar no FreeBSD!
 */

#define FREEBSD
#define SAPO_UID 1001
#define SAPO_GID 1001
#define NOTICIAS_UID 1010
#define NOTICIAS_GID 1010

/*
 * Defines da praxe
 */

#define SMALL_BUFFER	1024
#define MEDIUM_BUFFER	4096
#define	BIG_BUFFER	8096
#define HUGE_BUFFER	8096*2

/* Apontador novos tem menos de x dias */

#define DAYS_NEW 15
#define REPORT_DAYS 15
#define REPORT_DAYS_AS "15"

/*
 * General stuff
 */

#undef	NULL
#define	NULL 0

#define BANDAS_HOST	"ads.sapo.pt"


/*
 * Flags para apontadores
 */

#define APTD_NONE		0
#define APTD_EMAIL_OWNER	(1<<0)
#define APTD_EXPIRES		(1<<1)
#define APTD_DESTAQUE		(1<<2)

/*
 * Flags do index (Atencao so' pode ter 6 bits)
 */

#define IDX_HASDESC		(1<<0)
#define IDX_ISNEW		(1<<1)
#define IDX_ISDESTAQUE		(1<<2)

#define COR_DESTAQUE1		"#ffffcc"

/*
 * Flags para directorios
 */

#define DIR_NONE		0
#define DIR_DONT_CREATE_WWW	(1<<0L)
#define DIR_ORDER_ALFA		(1<<1L)
#define DIR_ORDER_DATE		(1<<2L)
#define DIR_HAS_LOGO		(1<<3L)
#define DIR_HAS_BACKGROUND	(1<<4L)
#define DIR_HAS_ALTBDGROUP	(1<<5L)
#define DIR_DONT_INDEX		(1<<6L)
#define DIR_ORDER_REVERSE	(1<<7L)

/*
 * Flags da tabela toadd (Apontadores por adicionar)
 */

#define TOADD_NONE		0
#define TOADD_EVENTO		(1<<0)

/*
 * Counters
 */

#define APONTADORES     1
#define BANDAS          2
#define GRUPOS          3
#define CLIENTES        4
#define TOADD           5

/*
 * 'old' table definitions
 */

#define MSQL_DIR 1
#define MSQL_FILE 2

/*
 * Misc
 */

#define BITMAP_SIZE	2048

#define MSQL_DUMP	"/home/sapo/msql2/bin/msqldump"
#define BACKUP_DIR	"/home/sapo/backups"
#define SQL_BACKUP_DIR	"/home/sapo/backups/SQL"

/*
 * Miolo
 */

#define DBASE_MIOLO	"/home/sapo/dbase/"

#define MIOLO_NONE		0
#define MIOLO_SUBTITULO		(1<<0L)
#define MIOLO_CORPO		(1<<1L)
#define MIOLO_LEAD		(1<<2L)
#define MIOLO_DESENVOLVIMENTO	(1<<3L)
#define MIOLO_IMAGEM		(1<<4L)

/* 
 * NOTICIAS SOURCES
 */

#define SOURCE_NONE		0
#define SOURCE_CM		(1<<0L)
#define SOURCE_DIGITO		(1<<1L)

/* 
 * NOTICIAS TIPOS
 */

#define NSECS			5

#define NACIONAIS		(1<<0L)
#define INTERNACIONAIS		(1<<1L)
#define DESPORTO		(1<<2L)
#define ESPECTACULOS		(1<<3L)
#define TECNOLOGIA		(1<<4L)

/*
 * bandas.c
 */
#define SB_OUTPUT       1<<3L
#define SB_NONE         1<<0L
#define SB_TARGET       1<<1L
#define SB_NOTEXT       1<<2L
#define SB_INPUT        1<<4L
#define SB_SPECIAL      1<<5L
#define SB_ENV		1<<6L
#define SB_NOTEXT_NT	1<<7L

#define SEARCH_HOST	"pesquisa.sapo.pt"
#define SEARCH_PORT	6969
