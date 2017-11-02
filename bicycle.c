/*
 * Author: Andrew Geist
 * Last Update: Wed 01 Nov 2017 03:30:20 PM EDT
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bicycle.h"

struct card newcard(int x, int y){
	struct card temp;
	temp.name = x;
	temp.suit = y;
	switch(x){
		case 'A':
			strcpy(temp.fullName, "ace");
			break;
		case '2':
			strcpy(temp.fullName, "two");
			break;
		case '3':
			strcpy(temp.fullName, "three");
			break;
		case '4':
			strcpy(temp.fullName, "four");
			break;
		case '5':
			strcpy(temp.fullName, "five");
			break;
		case '6':
			strcpy(temp.fullName, "six");
			break;
		case '7':
			strcpy(temp.fullName, "seven");
			break;
		case '8':
			strcpy(temp.fullName, "eight");
			break;
		case '9':
			strcpy(temp.fullName, "nine");
			break;
		case 'T':
			strcpy(temp.fullName, "ten");
			break;
		case 'J':
			strcpy(temp.fullName, "jack");
			break;
		case 'Q':
			strcpy(temp.fullName, "queen");
			break;
		case 'K':
			strcpy(temp.fullName, "king");
			break;
		default:
			strcpy(temp.fullName, "error");
	}
	switch(y){
		case 'S':
			strcpy(temp.fullSuit, "spades");
			break;
		case 'D':
			strcpy(temp.fullSuit, "diamonds");
			break;
		case 'C':
			strcpy(temp.fullSuit, "clubs");
			break;
		case 'H':
			strcpy(temp.fullSuit, "hearts");
			break;
		default:
			strcpy(temp.fullSuit, "error");
	}
	temp.shortName[0] = x;
	temp.shortName[1] = y;	
	temp.shortName[2] = '\0';
	return temp;
}

struct deck newdeck(){
	struct deck temp;
	temp.cardArray[0] = newcard('A', 'S');
	temp.cardArray[1] = newcard('2', 'S');
	temp.cardArray[2] = newcard('3', 'S');
	temp.cardArray[3] = newcard('4', 'S');
	temp.cardArray[4] = newcard('5', 'S');
	temp.cardArray[5] = newcard('6', 'S');
	temp.cardArray[6] = newcard('7', 'S');
	temp.cardArray[7] = newcard('8', 'S');
	temp.cardArray[8] = newcard('9', 'S');
	temp.cardArray[9] = newcard('T', 'S');
	temp.cardArray[10] = newcard('J', 'S');
	temp.cardArray[11] = newcard('Q', 'S');
	temp.cardArray[12] = newcard('K', 'S');
	temp.cardArray[13] = newcard('A', 'D');
	temp.cardArray[14] = newcard('2', 'D');
	temp.cardArray[15] = newcard('3', 'D');
	temp.cardArray[16] = newcard('4', 'D');
	temp.cardArray[17] = newcard('5', 'D');
	temp.cardArray[18] = newcard('6', 'D');
	temp.cardArray[19] = newcard('7', 'D');
	temp.cardArray[20] = newcard('8', 'D');
	temp.cardArray[21] = newcard('9', 'D');
	temp.cardArray[22] = newcard('T', 'D');
	temp.cardArray[23] = newcard('J', 'D');
	temp.cardArray[24] = newcard('Q', 'D');
	temp.cardArray[25] = newcard('K', 'D');
	temp.cardArray[26] = newcard('A', 'C');
	temp.cardArray[27] = newcard('2', 'C');
	temp.cardArray[28] = newcard('3', 'C');
	temp.cardArray[29] = newcard('4', 'C');
	temp.cardArray[30] = newcard('5', 'C');
	temp.cardArray[31] = newcard('6', 'C');
	temp.cardArray[32] = newcard('7', 'C');
	temp.cardArray[33] = newcard('8', 'C');
	temp.cardArray[34] = newcard('9', 'C');
	temp.cardArray[35] = newcard('T', 'C');
	temp.cardArray[36] = newcard('J', 'C');
	temp.cardArray[37] = newcard('Q', 'C');
	temp.cardArray[38] = newcard('K', 'C');
	temp.cardArray[39] = newcard('A', 'H');
	temp.cardArray[40] = newcard('2', 'H');
	temp.cardArray[41] = newcard('3', 'H');
	temp.cardArray[42] = newcard('4', 'H');
	temp.cardArray[43] = newcard('5', 'H');
	temp.cardArray[44] = newcard('6', 'H');
	temp.cardArray[45] = newcard('7', 'H');
	temp.cardArray[46] = newcard('8', 'H');
	temp.cardArray[47] = newcard('9', 'H');
	temp.cardArray[48] = newcard('T', 'H');
	temp.cardArray[49] = newcard('J', 'H');
	temp.cardArray[50] = newcard('Q', 'H');
	temp.cardArray[51] = newcard('K', 'H');
	int i;
	for (i = 0; i < CARDS_IN_DECK; i++)
		temp.cardArray[i].val = nameToVal(temp.cardArray[i].name);	
	return temp;
}

int nameToVal(int name){
	switch(name){
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return name - 48;
		case 'A':
		case 'a':
			return 1;
		case 'T':
		case 't':
		case 'J':
		case 'j':
		case 'Q':
		case 'q':
		case 'K':
		case 'k':
			return 10;
		default:
			return -1;
	}
}

void printdeck(struct deck *d){
	int i;
	for (i = 0; i < CARDS_IN_DECK; i++){
		printf("%c%c ", (*d).cardArray[i].name,
				(*d).cardArray[i].suit);
		if ((i + 1) % 13 == 0) printf("\n");
	}
}

/*
 * Perform a Fisher-Yates shuffle on the deck.
 * <https://en.wikipedia.org/wiki/Fisher-Yates_shuffle>
 */
void shuffle(struct deck *d){
	int i, j;
	struct card temp;
	for (i = CARDS_IN_DECK - 1; i >= 1; i--){
		j = randomcard(i + 1);
		temp = (*d).cardArray[j];
		(*d).cardArray[j] = (*d).cardArray[i];
		(*d).cardArray[i] = temp;
	}
}

/*
 * Adapted from <https://stackoverflow.com/a/822361>
 * Original Author: Laurence Gonsalves
 * Returns an integer between 0 and CARDS_IN_DECK - 1 (inclusive).
 * Uses rand(), and so is affected by/affects the same seed.
 * Assumes srand() has been initialized!
 * TODO: Figure out if there's a way to tell if srand has been initialized.
 */
int randomcard(){
	if ((CARDS_IN_DECK - 1) == RAND_MAX)
		return rand();
	else {
		// Chop off all values that would cause skew...
		long end = RAND_MAX / CARDS_IN_DECK;
		assert (end > 0L);
		end *= CARDS_IN_DECK;

		// ... and ignore results from rand() that fall above that limit.
		// (Worst case the loop condition should succeed 50% of the time,
		// so we can expect to bail out of this loop pretty quickly.)
		int r;
		while ((r = rand()) >= end);

		return r % CARDS_IN_DECK;
	}
}

int aresamecard(struct card *c1, struct card *c2){
	return c1->name == c2->name && c1->suit == c2->suit ?
		1 : 0;
}
