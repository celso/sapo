#include <stdio.h>
#include "cgic.h"

void Name();
void Address();
void Hungry();
void Temperature();
void Frogs();
void Color();
void Flavors();
void NonExButtons();
void RadioButtons();

int cgiMain() {
#if DEBUG
	/* Load a saved CGI scenario if we're debugging */
	cgiReadEnvironment("/home/boutell/public_html/capcgi.dat");
#endif
	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML><HEAD>\n");
	fprintf(cgiOut, "<TITLE>cgic test</TITLE></HEAD>\n");
	fprintf(cgiOut, "<BODY><H1>cgic test</H1>\n");
	Name();
	Address();
	Hungry();
	Temperature();
	Frogs();
	Color();
	Flavors();
	NonExButtons();
	RadioButtons();
	fprintf(cgiOut, "</BODY></HTML>\n");
	return 0;
}

void Name() {
	char name[81];
	int result = cgiFormStringNoNewlines("name", name, 81);
	switch (result) {
		case cgiFormSuccess:
		fprintf(cgiOut, "Name fetched, result code: cgiFormSuccess<br>\n");
		break;
		case cgiFormTruncated:
		fprintf(cgiOut, "Name fetched, result code: cgiFormTruncated<br>\n");
		break;
		case cgiFormEmpty:
		fprintf(cgiOut, "Name fetched, result code: cgiFormEmpty<br>\n");
		break;
		case cgiFormNotFound:
		fprintf(cgiOut, "Name fetched, result code: cgiFormNotFound<br>\n");
		break;
		case cgiFormMemory:
		fprintf(cgiOut, "Name fetched, result code: cgiFormMemory<br>\n");
		break;
		default:
		fprintf(cgiOut, "Name fetched, unexpected result code: %s\n", result);
		break;
	}	
	fprintf(cgiOut, "Name: %s<BR>\n", name);
}
	
void Address() {
	char address[241];
	cgiFormString("address", address, 241);
	fprintf(cgiOut, "Address: <PRE>\n%s</PRE>\n", address);
}

void Hungry() {
	if (cgiFormCheckboxSingle("hungry") == cgiFormSuccess) {
		fprintf(cgiOut, "I'm Hungry!<BR>\n");
	} else {
		fprintf(cgiOut, "I'm Not Hungry!<BR>\n");
	}
}
	
void Temperature() {
	double temperature;
	cgiFormDoubleBounded("temperature", &temperature, 80.0, 120.0, 98.6);
	fprintf(cgiOut, "My temperature is %f.<BR>\n", temperature);
}
	
void Frogs() {
	int frogsEaten;
	cgiFormInteger("frogs", &frogsEaten, 0);
	fprintf(cgiOut, "I have eaten %d frogs.<BR>\n", frogsEaten);
}

char *colors[] = {
	"Red",
	"Green",
	"Blue"
};

void Color() {
	int colorChoice;
	cgiFormSelectSingle("colors", colors, 3, &colorChoice, 0);
	fprintf(cgiOut, "I am: %s<BR>\n", colors[colorChoice]);
}	 

char *flavors[] = {
	"pistachio",
	"walnut",
	"creme"
};

void Flavors() {
	int flavorChoices[3];
	int i;
	int result;	
	int invalid;
	result = cgiFormSelectMultiple("flavors", flavors, 3, 
		flavorChoices, &invalid);
	if (result == cgiFormNotFound) {
		fprintf(cgiOut, "I hate ice cream.<p>\n");
	} else {	
		fprintf(cgiOut, "My favorite ice cream flavors are:\n");
		fprintf(cgiOut, "<ul>\n");
		for (i=0; (i < 3); i++) {
			if (flavorChoices[i]) {
				fprintf(cgiOut, "<li>%s\n", flavors[i]);
			}
		}
		fprintf(cgiOut, "</ul>\n");
	}
}

char *ages[] = {
	"1",
	"2",
	"3",
	"4"
};

void RadioButtons() {
	int ageChoice;
	char ageText[10];
	/* Approach #1: check for one of several valid responses. 
		Good if there are a short list of possible button values and
		you wish to enumerate them. */
	cgiFormRadio("age", ages, 4, &ageChoice, 0);

	fprintf(cgiOut, "Age of Truck: %s (method #1)<BR>\n", 
		ages[ageChoice]);

	/* Approach #2: just get the string. Good
		if the information is not critical or if you wish
		to verify it in some other way. Note that if
		the information is numeric, cgiFormInteger,
		cgiFormDouble, and related functions may be
		used instead of cgiFormString. */	
	cgiFormString("age", ageText, 10);

	fprintf(cgiOut, "Age of Truck: %s (method #2)<BR>\n", ageText);
}

char *votes[] = {
	"A",
	"B",
	"C",
	"D"
};

void NonExButtons() {
	int voteChoices[4];
	int i;
	int result;	
	int invalid;

	char **responses;

	/* Method #1: check for valid votes. This is a good idea,
		since votes for nonexistent candidates should probably
		be discounted... */
	fprintf(cgiOut, "Votes (method 1):<BR>\n");
	result = cgiFormCheckboxMultiple("vote", votes, 4, 
		voteChoices, &invalid);
	if (result == cgiFormNotFound) {
		fprintf(cgiOut, "I hate them all!<p>\n");
	} else {	
		fprintf(cgiOut, "My preferred candidates are:\n");
		fprintf(cgiOut, "<ul>\n");
		for (i=0; (i < 4); i++) {
			if (voteChoices[i]) {
				fprintf(cgiOut, "<li>%s\n", votes[i]);
			}
		}
		fprintf(cgiOut, "</ul>\n");
	}

	/* Method #2: get all the names voted for and trust them.
		This is good if the form will change more often
		than the code and invented responses are not a danger
		or can be checked in some other way. */
	fprintf(cgiOut, "Votes (method 2):<BR>\n");
	result = cgiFormStringMultiple("vote", &responses);
	if (result == cgiFormNotFound) {	
		fprintf(cgiOut, "I hate them all!<p>\n");
	} else {
		int i = 0;
		fprintf(cgiOut, "My preferred candidates are:\n");
		fprintf(cgiOut, "<ul>\n");
		while (responses[i]) {
			fprintf(cgiOut, "<li>%s\n", responses[i]);
			i++;
		}
		fprintf(cgiOut, "</ul>\n");
	}
	/* We must be sure to free the string array or a memory
		leak will occur. Simply calling free() would free
		the array but not the individual strings. The
		function cgiStringArrayFree() does the job completely. */	
	cgiStringArrayFree(responses);
}

