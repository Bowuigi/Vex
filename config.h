#ifndef VEX_CONFIG_H
#define VEX_CONFIG_H

#include "keyfuncs.c"
#define LEN(arr) sizeof(arr)-sizeof(arr[0])

/* Specify the command used to start your editor */
const char editorcmd[]="nvim";

typedef struct {
    int keycode;
    void (*trigger)(void);
} key;

const key keys[] = {
    {.keycode = KEY_RIGHT, .trigger=open},
    {.keycode = 'l', .trigger=open},
    {.keycode = KEY_LEFT, .trigger=back},
    {.keycode = 'h', .trigger=back},
};

#define KEY_AMOUNT LEN(keys)

#endif /* VEX_CONFIG_H */
