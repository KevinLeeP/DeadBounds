// images.h
// contains image buffers for simple space invaders
// Jonathan Valvano, March 5, 2018
// Capture image dimensions from BMP files

#ifndef __images_h_
#define __images_h_
#include <stdint.h>

#define SHOTGUN_NORMAL_WIDTH      60
#define SHOTGUN_NORMAL_HEIGHT     40

#define CROSSHAIR_WIDTH           6
#define CROSSHAIR_HEIGHT          6

#define SHOTGUN_SHOOT1_WIDTH      60
#define SHOTGUN_SHOOT1_HEIGHT     47

#define SHOTGUN_SHOOT2_WIDTH      60
#define SHOTGUN_SHOOT2_HEIGHT     51

#define SHOTGUN_SHOOT3_WIDTH      60
#define SHOTGUN_SHOOT3_HEIGHT     100

#define SHOTGUN_SHOOT4_WIDTH      60
#define SHOTGUN_SHOOT4_HEIGHT     86

#define SHOTGUN_SHOOT5_WIDTH      60
#define SHOTGUN_SHOOT5_HEIGHT     90

#define ZOMBIE1_WIDTH             64
#define ZOMBIE1_HEIGHT            118

#define ZOMBIE2_WIDTH             64
#define ZOMBIE2_HEIGHT            126

#define ZOMBIE_ATTACK_WIDTH       64
#define ZOMBIE_ATTACK_HEIGHT      111

#define RELOAD1_WIDTH             80
#define RELOAD1_HEIGHT            52

#define RELOAD2_WIDTH             80
#define RELOAD2_HEIGHT            57

#define RELOAD3_WIDTH             80
#define RELOAD3_HEIGHT            66

#define YOU_DIED_ENGLISH_WIDTH    70
#define YOU_DIED_ENGLISH_HEIGHT   19

#define YOU_DIED_SPANISH_WIDTH    90
#define YOU_DIED_SPANISH_HEIGHT   19

extern const unsigned short crosshair[];

extern const unsigned short shotgunNormal[];

extern const unsigned short shotgunShoot2[];

extern const unsigned short shotgunShoot3[];

extern const unsigned short shotgunShoot4[];

extern const unsigned short zombie1[];

//extern const unsigned short zombie2[];

extern const unsigned short zombieattack[];

extern const unsigned short reload1[];

extern const unsigned short reload2[];

extern const unsigned short reload3[];

extern unsigned short youDiedEnglish[];

extern unsigned short youDiedSpanish[];




#endif /* __images_h */