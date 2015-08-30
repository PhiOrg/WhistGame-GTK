#include <player.h>
#include <constants.h>
#include <errors.h>

#include <cutter.h>



void test_player_createPlayer()
{
    struct Player *player;
    cut_assert_equal_pointer(NULL, player_createPlayer(NULL, 1));

    char *name[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
    for (int i = 0; i < 10; i++) {
        player = player_createPlayer(name[i], i);
        int check = 0;
        if (player == NULL)
            check++;
        cut_assert_equal_int(0, check);
        cut_assert_equal_int(i, player->isHuman);
        cut_assert_equal_string(name[i], player->name);
        for (int j = 0; j < MAX_CARDS; j++)
            if (player->hand[j] != NULL)
                check++;
        cut_assert_equal_int(0, check);
        player_deletePlayer(&player);
    }
}

void test_player_deletePlayer()
{
    struct Player *player = player_createPlayer("A", 1);
    cut_assert_equal_int(POINTER_NULL, player_deletePlayer(NULL));
    cut_assert_equal_int(FUNCTIOON_NO_ERROR, player_deletePlayer(&player));
    cut_assert_equal_pointer(NULL, player);
    cut_assert_equal_int(PLAYER_NULL, player_deletePlayer(&player));
}

void test_player_addCard()
{
    struct Deck *deck = deck_createDeck(MIN_GAME_PLAYERS);
    struct Player *player = player_createPlayer("A", 1);

    cut_assert_equal_int(PLAYER_NULL, player_addCard(NULL, &deck->cards[0]));
    cut_assert_equal_int(POINTER_NULL, player_addCard(player, NULL));
    cut_assert_operator_int(0, >, player_addCard(NULL, NULL));

    int i;
    for (i = 0; i < MAX_CARDS; i++) {
        cut_assert_equal_int(FUNCTIOON_NO_ERROR,
                             player_addCard(player, &deck->cards[i]));
        cut_assert_equal_int(CARD_NULL, 
                             player_addCard(player, &deck->cards[i]));
    }
    cut_assert_equal_int(FULL, player_addCard(player, &deck->cards[++i]));

    player_deletePlayer(&player);
    deck_deleteDeck(&deck);
}

