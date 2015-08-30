/**
 * @file hand.h
 * @brief Hand structure, as well as helper functions.
 */

#ifndef HAND_H
#define HAND_H

#include "deck.h"
#include "player.h"
#include "constants.h"

/**
 * @struct Hand
 *
 * @brief Hand structure. In Hand, player[i] gives cards[i]. The players should
 *        be added in the order of the bids.
 *
 * @var Hand::cards
 *      Pointer to the cards of the hand.
 * @var Hand::players
 *      Pointer to the players of the hand.
 */
struct Hand {
    struct Card *cards[MAX_GAME_PLAYERS];
    struct Player *players[MAX_GAME_PLAYERS];
};

/**
 * @brief Function allocates and initializes a hand.
 *
 * @return Pointer to the new hand on success, NULL on failure.
 */
struct Hand *hand_createHand();

/**
 * @brief Function releases the memory a hand.
 *
 * @param hand Pointer to pointer to the hand which to be released.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int hand_deleteHand(struct Hand** hand);

/**
 * @brief Function adds a player in a hand.
 *
 * @param hand Pointer to the hand in which is added the player.
 * @param player Pointer to the player which to be added.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int hand_addPlayer(struct Hand* hand, struct Player* player);

/**
 * @brief Function adds a card in a hand.
 *
 * @param hand Pointer to the hand in which to be added the card.
 * @param player Pointer to the player which places the card.
 * @param card Pointer to pointer to the card which is added.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int hand_addCard(struct Hand* hand, const struct Player* player,
                 struct Card** card);

/**
 * @brief Function checks if a card can be put down.
 *
 * @param hand Pointer to the hand in which checks it if the card can be put
 *             down.
 * @param player Pointer to the player which has the card.
 * @param cardId The id of the card from player's hand.
 * @param trump Pointer to the card which is the trump of the round.
 *
 * @return 1 if the card can be put down.
 *         0 if the card can't be put down. 
 *         other value on failure.
 */
int hand_checkCard(const struct Hand* hand, const struct Player* player,
                   int cardId, const struct Card* trump);

/**
 * @brief Function get the id of the player.
 *
 * @param hand Pointer to the hand in which is the player.
 * @param player Pointer to the player for which it get the id.
 *
 * @return A number between 0 and MAX_GAME_PLAYERS - 1 on success, a negative
 *         value on failure.
 */
int hand_getPlayerId(const struct Hand* hand, const struct Player* player);

#endif

