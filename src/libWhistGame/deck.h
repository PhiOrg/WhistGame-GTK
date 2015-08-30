/**
 * @file deck.h
 * @brief Deck and Card structures, as well as helper functions.
 */

#ifndef DECK_H
#define DECK_H

#include "constants.h"

/**
 * @struct Card
 *
 * @brief Card structure. Structure used to keep information about an card.
 *
 * @var Card::suit
 *      The suit of the card.      
 * @var Card::value
 *      The value of the card.
 */
struct Card {
    enum Suit suit;
    int value;
};

/**
 * @struct Deck
 *
 * @brief Deck structure. Structure used to keep pointers to the cards of the 
 *        deck.
 *
 * @var Deck::cards
 *      Pointer to the cards of the deck.
 */
struct Deck {
    struct Card *cards[DECK_SIZE];
};

/**
 * @brief Allocates and initializes a card.
 *
 * @param suit The suit of the new card.
 * @param value The value of the new card.
 *
 * @return Pointer to the new card on success or NULL on failure.
 */
struct Card *deck_createCard(enum Suit suit, int value);

/**
 * @brief Function releases the memory of a card and makes the pointer NULL.
 *
 * @param card Pointer to pointer to the card which to be released.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int deck_deleteCard(struct Card** card);

/**
 * @brief Allocates and initializes a deck.
 *
 * @param playersNumber The players number from game.
 *
 * @return Pointer to the new deck on success or NULL on failure.
 */
struct Deck *deck_createDeck(int playersNumber);

/**
 * @brief Function realeses the memory of a deck and makes the pointer NULL.
 *
 * @param deck Pointer to pointer to the deck whick to be released.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int deck_deleteDeck(struct Deck** deck);

/**
 * @brief Function counting the cards from a deck.
 *
 * @param deck Pointer to the deck in which are the cards.
 *
 * @return An positive integer value contained between 0 and DECK_SIZE on 
 *         success, an negative value on failure.
 */
int deck_getDeckSize(const struct Deck* deck);

/**
 * @brief Function shuffle the cards from a deck.
 *
 * @param deck Pointer to the deck which to be shuffled.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int deck_shuffleDeck(struct Deck* deck);

/**
* @brief Function compare two cards.
*
* @param card1 Pointer to the first card which to be compared.
* @param card2 Pointer to the second card which to be compared.
* @param trump The trump which is set in game.
*
* @return 0 If the cards are equal.
*         1 If the first card (card1) is the winning.
*         2 If the second card (card2) is the winning.
*         Other value on failure.
*/
int deck_compareCards(const struct Card* card1, const struct Card* card2,
                      enum Suit trump);

#endif

