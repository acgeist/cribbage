/*
 * Author: Andrew Geist
 * Last Update: Thu 02 Nov 2017 12:34:50 PM EDT
 * Ultimate goal - split this into client and server and allow two machines to 
 * play each other.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bicycle.h"

#define CARDS_IN_CRIB	4 
#define CARDS_IN_HAND	6
#define MAX_NAME_LEN	20
#define OK				0
#define NO_INPUT		1
#define TOO_LONG		2
#define TRUE			1
#define FALSE			0

struct hand{
	struct card cardArray[CARDS_IN_HAND];
};

struct player{
	char name[MAX_NAME_LEN];
	int score;
	int isDealer;
	struct hand hand;
};

static int getLine (char *prmpt, char *buff, size_t sz);
void getPlayerNames(char *p1name, char *p2name);
void cutForDeal(struct player *p1, struct player *p2, struct deck *myDeck,
		struct player *dealer, struct player *notDealer);
void deal(struct deck *myDeck, struct player *dealer, struct player *notDealer);
void printhands(struct player *p1, struct player *p2);
void analyzehand(struct hand *h);
void sorthand(struct player *p1);

int main(void){
	while(1){
		struct deck myDeck = newdeck();
		struct player p1, p2;
		struct player *dealer = &p1;
		struct player *notDealer = &p2;
		p1.score = 0;
		p2.score = 0;
		// Initialize/seed the randomizer.  Comment this line out to get dealt
		// the same hands every time.
		srand((unsigned int) time(NULL));

		printf("-----------------------------------------------------------\n");
		printf("Welcome to Fore's text-based cribbage game.\n");
		shuffle(&myDeck);
		getPlayerNames(p1.name, p2.name);
		printf("Now it's time to cut for the deal.  Low card wins.\n");
		cutForDeal(&p1, &p2, &myDeck, dealer, notDealer);
		shuffle(&myDeck);
		deal(&myDeck, dealer, notDealer);
		sorthand(&p1);
		sorthand(&p2);
		printhands(&p1, &p2);
		analyzehand(&(p2.hand));
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
	printf ("Welcome, %s!\n", p1name);
	rc = getLine ("Enter name for Player 2: ", p2name, sizeof(p1name));
	while (rc != OK)
		rc = getLine ("Enter name for Player 2: ", p2name, sizeof(p1name));
	printf ("Welcome, %s!\n", p2name);
}

void cutForDeal(struct player *p1, struct player *p2, struct deck *myDeck,
		struct player *dealer, struct player *notDealer){
	struct card p1cut, p2cut;
	p1cut = (*myDeck).cardArray[randomcard()];
	p2cut = (*myDeck).cardArray[randomcard()];
	while (aresamecard(&p1cut, &p2cut))
		p2cut = (*myDeck).cardArray[randomcard()];
	while (p1cut.val == p2cut.val){
		printf("Tied, cut again.\n");
		p1cut = (*myDeck).cardArray[randomcard()];
		p2cut = (*myDeck).cardArray[randomcard()];
		while (aresamecard(&p1cut, &p2cut))
			p2cut = (*myDeck).cardArray[randomcard()];
	}
	if (p1cut.val < p2cut.val){
		p1->isDealer = TRUE;
		p2->isDealer = FALSE;
		dealer = p1;
		notDealer = p2;
	} else {
		p1->isDealer = FALSE;
		p2->isDealer = TRUE;
		dealer = p2;
		notDealer = p1;
	}
	// With the -Werror option set, gcc gives the following error:
	// parameter 'notDealer' set but not used [-Werror=unused-but-set
	// -parameter].  TODO: fix so I don't have to include both
	// players' names in this printf statement.
	printf("%s: %s\n", p1->name, p1cut.shortName);
	printf("%s: %s\n", p2->name, p2cut.shortName);
	printf("%s wins and will deal to %s first.\n", (*dealer).name,
			(*notDealer).name);
}

void deal(struct deck *myDeck, struct player *dealer, struct player *notDealer){
		int i;
		for (i = 0; i < CARDS_IN_HAND * 2; i++){
			if (i % 2 == 0)
				(*notDealer).hand.cardArray[i / 2] = (*myDeck).cardArray[i];
			else
				(*dealer).hand.cardArray[(i - 1) / 2] = (*myDeck).cardArray[i];
		}
}

void printhands(struct player *p1, struct player *p2){
	printf("%s's hand: ", p1->name);
	int i;
	for (i = 0; i < CARDS_IN_HAND; i++){
		printf("%s ", p1->hand.cardArray[i].shortName);
	}
	printf("\n");
	printf("%s's hand: ", p2->name);
	for (i = 0; i < CARDS_IN_HAND; i++){
		printf("%s ", p2->hand.cardArray[i].shortName);
	}
	printf("\n");
}

void analyzehand(struct hand *h){
	printf("Analyzing: %s %s %s %s %s %s\n",
			(*h).cardArray[0].shortName,
			(*h).cardArray[1].shortName,
			(*h).cardArray[2].shortName,
			(*h).cardArray[3].shortName,
			(*h).cardArray[4].shortName,
			(*h).cardArray[5].shortName);
}

/* Bubble sort implemented per the pseudocode located at:
 * <https://en.wikipedia.org/wiki/Bubble_sort>
 */
void sorthand(struct player *p1){
	int swapped = TRUE;
	while (swapped){
		int i;
		struct card temp;
		swapped = FALSE;
		for (i = 1; i < CARDS_IN_HAND; i++){
		   /* If these two are out of order */
			if ((*p1).hand.cardArray[i-1].val > (*p1).hand.cardArray[i].val){
				temp = (*p1).hand.cardArray[i-1];
				(*p1).hand.cardArray[i-1] = (*p1).hand.cardArray[i];
				(*p1).hand.cardArray[i] = temp;
				swapped = TRUE;
			}
		}
	}
}
