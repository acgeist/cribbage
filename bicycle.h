#define CARDS_IN_DECK 52
//TODO: typdef?
struct card {
	int name, suit, val;
	char shortName[3];
	char fullName[10];
	char fullSuit[10];
};
struct deck {
	struct card cardArray[CARDS_IN_DECK];
};
struct card newcard(int x, int y);
struct deck newdeck();
int nameToVal(int name);
void printdeck(struct deck *d);
void shuffle(struct deck *d);
int randomcard();
int aresamecard(struct card *c1, struct card *c2);
