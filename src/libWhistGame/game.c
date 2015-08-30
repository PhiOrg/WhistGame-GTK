/**
 * @file game.c
 * @brief In this file are defined functions used for Game-related operations,
 *        these functions are declared in the header file game.h.
 */

#include "game.h"
#include "errors.h"

#include <stdlib.h>
#include <string.h>

struct Game *game_createGame(int gameType)
{
    if (gameType != 1 && gameType != 8)
        return NULL;

    struct Game *game = malloc(sizeof(struct Game));
    if (game == NULL)
        return NULL;

    game->playersNumber = 0;
    game->currentRound  = -1;
    game->gameType      = gameType;
    game->deck          = NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        game->players[i] = NULL;
    for (int i = 0; i < MAX_GAME_ROUNDS; i++)
        game->rounds[i] = NULL;

    return game;
}

int game_deleteGame(struct Game** game)
{
    if (game == NULL)
        return POINTER_NULL;
    if (*game == NULL)
        return GAME_NULL;

    if ((*game)->deck != NULL)
        deck_deleteDeck(&((*game)->deck));

    for (int i = 0; i < MAX_GAME_ROUNDS; i++)
        if ((*game)->rounds[i] != NULL)
            round_deleteRound(&((*game)->rounds[i]));

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if ((*game)->players[i] != NULL)
            player_deletePlayer(&((*game)->players[i]));

    free(*game);
    *game = NULL;

    return FUNCTION_NO_ERROR;
}

int game_addDeck(struct Game* game, struct Deck** deck)
{
    if (game == NULL)
        return GAME_NULL;
    if (deck == NULL)
        return POINTER_NULL;
    if (*deck == NULL)
        return DECK_NULL;

    if (game->deck != NULL)
        deck_deleteDeck(&game->deck);

    game->deck = *deck;
    *deck = NULL;

    return FUNCTION_NO_ERROR;
}

int game_addPlayer(struct Game* game, struct Player** player)
{
    if (game == NULL)
        return GAME_NULL;
    if (player == NULL)
        return POINTER_NULL;
    if (*player == NULL)
        return PLAYER_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        if (game->players[i] == *player)
            return DUPLICATE_POINTER;
        if (game->players[i] != NULL && 
            !strcmp(game->players[i]->name, (*player)->name))
            return DUPLICATE_NAME;
    }


    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] == NULL) {
            game->players[i] = *player;
            *player = NULL;
            game->playersNumber++;
            return FUNCTION_NO_ERROR;
        }

    return FULL;
}

int game_addRound(struct Game* game, struct Round** round)
{
    if (game == NULL)
        return GAME_NULL;
    if (round == NULL)
        return POINTER_NULL;
    if (*round == NULL)
        return ROUND_NULL;

    for (int i = 0; i < MAX_GAME_ROUNDS; i++)
        if (game->rounds[i] == *round)
            return DUPLICATE_POINTER;

    for (int i = 0; i < MAX_GAME_ROUNDS; i++)
        if (game->rounds[i] == NULL) {
            game->rounds[i] = *round;
            *round = NULL;
            return FUNCTION_NO_ERROR;
        }

    return FULL;
}

int game_addPlayersInRound(const struct Game* game, struct Round* round,
                           int firstPlayer)
{
    if (game == NULL)
        return GAME_NULL;
    if (round == NULL)
        return ROUND_NULL;
    if (firstPlayer < 0 || firstPlayer >= MAX_GAME_PLAYERS)
        return ILLEGAL_VALUE;
    if (game->playersNumber < MIN_GAME_PLAYERS)
        return INSUFFICIENT_PLAYERS;

    for (int i = firstPlayer; i < MAX_GAME_PLAYERS; i++)
        round_addPlayer(round, game->players[i]);
    for (int i = 0; i < firstPlayer; i++)
        round_addPlayer(round, game->players[i]);

    return FUNCTION_NO_ERROR;
}

int game_addPlayersInAllRounds(const struct Game* game)
{
    if (game == NULL)
        return GAME_NULL;

    for (int i = 0; i < MAX_GAME_ROUNDS; i++)
        if (game->rounds[i] != NULL)
            game_addPlayersInRound(game, game->rounds[i],
                                   i % game->playersNumber);

    return FUNCTION_NO_ERROR;
}

