#define HTML_ENTITIES 66

char * ISO_Latin1[HTML_ENTITIES] = {
    "\306",	/* capital AE diphthong (ligature) */ 
    "\301",	/* capital A, acute accent */ 
    "\302",	/* capital A, circumflex accent */ 
    "\300",	/* capital A, grave accent */ 
    "\305",	/* capital A, ring */ 
    "\303",	/* capital A, tilde */ 
    "\304",	/* capital A, dieresis or umlaut mark */ 
    "\307",	/* capital C, cedilla */ 
    "\320",	/* capital Eth, Icelandic */ 
    "\311",	/* capital E, acute accent */ 
    "\312",	/* capital E, circumflex accent */ 
    "\310",	/* capital E, grave accent */ 
    "\313",	/* capital E, dieresis or umlaut mark */ 
    "\315",	/* capital I, acute accent */ 
    "\316",	/* capital I, circumflex accent */ 
    "\314",	/* capital I, grave accent */ 
    "\317",	/* capital I, dieresis or umlaut mark */ 
    "\321",	/* capital N, tilde */ 
    "\323",	/* capital O, acute accent */ 
    "\324",	/* capital O, circumflex accent */ 
    "\322",	/* capital O, grave accent */ 
    "\330",	/* capital O, slash */ 
    "\325",	/* capital O, tilde */ 
    "\326",	/* capital O, dieresis or umlaut mark */ 
    "\336",	/* capital THORN, Icelandic */ 
    "\332",	/* capital U, acute accent */ 
    "\333",	/* capital U, circumflex accent */ 
    "\331",	/* capital U, grave accent */ 
    "\334",	/* capital U, dieresis or umlaut mark */ 
    "\335",	/* capital Y, acute accent */ 
    "\341",	/* small a, acute accent */ 
    "\342",	/* small a, circumflex accent */ 
    "\346",	/* small ae diphthong (ligature) */ 
    "\340",	/* small a, grave accent */ 
    "\046",	/* ampersand */ 
    "\345",	/* small a, ring */ 
    "\343",	/* small a, tilde */ 
    "\344",	/* small a, dieresis or umlaut mark */ 
    "\347",	/* small c, cedilla */ 
    "\351",	/* small e, acute accent */ 
    "\352",	/* small e, circumflex accent */ 
    "\350",	/* small e, grave accent */ 
    "\360",	/* small eth, Icelandic */ 
    "\353",	/* small e, dieresis or umlaut mark */ 
    "\076",	/* greater than */ 
    "\355",	/* small i, acute accent */ 
    "\356",	/* small i, circumflex accent */ 
    "\354",	/* small i, grave accent */ 
    "\357",	/* small i, dieresis or umlaut mark */ 
    "\074",	/* less than */ 
    "\361",	/* small n, tilde */ 
    "\363",	/* small o, acute accent */ 
    "\364",	/* small o, circumflex accent */ 
    "\362",	/* small o, grave accent */ 
    "\370",	/* small o, slash */ 
    "\365",	/* small o, tilde */ 
    "\366",	/* small o, dieresis or umlaut mark */ 
    "\042", /* double quote sign - June 94 */
    "\337",	/* small sharp s, German (sz ligature) */ 
    "\376",	/* small thorn, Icelandic */ 
    "\372",	/* small u, acute accent */ 
    "\373",	/* small u, circumflex accent */ 
    "\371",	/* small u, grave accent */ 
    "\374",	/* small u, dieresis or umlaut mark */ 
    "\375",	/* small y, acute accent */ 
    "\377",	/* small y, dieresis or umlaut mark */ 
};

