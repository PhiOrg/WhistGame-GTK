/**
 * @file player.c
 * @brief In this file are defined functions used for Player-related operations,
 *        these functions are declared in the header file player.h.
 */

#include "player.h"
#include "errors.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Player *player_createPlayer(const char* name, int isHuman)
{
    if (name == NULL)
        return NULL;

    struct Player *player = malloc(sizeof(struct Player));
    if (player == NULL)
        return NULL;

    player->name = malloc((strlen(name) + 1) * sizeof(char));
    if (player->name != NULL)
        strcpy(player->name, name);
    else
        return NULL;

    player->isHuman = isHuman;

    for (int i = 0; i < MAX_CARDS; i++)
        player->hand[i] = NULL;

    return player;
}

int player_deletePlayer(struct Player** player)
{
    if (player == NULL)
        return POINTER_NULL;
    if (*player == NULL)
        return PLAYER_NULL;

    free((*player)->name);
    (*player)->name = NULL;

    free(*player);
    *player = NULL;

    return FUNCTION_NO_ERROR;
}

int player_addCard(struct Player* player, struct Card** card)
{
    if (player == NULL)
        return PLAYER_NULL;
    if (card == NULL)
        return POINTER_NULL;
    if (*card == NULL)
        return CARD_NULL;

    int position = -1;
    for (int i = 0; i < MAX_CARDS; i++) {
        if (player->hand[i] == *card)
            return DUPLICATE_POINTER;
        if (position == -1 && player->hand[i] == NULL)
            position = i;
    }

    if (position != -1) {
        player->hand[position] = *card;
        *card = NULL;
        return FUNCTION_NO_ERROR;
    }

    return FULL;
}

int player_compareCards(const void* const a, const void* const b)
{
    int suit = (*(struct Card**)a)->suit - (*(struct Card**)b)->suit;
    int value = (*(struct Card**)a)->value - (*(struct Card**)b)->value;
    if (suit == 0)
        return value;

    return suit;
}

int player_checkPlayerName(const char* name)
{
    if (name == NULL)
        return POINTER_NULL;

    int firstLetter = (int)tolower(name[0]);
    if (strlen(name) < 5 || firstLetter < 97 || firstLetter > 122)
        return INCORRECT_NAME;

    return FUNCTION_NO_ERROR;
}

int player_getIdNumberthCardWhichIsNotNull(const struct Player* player,
                                           int number)
{
    if (player == NULL)
        return PLAYER_NULL;
    if (number < 1 || number > MAX_CARDS)
        return ILLEGAL_VALUE;

    int noOfCards = 0;
    for (int i = 0; i < MAX_CARDS; i++)
        if (player->hand[i] != NULL) {
            noOfCards++;
            if (noOfCards == number)
                return i;
        }

    return ILLEGAL_VALUE;
}

int player_getCardsNumber(const struct Player* player)
{
    if (player == NULL)
        return PLAYER_NULL;

    int cardsNumber = 0;
    for (int i = 0; i < MAX_CARDS; i++)
        if (player->hand[i] != NULL)
            cardsNumber++;

    return cardsNumber;
}