int game_createAndAddRounds(struct Game* game)
{
    if (game == NULL)
        return GAME_NULL;

    struct Round *round;
    for (int i = 0; i < game->playersNumber; i++) {
        round = round_createRound(game->gameType);
        game_addRound(game, &round);
    }

    int roundType;
    int type;
    if (game->gameType == 8) {
        roundType = -1;
        type = 1;
    } else {
        roundType = 1;
        type = 8;
    }

    for (int i = 0; i < 6; i++) {
        int type2 = game->rounds[game->playersNumber + i - 1]->roundType + 
                    roundType;
        round = round_createRound(type2);
        game_addRound(game, &round);
    }

    for (int i = 0; i < game->playersNumber; i++) {
        round = round_createRound(type);
        game_addRound(game, &round);
    }

    int position = 2 * game->playersNumber + 5;
    for (int i = 0; i < 6; i++) {
        int type = game->rounds[position]->roundType - roundType;
        round = round_createRound(type);
        game_addRound(game, &round);
        position++;
    }

    for (int i = 0; i < game->playersNumber; i++) {
        round = round_createRound(game->gameType);
        game_addRound(game, &round);
    }

    return FUNCTION_NO_ERROR;
}

int game_rewardsPlayer(const struct Game* game, const struct Player* player,
                       int currentRound)
{
    if (game == NULL)
        return GAME_NULL;
    if (player == NULL)
        return PLAYER_NULL;
    if (currentRound < 0 || currentRound >= MAX_GAME_ROUNDS)
        return ILLEGAL_VALUE;
    if (currentRound - BONUS_ROUNDS_NUMBER + 1 < 0)
        return FUNCTION_NO_ERROR;

    int wonRounds  = 0;
    int lostRounds = 0;
    int i = currentRound - BONUS_ROUNDS_NUMBER + 1;

    for (; i <= currentRound; i++)
        if (game->rounds[i] != NULL) {
            int position = round_getPlayerId(game->rounds[i], player);
            if (position < 0)
                return position;
            if (game->rounds[i]->bonus[position] == 0 && 
                game->rounds[i]->roundType != 1) {
                if (game->rounds[i]->bids[position] == 
                    game->rounds[i]->handsNumber[position])
                    wonRounds++;
                else
                    lostRounds++;
            }
        } else {
            return ROUND_NULL;
        }

    int position = round_getPlayerId(game->rounds[currentRound], player);
    if (wonRounds == BONUS_ROUNDS_NUMBER) {
        game->rounds[currentRound]->pointsNumber[position] += BONUS;
        game->rounds[currentRound]->bonus[position]         = 1;
        return 1;
    }
    if (lostRounds == BONUS_ROUNDS_NUMBER) {
        game->rounds[currentRound]->pointsNumber[position] -= BONUS;
        game->rounds[currentRound]->bonus[position]         = 2;
        return 2;
    }

    return FUNCTION_NO_ERROR;
}

int game_rewardsPlayersFromGame(const struct Game* game, int currentRound)
{
    if (game == NULL)
        return GAME_NULL;
    if (currentRound < 0 || currentRound >= MAX_GAME_ROUNDS)
        return ILLEGAL_VALUE;
    if (currentRound - BONUS_ROUNDS_NUMBER + 1 < 0)
        return FUNCTION_NO_ERROR;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] != NULL) {
            int result = game_rewardsPlayer(game, game->players[i],
                                            currentRound);
            if (result < 0)
                return result;
        }

    return FUNCTION_NO_ERROR;
}

int game_getPlayerPosition(const struct Game *game,
                           const struct Player *player)
{
    if (game == NULL)
        return GAME_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    int position = -1;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] != NULL) {
            position++;
            if (game->players[i] == player)
                return position;
        }

    return NOT_FOUND;
}

int game_checkIfPlayerIsAtReward(const struct Game* game, int currentRound,
                                 const struct Player* player)
{
    if (game == NULL)
        return GAME_NULL;
    if (player == NULL)
        return PLAYER_NULL;
    if (currentRound < 0 || currentRound >= MAX_GAME_ROUNDS)
        return ILLEGAL_VALUE;
    if (currentRound - BONUS_ROUNDS_NUMBER + 1 < 0)
        return FUNCTION_NO_ERROR;

    int wonRounds  = 0;
    int lostRounds = 0;
    int i = currentRound - BONUS_ROUNDS_NUMBER + 1;

    for (; i < currentRound; i++)
        if (game->rounds[i] != NULL) {
            int position = round_getPlayerId(game->rounds[i], player);
            if (position < 0)
                return position;
            if (game->rounds[i]->bonus[position] == 0 && 
                game->rounds[i]->roundType != 1) {
                if (game->rounds[i]->bids[position] == 
                    game->rounds[i]->handsNumber[position])
                    wonRounds++;
                else
                    lostRounds++;
            }
        } else {
            return ROUND_NULL;
        }

    if (wonRounds == BONUS_ROUNDS_NUMBER - 1)
        return 1;
    if (lostRounds == BONUS_ROUNDS_NUMBER - 1)
        return 2;

    return FUNCTION_NO_ERROR;
}

