/**
 * @file      Entities.h
 * @brief     Structs and attributes of the player and zombie sprites
 * @author    Kevin Pfeffer and Charlie Nguyen

  ******************************************************************************/
#ifndef __Entities_H__
#define __Entities_H__

// initialize the player with 100 health and 5 bullets
void Player_Init(void);

// player takes 10 damage
void Player_Damaged(void);

// player shoots shotgun; lose 1 bullet
void Player_Shoot(void);

// player reloads fully back to 5 bullets
void Player_Reload(void);

#endif