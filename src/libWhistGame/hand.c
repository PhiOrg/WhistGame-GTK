/**
 * @file hand.c
 * @brief In this file are defined functions used for Hand-related operations,
 *        these functions are declared in the header file hand.h.
 */

#include "hand.h"
#include "errors.h"

#include <stdlib.h>

struct Hand *hand_createHand()
{
    struct Hand *hand = malloc(sizeof(struct Hand));

    if (hand == NULL)
        return NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        hand->cards[i]   = NULL;
        hand->players[i] = NULL;
    }

    return hand;
}

int hand_deleteHand(struct Hand** hand)
{
    if (hand == NULL)
        return POINTER_NULL;
    if (*hand == NULL)
        return HAND_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        if ((*hand)->cards[i] != NULL)
            deck_deleteCard(&((*hand)->cards[i]));
        if ((*hand)->players[i] != NULL)
            (*hand)->players[i] = NULL;
    }

    free(*hand);
    *hand = NULL;

    return FUNCTION_NO_ERROR;
}

int hand_addPlayer(struct Hand* hand, struct Player* player)
{
    if (hand == NULL)
        return HAND_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    int position = -1;
    for (int i = MAX_GAME_PLAYERS - 1; i >= 0; i--) {
        if (player == hand->players[i])
            return DUPLICATE_POINTER;
        if (hand->players[i] == NULL)
            position = i;
    }

    if (position != -1) {
        hand->players[position] = player;
        return FUNCTION_NO_ERROR;
    }

    return FULL;
}

int hand_addCard(struct Hand* hand, const struct Player* player,
                 struct Card** card)
{
    if (hand == NULL)
        return HAND_NULL;
    if (card == NULL)
        return POINTER_NULL;
    if (*card == NULL)
        return CARD_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (hand->players[i] == player) {
            hand->cards[i] = *card;
            *card = NULL;
            return FUNCTION_NO_ERROR;
        }

    return NOT_FOUND;
}

int hand_checkCard(const struct Hand* hand, const struct Player* player,
                   int cardId, const struct Card* trump)
{
    if (hand == NULL)
        return HAND_NULL;
    if (player == NULL)
        return PLAYER_NULL;
    if (cardId < 0 || cardId > MAX_CARDS - 1)
        return ILLEGAL_VALUE;
    if (player->hand[cardId] == NULL)
        return CARD_NULL;
    if (hand->cards[0] == NULL)
        return 1;

    int playerFirstCard  = 0;
    int playerSuitTrump  = 0;
    enum Suit suitTrump;
    if (trump != NULL)
        suitTrump = trump->suit;
    else
        suitTrump = SuitEnd;

    for (int i = 0; i < MAX_CARDS; i++) {
        if (player->hand[i] != NULL) {
            if (player->hand[i]->suit == hand->cards[0]->suit)
                playerFirstCard = 1;
            if (suitTrump != SuitEnd && player->hand[i]->suit == trump->suit)
               playerSuitTrump = 1;
        }
    }

    if ((player->hand[cardId]->suit == hand->cards[0]->suit) ||
        (suitTrump == SuitEnd && playerFirstCard == 0) ||
        (playerFirstCard == 0 && playerSuitTrump == 0) ||
        (player->hand[cardId]->suit == suitTrump && playerFirstCard == 0))
        return 1;

    return 0;
}

int hand_getPlayerId(const struct Hand* hand, const struct Player* player)
{
    if (hand == NULL)
        return HAND_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (hand->players[i] == player)
            return i;

    return NOT_FOUND;
}

