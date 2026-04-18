/**
 * @file      Animations.h
 * @brief     FSM for all animations
 * @author    Kevin Pfeffer and Charlie Nguyen

  ******************************************************************************/
#ifndef __ANIMATIONS_H__
#define __ANIMATIONS_H__

struct animationFrame{
    const uint16_t *image;
    uint8_t x;
    uint8_t y;
    uint8_t w;
    uint8_t h;
};
typedef struct animationFrame animationFrame_t;

#endif // __ANIMATIONS_H_
