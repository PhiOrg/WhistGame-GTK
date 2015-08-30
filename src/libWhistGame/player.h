/**
 * @file player.h
 * @brief Player structure, as well as helper functions.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"
#include "constants.h"

/**
 * @struct Player
 *
 * @brief Player structure. Structure to keep informations about a player.
 *
 * @var Player::isHuman
 *      Variable used to indicate if the player is human or robot, 0 for AI and
 *      non-zero for human.
 * @var Player::name
 *      Pointer to the name of the player.
 * @var Player::hand
 *      Pointer to the cards of the player.
 */
struct Player {
    int isHuman;
    char *name;
    struct Card *hand[MAX_CARDS];
};

/**
 * @brief Allocates and initializes a player.
 *
 * @param name The name of the player.
 * @param isHuman Indicate the player type.
 *
 * @return Pointer to the new player on success or NULL on failure.
 */
struct Player *player_createPlayer(const char* name, int isHuman);

/**
 * @brief Function releases the memory of a player and makes pointer NULL.
 *
 * @param player Pointer to pointer to the player which to be released.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int player_deletePlayer(struct Player** player);

/**
 * @brief Function add the card of the player.
 *
 * @param player Pointer to the player which receives the card.
 * @param card Pointer to pointer to the card which is added.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int player_addCard(struct Player* player, struct Card** card);

/**
 * @brief Function compare two cards. This function will be used of qsort().
 *
 * @param a Pointer to void. This pointer will be convert to struct Card and
 *          will be compared with the second card.
 * @param b Pointer to void. This pointer will be convert to struct Card and
 *          will be compared with the first card.
 *
 * @return A positive value if the first card is greater, otherwise a negative
 *         value.
 */
int player_compareCards(const void* const a, const void* const b);

/**
 * @brief Function check if the player introduced a correct name.
 *
 * @param name Pointer to the name on which introduced him the player.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int player_checkPlayerName(const char* name);

/**
 * @brief Function get the position of the number-th card which is not null
 *        from cards a player.
 *
 * @param player Pointer to the player for which is obtained the position of
 *               the number-th card.
 * @param number Indicates the number of NULL cards on which the function not
 *               consider.
 *
 * @return A value between 0 and MAX_CARDS - 1 on success, a negative value on
 *         failure.
 */
int player_getIdNumberthCardWhichIsNotNull(const struct Player* player,
                                           int number);

/* @brief Function get the number of cards from player's hand.
 *
 * @param player Pointer to the player for which are counted the cards.
 *
 * @return A value between 0 and MAX_CARDS - 1 on success.
 *         PLAYER_NULL on failure.
 */
int player_getCardsNumber(const struct Player* player);

#endif

