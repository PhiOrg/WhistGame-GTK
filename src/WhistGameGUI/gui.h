/**
 * @file gui.h
 * @brief In this file are declared the functions and the structures used at
 *        GUI.
 */

#ifndef GUI_H
#define GUI_H

#include <libWhistGameAI.h>
#include <libWhistGame.h>

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdlib.h>

#define LIMIT_TIME 15
#define LENGTH_TIME_LINE 50
#define WIDTH_IMAGE_TIME_LINE 2

struct BidGUI {
    GtkWidget *image;
    GtkWidget *label[MAX_CARDS + 1];
};

struct CardsFromTable {
    GtkWidget *images[MAX_GAME_PLAYERS];
};

struct PlayersGUI {
    GtkWidget *rewardImage[MAX_GAME_PLAYERS];
    GtkWidget *image[MAX_GAME_PLAYERS];
    GtkWidget *nameLabel[MAX_GAME_PLAYERS];
    GtkWidget *bidsLabel[MAX_GAME_PLAYERS];
    GtkWidget *tookLabel[MAX_GAME_PLAYERS];
    GtkWidget *scoreLabel[MAX_GAME_PLAYERS];
};

struct Select {
    GtkWidget *fixed;
    GtkWidget *imageSelectedCard;
    GtkWidget *imageSelectedBid;
    struct Player *player;
    struct Game *game;
    int cardPlayerTurn;
    int bidPlayerTurn;
    int x;
    int y;
};

struct PlayerCards {
    GtkWidget *images[MAX_CARDS];
};

struct LimitTimeGUI {
    GtkWidget *fixed;
    GtkWidget *images[LENGTH_TIME_LINE];
    int x;
    int y;
    int lastImage;
};

struct GameGUI {
    struct Game *game;
    struct Select *select;
    struct PlayerCards *playerCards;
    struct PlayersGUI *playersGUI;
    struct CardsFromTable *cardsFromTable;
    struct BidGUI *bidGUI;
    struct LimitTimeGUI *limitTimeGUI;
    GtkWidget *windowTable;
    GtkWidget *fixedTable;
    GtkWidget *buttonShowScore;
    GtkWidget *imageTrump;
    GtkWidget *labelRoundType;
    GtkWidget *labelNoOfBids;
    GtkWidget *buttonStart;
    GtkWidget *imagePlayerTurn;
    int *noOfGames;
    int bidPlayerId;
    int cardPlayerId;
};

/**
 * @struct Input
 *
 * @brief The structure is used to keep informations about a game,
 *
 * @var Input::name
 *      Pointer to the GtkEntry. Is used to keep the user name.
 * @var Input::robotsNumber
 *      Pointer to the spin button. Is used to keep the bots number.
 * @var Input::gameType
 *      Pointer to the radio button. Is used to keep the game type.
 * @var Input::mainWindow
 *      Pointer to the window. Is used to show the dialogs with errors.
 * @var Input::noOfGames
 *      Is used to keep the number of open games.
 */
struct Input {
    GtkWidget *name;
    GtkWidget *robotsNumber;
    GtkWidget *gameType;
    GtkWidget *mainWindow;
    int noOfGames;
};

struct GameGUI* gui_changeGameGUI(const struct GameGUI* gameGUI,
                                  const int onlyReturn);

void gui_setGameGUI(const struct GameGUI* gameGUI);

struct GameGUI* gui_getGameGUI();

GtkWidget* gui_changeWindowScore(const GtkWidget *window, const int onlyReturn);

void gui_setWindowScore(const GtkWidget *window);

GtkWidget* gui_getWindowScore();

