#include <stdio.h>
#include <stdlib.h>

#include "gui.h"

/**
 * @brief The maximum number of games on which a player can play them in
 *        same time.
 */
#define MAX_GAMES 1

int InitWhistGame(const char *name, int gameType, int noOfBots, int *noOfGames)
{
    ++*noOfGames;

    struct GameGUI *gameGUI = gui_createGameGUI();
    gui_setGameGUI(gameGUI);
    struct Player *player;

    gameGUI->game = game_createGame(gameType);
    gameGUI->noOfGames = noOfGames;

    player = player_createPlayer(name, 1);
    game_addPlayer(gameGUI->game, &player);

    for (int i = 1; i <= noOfBots; i++) {
        char no = (char)(((int)'0') + i);
        char botName[7] = "robot";
        botName[5] = no;
        botName[6] = '\0';
        player = player_createPlayer(botName, 0);
        game_addPlayer(gameGUI->game, &player);
    }

    game_createAndAddRounds(gameGUI->game);
    game_addPlayersInAllRounds(gameGUI->game);

    gui_init(&(gameGUI->windowTable), &(gameGUI->fixedTable),
             "Whist", 798, 520);
    gui_setBackground(gameGUI->fixedTable, "pictures/table.png");
    gui_createButtonShowScore(gameGUI->fixedTable, &(gameGUI->buttonShowScore),
                              gameGUI->game);

    gui_initTrump(gameGUI->fixedTable, &(gameGUI->imageTrump));
    gui_showTrump(NULL, gameGUI->imageTrump);

    gameGUI->bidGUI = gui_createBidGUI();
    gui_initBidGUI(gameGUI->bidGUI, gameGUI->fixedTable);

    gameGUI->playerCards = gui_initializePlayerCards(gameGUI->fixedTable);

    gui_initNoOfBidsLabel(&(gameGUI->labelNoOfBids), gameGUI->fixedTable);
    gui_initRoundTypeLabel(&(gameGUI->labelRoundType), gameGUI->fixedTable);

    gameGUI->playersGUI = gui_createPlayersGUI();
    gui_showPlayers(gameGUI->game, gameGUI->fixedTable, gameGUI->playersGUI);

    gameGUI->cardsFromTable = gui_createCardsFromTable();
    gui_initCardsFromTable(gameGUI->cardsFromTable, gameGUI->fixedTable);

    gameGUI->select = gui_createSelect(gameGUI->fixedTable,
                                       gameGUI->game->players[0],
                                       gameGUI->game);

    gtk_widget_add_events(gameGUI->windowTable, GDK_BUTTON_PRESS_MASK);
    gtk_widget_add_events(gameGUI->windowTable, GDK_POINTER_MOTION_MASK);
    g_signal_connect(G_OBJECT(gameGUI->windowTable), "motion-notify-event",
                     G_CALLBACK(gui_moveMouse), gameGUI->select);
    g_signal_connect(G_OBJECT(gameGUI->windowTable), "destroy",
                     G_CALLBACK(gui_closeWhistGame), NULL);
    g_signal_connect(G_OBJECT(gameGUI->windowTable), "button-press-event",
                     G_CALLBACK(gui_clickMouse), gameGUI);

    gui_createButtonStart(gameGUI);

    gameGUI->imagePlayerTurn = gui_imageNewFromFile("pictures/playerTurn.png");
    gtk_fixed_put(GTK_FIXED(gameGUI->fixedTable),
                  gameGUI->imagePlayerTurn, 0, 0);

    gameGUI->limitTimeGUI = gui_createLimitTimeGUI(gameGUI->fixedTable,
                                                   310, 526);
    gui_initLimitTimeGUI(gameGUI->limitTimeGUI, "pictures/limit_time.png");

    gtk_main();

    return EXIT_SUCCESS;
}

int CheckInput(GtkWidget *button, struct Input *input)
{
    if (input == NULL)
        return POINTER_NULL;

    const char *playerName = gtk_entry_get_text(GTK_ENTRY(input->name));
    if (player_checkPlayerName(playerName) != FUNCTION_NO_ERROR) {
        gui_initAndShowDialogIncorrectName(input->mainWindow);
        return EXIT_FAILURE;
    }

    if (input->noOfGames >= MAX_GAMES) {
        gui_initAndShowDialogMaxGames(input->mainWindow);
        return EXIT_FAILURE;
    }


    int botsNumber = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON
                                                     (input->robotsNumber));
    int gameType;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(input->gameType)))
        gameType = 1;
    else
        gameType = 8;

    InitWhistGame(playerName, gameType, botsNumber, &(input->noOfGames));

    return EXIT_SUCCESS;
}

gboolean closeSplashScreen(gpointer data)
{
    gtk_widget_destroy((GtkWidget*)data);
    gtk_main_quit();
    return FALSE;
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *fixed;
    GtkWidget *labelName, *labelType, *labelNumber;
    GtkWidget *name;
    GtkWidget *radio1, *radio8;
    GtkWidget *spinNumber;
    GtkAdjustment *number;
    struct Input *input = malloc(sizeof(struct Input));

    gtk_init(&argc, &argv);

    GtkWidget *splash;
    GtkWidget *splashFixed;
    guint time = 5;

    gui_init(&splash, &splashFixed, "Whist Splash", 450, 318);
    gtk_window_set_decorated(GTK_WINDOW(splash), FALSE);
    gui_setBackground(splashFixed, "pictures/splash_screen.jpg");
    g_timeout_add_seconds(time, closeSplashScreen, splash);

    gtk_main();

    gui_init(&window, &fixed, "Whist Game", 230, 200);
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    gui_playerName(window, fixed, &labelName, &name);
    gui_gameType(window, fixed, &labelType, &radio1, &radio8);
    gui_noOfBots(window, fixed, &labelNumber, &spinNumber, &number);

    input->name         = name;
    input->robotsNumber = spinNumber;
    input->gameType     = radio1;
    input->mainWindow   = window;
    input->noOfGames    = 0;

    button = gtk_button_new_with_label("Start");
    gtk_fixed_put(GTK_FIXED(fixed), button, 100, 160);
    g_signal_connect(G_OBJECT(button), "clicked",
                     G_CALLBACK(CheckInput), input);
    gtk_widget_show(button);

    gtk_main();

    free(input);

    return EXIT_SUCCESS;
}

