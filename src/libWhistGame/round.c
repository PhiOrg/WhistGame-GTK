/**
 * @file round.c
 * @brief In this file are defined functions used for Round-related operations,
 *        these functions are declared in the header file round.h.
 */

#include "round.h"
#include "errors.h"

#include <stdlib.h>

struct Round *round_createRound(int roundType)
{
    if (roundType < MIN_CARDS || roundType > MAX_CARDS)
        return NULL;

    struct Round *round = malloc(sizeof(struct Round));
    if (round == NULL)
        return NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        round->bids[i]         = 0;
        round->pointsNumber[i] = 0;
        round->handsNumber[i]  = 0;
        round->bonus[i]        = 0;
        round->players[i]      = NULL;
    }

    round->hand      = NULL;
    round->trump     = NULL;
    round->roundType = roundType;

    return round;
}

int round_deleteRound(struct Round** round)
{
    if (round == NULL)
        return POINTER_NULL;
    if (*round == NULL)
        return ROUND_NULL;

    if ((*round)->hand != NULL)
        hand_deleteHand(&((*round)->hand));
    if ((*round)->trump != NULL)
        deck_deleteCard(&((*round)->trump));

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        (*round)->players[i] = NULL;
    
    free(*round);
    *round = NULL;

    return FUNCTION_NO_ERROR;
}

int round_addPlayer(struct Round* round, struct Player* player)
{
    if (round == NULL)
        return ROUND_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    int position = -1;
    for (int i = MAX_GAME_PLAYERS - 1; i >= 0; i--) {
        if (round->players[i] == player)
            return DUPLICATE_POINTER;
        if (round->players[i] == NULL)
            position = i;
    }

    if (position != -1) {
        round->players[position] = player;
        return FUNCTION_NO_ERROR;
    }

    return FULL;
}

int round_addHand(struct Round* round, struct Hand** hand)
{
    if (round == NULL)
        return ROUND_NULL;
    if (hand == NULL)
        return POINTER_NULL;
    if (*hand == NULL)
        return HAND_NULL;

    if (round->hand != NULL)
        hand_deleteHand(&(round->hand));

    round->hand = *hand;
    *hand = NULL;    

    return FUNCTION_NO_ERROR;
}

int round_addTrump(struct Round* round, struct Card** trump)
{
    if (round == NULL)
        return ROUND_NULL;
    if (trump == NULL)
        return POINTER_NULL;

    if (round->trump != NULL)
        deck_deleteCard(&(round->trump));

    round->trump = *trump;
    *trump = NULL;

    return FUNCTION_NO_ERROR;
}

int round_addPlayersInHand(const struct Round* round, int firstPlayer)
{
    if (round == NULL)
        return ROUND_NULL;
    if (firstPlayer < 0 || firstPlayer >= MAX_GAME_PLAYERS)
        return ILLEGAL_VALUE;
    if (round->hand == NULL)
        return HAND_NULL;

    int playersNumber = 0;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] != NULL)
            playersNumber++;

    if (playersNumber < MIN_GAME_PLAYERS)
        return INSUFFICIENT_PLAYERS;

    for (int i = firstPlayer; i < MAX_GAME_PLAYERS; i++)
        hand_addPlayer(round->hand, round->players[i]);
    for (int i = 0; i < firstPlayer; i++)
        hand_addPlayer(round->hand, round->players[i]);

    return FUNCTION_NO_ERROR;
}

int round_distributeCard(const struct Round* round, struct Deck* deck)
{
    if (round == NULL)
        return ROUND_NULL;
    if (deck == NULL)
        return DECK_NULL;

    int playersNumber = 0;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        if (round->players[i] != NULL)
            playersNumber++;
    }

    if (playersNumber < MIN_GAME_PLAYERS)
        return INSUFFICIENT_PLAYERS;

    int deckSize = deck_getDeckSize(deck);
    if (deckSize < playersNumber)
        return INSUFFICIENT_CARDS;

    int i,j;
    for (i = 0, j = 0; i < MAX_GAME_PLAYERS && j < DECK_SIZE; i++, j++) {
        while (deck->cards[j] == NULL && j < DECK_SIZE)
            j++;
        while (round->players[i] == NULL && i < MAX_GAME_PLAYERS)
            i++;
        if (i < MAX_GAME_PLAYERS && j < DECK_SIZE) {
            int check = player_addCard(round->players[i], &deck->cards[j]);
            if (check != FUNCTION_NO_ERROR)
                return check;
        }
    }

    return FUNCTION_NO_ERROR;
}