/**
 * @brief Function initializes the window and add fixed in window.
 *
 * @param window Pointer to pointer to GtkWidget. Function will initializes
 *               this pointer with GtkWindow.
 * @param fixed Pointer to pointer to GtkWidget. Function will initializes
 *              this pointer with GtkFixed.
 * @param title Pointer to the string which will be setting as the name of the
 *              window.
 * @param width The width of the window.
 * @param height The height of the window.
 *
 *return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_init(GtkWidget **window, GtkWidget **fixed, char *title,
             int width, int height);

/**
 * @brief Function adds a label and a spin button to be able the player to
 *        enter the bots number.
 *
 * @param window Pointer to the GtkWindow in which to be added the label and
 *               the spin button.
 * @param fixed Pointer to the GtkFixed which is added in window.
 * @param label Pointer to pointer to GtkWidget. Function will creates a label
 *              to that address.
 * @param spinNumber Pointer to pointer to GtkWidget. Function will creates a
 *                   spin button to that address.
 * @param number Pointer to pointer to GtkAdjustment. Function will creates a
 *               GtkAdjustment to that address. Function has need this
 *               parameter to create a spin button.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_noOfBots(GtkWidget *window, GtkWidget *fixed, GtkWidget **label,
                 GtkWidget **spinNumber, GtkAdjustment **number);

/**
 * @brief Function adds a label and a entry to be able the player to enter his
 *        name.
 *
 * @param window Pointer to the GtkWindow in which to be added the label and
 *               the entry.
 * @param fixed Pointer to the GtkFixed which is added in window.
 * @param label Pointer to pointer to GtkWidget. Function will creates a label
 *              to that address.
 * @param name Pointer to pointer to GtkEntry. Function will creates a entry
 *             to that address.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_playerName(GtkWidget *window, GtkWidget *fixed,
                   GtkWidget **label, GtkWidget **name);

/**
 * @brief Function adds a label, a vbox and two radio buttons to be able the
 *        player to enter the game type.
 *
 * @param window Pointer to the GtkWindow in which to be added the label, the
 *               vbox and the radio buttons.
 * @param fixed Pointer to the GtkFixed which is added in window.
 * @param label Pointer to pointer to GtkWidget. Function will creates a label
 *              to that address.
 * @param radio1 Pointer to pointer to GtkWidget. Function will creates a radio
 *               button to that address.
 * @param radio8 Pointer to pointer to GtkWidget. Function will creates a radio
 *               button to that address.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_gameType(GtkWidget *window, GtkWidget *fixed, GtkWidget **label,
                 GtkWidget **radio1, GtkWidget **radio8);
/**
 * @brief Function set background for a GtkFixed.
 *
 * @param fixed Pointer to the GtkFixed for which is set the background.
 * @param pathPicture The path to the image which to be set such as background.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_setBackground(GtkWidget *fixed, char *pathPicture);

int gui_closeWhistGame(GtkWidget *window, gpointer unused);

/**
 * @brief Function displays the score when is clicked the ShowScore button.
 *
 * @param button Pointer to the ShowScore button.
 * @param game Pointer to the game from which is displayed the score.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_showScore(GtkWidget *button, struct Game *game);

/**
 * @brief Function create the button which will show the score.
 *
 * @param fixed Pointer to the GtkFixed in which is added the button.
 * @param showButton The address to which is created the button.
 * @param game Pointer to the game from which will be displaying the score.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_createButtonShowScore(GtkWidget *fixed, GtkWidget **showButton,
                              struct Game *game);

/**
 * @brief Function get the name of a card.
 *
 * @param card Pointer to the card for which is got the name.
 * @param name Pointer to first position whence to be saved the card's name.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_getPictureName(struct Card *card, char *name);

/**
 * @brief Function initializes the trump on table.
 *
 * @param fixed Pointer to the fixed where will be displaying the trump.
 * @param image Pointer to pointer to image which will be displaying as trump.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_initTrump(GtkWidget *fixed, GtkWidget **image);

/**
 * @brief Function hides the trump.
 *
 * @param image Pointer to the image which will be hiding.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_hideTrump(GtkWidget *image);

/**
 * @brief Function displays the trump.
 *
 * @param trump Pointer to the card which is trump.
 * @param image Pointer to the image which will be displaying as trump.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_showTrump(struct Card *trump, GtkWidget *image);

/**
 * @brief Function frees a pointer to PlayerCards and makes him NULL.
 *
 * @param playerCards Pointer to pointer to the PlayerCards which will be
 *                    removing.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_deletePlayerCards(struct PlayerCards **playerCards);

/**
 * @brief Function creates and initializes a PlayerCards structure.
 *
 * @param fixed Pointer to the fixed in which will be displaying player cards.
 *
 * @return Pointer to the PlayerCards structure on success, NULL on failure.
 */
struct PlayerCards *gui_initializePlayerCards(GtkWidget *fixed);

/**
 * @brief Function hides the player cards.
 *
 * @param playerCards Pointer to the PlayerCards structure which be hiding.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_hidePlayerCards(struct PlayerCards *playerCards);

/**
 * @brief Function displays the player cards.
 *
 * @param playerCards Pointer to the PlayerCards structure which be displaying.
 * @param player Pointer to the player for which are displayed the cards.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_showPlayerCards(struct PlayerCards *playerCards, struct Player *player);

/**
 * @brief Function initializes and displays a dialog if the user introduced a
 *        wrong name.
 *
 * @param window Pointer to the window which will be the parent of the dialog.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_initAndShowDialogIncorrectName(GtkWidget *window);

/**
 * @brief Function initializes and displays a dialog if the user opened too
 *        many games.
 *
 * @param window Pointer to the window which will be the parent of the dialog.
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_initAndShowDialogMaxGames(GtkWidget *window);

/**
 * @brief Function releases the memory when is closed the table of game.
 *
 * @param windowTable Pointer to the window of game.
 * @param
 *
 * @return FUNCTION_NO_ERROR or 0 on success, other value on failure.
 */
int gui_closeWhistGame(GtkWidget *windowTable, gpointer unused);

