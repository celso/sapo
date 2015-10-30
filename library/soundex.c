#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include "soundex.h"

/* Simple soundex algorithm as described by Knuth in TAOCP, vol 3 */
char *soundex(char *arg)
{
	char l, u;
	char somestring[1024];
	int i, j, n;
	static char out[10];

	/* pad with '0' and terminate with 0 ;-) */
	char soundex[5] =
	{'0', '0', '0', '0', 0};

	static char soundex_table[26] = {0, '1', '2', '3', 0, '1', '2', 0, 0, '2', '2', '4', '5', '5', 0, '1', '2', '6', '2', '3', 0,	'1', 0,	'2', 0,	'2'};

	if (strlen(arg)==0) {
		return(0);
	}

	if(strlen(arg)<1024) {
          strncpy(somestring,arg,strlen(arg));
	  n = strlen(arg);
          }
	  else 
          {
          strncpy(somestring,arg,1024);
          n = 1024;
          }

	/* convert chars to upper case and strip non-letter chars */
	j = 0;
	for (i = 0; i < n; i++) {
		u = toupper(somestring[i]);
		if ((u > 64) && (u < 91)) {
			somestring[j] = u;
			j++;
		}
	}

	/* null-terminate string */
	somestring[j] = 0;

	n = strlen(somestring);

	/* prefix soundex string with first valid char */
	soundex[0] = somestring[0];

	/* remember first char */
	l = soundex_table[((somestring[0]) - 65)];

	j = 1;

	/* build soundex string */
	for (i = 1; i < n && j < 4; i++) {
		u = soundex_table[((somestring[i]) - 65)];

		if (u != l) {
			if (u != 0) {
				soundex[(int) j++] = u;
			}
			l = u;
		}
	}
        strncpy(out,soundex,5);
        return(out);
}