const char* entities[HTML_ENTITIES] = {
    "AElig",	/* capital AE diphthong (ligature) */ 
    "Aacute",	/* capital A, acute accent */ 
    "Acirc",	/* capital A, circumflex accent */ 
    "Agrave",	/* capital A, grave accent */ 
    "Aring",	/* capital A, ring */ 
    "Atilde",	/* capital A, tilde */ 
    "Auml",	/* capital A, dieresis or umlaut mark */ 
    "Ccedil",	/* capital C, cedilla */ 
    "ETH",	/* capital Eth, Icelandic */ 
    "Eacute",	/* capital E, acute accent */ 
    "Ecirc",	/* capital E, circumflex accent */ 
    "Egrave",	/* capital E, grave accent */ 
    "Euml",	/* capital E, dieresis or umlaut mark */ 
    "Iacute",	/* capital I, acute accent */ 
    "Icirc",	/* capital I, circumflex accent */ 
    "Igrave",	/* capital I, grave accent */ 
    "Iuml",	/* capital I, dieresis or umlaut mark */ 
    "Ntilde",	/* capital N, tilde */ 
    "Oacute",	/* capital O, acute accent */ 
    "Ocirc",	/* capital O, circumflex accent */ 
    "Ograve",	/* capital O, grave accent */ 
    "Oslash",	/* capital O, slash */ 
    "Otilde",	/* capital O, tilde */ 
    "Ouml",	/* capital O, dieresis or umlaut mark */ 
    "THORN",	/* capital THORN, Icelandic */ 
    "Uacute",	/* capital U, acute accent */ 
    "Ucirc",	/* capital U, circumflex accent */ 
    "Ugrave",	/* capital U, grave accent */ 
    "Uuml",	/* capital U, dieresis or umlaut mark */ 
    "Yacute",	/* capital Y, acute accent */ 
    "aacute",	/* small a, acute accent */ 
    "acirc",	/* small a, circumflex accent */ 
    "aelig",	/* small ae diphthong (ligature) */ 
    "agrave",	/* small a, grave accent */ 
    "amp",	/* ampersand */ 
    "aring",	/* small a, ring */ 
    "atilde",	/* small a, tilde */ 
    "auml",	/* small a, dieresis or umlaut mark */ 
    "ccedil",	/* small c, cedilla */ 
    "eacute",	/* small e, acute accent */ 
    "ecirc",	/* small e, circumflex accent */ 
    "egrave",	/* small e, grave accent */ 
    "eth",	/* small eth, Icelandic */ 
    "euml",	/* small e, dieresis or umlaut mark */ 
    "gt",		/* greater than */ 
    "iacute",	/* small i, acute accent */ 
    "icirc",	/* small i, circumflex accent */ 
    "igrave",	/* small i, grave accent */ 
    "iuml",	/* small i, dieresis or umlaut mark */ 
    "lt",		/* less than */ 
    "ntilde",	/* small n, tilde */ 
    "oacute",	/* small o, acute accent */ 
    "ocirc",	/* small o, circumflex accent */ 
    "ograve",	/* small o, grave accent */ 
    "oslash",	/* small o, slash */ 
    "otilde",	/* small o, tilde */ 
    "ouml",	/* small o, dieresis or umlaut mark */
    "quot",	/* double quote sign  - June 1994 */ 
    "szlig",	/* small sharp s, German (sz ligature) */ 
    "thorn",	/* small thorn, Icelandic */ 
    "uacute",	/* small u, acute accent */ 
    "ucirc",	/* small u, circumflex accent */ 
    "ugrave",	/* small u, grave accent */ 
    "uuml",	/* small u, dieresis or umlaut mark */ 
    "yacute",	/* small y, acute accent */ 
    "yuml",	/* small y, dieresis or umlaut mark */ 
};

#define ISO_SIMBOLS 60

struct iso2ascii {
    char iso;
    char ascii;
};

struct iso2ascii isotable[ISO_SIMBOLS] = {
    '\306',	'a', /* capital AE diphthong (ligature) */ 
    '\301',	'a', /* capital A, acute accent */ 
    '\302',	'a', /* capital A, circumflex accent */ 
    '\300',	'a', /* capital A, grave accent */ 
    '\305',	'a', /* capital A, ring */ 
    '\303',	'a', /* capital A, tilde */ 
    '\304',	'a', /* capital A, dieresis or umlaut mark */ 
    '\307',	'c', /* capital C, cedilla */ 
    '\320',	'e', /* capital Eth, Icelandic */ 
    '\311',	'e', /* capital E, acute accent */ 
    '\312',	'e', /* capital E, circumflex accent */ 
    '\310',	'e', /* capital E, grave accent */ 
    '\313',	'e', /* capital E, dieresis or umlaut mark */ 
    '\315',	'i', /* capital I, acute accent */ 
    '\316',	'i', /* capital I, circumflex accent */ 
    '\314',	'i', /* capital I, grave accent */ 
    '\317',	'i', /* capital I, dieresis or umlaut mark */ 
    '\321',	'n', /* capital N, tilde */ 
    '\323',	'o', /* capital O, acute accent */ 
    '\324',	'o', /* capital O, circumflex accent */ 
    '\322',	'o', /* capital O, grave accent */ 
    '\330',	'o', /* capital O, slash */ 
    '\325',	'o', /* capital O, tilde */ 
    '\326',	'o', /* capital O, dieresis or umlaut mark */ 
    '\332',	'u', /* capital U, acute accent */ 
    '\333',	'u', /* capital U, circumflex accent */ 
    '\331',	'u', /* capital U, grave accent */ 
    '\334',	'u', /* capital U, dieresis or umlaut mark */ 
    '\335',	'y', /* capital Y, acute accent */ 
    '\341',	'a', /* small a, acute accent */ 
    '\342',	'a', /* small a, circumflex accent */ 
    '\346',	'a', /* small ae diphthong (ligature) */ 
    '\340',	'a', /* small a, grave accent */ 
    '\345',	'a', /* small a, ring */ 
    '\343',	'a', /* small a, tilde */ 
    '\344',	'a', /* small a, dieresis or umlaut mark */ 
    '\347',	'c', /* small c, cedilla */ 
    '\351',	'e', /* small e, acute accent */ 
    '\352',	'e', /* small e, circumflex accent */ 
    '\350',	'e', /* small e, grave accent */ 
    '\360',	'e', /* small eth, Icelandic */ 
    '\353',	'e', /* small e, dieresis or umlaut mark */ 
    '\355',	'i', /* small i, acute accent */ 
    '\356',	'i', /* small i, circumflex accent */ 
    '\354',	'i', /* small i, grave accent */ 
    '\357',	'i', /* small i, dieresis or umlaut mark */ 
    '\361',	'n', /* small n, tilde */ 
    '\363',	'o', /* small o, acute accent */ 
    '\364',	'o', /* small o, circumflex accent */ 
    '\362',	'o', /* small o, grave accent */ 
    '\370',	'o', /* small o, slash */ 
    '\365',	'o', /* small o, tilde */ 
    '\366',	'o', /* small o, dieresis or umlaut mark */ 
    '\337',	's', /* small sharp s, German (sz ligature) */ 
    '\372',	'u', /* small u, acute accent */ 
    '\373',	'u', /* small u, circumflex accent */ 
    '\371',	'u', /* small u, grave accent */ 
    '\374',	'u', /* small u, dieresis or umlaut mark */ 
    '\375',	'y', /* small y, acute accent */ 
    '\377',	'y' /* small y, dieresis or umlaut mark */ 
};

