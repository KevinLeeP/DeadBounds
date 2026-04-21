#include "Language.h"
#include "../images/images.h"
#include <stdint.h>
#include <stdlib.h>

#define English 0
#define Spanish 1

Language_t myLanguages[2] = {
    {"Press any button", "to Restart", 4, youDiedEnglish, 70},
    {"Presione para ", "Reiniciar", 4, youDiedSpanish, 90}
};

uint8_t currentLanguage;

void Language_Init(void){
    currentLanguage = 0;
}

void Language_Switch(void){
    if(currentLanguage == English){
        currentLanguage = Spanish;
    }
    else{
        currentLanguage = English;
    }
}

