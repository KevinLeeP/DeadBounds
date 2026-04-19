#ifndef SOUND_SD_H
#define SOUND_SD_H

#include <stdint.h>

void SoundSD_Init(void);
int SoundSD_Play(const char *filename);
void SoundSD_Task(void);
void SoundSD_Stop(void);

#endif