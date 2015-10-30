/* Structure containing info on a URL.  */
struct urlinfo
{
    char *url;                    /* Unchanged URL */
    char *host;                   /* Extracted hostname */
    int protocol;
    unsigned short port;
    char *user, *passwd;          /* Username and password */
};

#define URL_HTTP	1<<0L
#define URL_FTP		1<<1L
#define URL_UNKNOWN	1<<2L
