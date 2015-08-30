/**
 * @file constants.h
 * @brief Contains definitions of various symbolic constants.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @brief Constants for suit.
 *
 * SuitEnd is a flag used when iterating.
 */
enum Suit {DIAMONDS = 0, CLUBS, SPADES, HEARTS, SuitEnd};

/**
 * @brief Game values for cards.
 *
 * -1 is a flag used when iterating.
 */
const int VALUES[13];

/**
 * @brief The maximum number of cards in a deck.
 */
#define DECK_SIZE 48

/**
 * @brief The maximum number of players in a game.
 */
#define MAX_GAME_PLAYERS 6

/**
 * @brief The minimum number of players in a game.
 */
#define MIN_GAME_PLAYERS 3

/**
 * @brief The maximum number of rounds in a game.
 */
#define MAX_GAME_ROUNDS 30

/**
 * @brief The maximum number of cards in a player's hand.
 */
#define MAX_CARDS 8

/**
 * @brief The minimum number of cards in a player's hand at start.
 */
#define MIN_CARDS 1
 
/**
 * @brief The swaps number made at shuffling of the deck.
 */
#define SWAPS_NUMBER 100

/**
 * @brief The points number on which a player earns them when the won hands
 *        number is equal with the hands number on which he bid them.
 */
#define POINTS_PER_ROUND 5

/**
 * @brief In this game the players can be rewarded on positive or on negative.
 *        When a player is rewarded on positive then he receives +BONUS points
 *        to the score his. When a player is rewarded on negative then he 
 *        receives -BONUS points to the score his.
 */
#define BONUS 10

/**
 * @brief This constant represents the number of rounds on which a player
 *        should them win or to them lose like he to be rewarded on positive
 *        or negative.
 */
#define BONUS_ROUNDS_NUMBER 5
 
#endif

