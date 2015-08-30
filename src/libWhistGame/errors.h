/**
 * @file errors.h
 * @brief Contains definitions of the symbolic constants that represents error
 *        codes, as well as the declarations of the functions that belongs to
 *        the error module.
 */

#ifndef ERRORS_H
#define ERRORS_H

/**
 * @enum ERROR_CODES
 * 
 * @brief Specifies the error codes used to specify the wrong behaviour of the
 *        functions used in this game.
 */
enum ERROR_CODES {
    FUNCTION_NO_ERROR    =   0,
    CARD_NULL            = - 1,
    DECK_NULL            = - 2,
    PLAYER_NULL          = - 3,
    DUPLICATE_POINTER    = - 4,
    FULL                 = - 5,
    HAND_NULL            = - 6,
    NOT_FOUND            = - 7,
    POINTER_NULL         = - 8,
    ROUND_NULL           = - 9,
    ILLEGAL_VALUE        = -10,
    INSUFFICIENT_PLAYERS = -11,
    INSUFFICIENT_CARDS   = -12,
    GAME_NULL            = -13,
    DUPLICATE_NAME       = -14,
    INCORRECT_NAME       = -15,
    ILLEGAL_BID          = -16,
    GAME_OVER            = -17,
    ROUND_OVER           = -18
};

#endif

