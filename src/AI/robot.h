/** 
 * @file robot.h
 * @brief The function used at the logic of the robot (AI).
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <libWhistGame.h>

/**
 * @brief Function determines the number of bids on which him will bid the robot.
 *
 * @param player Pointer to the player which is robot.
 * @param round  Pointer to the round in which is the robot.
 *
 * @return A value between 0 and roundType on success, a negative value on
 *         failure.
 */
int robot_getBid(const struct Player* player, const struct Round* round);

/**
 * @brief Function determines the position of the card on which the robot her 
 *        will put down.
 *
 * @param player Pointer to the player which is robot.
 * @param round  Pointer to the round in which is the robot.
 *
 * @return A value between 0 and roundType on success, a negative value on
 *         failure.
 */
int robot_getCardId(const struct Player* player, const struct Round* round);

#endif