char ISO_Latin1_new[HTML_ENTITIES] = {
    '\306',	/* capital AE diphthong (ligature) */ 
    '\301',	/* capital A, acute accent */ 
    '\302',	/* capital A, circumflex accent */ 
    '\300',	/* capital A, grave accent */ 
    '\305',	/* capital A, ring */ 
    '\303',	/* capital A, tilde */ 
    '\304',	/* capital A, dieresis or umlaut mark */ 
    '\307',	/* capital C, cedilla */ 
    '\320',	/* capital Eth, Icelandic */ 
    '\311',	/* capital E, acute accent */ 
    '\312',	/* capital E, circumflex accent */ 
    '\310',	/* capital E, grave accent */ 
    '\313',	/* capital E, dieresis or umlaut mark */ 
    '\315',	/* capital I, acute accent */ 
    '\316',	/* capital I, circumflex accent */ 
    '\314',	/* capital I, grave accent */ 
    '\317',	/* capital I, dieresis or umlaut mark */ 
    '\321',	/* capital N, tilde */ 
    '\323',	/* capital O, acute accent */ 
    '\324',	/* capital O, circumflex accent */ 
    '\322',	/* capital O, grave accent */ 
    '\330',	/* capital O, slash */ 
    '\325',	/* capital O, tilde */ 
    '\326',	/* capital O, dieresis or umlaut mark */ 
    '\336',	/* capital THORN, Icelandic */ 
    '\332',	/* capital U, acute accent */ 
    '\333',	/* capital U, circumflex accent */ 
    '\331',	/* capital U, grave accent */ 
    '\334',	/* capital U, dieresis or umlaut mark */ 
    '\335',	/* capital Y, acute accent */ 
    '\341',	/* small a, acute accent */ 
    '\342',	/* small a, circumflex accent */ 
    '\346',	/* small ae diphthong (ligature) */ 
    '\340',	/* small a, grave accent */ 
    '\046',	/* ampersand */ 
    '\345',	/* small a, ring */ 
    '\343',	/* small a, tilde */ 
    '\344',	/* small a, dieresis or umlaut mark */ 
    '\347',	/* small c, cedilla */ 
    '\351',	/* small e, acute accent */ 
    '\352',	/* small e, circumflex accent */ 
    '\350',	/* small e, grave accent */ 
    '\360',	/* small eth, Icelandic */ 
    '\353',	/* small e, dieresis or umlaut mark */ 
    '\076',	/* greater than */ 
    '\355',	/* small i, acute accent */ 
    '\356',	/* small i, circumflex accent */ 
    '\354',	/* small i, grave accent */ 
    '\357',	/* small i, dieresis or umlaut mark */ 
    '\074',	/* less than */ 
    '\361',	/* small n, tilde */ 
    '\363',	/* small o, acute accent */ 
    '\364',	/* small o, circumflex accent */ 
    '\362',	/* small o, grave accent */ 
    '\370',	/* small o, slash */ 
    '\365',	/* small o, tilde */ 
    '\366',	/* small o, dieresis or umlaut mark */ 
    '\042', /* double quote sign - June 94 */
    '\337',	/* small sharp s, German (sz ligature) */ 
    '\376',	/* small thorn, Icelandic */ 
    '\372',	/* small u, acute accent */ 
    '\373',	/* small u, circumflex accent */ 
    '\371',	/* small u, grave accent */ 
    '\374',	/* small u, dieresis or umlaut mark */ 
    '\375',	/* small y, acute accent */ 
    '\377',	/* small y, dieresis or umlaut mark */ 
};
