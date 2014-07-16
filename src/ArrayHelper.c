//Some helper functions for array manipulation.


#include <stdint.h>
#include <string.h>

#include "Config.h"
#include "ArrayHelper.h"


void clearArray(int8_t array[][yres], int size) {
    memset(array,0,size);
}