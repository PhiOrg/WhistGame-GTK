/**
 * @file deck.c
 * @brief In this file are defined functions used for Deck-related and 
 *        Card-related operations, these functions are declared in the header
 *        file deck.h.
 */

#include "deck.h"
#include "errors.h"

#include <stdlib.h>
#include <time.h>

/**
 * Constants for game values
 */
const int VALUES[] = {3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, -1};

struct Card *deck_createCard(enum Suit suit, int value)
{
    int check = 0;
    for (int i = 0; VALUES[i] != -1; i++)
        if (VALUES[i] == value)
            check++;
    if (check != 1)
        return NULL;

    for (int i = 0; i < SuitEnd; i++)
        if (suit == i)
            check++;
    if (check != 2)
        return NULL;

    struct Card *card = malloc(sizeof(struct Card));
    if (card == NULL)
        return NULL;

    card->suit  = suit;
    card->value = value;

    return card;
}

int deck_deleteCard(struct Card** card)
{
    if (card == NULL)
        return POINTER_NULL;
    if (*card == NULL)
        return CARD_NULL;

    free(*card);
    *card = NULL;

    return FUNCTION_NO_ERROR;
}

struct Deck *deck_createDeck(int playersNumber)
{
    if (playersNumber > MAX_GAME_PLAYERS || playersNumber < MIN_GAME_PLAYERS)
        return NULL;

    struct Deck *deck = malloc(sizeof(struct Deck));
    if (deck == NULL)
        return NULL;

    int k = 0;
    for (int i = 0 + (MAX_GAME_PLAYERS - playersNumber) * 2;
         VALUES[i] != -1; i++)
    for (int j = 0; j != SuitEnd; j++) {
        deck->cards[k++] = deck_createCard(j, VALUES[i]);
    }

    for (int i = k; i < DECK_SIZE; i++)
        deck->cards[i] = NULL;

    return deck;
}

int deck_deleteDeck(struct Deck** deck)
{
    if (deck == NULL)
        return POINTER_NULL;
    if (*deck == NULL)
        return DECK_NULL;

    for (int i = 0; i < DECK_SIZE; i++)
        deck_deleteCard(&((*deck)->cards[i]));

    free(*deck);
    *deck = NULL;

    return FUNCTION_NO_ERROR;
}

int deck_getDeckSize(const struct Deck* deck)
{
    if (deck == NULL)
        return DECK_NULL;

    int deckSize = 0;
    for (int i  = 0; i < DECK_SIZE; i++)
        if (deck->cards[i] != NULL)
            deckSize++;

    return deckSize;
}

int deck_shuffleDeck(struct Deck* deck)
{
    if (deck == NULL)
        return DECK_NULL;

    srand(time(NULL));
    int deckSize = deck_getDeckSize(deck);
    for (int i = 0; i < SWAPS_NUMBER; i++) {
        int a = rand() % deckSize;
        int b = rand() % deckSize;
        while (a == b) {
            a = rand() % deckSize;
            b = rand() % deckSize;
        }
        struct Card *card = deck->cards[a];
        deck->cards[a] = deck->cards[b];
        deck->cards[b] = card;
    }

    return FUNCTION_NO_ERROR;
}

int deck_compareCards(const struct Card* card1, const struct Card* card2,
                      enum Suit trump)
{
    if (card1 == NULL || card2 == NULL)
        return CARD_NULL;
    if (card1->suit == card2->suit && card1->value == card2->value)
        return 0;

    int value1 = card1->value;
    int value2 = card2->value;
    if ((card1->suit == trump && card2->suit != trump) ||
        (card1->suit == card2->suit && value1 > value2) ||
        (card1->suit != card2->suit && card2->suit != trump))
        return 1;

    return 2;
}

