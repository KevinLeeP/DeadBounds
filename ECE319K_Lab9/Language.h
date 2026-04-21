/**
 * @file      Language.h
 * @brief     English and Spanish text
 * @author    Kevin Pfeffer and Charlie Nguyen

  ******************************************************************************/
#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include <stdint.h>

struct Language{
    char *phrase1;
    char *phrase2;
    uint8_t xOffset;
    uint16_t *deathScreen;
    uint8_t deathScreenWidth;
};
typedef struct Language Language_t;

extern Language_t myLanguages[];

extern uint8_t currentLanguage;

void Language_Init();
void Language_Switch(void);


#endif // __LANGUAGE_H_
