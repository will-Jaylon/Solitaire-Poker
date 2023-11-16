/*
 SolitairePoker.c
 
 Notes: The 52 cards of a deck are represented as integers: 0 .. 51
 0..12 are clubs Ace, 2, ..., King
 13..25 are diamonds Ace, 2, ..., King
 26..38 are hearts Ace, 2, ..., King
 39..51 are spades Ace, 2, ..., King

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//do not remove
#include "studentinclude.code" //Include custom header file (it contains necessary functions)
//A version of the file:include.code is available from the assignment page
//as studentinclude.code which you should save locally as include.code
//include.code contains implementations for seed, instructions, and private_nextcard(int)
//used by shuffle and next card.
//The version used during testing is slightly different but will not affect your efforts.
//For testing you may modify studentinclude.code -- it will not be part of your submission.


// Function to shuffle the deck
//you should call this before each deal (including the first)
void shuffle() {
    private_nextcard(1); // Call a custom function to shuffle
}

// Function to get the next card to be dealt
//call this to deal a card. Do not call rand().
int nextcard() {
    return private_nextcard(0); // Call a custom function to get the next card
}

// Enumeration for different poker hands
enum hands { UNKNOWN, HIGHCARD, PAIR, TWOPAIR, TRIPS, STRAIGHT,
    FLUSH, FULLHOUSE, QUADS, STRAIGHTFLUSH, ROYALFLUSH };
char * handNames[] ={ "UNKNOWN", "HIGHCARD", "PAIR", "TWOPAIR", "TRIPS", "STRAIGHT",
    "FLUSH", "FULLHOUSE", "QUADS", "STRAIGHTFLUSH", "ROYALFLUSH" }; // Names of each hand

// Enumeration for card suits
enum suits {CLUB, DIAMOND, HEART, SPADE};
char * suitNames[] ={ "CLUB", "DIAMOND", "HEART", "SPADE"}; // Names of card suits

// Enumeration for card ranks
enum ranks {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
char * rankNames[] ={ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN",
    "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"}; // Names of card ranks

//FUNCTION PROTOTYPES: YOU MUST IMPLEMENT THESE FUNCTIONS

// Function to get the rank of a card
enum ranks getrank(int card);

// Function to get the suit of a card
enum suits getsuit(int card);

// Function to evaluate the poker hand
enum hands eval(int []);

// Function to check for a royal flush
int royalflush(int []);

// Function to check for a straight flush
int straightflush(int []);

// Function to check for four of a kind
int fourofkind(int []);

// Function to check for a full house
int fullhouse(int []);

// Function to check for a flush
int flush(int []);

// Function to check for a straight
int straight(int []);

// Function to check for three of a kind
int threekind(int []);

// Function to check for two pairs
int twopair(int []);

// Function to check for a pair
int pair(int []);


int main(int argc, char ** argv) {
    //do not remove
    seed(argc, argv); // Seed the random number generator
    instructions(); // Display game instructions
    int totalScore = 0;
    int handScores[10];
    enum hands handTypes[10];
    int handCards[10][5];
    int handScore = 0;
    

    for (int handNum = 1; handNum <= 10; handNum++) {
        shuffle();
        int hand[5];
        
        for (int i = 0; i < 5; i++) {
            hand[i] = nextcard();
        }
         printf("Dealt Hand: \n");
        for (int i = 0; i < 5; i++) {
            int suit = getsuit(hand[i]);
            int rank = getrank(hand[i]);
            printf("%s-%s\t", suitNames[suit], rankNames[rank]);
        }

        int cardsToReplace[3];
        int numCardsToReplace = 0;

        printf("\nSelect up to three cards to replace[1-5] and press enter: \n");
        while (numCardsToReplace < 3) {
            int cardNumber;
            scanf("%d", &cardNumber);
            if (cardNumber == 0) {
                break;
            }
            if (cardNumber >= 1 && cardNumber <= 5) {
                cardsToReplace[numCardsToReplace] = cardNumber;
                numCardsToReplace++;
            } else {
                printf("Invalid card number.\n");
            }
        }
        for (int i = 0; i < numCardsToReplace; i++) {
            hand[cardsToReplace[i] - 1] = nextcard(); 
        }
        enum hands handType = eval(hand);
        

        switch (handType) {
            case ROYALFLUSH:
            handScore = 50;
            break;

            case STRAIGHTFLUSH:
            handScore = 45;
            break;

            case FULLHOUSE:
            handScore = 32;
            break;

            case FLUSH:
            handScore = 26;
            break;

            case STRAIGHT:
            handScore = 17;
            break;

            case TRIPS:
            handScore = 11;
            break;

            case TWOPAIR:
            handScore = 7;
            break;

            case PAIR:
            handScore = 3;
            break;

            default:
            handScore = 1;
            break;
        }

        printf("\nHand %2d: Score: %2d %s\n", handNum, handScore, handNames[handType]);
        handScores[handNum - 1] = handScore;
        handTypes[handNum - 1] = handType;
        for (int i = 0; i < 5; i++) {
            handCards[handNum - 1][i] = hand[i];
        }

        
        totalScore += handScore;
    }

    printf("********************************************************************************\n");
    printf("***                         S C O R E S H E E T                              ***\n");
    printf("********************************************************************************\n");
    for (int handNum = 0; handNum < 10; handNum++) {
        printf("Hand %2d: Score %2d %s [", handNum + 1, handScores[handNum], handNames[handTypes[handNum]]);
        for (int i = 0; i < 5; i++) {
            int card = handCards[handNum][i];
            enum suits cardSuit = getsuit(card);
            enum ranks cardRank = getrank(card);
            printf("%2d %s-%s", card, suitNames[cardSuit], rankNames[cardRank]);
            if (i < 4) {
                printf("  ");
            }
        }
        printf("]\n");
    }

    printf("==============================================================================\n");
    printf("Total Points: %3d\n", totalScore);
    printf("==============================================================================\n");
    //TODO:
        //WRITE CODE TO PLAY 10 HANDS OF POKER
            //DEAL 5 CARDS
            //SHOW DEALT HAND
            //DRAW UP TO 3 CARDS
            //SHOW FINAL HAND
            //EVAL REPPORT AND SAVE INFO FOR LATER
        //GENERATE SCORESHEET USING INFO
    
    return 0;
}

//TODO:
//THE FOLLOWING STUBS NEED TO BE IMPLEMENTED CORRECTLY

// Function to get the suit of a card
enum suits getsuit(int card) {
    return (enum suits)(card / 13);
}

// Function to get the rank of a card
enum ranks getrank(int card){
    return (enum ranks)(card % 13);
}

// Function to evaluate the poker hand
enum hands eval(int hand[]) {
    if (royalflush(hand)) return ROYALFLUSH;
    if (straightflush(hand)) return STRAIGHTFLUSH;
    if (fourofkind(hand)) return QUADS;
    if (fullhouse(hand)) return FULLHOUSE;
    if (flush(hand)) return FLUSH;
    if (straight(hand)) return STRAIGHT;
    if (threekind(hand)) return TRIPS;
    if (twopair(hand)) return TWOPAIR;
    if (pair(hand)) return PAIR;
    return HIGHCARD;
}

// Function to check for a royal flush
int royalflush(int hand[]) {
    int rankCounts[13] = {0};
    int requiredCards[13] = {0};

    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCounts[rank]++;
    }
    requiredCards[ACE] = 1;
    requiredCards[KING] = 1;
    requiredCards[QUEEN] = 1;
    requiredCards[JACK] = 1;
    requiredCards[TEN] = 1;

    for (int i = 0; i < 13; i++) {
        if (requiredCards[i] && rankCounts[i] != 1) {
            return 0;
        }
        if (!requiredCards[i] && rankCounts[i] != 0) {
            return 0;
        }
    }
    if (getsuit(hand[0]) == getsuit(hand[1]) && getsuit(hand[0]) == getsuit(hand[2]) &&
        getsuit(hand[0]) == getsuit(hand[3]) && getsuit(hand[0]) == getsuit(hand[4])) {
        return 1;
    }
    return 0;
}

// Function to check for a straight flush
int straightflush(int hand[]) {
    int rankCounts[13] = {0};
    int suitCounts[4] = {0};

    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        int suit = getsuit(hand[i]);
        rankCounts[rank]++;
        suitCounts[suit]++;
    }

    int consecutiveRanks = 0;
    for (int i = 0; i < 13; i++) {
        if (rankCounts[i] > 0) {
            consecutiveRanks++;
            if (consecutiveRanks == 5) {
                break;
            }
        } else {
            consecutiveRanks = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (suitCounts[i] == 5) {
            if (consecutiveRanks == 5) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

// Function to check for a flush
int flush(int hand[]) {
    int suitCounts[4] = {0};

    for (int i = 0; i < 5; i++) {
        int suit = getsuit(hand[i]);
        suitCounts[suit]++;
    }
    for (int i = 0; i < 4; i++) {
        if (suitCounts[i] == 5) {
            return 1;
        }
    }
    return 0;
}

// Function to check for a straight
int straight(int hand[]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (getrank(hand[j]) > getrank(hand[j + 1])) {
                int temp = hand[j];
                hand[j] = hand[j + 1];
                hand[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (getrank(hand[i + 1]) != getrank(hand[i] + 1)) {
            return 0;
        }
    }
    return 1;
}

// Function to check for four of a kind
int fourofkind(int hand[]) {
    int counts[13] = {0};
    for (int i = 0; i < 5; i++) {
        counts[getrank(hand[i])]++;
    }
    for (int i = 0; i < 13; i++) {
        if (counts[i] == 4) {
            return 1;
        }
    }
    return 0;
}

// Function to check for a full house
int fullhouse(int hand[]) {
    int counts[13] = {0};
    for (int i = 0; i < 5; i++) {
        counts[getrank(hand[i])]++;
    }
    int hasThree = 0; 
    int hasTwo = 0;

    for (int i = 0; i < 13; i++) {
        if (counts[i] == 3) {
            hasThree = 1;
        } else if (counts[i] == 2) {
            hasTwo = 1;
        }
    }
    return (hasThree && hasTwo);
}

// Function to check for three of a kind
int threekind(int hand[]) {
    int counts[13] = {0};
    for (int i = 0; i < 5; i++) {
        counts[getrank(hand[i])]++;
    }
    for (int i = 0; i < 13; i++) {
        if (counts[i] == 3) {
            return 1;
        }
    }
    return 0;
}

// Function to check for two pairs
int twopair(int hand[]) {
    int counts[13] = {0};
    int pairs = 0;

    for (int i = 0; i < 5; i++) {
        counts[getrank(hand[i])]++;
    }
    for (int i = 0; i < 13; i++) {
        if (counts[i] == 2) {
            pairs++;
        }
    }

    return (pairs >= 2);
}

// Function to check for a pair
int pair(int hand[]) {
    int counts[13] = {0};
    
    for (int i = 0; i < 5; i++) {
        counts[getrank(hand[i])]++;
    }
    for (int i = 0; i < 13; i++) {
        if (counts[i] == 2) {
            return 1;
        }
    }
    return 0;
}