/**
 * @brief Function gets the card id.
 *
 * @param x The value of the coordinate X of mouse.
 * @param y The value of the coordinate Y of mouse.
 *
 * @return A value between 0 and MAX_CARDS - 1 or -1 if to the coordinates
 *         received as parameters not exist a card.
 */
int gui_getCardId(int x, int y);

/**
 * @brief Function is called when the mouse is clicked.
 *
 * @param window Pointer to the window in which was clicked the mouse.
 * @param event Pointer to the event of the window. This parameter is used to
 *              get the coordinates of mouse.
 * @param gameGUI Pointer to the GameGUI.
 */
int gui_clickMouse(GtkWidget *window, GdkEvent *event, struct GameGUI *gameGUI);

void gui_setGameGUI(const struct GameGUI* gameGUI);

struct GameGUI* gui_getGameGUI();

struct Select *gui_createSelect(GtkWidget *fixed, struct Player *player,
                                struct Game *game);

int gui_selectedCard(struct Select *select);

int gui_moveMouse(GtkWidget *window, GdkEvent *event, struct Select *select);

struct PlayersGUI *gui_createPlayersGUI();

int gui_showPlayers(struct Game *game, GtkWidget *fixed,
                    struct PlayersGUI *playersGUI);

int gui_showInformationsPlayers(struct PlayersGUI *playersGUI,
                                struct Game *game);

struct CardsFromTable *gui_createCardsFromTable();

int gui_deleteCardsFromTable(struct CardsFromTable **cardsFromTable);

int gui_initCardsFromTable(struct CardsFromTable *cardsFromTable,
                           GtkWidget *fixed);

int gui_hideCardsFromTable(struct CardsFromTable *cardsFromTable);

int gui_showCardsOnTable(struct CardsFromTable *cardsFromTable,
                         struct Game *game);

int gui_deletePlayersGUI(struct PlayersGUI **playersGUI);

int gui_deleteSelect(struct Select **select);

int gui_deleteInput(struct Input **input);

int gui_initRoundTypeLabel(GtkWidget **roundTypeLabel, GtkWidget *fixed);

int gui_initNoOfBidsLabel(GtkWidget **noOfBidsLabel, GtkWidget *fixed);

int gui_setRoundType(GtkWidget *roundTypeLabel, struct Round *round);

int gui_setNoOfBids(GtkWidget *noOfBidsLabel, struct Round *round);

struct BidGUI *gui_createBidGUI();

int gui_deleteBidGUI(struct BidGUI **bidGUI);

int gui_initBidGUI(struct BidGUI *bidGUI, GtkWidget *fixed);

int gui_showBidGUI(struct BidGUI *bidGUI, struct Round *round,
                   struct Player *player);

int gui_getBidValue(int x, int y);

int gui_selectedBid(struct Select *select);

int gui_clickMouseOnCard(struct GameGUI *gameGUI, int x, int y);

int gui_clickMouseOnBid(struct GameGUI *gameGUI, int x, int y);

int gui_hideBidGUI(struct BidGUI *bidGUI);

int gui_clickStart(GtkWidget *button, struct GameGUI *gameGUI);

int gui_createButtonStart(struct GameGUI *gameGUI);

struct GameGUI *gui_createGameGUI();

int gui_deleteGameGUI(struct GameGUI **gameGUI);

int gui_hideRewardImages(struct PlayersGUI* playersGUI);

int gui_startRound(struct GameGUI *gameGUI);

int gui_startHand(struct GameGUI *gameGUI, int winnerPlayerId);

gboolean gui_endHand(gpointer data);

gboolean gui_botChooseBid(gpointer data);

gboolean gui_chooseBidForBots(struct GameGUI *gameGUI, int leftLimit,
                              int rightLimit);

gboolean gui_botChooseCard(gpointer data);

gboolean gui_chooseCardForBots(struct GameGUI *gameGUI, int leftLimit,
                               int rightLimit);

int gui_showPlayerTurn(struct GameGUI *gameGUI, int playerId);

struct LimitTimeGUI *gui_createLimitTimeGUI(GtkWidget *fixed, int x, int y);

int gui_deleteLimitTimeGUI(struct LimitTimeGUI **limitTimeGUI);

int gui_showLimitTimeGUI(struct LimitTimeGUI *limitTimeGUI);

int gui_hideLimitTimeGUI(struct LimitTimeGUI *limitTimeGUI);

int gui_initLimitTimeGUI(struct LimitTimeGUI *limitTimeGUI, char *pathImage);

int gui_hideLastImageFromLimitTimeGUI(struct LimitTimeGUI *limitTimeGUI);

int gui_startTime(struct GameGUI *gameGUI);

gboolean gui_timer(gpointer data);

GtkWidget *gui_imageNewFromFile(const char *name);

void gui_imageSetFromFile(GtkWidget* image, const char* name);

#endif

