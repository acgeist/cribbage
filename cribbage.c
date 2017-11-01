/*
 * Author: Andrew Geist
 * Last Update: Wed 01 Nov 2017 09:04:21 AM EDT
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bicycle.h"

//#define CARDS_IN_DECK	52
#define CARDS_IN_CRIB	4 
#define CARDS_IN_HAND	6
#define MAX_NAME_LEN	20
#define OK				0
#define NO_INPUT		1
#define TOO_LONG		2

static int getLine (char *prmpt, char *buff, size_t sz);
void getPlayerNames(char *p1name, char *p2name);
void cutForDeal(struct card *p1cut, struct card *p2cut, 
		char *p1name, char *p2name, struct deck *myDeck);

int main(void){
	while(1){
	struct deck myDeck = newdeck();
	srand((unsigned int) time(NULL));
	printf("---------------------------------------------------------------\n");
	printf("Welcome to Fore's text-based cribbage game.\n");
	shuffle(&myDeck);
	char p1name[MAX_NAME_LEN], p2name[MAX_NAME_LEN];
	getPlayerNames(p1name, p2name);
	printf("Now it's time to cut for the deal.  Low card wins.\n");
	struct card p1cut, p2cut;
	cutForDeal(&p1cut, &p2cut, p1name, p2name, &myDeck);
	while (p1cut.val == p2cut.val){
		printf("Tied, cut again.\n");
		cutForDeal(&p1cut, &p2cut, p1name, p2name, &myDeck);
	}
	printf("%s wins and will deal first.\n", p1cut.val < p2cut.val ?
			p1name : p2name);
	shuffle(&myDeck);
	}	
	return 0;
}

/*
 * Stolen from <https://stackoverflow.com/a/4023921>
 * Author: paxdiablo
 */
static int getLine (char *prmpt, char *buff, size_t sz){
	int ch, extra;

	// Get line with buffer overrun protection.
	if (prmpt != NULL){
		printf("%s", prmpt);
		fflush (stdout);
	}
	if (fgets (buff, sz, stdin) == NULL)
		return NO_INPUT;

	// If it was too long, there'll be no newline.  In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff)-1] != '\n'){
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;
		return (extra == 1) ? TOO_LONG: OK;
	}

	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff) - 1] = '\0';
	return OK;
}

void getPlayerNames(char *p1name, char *p2name){
	
	int rc = NO_INPUT;
	rc = getLine ("Enter name for Player 1: ", p1name, sizeof(p1name));
	while (rc != OK)
		rc = getLine ("Enter name for Player 1: ", p1name, sizeof(p1name));
	printf ("Welcome,%s!\n", p1name);
	rc = getLine ("Enter name for Player 2: ", p2name, sizeof(p1name));
	while (rc != OK)
		rc = getLine ("Enter name for Player 2: ", p2name, sizeof(p1name));
	printf ("Welcome,%s!\n", p2name);
}

void cutForDeal(struct card *p1cut, struct card *p2cut, 
		char *p1name, char *p2name, struct deck *myDeck){
	*p1cut = (*myDeck).cardArray[randomcard()];
	*p2cut = (*myDeck).cardArray[randomcard()];
	while ((*p1cut).name == (*p2cut).name && (*p1cut).suit == (*p2cut).suit)
		*p2cut = (*myDeck).cardArray[randomcard()];
	printf("%s cut the %s of %s.\n", p1name, (*p1cut).fullName, (*p1cut).fullSuit);
	printf("%s cut the %s of %s.\n", p2name, (*p2cut).fullName, (*p2cut).fullSuit);
}
