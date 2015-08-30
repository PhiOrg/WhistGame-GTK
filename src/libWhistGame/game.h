/**
 * @file game.h
 * @brief Game structure, as well as helper functions.
 */

#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include "round.h"
#include "constants.h"

/**
 * @struct Game
 *
 * @brief Game structure. Structure used to keep informations about a game.
 *
 * @var Game::playersNumber
 *      The number of the player that are in game.
 * @var Game::gameType
 *      The game type (1 for 1-8-1 or 8 for 8-1-8).
 * @var Game::currentRound
 *      The current round of game.
 * @var Game::deck
 *      Pointer to the deck of cards of the game.
 * @var Game::players
 *      Pointer to the players of the game.
 * @var Game::rounds
 *      Pointer to the rounds of the game.
 */
struct Game {
    int playersNumber;
    int gameType;
    int currentRound;
    struct Deck *deck;
    struct Player *players[MAX_GAME_PLAYERS];
    struct Round *rounds[MAX_GAME_ROUNDS];
};

/**
 * @brief Function allocates and initializes a game.
 *
 * @param gameType The type of the game (1 or 8).
 *
 * @return Pointer to the new game on success, NULL on failure.
 */
struct Game *game_createGame(int gameType);

/**
 * @brief Function releases the memory a game and makes pointer NULL.
 *
 * @param game Pointer to pointer to the game which to be released.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int game_deleteGame(struct Game **game);

/**
 * @brief Function adds deck in game.
 *
 * @param game Pointer to the game in which will be added the deck.
 * @param deck Pointer to pointer to the deck which to be added.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int game_addDeck(struct Game *game, struct Deck **deck);

/**
 * @brief Function adds a player in game.
 *
 * @param game Pointer to the game in which to be added the player.
 * @param player Pointer to pointer to the player which to be added.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int game_addPlayer(struct Game *game, struct Player **player);

/**
 * @brief Function adds a round in game.
 *
 * @param game Pointer to the game in which to be added the round.
 * @param player Pointer to pointer to the round which to be added.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int game_addRound(struct Game *game, struct Round **round);

/**
 * @brief Function adds the players from game in round as from the position 
 *        firstPlayer.
 *
 * @param game Pointer to the game from which are added the players.
 * @param round Pointer to the round in which to be added the players.
 * @param firstPlayer The player id from game which is the first added in round.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int game_addPlayersInRound(const struct Game *game, struct Round *round,
                           int firstPlayer);

/**
 * @brief Function add the players from game in all rounds from a game.
 *
 * @param game Pointer to the game which to be modified.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int game_addPlayersInAllRounds(const struct Game *game);

/**
 * @brief Function creates and adds all the rounds in game.
 *
 * @param game Pointer to the game in which to be added the rounds.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int game_createAndAddRounds(struct Game *game);

/**
 * @brief This function check if a player must rewarded and if the player must
 *        to be rewarded then he is rewarded.
 *
 * @param game Pointer to the game in which are the rounds and the player.
 * @param player Pointer to the player which must checked.
 * @param currentRound The id of the current round.
 *
 * @return FUNCTION_NO_ERROR or 0 if the player wasn't rewarded.
 *         1 if the player was rewarded on positive.
 *         2 if the player was rewarded on negative.
 *         A negative value on failure.
 */
int game_rewardsPlayer(const struct Game *game, const struct Player *player,
                       int currentRound);

/**
 * @brief This function check if players from a game must rewarded and if in a
 *        game exists players which must to be rewarded then the function him
 *        rewards.
 *
 * @param game Pointer to the game in which are the players and the rounds.
 * @param currentRound The id of the current round.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int game_rewardsPlayersFromGame(const struct Game *game, int currentRound);

/**
 * @brief Function calculates the position a player in game. The function
 *        disregard the players which have the NULL value.
 *
 * @param game Pointer to the game in which is found the player.
 * @param player Pointer to the player for which is calculated the position.
 *
 * @return A positive value between 0 and MAX_GAME_PLAYERS - 1 on success, a
 *         negative value on failure.
 */
int game_getPlayerPosition(const struct Game *game,
                           const struct Player *player);

/**
 * @brief Function check if the player is at reward.
 *
 * @param game Pointer to the game in which is the player.
 * @param currentround The id of the current round.
 * @param player Pointer to the player for which checks it if is at reward.
 *
 * @return FUNCTION_NO_ERROR or 0 if the player isn't at reward.
 *         1 if the player is at positive reward.
 *         2 if the player is at negative reward.
 *         A negative value on failure.
 */
int game_checkIfPlayerIsAtReward(const struct Game* game, int currentRound,
                                 const struct Player* player);

#endif