int round_distributeDeck(struct Round* round, struct Deck* deck)
{
    if (round == NULL)
        return ROUND_NULL;
    if (deck == NULL)
        return DECK_NULL;

    for (int i = MIN_CARDS; i <= round->roundType; i++) {
        int check = round_distributeCard(round, deck);
        if (check != FUNCTION_NO_ERROR)
            return check;
    }

    int i = 0;
    while (deck->cards[i] == NULL && i < DECK_SIZE)
        i++;

    if (i < DECK_SIZE)
        round_addTrump(round, &deck->cards[i]);

    return FUNCTION_NO_ERROR;
}

int round_getPlayerId(const struct Round* round,
                      const struct Player* player)
{
    if (round == NULL)
        return ROUND_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] == player)
            return i;

    return NOT_FOUND;
}

int round_getBidsSum(const struct Round* round)
{
    if (round == NULL)
        return ROUND_NULL;

    int sum = 0;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] != NULL)
            sum += round->bids[i];

    return sum;
}

int round_checkBid(const struct Round* round,
                   const struct Player* player, int bid)
{
    if (round == NULL)
        return ROUND_NULL;
    if (player == NULL)
        return PLAYER_NULL;
    if (bid < MIN_CARDS - 1 || bid > round->roundType)
        return ILLEGAL_BID;

    int position = round_getPlayerId(round, player);
    if (position < 0)
        return position;

    for (int i = position + 1; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] != NULL)
            return FUNCTION_NO_ERROR;

    if (round_getBidsSum(round) + bid == round->roundType)
        return ILLEGAL_BID;

    return FUNCTION_NO_ERROR;
}

int round_placeBid(struct Round* round, const struct Player* player, int bid)
{
    int check = round_checkBid(round, player, bid);
    if (check != 0)
        return check;

    int position = round_getPlayerId(round, player);
    round->bids[position] = bid;

    return FUNCTION_NO_ERROR;
}

struct Player *round_getPlayerWhichWonHand(const struct Round* round)
{
    if (round == NULL || round->hand == NULL)
        return NULL;

    int playersNumber = 0;
    int cardsNumber = 0;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        if (round->hand->players[i] != NULL)
            playersNumber++;
        if (round->hand->cards[i] != NULL)
            cardsNumber++;
    }

    if (playersNumber < MIN_GAME_PLAYERS || playersNumber != cardsNumber)
        return NULL;

    struct Player *winningPlayer = round->hand->players[0];
    struct Card   *winningCard   = round->hand->cards[0];
    enum Suit trump;
    if (round->trump == NULL)
        trump = SuitEnd;
    else
        trump = round->trump->suit;

    for (int i = 1; i < MAX_GAME_PLAYERS; i++)
        if (deck_compareCards(winningCard, round->hand->cards[i], trump) == 2) {
            winningPlayer = round->hand->players[i];
            winningCard   = round->hand->cards[i];
        }

    return winningPlayer;
}

int round_determinesScore(struct Round* round)
{
    if (round == NULL)
        return ROUND_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] != NULL) {
            if (round->handsNumber[i] == round->bids[i])
                round->pointsNumber[i] += POINTS_PER_ROUND + round->bids[i];
            else {
                int difference = round->handsNumber[i] - round->bids[i];
                if (difference < 0)
                    difference = -difference;
                round->pointsNumber[i] -= difference;
            }
        }

    return FUNCTION_NO_ERROR;
}

int round_copyScore(const struct Round* round1, struct Round* round2)
{
    if (round1 == NULL || round2 == NULL)
        return ROUND_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (round1->players[i] !=  NULL) {
            int position = round_getPlayerId(round2, round1->players[i]);
            if (position >= 0)
                round2->pointsNumber[position] = round1->pointsNumber[i]; 
            else
                return position;
        }

    return FUNCTION_NO_ERROR;
}

int round_repeatRound(const struct Round* round)
{
    if (round == NULL)
        return ROUND_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] != NULL && 
            round->bids[i] == round->handsNumber[i])
            return FUNCTION_NO_ERROR;

    return 1;
}

int round_reinitializeRound(struct Round* round)
{
    if (round == NULL)
        return ROUND_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        round->bids[i]        = 0;
        round->handsNumber[i] = 0;
    }

    deck_deleteCard(&(round->trump));
    hand_deleteHand(&(round->hand));

    return FUNCTION_NO_ERROR;
}

