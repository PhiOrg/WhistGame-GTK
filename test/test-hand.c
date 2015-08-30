#include <hand.h>
#include <errors.h>

#include <cutter.h>

void test_hand_createHand()
{
    struct Hand *hand = hand_createHand();
    int check = 0;
    if (hand != NULL)
        check++;
    cut_assert_equal_int(1, check);

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        cut_assert_equal_pointer(NULL, hand->cards[i]);
        cut_assert_equal_pointer(NULL, hand->players[i]);
    }

    hand_deleteHand(&hand);
}

void test_hand_deleteHand()
{
    struct Hand *hand = hand_createHand();
    cut_assert_equal_int(FUNCTIOON_NO_ERROR, hand_deleteHand(&hand));
    cut_assert_equal_pointer(NULL, hand);
    cut_assert_equal_int(HAND_NULL, hand_deleteHand(&hand));
    cut_assert_equal_int(POINTER_NULL, hand_deleteHand(NULL));
}

void test_hand_addPlayer()
{
    struct Hand *hand = hand_createHand();
    struct Player *players[MAX_GAME_PLAYERS + 1];
    players[0] = player_createPlayer("A", 1);

    cut_assert_equal_int(HAND_NULL, hand_addPlayer(NULL, players[0]));
    cut_assert_equal_int(PLAYER_NULL, hand_addPlayer(hand, NULL));
    cut_assert_operator_int(0, >, hand_addPlayer(NULL, NULL));

    for (int i = 1; i <= MAX_GAME_PLAYERS; i++) {
        players[i] = player_createPlayer("A", i);
        cut_assert_equal_int(FUNCTIOON_NO_ERROR,
                             hand_addPlayer(hand, players[i]));
        cut_assert_equal_int(DUPLICATE_POINTER,
                             hand_addPlayer(hand, players[i]));
        int check = 0;
        for (int j = 0; j < MAX_GAME_PLAYERS; j++)
            if (players[i] == hand->players[j])
                check++;
        cut_assert_equal_int(1, check);
    }
    cut_assert_equal_int(FULL, hand_addPlayer(hand, players[0]));

    for (int i = 0; i <= MAX_GAME_PLAYERS; i++)
        player_deletePlayer(&players[i]);
    hand_deleteHand(&hand);
}

void test_hand_addCard()
{
    struct Hand *hand = hand_createHand();
    struct Deck *deck = deck_createDeck(MAX_GAME_PLAYERS);
    struct Player *players[MAX_GAME_PLAYERS + 1];   

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        players[i] = player_createPlayer("A", i);
        hand_addPlayer(hand, players[i]);
        struct Card *card  = deck->cards[i];
        struct Card *card2 = deck->cards[i];
        cut_assert_equal_int(FUNCTIOON_NO_ERROR, 
                            hand_addCard(hand, players[i], &(deck->cards[i])));
        cut_assert_equal_pointer(NULL, deck->cards[i]);
        int check = 0;
        for (int j = 0; j < MAX_GAME_PLAYERS; j++)
            if (players[i] == hand->players[j] && card == hand->cards[j])
                check++;
        cut_assert_equal_int(1, check);
    }
    players[MAX_GAME_PLAYERS] = player_createPlayer("A", 1);
    cut_assert_equal_int(NOT_FOUND,
                         hand_addCard(hand, players[MAX_GAME_PLAYERS],
                                      &deck->cards[MAX_GAME_PLAYERS]));

    for (int i = 0; i <= MAX_GAME_PLAYERS; i++)
        player_deletePlayer(&players[i]);
    deck_deleteDeck(&deck);
    hand_deleteHand(&hand);
}

void test_hand_checkCard()
{
    struct Hand *hand = hand_createHand();
    struct Player *players[3];
    struct Card *card;

    for (int i = 0; i < 3; i++) {
        players[i] = player_createPlayer("A", i);
        hand_addPlayer(hand, players[i]);
    }

    for (int i = 0; i != SuitEnd; i++ )
        for (int j = 0; j < 6; j++) {
            card = deck_createCard(i, VALUES[j]);
            player_addCard(players[j % 3], &card);
        }

    cut_assert_equal_int(1, hand_checkCard(hand, players[0], 0, NULL));
    cut_assert_equal_int(1, hand_checkCard(hand, players[0], 2, NULL));
    cut_assert_equal_int(1, hand_checkCard(hand, players[0], 4, NULL));
    cut_assert_equal_int(1, hand_checkCard(hand, players[0], 6, NULL));
    hand_addCard(hand, players[0], &players[0]->hand[0]); 
    cut_assert_equal_int(0, hand_checkCard(hand, players[1], 2, NULL));
    cut_assert_equal_int(1, hand_checkCard(hand, players[1], 0, NULL));
    deck_deleteCard(&(players[1]->hand[0]));
    deck_deleteCard(&(players[1]->hand[1]));
    cut_assert_equal_int(1, hand_checkCard(hand, players[1], 2, NULL));
    hand_addCard(hand, players[1], &players[1]->hand[2]);
    card = deck_createCard(CLUBS, VALUES[6]);
    cut_assert_equal_int(0, hand_checkCard(hand, players[2], 2, card));
    cut_assert_equal_int(0, hand_checkCard(hand, players[2], 4, card));
    cut_assert_equal_int(1, hand_checkCard(hand, players[2], 0, card));
    cut_assert_equal_int(1, hand_checkCard(hand, players[2], 1, card));
    deck_deleteCard(&(players[2]->hand[0]));
    deck_deleteCard(&(players[2]->hand[1]));
    cut_assert_equal_int(1, hand_checkCard(hand, players[2], 2, card));
    cut_assert_equal_int(0, hand_checkCard(hand, players[2], 4, card));
    deck_deleteCard(&(players[2]->hand[2]));
    deck_deleteCard(&(players[2]->hand[3]));
    cut_assert_equal_int(1, hand_checkCard(hand, players[2], 4, card));
    cut_assert_equal_int(1, hand_checkCard(hand, players[2], 6, card));

    deck_deleteCard(&card);
    hand_deleteHand(&hand);     
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < MAX_CARDS; j++)
            deck_deleteCard(&players[i]->hand[j]);
        player_deletePlayer(&players[i]);
    }
}

