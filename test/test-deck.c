#include <deck.h>
#include <constants.h>
#include <errors.h>

#include <cutter.h>
#include <string.h>

void test_deck_createCard()
{
    struct Card *card;
    cut_assert_equal_pointer(NULL, deck_createCard(SuitEnd, VALUES[0]));
    cut_assert_equal_pointer(NULL, deck_createCard(DIAMONDS, -1));
    cut_assert_equal_pointer(NULL, deck_createCard(SuitEnd, -1));

    for (int i = 0; i < SuitEnd; i++)
        for (int j = 0; VALUES[j] != -1; j++) {
            card = deck_createCard(i, VALUES[j]);
            cut_assert_equal_int(card->suit, i);
            cut_assert_equal_int(card->value, VALUES[j]);
            deck_deleteCard(&card);
        }
}

void test_deck_deleteCard()
{
    struct Card *card = deck_createCard(DIAMONDS, VALUES[0]);
    cut_assert_equal_int(POINTER_NULL, deck_deleteCard(NULL));
    cut_assert_equal_int(FUNCTIOON_NO_ERROR, deck_deleteCard(&card));
    cut_assert_equal_pointer(NULL, card);
    cut_assert_equal_int(CARD_NULL, deck_deleteCard(&card));
}

void test_deck_createDeck()
{
    struct Deck *deck;
    cut_assert_equal_pointer(NULL, deck_createDeck(MAX_GAME_PLAYERS + 1));
    cut_assert_equal_pointer(NULL, deck_createDeck(MIN_GAME_PLAYERS - 1));

    for (int i = MIN_GAME_PLAYERS; i <= MAX_GAME_PLAYERS; i++) {
        deck = deck_createDeck(i);
        int check = 0;
        if (deck == NULL)
            check++;
        cut_assert_equal_int(0, check);
        cut_assert_equal_int(i * MAX_CARDS, deck_getDeckSize(deck));
        
        int duplicates = 0;
        for (int j = 0; j < DECK_SIZE; j++)
            for (int k = 0; k < DECK_SIZE; k++)
                if (k != j && deck->cards[k] != NULL && deck->cards[j] != NULL
                    && deck->cards[k]->suit == deck->cards[j]->suit &&
                    deck->cards[k]->value == deck->cards[j]->value)
                    duplicates++;
        cut_assert_equal_int(0, duplicates);
        deck_deleteDeck(&deck);
    }
}

void test_deck_deleteDeck()
{
    cut_assert_equal_int(POINTER_NULL, deck_deleteDeck(NULL));
    struct Deck *deck = deck_createDeck(MAX_GAME_PLAYERS);
    cut_assert_equal_int(FUNCTIOON_NO_ERROR, deck_deleteDeck(&deck));
    cut_assert_equal_pointer(NULL, deck);
    cut_assert_equal_int(DECK_NULL, deck_deleteDeck(&deck));
}

void test_deck_getDeckSize()
{
    cut_assert_equal_int(DECK_NULL, deck_getDeckSize(NULL));
    struct Deck *deck;

    for (int i = MIN_GAME_PLAYERS; i <= MAX_GAME_PLAYERS; i++) {
        deck = deck_createDeck(i);
        cut_assert_equal_int(i * MAX_CARDS, deck_getDeckSize(deck));
        deck_deleteDeck(&deck);
    }
}

void test_deck_shuffleDeck()
{
    cut_assert_equal_int(DECK_NULL, deck_shuffleDeck(NULL));
    struct Deck *deck = deck_createDeck(MAX_GAME_PLAYERS);
    struct Deck *shuffled_deck = malloc(sizeof(struct Deck));
    memcpy(shuffled_deck, deck, sizeof(struct Deck));
    cut_assert_equal_int(FUNCTIOON_NO_ERROR, deck_shuffleDeck(shuffled_deck));

    int deckSize = deck_getDeckSize(deck);
    int differences = 0;
    for (int j = 0; j < 100; j++) {
        differences = 0;
        for (int i = 0; i < deckSize; i++)
            if (deck->cards[i]->suit  != shuffled_deck->cards[i]->suit ||
                deck->cards[i]->value != shuffled_deck->cards[i]->value)
                differences++;
        cut_assert_not_equal_int(0, differences);
    }

    deck_deleteDeck(&deck);
}

void test_deck_compareCards()
{
    struct Card *card1 = deck_createCard(DIAMONDS, VALUES[2]);
    struct Card *card2 = deck_createCard(DIAMONDS, VALUES[2]);

    cut_assert_equal_int(CARD_NULL, deck_compareCards(card1, NULL, DIAMONDS));
    cut_assert_equal_int(CARD_NULL, deck_compareCards(NULL, card2, DIAMONDS));
    cut_assert_equal_int(CARD_NULL, deck_compareCards(NULL, NULL, DIAMONDS));

    cut_assert_equal_int(0, deck_compareCards(card1, card2, SuitEnd));

    card1->value = VALUES[3];
    cut_assert_equal_int(1, deck_compareCards(card1, card2, SuitEnd));
    cut_assert_equal_int(1, deck_compareCards(card1, card2, DIAMONDS));
    cut_assert_equal_int(1, deck_compareCards(card1, card2, CLUBS));
    cut_assert_equal_int(2, deck_compareCards(card2, card1, SuitEnd));
    cut_assert_equal_int(2, deck_compareCards(card2, card1, DIAMONDS));
    cut_assert_equal_int(2, deck_compareCards(card2, card1, CLUBS));

    card2->suit = CLUBS;
    cut_assert_equal_int(1, deck_compareCards(card1, card2, DIAMONDS));
    cut_assert_equal_int(1, deck_compareCards(card1, card2, SuitEnd));
    cut_assert_equal_int(1, deck_compareCards(card1, card2, SPADES));
    cut_assert_equal_int(2, deck_compareCards(card2, card1, DIAMONDS));
    cut_assert_equal_int(1, deck_compareCards(card2, card1, SuitEnd));
    cut_assert_equal_int(1, deck_compareCards(card2, card1, SPADES));

    deck_deleteCard(&card1);
    deck_deleteCard(&card2);
}

